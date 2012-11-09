;****************************************************************************
;
;	CTCSS Dekoder mit AT Tiny 2313 CPU
;	es werden die CTCSS frequenzen mit hilfe des Goertzel Algorhytmuses detektiert
;	als erstes wird das Signal mit hilfe eines Software maessigen ADC
;	der mithilfe des eingebauten Komparators und einer aussen an der CPU 
;	angeschlossenen widerstand Netzwerkes Digitalisiert. Dabei wird das
;	sukzesive Apromationsverfahren verwendet. Die Aufloesung dieses ADC
;	betraegt 6 Bit (36 dB Dynamik Umfang). Die Abtastrate wird mit hilfe von
;	Timer 0 auf 1Khz eingestellt.
;	Dann werden die Daten mit hilfe des Goertzel Algorythmuses detektiert
;	und zwar wird mit hilfe der Formel:
;		V = ADC + (a*V1)>>7 - V2
;		V2 = V1
;		V1 = V
;	uber N_VAL = 435 Abtastungen werden die werte fuer V1 + V2 bestimmt.
;	Dabei ergibt sich eine Rechnerische Bandbreite von FS(1Khz) / N_VAL(435) = 2,3 Hz
;	was fuer die Detektion der CTCSS frequenzen ausreichend ist
;	Nach den N_VAL = 435 abtastungen des Signals wird werden die Y-Werte der
;	einzelenen Frequenzen ausgerechnet mit Hilfe der Folgenden Formel
;		V1 = V1 >> 8
;		V2 = V2 >> 8
;		Y = V1*V1 + V2*V2 - V1*V2*a
;	Dabei wird sich die Hoechste Y Amplitude und die dazugehoerige Kanalnummer
;	gemerkt
;	Ueberschreitet dieser Y-Wert jetzt die Trigger schwelle AmpTrgLevel
;	ist die jeweilige Frequenz detektiert worden um aber eine endgueltige
;	Aussage zu erhalten ob die jenige Frequenz korrekt anliegt muss sie "TrgCntLevel"
;	mal korrekt gemessen werden um sie anschliesend ausgeben zu koennen auf dem PORTD
;
;	Berechnung der Faktoren N,a,k
;	Den Faktor N der die Bandbreite des Goertzel Filter bestimmt wird folgendermassen
;	berechnet
;		N = FS/B
;		FS = Abtastfrequenz
;		B  = Bandbreite
;		N = 1000 / 2.3Hz = 435
;
;	Der Faktor k berechnet sich folgender massen
;		k = (Fk * N) / FS
;		Fk = die zu detektierende Frequenz
;		N = siehe oben
;		FS = siehe oben
;		k = 67 * 435 / 1000 = 29.145
;
;	Der Faktor a berechnet 	sich folgender massen
;		a = 2 * cos ((k*2*Pi)/N)
;		a = 1.8253
;
;	da hier aber mit ganzzahl arithmetik gerechnet wird mus dieser
;	faktor a noch skaliert werden
;	a = a * 128
;	a = 234
;	die 128 kommt dadurch zu stande das hier im diesem Programm mit 16 Bit mit
;	vorzeichen gerechnet wird und es unter keinen Umstaenden vorkommen darf
;	den Zahlen bereich zu ueberschreiten und es dadurch zu vorzeichen umkehrungen
;	kommen darf. Allerdings sollt auch der zu verfuegung stehende werte bereich
;	moeglichst ausgenutzt werden um eine hohe genauigkeit zu bekommen
;	
;
;	Version 1.0 H.Lenzen  Oktober 2007
;
;****************************************************************************

	.macro	callne para
;	breq hier
	rcall para
