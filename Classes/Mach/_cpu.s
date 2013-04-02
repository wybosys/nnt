
%include "mcore.inc"

.section .text

.global NNTAPI(cpuid)

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

%else ;end x32

%ifdef NNT_WINDOWS
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

%ifdef NNT_MACH
    mov %rdi, %rax
    mov %rsi, %rbx
    mov %rbx, %rbp
    cpuid
    dump_registers
%endif

%endif ;end x64

	ret
	
