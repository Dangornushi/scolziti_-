	.file "main.c"
	.text
	.globl main
	.type main, @function
main:
num: 10
p m: +
num: 2
p m: -
num: 12
p m: +
num: 46
p m: +
num: 56
p m: -
num: 100
num: 
	pushq  %rbp
	movq   %rsp, %rbp
	movq $0, %rax
	leave
	ret