;hier:
	.endm

		.include "tn2313def.inc"

		.equ    RAMSTART	= $60		; Start On-Chip SRAM Location
		.equ	TRGCNT		= RAMSTART+2
		.equ	LASTCHAN	= TRGCNT+1
		.equ	VARSTART	= LASTCHAN+1
		.equ	N_VAL		= 435

		.equ	TrgCntLevel	= 2			;trigger counter level ( max 255)
		.equ	AmpTrgLevel = 0x1000	;amplituden trigger schwelle
		.equ	MAXFREQ		= 28		;anzahl der frequenzen (max 28 sonst Stack ueberlauf)
			
;***** Subroutine Register Variables

		.def	mc16sL	=r16		;multiplicand low byte
		.def	mc16sH	=r17		;multiplicand high byte
		.def	mp16sL	=r18		;multiplier low byte
		.def	mp16sH	=r19		;multiplier high byte
		.def	m16s0	=r18		;result byte 0 (LSB)
		.def	m16s1	=r19		;result byte 1
		.def	m16s2	=r20		;result byte 2
		.def	m16s3	=r21		;result byte 3 (MSB)
		.def	mcnt16s	=r22		;loop counter


		rjmp	MAIN		; Reset Handler
		rjmp	EXT_INT0	; IRQ0 Handler
		rjmp	EXT_INT1	; IRQ0 Handler
		rjmp	TIM1_CAPT	; Timer1 Capture Handler
		rjmp	TIM1_COMP	; Timer1 Compare Handler
		rjmp	TIM1_OVF	; Timer1 Overflow Handler
		rjmp	TIM0_OVF	; Timer0 Overflow Handler
		rjmp	UART_RXC	; UART RX Complete Handler
		rjmp	UART_DRE	; UDR Empty Handler
		rjmp	UART_TXC	; UART TX Complete Handler
		rjmp	ANA_COMP	; Analog Comparator Handler


EXT_INT0:
EXT_INT1:
TIM1_CAPT:
TIM1_COMP:
TIM1_OVF:
UART_RXC:
UART_DRE:
UART_TXC:
ANA_COMP:
		reti


MAIN:
	; **** Initialize Stack Pointer ****
		ldi		R24, LOW(RAMEND)	; Stack Pointer Setup
		out		SPL, R24			; Stack Pointer Low Byte	
	; **** Turn off Watchdog timer ****
		ldi		R24, 0x18			; 
		out		WDTCR, R24			; 
		ldi		R24, 0x10			; 
		out		WDTCR, R24			; 

		; **** Initialize I/O Port ****
		ldi		R24, 0xfc			; Set PB2-7 as Output Mode
		out		DDRB, R24
		ldi		R24, 0x00			; DAC = 0 V out
		out		PORTB, R24

		ldi		R24,0x7f			;PD 0.. 6 -> output
		out		DDRD,R24

		ldi		R24, 0x02			; Enable Timer0 Overflow Interrupt
		out		TIMSK, R24
		ldi		R24, 6				; 1ms Timer Count
		out		TCNT0, R24
		ldi		R24, 0x03			; CK/64, Timer Start
		out		TCCR0, R24

		ldi		xl,low(VARSTART)
		ldi		xh,high(VARSTART)
		ldi		R16,MAXFREQ
		clr		r17
ClearLoop:
		st		X+,R17				;low byte loeschen  (V1)
		st		X+,R17				;high byte loeschen (V1)
		st		X+,R17				;V2
		st		X+,R17				;V2
		dec		r16
		brne	ClearLoop
		
		ldi		R16,low(N_VAL)		;n Counter setzen
		sts		RAMSTART,R16
		ldi		R16,high(N_VAL)
		sts		RAMSTART+1,R16

		clr		r17
		sts		TRGCNT,r17			;clear lastchan und trigger counter
		sts		LASTCHAN,r17

		sei							; Enable Global Interrupt
forever:	
		rjmp	forever
;		callne	SARADC

;-----------------------------------------------------------------------------------------
;
;	SARADC
;	ADC Converter routine
;	ergebnis in R16
;	register R16,R17,R18
;
;-----------------------------------------------------------------------------------------

