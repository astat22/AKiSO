;silnia
;Jacek Mucha
;6.01.2016

section .data 

msg      db      "0123456789"
msg1     db      " "
tmp      dd      0

section .text
        global  main
main: 
	call READ	; do eax wczytujemy input
	mov ebx,eax	; kopiujemy do ebx zaw. eax
petlaS:
	dec ebx		; b--
	mul ebx	
	cmp ebx,1 	; b==1
	jne petlaS
wypisywanie:
	call	_printEAXdecimal	
	ret


READ:
              mov   eax, 0	; a=0
              push  eax		; stos: a

RL1:
              mov   eax, 03h	
              mov   ebx, 0	; b=0
              mov   ecx, tmp	; c=tmp
              mov   edx, 1	; d=1
              int   80h		; 
              mov   eax, [tmp]
              cmp   eax, 48
              jl    RL2
              cmp   al, 58
              jge   RL2
              sub   eax, 48
              pop   ebx
              imul  ebx, 10
              add   eax, ebx
              push  eax
              jmp   RL1

RL2:
              pop   eax
              ret

_printEAXdecimal:
        push eax
        push ebx
        push ecx
        push edx		; wrzucamy na stos wszystko, co mielismy
        mov ecx, 0		; c=0
petla:
        mov edx, 0		; d=0
        mov ebx, 10		; b=10, liczba cyfr?
        div ebx			; liczy a%b=a%10
        push edx		; d=a%b na stos
        inc ecx			; c++ (biezaca cyfra?)
        cmp eax, 0		; porownaj a==0
        jnz petla		; jump if not 0
petla_2:
        mov ebx, 1		; ustawia na stdout
        mov edx, 1		; dlugosc outputu na 1
        pop eax			; zrzuc resztę z dzielenia
        push ecx		; wrzuc numer cyfry
        mov ecx, eax		; c=a
        mov eax, 4		; ustawia na write
        add ecx, msg		; c+=msg, tutaj wskaznik do outputu, czyli 0+c
        int 80h			; wypisuje
        pop ecx			; numer cyfry pobieramy z powrotem
        loop petla_2
        mov eax, 4		; ustawia na write
        mov ecx, msg1		; ecx jest spacja
        mov edx, 1		; dlugosc outputu na 1
        int 80h			; wypisz
        pop edx			; chcemy odzyskac wartosci, ktore mielismy
        pop ecx
        pop ebx
        pop eax
        ret

