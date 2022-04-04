	.file	"4-2.c"
	.text
	.globl	sum
	.type	sum, @function
sum:
.LFB23:
	.cfi_startproc
	movl	$0, %eax
.L2:
	addl	%edi, %eax
	addl	$1, %edi
	cmpl	%esi, %edi
	jle	.L2
	rep ret
	.cfi_endproc
.LFE23:
	.size	sum, .-sum
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%ld\n"
	.text
	.globl	main
	.type	main, @function
main:
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
	movl	$6, %esi
	movl	$1, %edi
	call	sum
	movslq	%eax, %r12
	movl	$5, %esi
	movl	$3, %edi
	call	sum
	movslq	%eax, %rbp
	movl	$3, %esi
	movl	$5, %edi
	call	sum
	movslq	%eax, %rbx
	movq	%r12, %rdx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movq	%rbp, %rdx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movq	%rbx, %rdx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