SARADC:	ldi		R18,0x80			;probe bit maske
		clr		R16					;result register
		ldi		R17,6				;6 bit to convert
SARLOOP:
		or		R16,R18				;set probe bit
		out		PORTB,R16			;out to DAC
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop							;500 nS warten fuer Comparator bei 16Mhz Takt
		sbic	ACSR,5				;DAC wert > analog wert ?
		eor		R16,R18				;wenn ja probe bit zurueck nehmen
		lsr		R18					;naechstes probe bit schieben
		subi	R17,1				;decrement Loop counter
		brne	SARLOOP				;alle durch ?
		lsr		R16
		lsr		R16					;ergebnis schieben
		subi	r16,32				;bereich 0..63 -> -32 .. +31
		lsl		r16
		ret							;fertig wert in R16


;***************************************************************************
;*
;* "mpy16s" - 16x16 Bit Signed Multiplication
;*
;* This subroutine multiplies signed the two 16-bit register variables 
;* mp16sH:mp16sL and mc16sH:mc16sL.
;* The result is placed in m16s3:m16s2:m16s1:m16s0.
;* The routine is an implementation of Booth's algorithm. If all 32 bits
;* in the result are needed, avoid calling the routine with
;* -32768 ($8000) as multiplicand
;*  
;* Number of words	:16 + return
;* Number of cycles	:210/226 (Min/Max) + return
;* Low registers used	:None
;* High registers used  :7 (mp16sL,mp16sH,mc16sL/m16s0,mc16sH/m16s1,
;*			    m16s2,m16s3,mcnt16s)	
;*
;***************************************************************************

mpy16s:	clr		m16s3			;clear result byte 3
		sub		m16s2,m16s2		;clear result byte 2 and carry
		ldi		mcnt16s,16		;init loop counter
m16s_1:	brcc	m16s_2			;if carry (previous bit) set
		add		m16s2,mc16sL	;add multiplicand Low to result byte 2
		adc		m16s3,mc16sH	;add multiplicand High to result byte 3
m16s_2:	sbrc	mp16sL,0		;if current bit set
		sub		m16s2,mc16sL	;sub multiplicand Low from result byte 2
		sbrc	mp16sL,0		;if current bit set
		sbc		m16s3,mc16sH	;sub multiplicand High from result byte 3
		asr		m16s3			;shift right result and multiplier
		ror		m16s2
		ror		m16s1
		ror		m16s0
		dec		mcnt16s			;decrement counter
		brne	m16s_1			;if not done, loop more	
		ret

;-----------------------------------------------------------------------------------------
;
;	Timer 0 Overflow interrupt
;
;-----------------------------------------------------------------------------------------

TIM0_OVF:
		ldi		R24, 6				; 1ms Timer Count
		out		TCNT0, R24			; reload timer

;********** ADC wert holen ***********
		rcall	SARADC				;ADC in R16
		mov		r10,r16				;in R10,r11 sichern
		clr		r11
		bst		r10,7				;vorzeichen auf 16 bit erweitern
		brtc	L1
		com		r11
L1:

;********** V = ADC + V1 * a - V2 berechnen ********
		ldi		yl,low(VARSTART)	;ptr auf variabeln bereich
		ldi		yh,high(VARSTART)
		ldi		zl,low(FAC_A*2)		;ptr auf factor A Frequenz
		ldi		zh,high(FAC_A*2)
		ldi		R24,MAXFREQ			;counter ueber alle frequenzen
FreqLoop1:
		mov		r2,r10				;adc wert laden
		mov		r3,r11
		lpm		r8,z+				;a laden
		lpm		r9,z+
		rcall	CalcInnerGoertzel
		adiw	Y,4					;ptr to next V1,V2
		dec		R24
		brne	FreqLoop1			;alle frequenzen durchgerechnet ?

