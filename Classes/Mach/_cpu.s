
%include "mcore.inc"

.section .text

.global NNTAPI(cpuid)

%ifdef NNT_WINDOWS

NNTAPI(cpuid):

%ifdef NNT_X32

	push %ebp
	mov %esp, %ebp
	mov 8(%ebp), %eax
	mov 12(%ebp), %ebx
	mov %ebx, %ebp
	cpuid
	dump_registers
	pop %ebp

%else

	push %rbp
	mov %rsp, %rbp
	add $64, %rbp
	mov (%rbp), %rax
	mov 8(%rbp), %rbx
	mov %rbx, %rbp
	cpuid
	dump_registers
	pop %rbp

%endif

	ret

%endif