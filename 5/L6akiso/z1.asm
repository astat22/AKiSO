; xasm z1.asm /o:z1 , ./emu6502 z1
	opt f-g-h+l+o+
	org $100

start	lda #$9a	;a=af, tylko dwie litery
	ldy #$1		;y=0x1
	jsr phex	;jump for subroutine, w phex wykonuja sie wlasciwe operacje
	lda <form	;mlodszy bajt
	ldx >form	;starszy bajt
	jsr $ff80	;wyswietlanie (instrukcja emulatora)
	brk		;koniec programu

phex	pha		; odklada na stos zawartosc akumulatora	
	jsr pxdig	; skok do pxdig
	pla		; wartosc ze stosu do akumulatora
	lsr @		; 2^4*a
	lsr @
	lsr @
	lsr @

pxdig	and #%00001111	; zeruje 4 najstarsze bity
	ora #'0'	; a+= 0011 0000
	cmp #':'	; porownaj do :==9+1
	bcc pr		; branch on carry clear, skaczemy do pr, jesli <
	adc #$6		; dodaje 

pr	sta formatowanie,y	; zapisywanie HEX, chodzi o przesuniecie
	dey		; dekrementacja y
	rts		; powrot

formatowanie	dta b(0)	; formatowanie
        dta b(0)
	dta b(10)

	org $2E0	;koniec zapisu ciągu bajtow
	dta a(start)	; slowo

	end of file