;************* Test n >= N_VAL ******************

		lds		xl,RAMSTART			;n Laden
		lds		xh,RAMSTART+1
		sbiw	x,1					;n-1
		sts		RAMSTART,xl
		sts		RAMSTART+1,xh
		or		xl,xh				;n = 0?
		cpi		xl,0
		breq	L2
		rjmp	TIM0_END			;nein dann fertig
L2:		ldi		xl,low(N_VAL)
		ldi		xh,high(N_VAL)
		sts		RAMSTART,xl
		sts		RAMSTART+1,xh		;n neu laden

;************** Y = V1*V1 + V2*V2 - V1*V2*a ****************

		ldi		yl,low(VARSTART)	;ptr auf variabeln bereich
		ldi		yh,high(VARSTART)
		ldi		zl,low(FAC_A*2)		;ptr auf factor A
		ldi		zh,high(FAC_A*2)
		clr		r23					;loop counter
		clr		r24					;frequenz nummer
		clr		r14					;Maxwert = 0 setzen
		clr		r15
FreqLoop2:
		lpm		r8,z+				;a  laden
		lpm		r9,z+				;ptr to next a
		rcall	CalcOuterGoertzel	;Y berechnen
		adiw	y,4					;ptr to next V1,V2
		cp		r2,r14				;maximum suchen
		cpc		r3,r15
		brge	FindNewMaximum		;groeseren wert gefunden ?

NextFreq:
		inc		r23					;inc Loop counter
		cpi		r23,MAXFREQ			;alle frequenzen durch ?
		brlo	FreqLoop2			;nein dann naechste frequenz berechnen
		rjmp	EndLoop				;alle frequenzen -> fertig

;***** neues maximum gefunden dann abspeichern und frequenz nummer merken ****

FindNewMaximum:
		mov		r24,r23
		inc		r24					;nummer von 1..MAXFREQ merken
		mov		r14,r2
		mov		r15,r3				;neues maximum merken
		rjmp	NextFreq

;***** test ob neues maximum uber der trigger schwelle liegt ****************

EndLoop:
		ldi		r16,low(AmpTrgLevel)
		ldi		r17,high(AmpTrgLevel)
		cp		r14,r16
		cpc		r15,r17
		brlt	NoFrequenzFound

		lds		r18,LASTCHAN
		cp		r18,r24				;neuer kanal endeckt ?
		brne	NewFreq
		lds		r18,TRGCNT			;gleicher kanal dann testen ob
		cpi		r18,TrgCntLevel		;trigger count level erreicht ist ?
		breq	FrequenzFound
		inc		r18
		sts		TRGCNT,r18			;Trgcounter ++
		rjmp	TIM0_END

NewFreq:
		sts		LASTCHAN,r24		;neuer kanal merken
		clr		r18
		sts		TRGCNT,r18			;trigger counter loeschen
		rjmp	TIM0_END

NoFrequenzFound:
		lds		r18,TRGCNT			;trigger counter laden
		cpi		r18,0				;counter = 0
		breq	ClearOut
		dec		r18					;counter --
		rjmp	TIM0_END
ClearOut:
		clr		r24
FrequenzFound:
;		com		r24
		out		PORTD,r24

TIM0_END:
		reti

;-------------------------------------------------------------------------------------
;
;	CalcInnerGoertzel
;	in Y ptr auf V1+V2
;	in R2,R3 den adc wert
;	in R8,R9 den faktor a
;
;	berechnet innere goertzel schleife
;
;	v(r2,r3) = adc(r2,r3) - V2(r6,r7) + a(r8,r9)*v1(r4,r5) >> 8
;	V2 = V1
;	V1 = v;
;	gebrauchte register (R2,R3,R6,R7,R8,R9)
;
;-------------------------------------------------------------------------------------

