
%ifdef Win32
%define NNT_WINDOWS
%define NNT_X32
%endif

%ifdef macho32
%define NNT_MACH
%define NNT_X32
%endif

%ifdef x64
%define NNT_WINDOWS
%define NNT_X64
%endif

%ifdef macho64
%define NNT_MACH
%define NNT_X64
%endif

%ifdef NNT_WINDOWS
%define NNTAPI(name) _ %+ name %+ _
%endif

%ifdef NNT_MACH
%define NNTAPI(name) __ %+ name
%endif

; copy value to mregister (ebp)
%macro dump_registers 0
%ifdef NNT_X32
	mov %eax, (%ebp)
	mov %ebx, 4(%ebp)
	mov %ecx, 8(%ebp)
	mov %edx, 12(%ebp)
	mov %edi, 16(%ebp)
	mov %esi, 20(%ebp)
%else
	mov %rax, (%rbp)
	mov %rbx, 8(%rbp)
	mov %rcx, 16(%rbp)
	mov %rdx, 24(%rbp)
	mov %rdi, 32(%rbp)
	mov %rsi, 40(%rbp)
%endif
%endmacro
