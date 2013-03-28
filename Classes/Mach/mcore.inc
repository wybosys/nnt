
%ifdef Win32
%define NNT_WINDOWS
%define NNT_X32
%endif

%ifdef X64
%define NNT_WINDOWS
%define NNT_X64
%endif

%ifdef NNT_WINDOWS
%define NNTAPI(name) _ %+ name %+ _
%endif

.section .data
mr:
	.long 0

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
%endif
%endmacro