CalcInnerGoertzel:

		ldd		mp16sl,Y+0			;load v1
		ldd		mp16sh,Y+1
		ldd		r6,Y+2
		ldd		r7,Y+3				;load v2
		std		Y+2,mp16sl
		std		Y+3,mp16sh			;V2 = V1
		sub		r2,r6
		sbc		r3,r7				;v(r2,r3) = adc(r2,r3) - V2(r6,r7)
		mov		mc16sl,r8
		mov		mc16sh,r9
		rcall	mpy16s				;a(r8,r9) * V1(r4,r5)
		lsl		m16s0
		rol		m16s1
		rol		m16s2				; >> 7
		add		r2,m16s1
		adc		r3,m16s2			;v(r2,r3) = adc(r2,r3) - V2(r6,r7) + a(r8,r9)*v1(r4,r5) >> 7
		std		Y+0,r2
		std		Y+1,r3				;V1 = v
		ret

;-------------------------------------------------------------------------------------
;
;	CalcOuterGoertzel
;	berechnet aussere Goertzel schleife
;
;	Y = (v1>>8)*(v1>>8)+(v2>>8)*(v2>8)-(v1*v2*a) >> 11
;	V1 = 0
;	V2 = 0
;	in Y ptr auf V1+V2
;	in R8,R9 den faktor a
;	Y = R2,R3,R4,R5
;
;-------------------------------------------------------------------------------------
CalcOuterGoertzel:
		ldd		mp16sl,Y+1		;v1 >> 8
		mov		mc16sl,mp16sl
		clr		mp16sh
		clr		mc16sh
		bst		mp16sl,7
		brtc	CalcOuter1
		com		mp16sh
		com		mc16sh
CalcOuter1:
		mov		r6,mp16sl
		mov		r7,mp16sh		;save v1 >> 8
		rcall	mpy16s			;Y = (v1>>8)*(v1>>8)
		mov		r2,m16s0
		mov		r3,m16s1
		mov		r4,m16s2
		mov		r5,m16s3		;store in R2,R3,R4,R5

		ldd		mp16sl,Y+3		;v2 >> 8
		mov		mc16sl,mp16sl
		clr		mp16sh
		clr		mc16sh
		bst		mp16sl,7
		brtc	CalcOuter2
		com		mp16sh
		com		mc16sh
CalcOuter2:
		mov		r12,mp16sl
		mov		r13,mp16sh		;save v2 >> 8
		rcall	mpy16s			;Y = (v2>>8)*(v2>>8)
			
		add		r2,m16s0
		adc		r3,m16s1
		adc		r4,m16s2
		adc		r5,m16s3		;Y = v1*v1+v2*v2

		mov		mp16sl,r6		;load v1 >> 8
		mov		mp16sh,r7
		mov		mc16sl,r12
		mov		mc16sh,r13		;load v2 >> 8
		rcall	mpy16s			;v1 * v2
		mov		mc16sl,r8
		mov		mc16sh,r9		;mp16sl,mp16sh = m16s0,m16s1
		rcall	mpy16s			;v1*v2*a
		ror		m16s3
		ror		m16s2
		ror		m16s1
		ror		m16s3
		ror		m16s2
		ror		m16s1			;v1*v2*a >>10
		sub		r2,m16s1
		sbc		r3,m16s2
		sbc		r4,m16s3
		clr		m16s0
		sbc		r5,m16s0		;Y = v1*v1+v2*v2-(v1*v2*a)>>10
		std		Y+0,m16s0
		std		Y+1,m16s0
		std		Y+2,m16s0
		std		Y+3,m16s0		;V1 = V2 = 0
		ret


;--------------------------------------------------------------------------
;
;	Die faktoren 'a'
;
;--------------------------------------------------------------------------

FAC_A:		.dw		234,232,230,229,227,225,222,220,217,215
			.dw		212,210,207,204,200,196,192,188,183,178
			.dw		173,167,162,155,149,142,137,134


		.org		0x400
		.dw			0xefff				;Fuse wert fuer HED Chip Programmer
