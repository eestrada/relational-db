			.title	"Lab 5 - morse.asm"
;*******************************************************************************
;   CS/ECEn 124 Lab 5 - morse.asm: Student Code
;
;   Write a MSP430 assembler program that outputs a message in Morse Code on
;   the red LED and buzzer using an interrupt service routine (ISR).
;   Also, blink the eZ430 green LED on and off at one second intervals.
;   Use the watchdog timer interrupt to execute the ISR.
;
;   Watchdog   MMB 8.1, pg. 276.
;   ISR's      MMB 6.8, pg. 190.
; 
;   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
;
;     A  P4.4     Left Pot  O--O  O  Servo #1
;     B  P4.5       Buzzer  O--O  O  Servo #2
;     C  P4.6   Thermistor  O  O--O  LED_4
;     D  P2.2  ADXL345 INT  O  O--O  SW_3
;     E  P2.3         SW_4  O--O  O  Servo #3
;     F  P2.4    Backlight  O--O  O  Servo #4
;     G  P4.3    Right Pot  O--O  O  EZ0_AN
;     H  P2.1         SW_2  O--O  O  EZ0_TX
;
;                MSP430F2274
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->RED LED
;            |             P1.1|-->GREEN LED
;            |                 |
;            |             P4.5|-->BUZZER
;
;*******************************************************************************
            .nolist                     ; turn off list for headers
            .cdecls C,LIST,"msp430x22x4.h"   ; include c header
            .list                       ; turn list back on

COUNT       .set    2048                ; 1 second count
STACK       .set    0x0600              ; address of stack

ENDMESSAGE	.set	0
END         .set    1
DOT         .set    2
DASH        .set    3
SPACE       .set    4

ELEMENT		.set	512
                       
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
            .data                       ; data section
            .bss    cnt,2               ; ISR counter
            .bss	buzzOrWait,2		; whether to buzz or to wait
            .bss	morseTime,2			; how long to buzz
            .bss	waitTime,2			; how long to wait
            .bss	moveToNext,2        ; points to next dit or dah       
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
            .text                       ; program section
RESET:      mov.w   #STACK,SP           ; initialize stack pointer
            mov.w   #WDT_MDLY_0_5,&WDTCTL   ; set Watchdog interval to ~0.5ms
            mov.b   #WDTIE,&IE1         ; enable WDT interrupt
            bis.b   #0x03,&P1DIR        ; Turn P1.0 output on (Green and red LEDs)
            bic.b	#0x03,&P1OUT		; Make sure both P1.0 and P1.1 are off
            bis.b   #0x20,&P4DIR        ; P4.5 output (buzzer)

            mov.w   #COUNT,&cnt         ; initialize counter
            mov.b	#0x00,&buzzOrWait		; initialize to "wait"
            mov.w	#1,&morseTime		; initialize morsetime counter
            mov.w	#1,&waitTime		; initialize waitTime counter
            mov.w	#0,&moveToNext		; use as a pointer
            bis.w   #LPM0+GIE,SR        ; enter LPM0 w/ interrupt
            jmp     $                   ; loop forever - interrupts do all

message:    
			.byte	DOT,DOT,DOT,DOT,END		; H
			.byte	DOT,END					; E
			.byte	DOT,DASH,DOT,DOT,END	; L
			.byte	DOT,DASH,DOT,DOT,END	; L
			.byte	DASH,DASH,DASH,END		; O
			.byte	SPACE					; END OF WORD
			
			.byte	DOT,DASH,DASH,END		; W
			.byte	DASH,DASH,DASH,END		; O
			.byte	DOT,DASH,DOT,END		; R
			.byte	DOT,DASH,DOT,DOT,END	; L
			.byte	DASH,DOT,DOT,END		; D
			.byte	SPACE					; END OF WORD
			
			.byte	ENDMESSAGE				; END OF MESSAGE
;------------------------------------------------------------------------------
;   Watchdog Timer interrupt service routine
;
WDT_ISR:    
buzzer:		cmp.b	#1,&buzzOrWait		; buzz?
			  jne	wait				; no
			xor.b   #0x20,&P4OUT      	; yes, PWM buzzer
			dec.w	&morseTime        	; done with buzzing?
               jz	buzzdone          	; yes            
              jmp	WDT$done			; no

wait:		dec.w	&waitTime			; is the wait time finished?
			  jne	WDT$done			; no
			  jmp	whichElement		; yes

buzzdone:	bic.b	#0x01,&buzzOrWait
			bic.b   #0x01,&P1OUT		; turn off P1.0 (red LED)
			  jmp	WDT$done

whichElement:
			mov.w	&moveToNext,r15		; point to current byte
			mov.b	message(r15),r15	; and figure out which byte we are looking at
			inc.w	&moveToNext			; point to next byte
			
			cmp.b	#DOT,r15			; is it a dot?
			  jeq	doDOT				; yes
			cmp.b	#DASH,r15			; is it a dash?
			  jeq	doDASH				; yes
			cmp.b	#END,r15			; is it an end?
			  jeq	doEND				; yes
			cmp.b	#SPACE,r15			; is it a space?
			  jeq	doSPACE				; yes
			cmp.b	#ENDMESSAGE,r15		; is the message done?
			  jeq	doENDMESSAGE		; yes
			  
doDOT:
			bis.b	#0x01,&buzzOrWait	; make sure to buzz on next WDT_ISR
			bis.b   #0x01,&P1OUT		; turn on P1.0 (red LED)
			mov.w	#ELEMENT,&morseTime	; set length of buzz
			mov.w	#ELEMENT,&waitTime	; set length of wait
			  jmp	WDT$done			; let program wait for next WDT_ISR

doDASH:
			bis.b	#0x01,&buzzOrWait	; make sure to buzz on next WDT_ISR
			bis.b   #0x01,&P1OUT		; turn on P1.0 (red LED)
			mov.w	#ELEMENT*3,&morseTime	; set length of buzz
			mov.w	#ELEMENT,&waitTime	; set length of wait
			  jmp	WDT$done			; let program wait for next WDT_ISR

doEND:			
			mov.w	#ELEMENT*2,&waitTime	; set length of wait
			  jmp	WDT$done			; let program wait for next WDT_ISR

doSPACE:
			mov.w	#ELEMENT*4,&waitTime	; set length of wait
			  jmp	WDT$done			; let program wait for next WDT_ISR

doENDMESSAGE:
			mov.w	#0,&moveToNext		; set length of wait
			mov.b	#0x00,&buzzOrWait	; make sure the machine does not buzz accidentally
			mov.w	#0x01,&morseTime	; set length of buzz
			mov.w	#0x01,&waitTime		; set length of wait
			  
WDT$done:   
			dec.w	&cnt				; count one second.
			  jnz	WDT$done2			; noT done counting yet.
			xor.b   #0x02,&P1OUT		; toggle P1.1 (green LED).
			mov.w   #COUNT,&cnt         ; reinitialize counter.
						
WDT$done2:			
			reti                        ; return from interrupt

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".int10"            ; MSP430 RESET Vector
            .word   WDT_ISR             ; Watchdog ISR

            .sect   ".reset"            ; MSP430 RESET Vector
            .word   RESET               ; Power Up ISR
            .end
