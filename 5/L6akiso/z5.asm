;Jacek Mucha
;8.01.2016
;kalkulator
; zadanie 5 i zadanie 6 AKiSO
; float ENTER dzialanie ENTER float 
; L - ln, E - exp, S - sh, A - area
; nasm -f elf myprog.asm > 
; ld -m elf_i386 -o z5 z5.o -I/lib/ld-linux.so.2 -lc 

global _start 

extern scanf 
extern printf 
extern putchar
extern getchar

section .data 

	fmt1 db "%lf", 0 
	fmt2 db 10, "Wynik: %f", 10, 0 
	formatOperand db "%c", 0
	a: 	dq 0.0
	b:	dq 1.0
	c:	dq 1.0
	operand:	dd 'y'

section .text 
_start: 
	nop 
	call getfloata 		; wczytywanie a
	call getoperand		; wczytywanie znaku dzialania
jednoargumentowe:
	mov eax, [operand]
	cmp eax, 0x4c		; L, czyli logarytm naturalny
	je logarytm
	cmp eax, 0x45		; E, czyli eksponenta
	je eksponenta
	cmp eax, 0x53		; S, czyli sinh
	je sinh
	cmp eax, 0x41		; A, czyli area
	je area

	call getfloatb		; wczytywanie b

	;call putfloata
	;call putop
	;call putfloatb


warunek:
	mov eax, [operand]
	cmp eax, 0x2b 		; dodawanie
	je plus
	cmp eax, 0x2d		; odejmowanie
	je minus
	cmp eax, 0x2a		; mnozenie
	je multiply
	cmp eax, 0x2f		; dzielenie
	je divide



exit: 
	xor ebx, ebx 
	mov eax, 1 
	int 80h 
;---------- 

;---------- 
getfloata: 
	push ebp 
	mov ebp, esp 
	sub esp, 8 
	lea eax, [ebp - 8] 
	push eax 
	push fmt1 	; format %lf
	call scanf 
	add esp, 8 ; (probably be a good idea to check the return from scanf here, before proceeding...) 
	fld qword [ebp - 8] 	; laduje do st0
	fst qword [a]		; zapisujemy do a
	mov esp, ebp 
	pop ebp 
	ret 
;----------- 

;---------- 
getfloatb: 
	push ebp 
	mov ebp, esp 
	sub esp, 8 
	lea eax, [ebp - 8] 
	push eax 
	push fmt1 	; format %lf
	call scanf 
	add esp, 8 ; (probably be a good idea to check the return from scanf here, before proceeding...) 
	fld qword [ebp - 8] 	; laduje do st0
	fst qword [b]		; zapisujemy do a
	mov esp, ebp 
	pop ebp 
	ret 
;----------- 

;--------------
getoperand:
; read a byte from stdin
	mov eax, 3		 ; 3 is recognized by the system as meaning "read"
	mov ebx, 0		 ; read from standard input
	mov ecx, operand        ; address to pass to
	mov edx, 1		 ; input length (one byte)
	int 0x80                 ; call the kernel
	ret

;-------------

;------------ 
putfloata: 
	push ebp 
	mov ebp, esp 
	sub esp, 8 
	;fst qword [ebp - 8] 
	fld qword [a]
	fst qword [ebp - 8] 
	push fmt2 
	call printf 
	add esp, 12 
	mov esp, ebp 
	pop ebp 
	ret 
;------------- 

putfloatb: 
	push ebp 
	mov ebp, esp 
	sub esp, 8 
	;fst qword [ebp - 8] 
	fld qword [b]
	fst qword [ebp - 8] 
	push fmt2 
	call printf 
	add esp, 12 
	mov esp, ebp 
	pop ebp 
	ret 
;------------- 

putop: 
    mov eax, [operand]  ; The '!' character
    push eax
    push formatOperand
    call printf
    add esp, 8     ; Restore stack - 4 bytes for eax, and 4 bytes for 'message'
    ret 
;------------- 


plus:
	fld qword [a]
	fadd qword [b]
	fst qword [a]
	call putfloata
	jmp exit
minus:
	fld qword [a]
	fsub qword [b]
	fst qword [a]
	call putfloata
	jmp exit
multiply:
	fld qword [a]
	fmul qword [b]
	fst qword [a]
	call putfloata
	jmp exit
divide:
	nop
	fld qword [a]
	fdiv qword [b]
	fst qword [a]
	call putfloata
	jmp exit
logarytm:
	fldl2e			; laduje log(e) do st0
	fld1 ;fld qword [c]			; laduje 1.0 do st0, st1=log(e)
	fld qword [a]			; laduje a do st0
	fyl2x			; st1=log(a)
	fdivr			; dzielenie odwrotne
	fst qword [a]
	call putfloata
	jmp exit
eksponenta:
	fld qword [a]			; laduje a do st0
	fldl2e			; laduje log(e) do st0	
	fmulp
	;f2xm1			; st0=2^st0-1
	call frac
	;fld1			;st0=1
	;fscale			
	;fadd
	fst qword [a]
	call putfloata
	jmp exit
frac:			; 2^st0=2^florr*2^frac, zakladamy, ze na stiosie jest argument
	fld st0
	fld st0
	frndint		; czesc calkowita
	fxch		; zamien
	fsub st0, st1	; czesc ulamkowa
	f2xm1
	fld1
	faddp
	fxch		; wez czesc calkowita
	fld1
	fscale
	fstp st1	; pop st(1)==1
	fmulp
	ret

ekspMakro:
	fldl2e			; laduje log(e) do st0	
	fmulp
	call frac
	ret	; st0=e^x
sinh:
	fld qword [a]	
	fchs		; st0=-st0
	call ekspMakro	; e^-x
	fld st0		; duplikacja
	fld1		; st0=1, st1=e^-x
	fdiv st0,st1	; st0=e^x
	fstp st1	; usuwamy st1
	fsub st0,st1	; e^x+e^-x
	;fchs
	fld1		; st0=1
	fadd st0,st0	; st0=2
	fdiv st1,st0	; st1=st1/st0
	fstp st0	; usuwamy st0
	fst qword [a]
	call putfloata
	jmp exit	
logMakro:
	fld1			; laduje 1.0 do st0, st1=log(e)
	fxch st1		; st0=a+sqrt(a^2+1)
	fyl2x			; st1=log(a)
	fldl2e			; laduje log(e) do st0
	fdiv 			; dzielenie odwrotne
	ret
area:
	fld qword [a]	
	fld st0		; duplikacja
	fmulp		; st0=a^2	st1=a
	fld1		; st0=1, 
	fadd st0,st1	; st0=1+a^2	st2=a
	fsqrt		; sqrt(st0)
	fld qword [a]
	fadd st0,st1
	call logMakro
	fst qword [a]
	call putfloata
	jmp exit	

		







