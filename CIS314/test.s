	.file	"test.c"
	.text
	.globl	absdiff
	.type	absdiff, @function
absdiff:
.LFB41:
	.cfi_startproc
	movl	%esi, %eax
	subl	%edi, %eax
	ret
	.cfi_endproc
.LFE41:
	.size	absdiff, .-absdiff
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB42:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$5, %esi
	movl	$7, %edi
	call	absdiff
	movl	%eax, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE42:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
