;nasm -f elf z3.asm , gcc -m32 z3.o -o z3

segment .data 

msg      db      "0123456789"
msg1     db      " "
tmp      dd      0
limit 	 dd	 10000	; do jakiego zakresu

segment .text
        global  main
main: 
	mov	eax,[limit]	;laduj zakres do eax
        mov     ecx, eax	; c=limit
        push    ebp		; ebp na stos
        mov     ebp,esp		; b=s		szczyt=dol
        
L1:
        push    ecx		; aktualna liczba (od gory) na stos
        dec     ecx		; c--
        cmp     ecx,1		; schodzimy az do 1
        jne     L1
 
        mov     ebx,4		; b=4
L2:
        mov     edi,esp		; di=s
        pop     ecx     	; liczba ze stosu
        cmp     ecx,0		; sprawdz, czy wykreslona
        je      niePier		; 
 
        mov     eax,ecx		; c=a, aby wypisac
        call    _printEAXdecimal; wypisz
                
        mov     eax,ecx		; a= biezaca liczba=c
        xor     ecx,ecx		; c=0
        mul     ebx		; a*=4
L3:				; zerowanie wielokrotnosci
        mov     [edi],ecx	; to co bylo pod adresem d= 0
        add     edi,eax		; adres d: d+=4*biezaca liczba (bylo d=s), 4 to dlugosc liczby, a wiec przesuwamy tablice o bajt przemnozony przez liczbe
        cmp     edi,ebp		; porownanie z podtsawa stosu
        jg      niePier		; wyzeruj
        jmp     L3
 
niePier:		
        cmp     ebp,esp		; porownaj szczyt z dolem
        jne     L2		; jesli rozne, to wroc do petli 2
 
        pop     ebp		; wpp zrzuc ze stosu do ebp
 
        mov     eax, 1  	; sys_exit
        mov     ebx, 0
        mov     ecx, 0
        mov     edx, 0
        int     80h		; koniec
    
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

