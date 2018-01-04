	.file	"something.cpp"
	.section	.text._ZStanSt13_Ios_FmtflagsS_,"axG",@progbits,_ZStanSt13_Ios_FmtflagsS_,comdat
	.weak	_ZStanSt13_Ios_FmtflagsS_
	.type	_ZStanSt13_Ios_FmtflagsS_, @function
_ZStanSt13_Ios_FmtflagsS_:
.LFB636:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	andl	12(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE636:
	.size	_ZStanSt13_Ios_FmtflagsS_, .-_ZStanSt13_Ios_FmtflagsS_
	.section	.text._ZStorSt13_Ios_FmtflagsS_,"axG",@progbits,_ZStorSt13_Ios_FmtflagsS_,comdat
	.weak	_ZStorSt13_Ios_FmtflagsS_
	.type	_ZStorSt13_Ios_FmtflagsS_, @function
_ZStorSt13_Ios_FmtflagsS_:
.LFB637:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	orl	12(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE637:
	.size	_ZStorSt13_Ios_FmtflagsS_, .-_ZStorSt13_Ios_FmtflagsS_
	.section	.text._ZStcoSt13_Ios_Fmtflags,"axG",@progbits,_ZStcoSt13_Ios_Fmtflags,comdat
	.weak	_ZStcoSt13_Ios_Fmtflags
	.type	_ZStcoSt13_Ios_Fmtflags, @function
_ZStcoSt13_Ios_Fmtflags:
.LFB639:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	notl	%eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE639:
	.size	_ZStcoSt13_Ios_Fmtflags, .-_ZStcoSt13_Ios_Fmtflags
	.section	.text._ZStoRRSt13_Ios_FmtflagsS_,"axG",@progbits,_ZStoRRSt13_Ios_FmtflagsS_,comdat
	.weak	_ZStoRRSt13_Ios_FmtflagsS_
	.type	_ZStoRRSt13_Ios_FmtflagsS_, @function
_ZStoRRSt13_Ios_FmtflagsS_:
.LFB640:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	subl	$8, %esp
	pushl	12(%ebp)
	pushl	%eax
	call	_ZStorSt13_Ios_FmtflagsS_
	addl	$16, %esp
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE640:
	.size	_ZStoRRSt13_Ios_FmtflagsS_, .-_ZStoRRSt13_Ios_FmtflagsS_
	.section	.text._ZStaNRSt13_Ios_FmtflagsS_,"axG",@progbits,_ZStaNRSt13_Ios_FmtflagsS_,comdat
	.weak	_ZStaNRSt13_Ios_FmtflagsS_
	.type	_ZStaNRSt13_Ios_FmtflagsS_, @function
_ZStaNRSt13_Ios_FmtflagsS_:
.LFB641:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	subl	$8, %esp
	pushl	12(%ebp)
	pushl	%eax
	call	_ZStanSt13_Ios_FmtflagsS_
	addl	$16, %esp
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE641:
	.size	_ZStaNRSt13_Ios_FmtflagsS_, .-_ZStaNRSt13_Ios_FmtflagsS_
	.section	.text._ZStorSt13_Ios_OpenmodeS_,"axG",@progbits,_ZStorSt13_Ios_OpenmodeS_,comdat
	.weak	_ZStorSt13_Ios_OpenmodeS_
	.type	_ZStorSt13_Ios_OpenmodeS_, @function
_ZStorSt13_Ios_OpenmodeS_:
.LFB644:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	orl	12(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE644:
	.size	_ZStorSt13_Ios_OpenmodeS_, .-_ZStorSt13_Ios_OpenmodeS_
	.section	.text._ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_,"axG",@progbits,_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_,comdat
	.align 2
	.weak	_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_
	.type	_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_, @function
_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_:
.LFB671:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -12(%ebp)
	subl	$12, %esp
	pushl	16(%ebp)
	call	_ZStcoSt13_Ios_Fmtflags
	addl	$16, %esp
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	$12, %eax
	subl	$8, %esp
	pushl	%edx
	pushl	%eax
	call	_ZStaNRSt13_Ios_FmtflagsS_
	addl	$16, %esp
	subl	$8, %esp
	pushl	16(%ebp)
	pushl	12(%ebp)
	call	_ZStanSt13_Ios_FmtflagsS_
	addl	$16, %esp
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	$12, %eax
	subl	$8, %esp
	pushl	%edx
	pushl	%eax
	call	_ZStoRRSt13_Ios_FmtflagsS_
	addl	$16, %esp
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE671:
	.size	_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_, .-_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_
	.section	.text._ZSt4leftRSt8ios_base,"axG",@progbits,_ZSt4leftRSt8ios_base,comdat
	.weak	_ZSt4leftRSt8ios_base
	.type	_ZSt4leftRSt8ios_base, @function
_ZSt4leftRSt8ios_base:
.LFB696:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$4, %esp
	pushl	$176
	pushl	$32
	pushl	8(%ebp)
	call	_ZNSt8ios_base4setfESt13_Ios_FmtflagsS0_
	addl	$16, %esp
	movl	8(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE696:
	.size	_ZSt4leftRSt8ios_base, .-_ZSt4leftRSt8ios_base
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZSt4setwi,"axG",@progbits,_ZSt4setwi,comdat
	.weak	_ZSt4setwi
	.type	_ZSt4setwi, @function
_ZSt4setwi:
.LFB1100:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE1100:
	.size	_ZSt4setwi, .-_ZSt4setwi
	.section	.rodata
.LC0:
	.string	"|_______________________|"
	.text
	.globl	_Z7prnLineRSo
	.type	_Z7prnLineRSo, @function
_Z7prnLineRSo:
.LFB1103:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	8(%ebp)
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC0
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1103:
	.size	_Z7prnLineRSo, .-_Z7prnLineRSo
	.section	.rodata
.LC1:
	.string	"file"
.LC2:
	.string	"ID     "
.LC3:
	.string	" | "
.LC4:
	.string	"NAME     "
	.align 4
.LC5:
	.string	"please enter number of persons"
.LC6:
	.string	"please enter name"
.LC7:
	.string	"please enter id"
.LC8:
	.string	"please enter a number"
.LC9:
	.string	"|"
.LC10:
	.string	"| "
	.text
	.globl	main
	.type	main, @function
main:
.LFB1104:
	.cfi_startproc
	.cfi_personality 0,__gxx_personality_v0
	.cfi_lsda 0,.LLSDA1104
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
	subl	$352, %esp
	movl	%ecx, %eax
	movl	4(%eax), %eax
	movl	%eax, -348(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	subl	$12, %esp
	leal	-312(%ebp), %eax
	pushl	%eax
.LEHB0:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1Ev
.LEHE0:
	addl	$16, %esp
	subl	$8, %esp
	pushl	$32
	pushl	$16
	call	_ZStorSt13_Ios_OpenmodeS_
	addl	$16, %esp
	subl	$4, %esp
	pushl	%eax
	pushl	$.LC1
	leal	-288(%ebp), %eax
	pushl	%eax
.LEHB1:
	.cfi_escape 0x2e,0x10
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEEC1EPKcSt13_Ios_Openmode
.LEHE1:
	addl	$16, %esp
	leal	-328(%ebp), %eax
	subl	$8, %esp
	pushl	$10
	pushl	%eax
	call	_ZSt4setwi
	addl	$12, %esp
	leal	-324(%ebp), %eax
	subl	$8, %esp
	pushl	$10
	pushl	%eax
	call	_ZSt4setwi
	addl	$12, %esp
	subl	$8, %esp
	pushl	$_Z7prnLineRSo
	leal	-288(%ebp), %eax
	pushl	%eax
.LEHB2:
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$8, %esp
	pushl	-324(%ebp)
	pushl	%eax
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St5_Setw
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC2
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC3
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	-328(%ebp)
	pushl	%eax
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St5_Setw
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC4
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_Z7prnLineRSo
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC5
	pushl	$_ZSt4cout
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$8, %esp
	leal	-332(%ebp), %eax
	pushl	%eax
	pushl	$_ZSt3cin
	call	_ZNSirsERi
	addl	$16, %esp
.L25:
	movl	-332(%ebp), %eax
	testl	%eax, %eax
	je	.L22
	subl	$8, %esp
	pushl	$.LC6
	pushl	$_ZSt4cout
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$8, %esp
	leal	-312(%ebp), %eax
	pushl	%eax
	pushl	$_ZSt3cin
	call	_ZStrsIcSt11char_traitsIcESaIcEERSt13basic_istreamIT_T0_ES7_RNSt7__cxx1112basic_stringIS4_S5_T1_EE
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC7
	pushl	$_ZSt4cout
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$8, %esp
	leal	-336(%ebp), %eax
	pushl	%eax
	pushl	$_ZSt3cin
	call	_ZNSirsERi
	addl	$16, %esp
.L24:
	subl	$12, %esp
	pushl	$_ZSt3cin+8
	call	_ZNKSt9basic_iosIcSt11char_traitsIcEE4goodEv
	addl	$16, %esp
	xorl	$1, %eax
	testb	%al, %al
	je	.L23
	subl	$8, %esp
	pushl	$0
	pushl	$_ZSt3cin+8
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
	addl	$16, %esp
	subl	$12, %esp
	pushl	$_ZSt3cin
	call	_ZNSi6ignoreEv
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC8
	pushl	$_ZSt4cout
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$8, %esp
	leal	-336(%ebp), %eax
	pushl	%eax
	pushl	$_ZSt3cin
	call	_ZNSirsERi
	addl	$16, %esp
	jmp	.L24
.L23:
	leal	-338(%ebp), %eax
	subl	$8, %esp
	pushl	$45
	pushl	%eax
	call	_ZSt7setfillIcESt8_SetfillIT_ES1_
	addl	$12, %esp
	leal	-320(%ebp), %eax
	subl	$8, %esp
	pushl	$10
	pushl	%eax
	call	_ZSt4setwi
	addl	$12, %esp
	movl	-336(%ebp), %ebx
	leal	-337(%ebp), %eax
	subl	$8, %esp
	pushl	$45
	pushl	%eax
	call	_ZSt7setfillIcESt8_SetfillIT_ES1_
	addl	$12, %esp
	leal	-316(%ebp), %eax
	subl	$8, %esp
	pushl	$10
	pushl	%eax
	call	_ZSt4setwi
	addl	$12, %esp
	subl	$8, %esp
	pushl	$.LC9
	leal	-288(%ebp), %eax
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	-316(%ebp)
	pushl	%eax
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St5_Setw
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4leftRSt8ios_base
	pushl	%eax
	call	_ZNSolsEPFRSt8ios_baseS0_E
	addl	$16, %esp
	movl	%eax, %edx
	subl	$8, %esp
	movzbl	-337(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St8_SetfillIS3_E
	addl	$16, %esp
	subl	$8, %esp
	pushl	%ebx
	pushl	%eax
	call	_ZNSolsEi
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC3
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	-320(%ebp)
	pushl	%eax
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St5_Setw
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4leftRSt8ios_base
	pushl	%eax
	call	_ZNSolsEPFRSt8ios_baseS0_E
	addl	$16, %esp
	movl	%eax, %edx
	subl	$8, %esp
	leal	-312(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKNSt7__cxx1112basic_stringIS4_S5_T1_EE
	addl	$16, %esp
	movl	%eax, %edx
	subl	$8, %esp
	movzbl	-338(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St8_SetfillIS3_E
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC10
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_Z7prnLineRSo
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
.LEHE2:
	addl	$16, %esp
	movl	-332(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -332(%ebp)
	jmp	.L25
.L22:
	movl	$0, %ebx
	subl	$12, %esp
	leal	-288(%ebp), %eax
	pushl	%eax
.LEHB3:
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
.LEHE3:
	addl	$16, %esp
	subl	$12, %esp
	leal	-312(%ebp), %eax
	pushl	%eax
.LEHB4:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
.LEHE4:
	addl	$16, %esp
	movl	%ebx, %eax
	movl	-12(%ebp), %ecx
	xorl	%gs:20, %ecx
	je	.L29
	jmp	.L32
.L31:
	movl	%eax, %ebx
	subl	$12, %esp
	leal	-288(%ebp), %eax
	pushl	%eax
	call	_ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	addl	$16, %esp
	jmp	.L28
.L30:
	movl	%eax, %ebx
.L28:
	subl	$12, %esp
	leal	-312(%ebp), %eax
	pushl	%eax
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
	addl	$16, %esp
	movl	%ebx, %eax
	subl	$12, %esp
	pushl	%eax
.LEHB5:
	call	_Unwind_Resume
.LEHE5:
.L32:
	call	__stack_chk_fail
.L29:
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
.LFE1104:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1104:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1104-.LLSDACSB1104
.LLSDACSB1104:
	.uleb128 .LEHB0-.LFB1104
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1104
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L30-.LFB1104
	.uleb128 0
	.uleb128 .LEHB2-.LFB1104
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L31-.LFB1104
	.uleb128 0
	.uleb128 .LEHB3-.LFB1104
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L30-.LFB1104
	.uleb128 0
	.uleb128 .LEHB4-.LFB1104
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB5-.LFB1104
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
.LLSDACSE1104:
	.text
	.size	main, .-main
	.section	.text._ZSt7setfillIcESt8_SetfillIT_ES1_,"axG",@progbits,_ZSt7setfillIcESt8_SetfillIT_ES1_,comdat
	.weak	_ZSt7setfillIcESt8_SetfillIT_ES1_
	.type	_ZSt7setfillIcESt8_SetfillIT_ES1_, @function
_ZSt7setfillIcESt8_SetfillIT_ES1_:
.LFB1127:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	12(%ebp), %eax
	movb	%al, -4(%ebp)
	movl	8(%ebp), %eax
	movzbl	-4(%ebp), %edx
	movb	%dl, (%eax)
	movl	8(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE1127:
	.size	_ZSt7setfillIcESt8_SetfillIT_ES1_, .-_ZSt7setfillIcESt8_SetfillIT_ES1_
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1194:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	cmpl	$1, 8(%ebp)
	jne	.L37
	cmpl	$65535, 12(%ebp)
	jne	.L37
	subl	$12, %esp
	pushl	$_ZStL8__ioinit
	call	_ZNSt8ios_base4InitC1Ev
	addl	$16, %esp
	subl	$4, %esp
	pushl	$__dso_handle
	pushl	$_ZStL8__ioinit
	pushl	$_ZNSt8ios_base4InitD1Ev
	call	__cxa_atexit
	addl	$16, %esp
.L37:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1194:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z7prnLineRSo, @function
_GLOBAL__sub_I__Z7prnLineRSo:
.LFB1195:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$8, %esp
	pushl	$65535
	pushl	$1
	call	_Z41__static_initialization_and_destruction_0ii
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1195:
	.size	_GLOBAL__sub_I__Z7prnLineRSo, .-_GLOBAL__sub_I__Z7prnLineRSo
	.section	.init_array,"aw"
	.align 4
	.long	_GLOBAL__sub_I__Z7prnLineRSo
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
