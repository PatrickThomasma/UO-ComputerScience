
"""
Duck Machine model DM2019W CPU
"""

from instr_format import Instruction, OpCode, CondFlag, decode
from typing import Tuple
import logging
from memory import Memory
from register import Register, ZeroRegister
from mvc import MVCEvent, MVCListenable
logging.basicConfig()
log = logging.getLogger(__name__)
log.setLevel(logging.INFO)

class ALU(object):
    """The arithmetic logic unit (also called a "functional unit"
    in a modern CPU) executes a selected function but does not
    otherwise manage CPU state. A modern CPU core may have several
    ALUs to boost performance by performing multiple operatons
    in parallel, but the Duck Machine has just one ALU in one core.
    """
    # The ALU chooses one operation to apply based on a provided
    # operation code.  These are just simple functions of two arguments;
    # in hardware we would use a multiplexer circuit to connect the
    # inputs and output to the selected circuitry for each operation.
    ALU_OPS = {
        OpCode.ADD: lambda x, y: x + y,
        OpCode.SUB: lambda x, y: x - y,
        OpCode.DIV: lambda x , y: x // y,
        OpCode.MUL: lambda x , y: x * y,
        #
        # For memory access operations load, store, the ALU
        # performs the address calculation
        OpCode.LOAD: lambda x, y: x + y,
        OpCode.STORE: lambda x, y: x + y,
        # Some operations perform no operation
        OpCode.HALT: lambda x, y: 0
    }

    def exec(self, op: OpCode, in1: int, in2: int) -> Tuple[int, CondFlag]:
        if op == OpCode.ADD:
            res = in1 + in2
            if res > 0:
                return res, CondFlag(4)
            if res == 0:
                return res, CondFlag(2)
            if res < 0:
                return res, CondFlag(1)
        if op == OpCode.SUB:
            res = in1 - in2
            if res > 0:
                return res, CondFlag(4)
            if res == 0:
                return res, CondFlag(2)
            if res < 0:
                return res, CondFlag(1)
        if op == OpCode.DIV:
            if in2 == 0:
                res = 0
                return res, CondFlag(8)
            res = in1 // in2
            if res > 0:
                return res, CondFlag(4)
            elif res == 0:
                return res, CondFlag(2)
            elif res < 0:
                return res, CondFlag(1)
        if op == OpCode.MUL:
            res = in1 * in2
            if res > 0:
                return res, CondFlag(4)
            if res == 0:
                return res, CondFlag(2)
            if res < 0:
                return res, CondFlag(1)
        if op == OpCode.LOAD:
            res = in1 + in2
            if res > 0:
                return res, CondFlag(4)
            if res == 0:
                return res, CondFlag(2)
            if res < 0:
                return res, CondFlag(1)
        if op == OpCode.STORE:
            res = in1 + in2
            if res > 0:
                return res, CondFlag(4)
            if res == 0:
                return res, CondFlag(2)
            if res < 0:
                return res, CondFlag(1)
        if op == OpCode.HALT:
            res = 0
            return res, CondFlag(2)
class CPUStep(MVCEvent):
    """CPU is beginning step with PC at a given address"""
    def __init__(self, subject: "CPU", pc_addr: int,
                 instr_word: int, instr: Instruction)-> None:
        self.subject = subject
        self.pc_addr = pc_addr
        self.instr_word = instr_word
        self.instr = instr
class CPU(MVCListenable):
    """Duck Machine central processing unit (CPU)
    has 16 registers (including r0 that always holds zero
    and r15 that holds the program counter), a few
    flag registers (condition codes, halted state),
    and some logic for sequencing execution.  The CPU
    does not contain the main memory but has a bus connecting
    it to a separate memory.
    """
    def __init__(self, memory: Memory):
        super().__init__()
        self.memory = memory  # Not part of CPU; what we really have is a connection

        self.registers = [ZeroRegister(), Register(), Register(), Register(),
                      Register(), Register(), Register(), Register(),
                      Register(), Register(), Register(), Register(),
                      Register(), Register(), Register(), Register()]
        self.condition = CondFlag.ALWAYS
        self.halted = False
        self.alu = ALU()
        self.pc = self.registers[15]

    def step(self):
        """ Runs through a Fetch/Decode/Execute cycle """
        # Fetch
        instr_addr = self.pc.get()
        instr_word = self.memory.get(instr_addr)
        # Decode
        instr = decode(instr_word)
        self.notify_all(CPUStep(self, instr_addr, instr_word, instr))
        # Execute:
        if instr.cond & self.condition:
            left_oper = self.registers[instr.reg_src1].get()
            right_oper = instr.offset + self.registers[instr.reg_src2].get()
            self.pc.put(self.pc.get() + 1)
            result, self.condition = self.alu.exec(instr.op, left_oper, right_oper)
            if instr.op == OpCode.STORE:  # If the operation was STORE
                self.memory.put(result, self.registers[instr.reg_target].get())
            elif instr.op == OpCode.LOAD:  # If operation was LOAD/GET
                self.registers[instr.reg_target].put(self.memory.get(result))
            elif instr.op == OpCode.HALT:  # If operation was HALT
                self.halted = True
            else:  # If operation was ADD/SUB/MUL/DIV
                self.registers[instr.reg_target].put(result)
        else:
            self.pc.put(self.pc.get() + 1)

    def run(self, from_addr=0,  single_step=False) -> None:
        self.halted = False
        self.pc.put(from_addr)
        step_count = 0
        while not self.halted:
            if single_step:
                input("Step {}; press enter".format(step_count))
            self.step()
            step_count += 1

