	.text
	.file	"test"
	.globl	calc                    # -- Begin function calc
	.p2align	4, 0x90
	.type	calc,@function
calc:                                   # @calc
	.cfi_startproc
# %bb.0:                                # %entry
	movl	%edi, %eax
	imull	%esi, %eax
	retq
.Lfunc_end0:
	.size	calc, .Lfunc_end0-calc
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	callq	getchar
	movl	%eax, %ebx
	addl	$-48, %ebx
	callq	getchar
	addl	$-48, %eax
	xorl	%ecx, %ecx
	movl	$1, %edi
	cmpl	%eax, %ecx
	jae	.LBB1_3
	.p2align	4, 0x90
.LBB1_2:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	incl	%ecx
	imull	%ebx, %edi
	cmpl	%eax, %ecx
	jb	.LBB1_2
.LBB1_3:                                # %whilecont
	addl	$48, %edi
	callq	putchar
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
