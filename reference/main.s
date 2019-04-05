	.file	"main.cpp"
	.text
	.globl	_Z4funcv
	.type	_Z4funcv, @function
_Z4funcv:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_Z4funcv, .-_Z4funcv
	.section	.ctors,"aw",@progbits
	.align 4
	.long	_Z4funcv
	.text
	.globl	_Z5func2v
	.type	_Z5func2v, @function
_Z5func2v:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_Z5func2v, .-_Z5func2v
	.section	.ctors
	.align 4
	.long	_Z5func2v
	.section	.text._ZN2c24funcEv,"axG",@progbits,_ZN2c24funcEv,comdat
	.align 2
	.weak	_ZN2c24funcEv
	.type	_ZN2c24funcEv, @function
_ZN2c24funcEv:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$2, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	_ZN2c24funcEv, .-_ZN2c24funcEv
	.section	.text._ZN2c25func2Ev,"axG",@progbits,_ZN2c25func2Ev,comdat
	.align 2
	.weak	_ZN2c25func2Ev
	.type	_ZN2c25func2Ev, @function
_ZN2c25func2Ev:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$2, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	_ZN2c25func2Ev, .-_ZN2c25func2Ev
	.section	.text._ZN2c34funcEv,"axG",@progbits,_ZN2c34funcEv,comdat
	.align 2
	.weak	_ZN2c34funcEv
	.type	_ZN2c34funcEv, @function
_ZN2c34funcEv:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$3, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	_ZN2c34funcEv, .-_ZN2c34funcEv
	.section	.text._ZN2c35func2Ev,"axG",@progbits,_ZN2c35func2Ev,comdat
	.align 2
	.weak	_ZN2c35func2Ev
	.type	_ZN2c35func2Ev, @function
_ZN2c35func2Ev:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$3, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	_ZN2c35func2Ev, .-_ZN2c35func2Ev
	.globl	c_2
	.section	.data.rel.local,"aw",@progbits
	.align 4
	.type	c_2, @object
	.size	c_2, 4
c_2:
	.long	_ZTV2c2+8
	.globl	c_3
	.align 4
	.type	c_3, @object
	.size	c_3, 4
c_3:
	.long	_ZTV2c3+8
	.text
	.globl	main
	.type	main, @function
main:
.LFB15:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	subl	$16, %esp
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	movl	$0, -20(%ebp)
	leal	c_2@GOTOFF(%ebx), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	-16(%ebp)
	call	*%eax
	addl	$16, %esp
	movl	%eax, -20(%ebp)
	leal	c_3@GOTOFF(%ebx), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	-16(%ebp)
	call	*%eax
	addl	$16, %esp
	movl	%eax, -20(%ebp)
	leal	c_2@GOTOFF(%ebx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	-12(%ebp)
	call	*%eax
	addl	$16, %esp
	movl	%eax, -20(%ebp)
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	-12(%ebp)
	call	*%eax
	addl	$16, %esp
	movl	%eax, -20(%ebp)
	leal	c_3@GOTOFF(%ebx), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	-12(%ebp)
	call	*%eax
	addl	$16, %esp
	movl	%eax, -20(%ebp)
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	-12(%ebp)
	call	*%eax
	addl	$16, %esp
	movl	%eax, -20(%ebp)
	movl	$1, %eax
	leal	-8(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE15:
	.size	main, .-main
	.weak	_ZTV2c3
	.section	.data.rel.ro.local._ZTV2c3,"awG",@progbits,_ZTV2c3,comdat
	.align 4
	.type	_ZTV2c3, @object
	.size	_ZTV2c3, 16
_ZTV2c3:
	.long	0
	.long	_ZTI2c3
	.long	_ZN2c34funcEv
	.long	_ZN2c35func2Ev
	.weak	_ZTV2c2
	.section	.data.rel.ro.local._ZTV2c2,"awG",@progbits,_ZTV2c2,comdat
	.align 4
	.type	_ZTV2c2, @object
	.size	_ZTV2c2, 16
_ZTV2c2:
	.long	0
	.long	_ZTI2c2
	.long	_ZN2c24funcEv
	.long	_ZN2c25func2Ev
	.weak	_ZTI2c3
	.section	.data.rel.ro._ZTI2c3,"awG",@progbits,_ZTI2c3,comdat
	.align 4
	.type	_ZTI2c3, @object
	.size	_ZTI2c3, 12
_ZTI2c3:
	.long	_ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	_ZTS2c3
	.long	_ZTI2c2
	.weak	_ZTS2c3
	.section	.rodata._ZTS2c3,"aG",@progbits,_ZTS2c3,comdat
	.align 4
	.type	_ZTS2c3, @object
	.size	_ZTS2c3, 4
_ZTS2c3:
	.string	"2c3"
	.weak	_ZTI2c2
	.section	.data.rel.ro._ZTI2c2,"awG",@progbits,_ZTI2c2,comdat
	.align 4
	.type	_ZTI2c2, @object
	.size	_ZTI2c2, 12
_ZTI2c2:
	.long	_ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	_ZTS2c2
	.long	_ZTI2c1
	.weak	_ZTS2c2
	.section	.rodata._ZTS2c2,"aG",@progbits,_ZTS2c2,comdat
	.align 4
	.type	_ZTS2c2, @object
	.size	_ZTS2c2, 4
_ZTS2c2:
	.string	"2c2"
	.weak	_ZTI2c1
	.section	.data.rel.ro._ZTI2c1,"awG",@progbits,_ZTI2c1,comdat
	.align 4
	.type	_ZTI2c1, @object
	.size	_ZTI2c1, 8
_ZTI2c1:
	.long	_ZTVN10__cxxabiv117__class_type_infoE+8
	.long	_ZTS2c1
	.weak	_ZTS2c1
	.section	.rodata._ZTS2c1,"aG",@progbits,_ZTS2c1,comdat
	.align 4
	.type	_ZTS2c1, @object
	.size	_ZTS2c1, 4
_ZTS2c1:
	.string	"2c1"
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB16:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE16:
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB17:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE17:
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
