	.file	"selectionsort.c"
	.text
	.globl	swap
	.type	swap, @function
swap:
.LFB23:
	.cfi_startproc
	movl	(%rdi), %eax
	movl	(%rsi), %edx
	movl	%edx, (%rdi)
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE23:
	.size	swap, .-swap
	.globl	selectionSort
	.type	selectionSort, @function
selectionSort:
.LFB24:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movl	%esi, %ebp
	movl	$0, %edi
	jmp	.L3
.L5:
	addl	$1, %eax
.L4:
	cmpl	%ebp, %eax
	jge	.L10
	movslq	%eax, %rdx
	movslq	%ecx, %rsi
	movl	(%rbx,%rsi,4), %esi
	cmpl	%esi, (%rbx,%rdx,4)
	jge	.L5
	movl	%eax, %ecx
	jmp	.L5
.L10:
	movslq	%edi, %rdi
	movslq	%ecx, %rcx
	leaq	(%rbx,%rdi,4), %rsi
	leaq	(%rbx,%rcx,4), %rdi
	call	swap
	movl	%r12d, %edi
.L3:
	leal	-1(%rbp), %eax
	cmpl	%edi, %eax
	jle	.L11
	leal	1(%rdi), %r12d
	movl	%edi, %ecx
	movl	%r12d, %eax
	jmp	.L4
.L11:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	selectionSort, .-selectionSort
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d "
	.text
	.globl	printArray
	.type	printArray, @function
printArray:
.LFB25:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %r12
	movl	%esi, %ebp
	movl	$0, %ebx
	jmp	.L13
.L14:
	movslq	%ebx, %rax
	movl	(%r12,%rax,4), %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	addl	$1, %ebx
.L13:
	cmpl	%ebp, %ebx
	jl	.L14
	movl	$10, %edi
	call	putchar@PLT
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	printArray, .-printArray
	.section	.rodata.str1.1
.LC1:
	.string	"Sorted array: "
	.text
	.globl	main
	.type	main, @function
main:
.LFB26:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movl	$64, (%rsp)
	movl	$25, 4(%rsp)
	movl	$12, 8(%rsp)
	movl	$22, 12(%rsp)
	movl	$11, 16(%rsp)
	movq	%rsp, %rbx
	movl	$5, %esi
	movq	%rbx, %rdi
	call	selectionSort
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	movl	$5, %esi
	movq	%rbx, %rdi
	call	printArray
	movq	24(%rsp), %rdx
	xorq	%fs:40, %rdx
	jne	.L19
	movl	$0, %eax
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L19:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE26:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
