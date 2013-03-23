;*******************************************************************************
;   CS/ECEn 124 Lab 4 - stoplight.asm: Software Toggle P1.0
;*******************************************************************************
           .cdecls C,LIST, "msp430x22x4.h"  ; MSP430F2013
delay1		.set	10000
delay2		.set	0x0032					;50

;------------------------------------------------------------------------------
            .text                           ; beginning of executable code
;------------------------------------------------------------------------------
RESET:      mov.w   #0x0280,SP              ; init stack pointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; stop WDT
			bis.b	#0x03,&P1DIR			; eZ430-RF2500 LED's
			bic.b	#0xc0,&P2SEL			; select GPIO
			bis.b	#0xc0,&P2DIR			; LED #1-2 (P2.6-7)
			bis.b	#0x08,&P3DIR			; LED #3 (P3.3)
			bis.b	#0x40,&P4DIR			; LED #4 (P4.6)

			bic.b	#0x01,&P1OUT			; eZ430-RF2500 LED's
			bic.b	#0x40,&P2OUT			; LED #1 (P2.6)
			bic.b	#0x08,&P3OUT			; LED #3 (P3.3)

			bis.b	#0x02,&P1OUT			; eZ430-RF2500 LED's
			bis.b	#10000000b,&P2OUT		; LED #2 (P2.7)
			bis.b	#01000000b,&P4OUT		; LED #4 (P4.6)


mainloop:	xor.b	#0x03,&P1OUT			; eZ430-RF2500 LED's
			xor.b	#0xc0,&P2OUT			; LED #1-2 (P2.6-7)
			xor.b	#0x08,&P3OUT			; LED #3 (P3.3)
			xor.b	#0x40,&P4OUT			; LED #4 (P4.6)
			mov.w	#delay2,r14

myDelay2:	dec.w	r14
	 		  jeq	mainloop
			mov.w	#delay1,r15

myDelay:	dec.w	r15
			  jne	myDelay
    		jmp     myDelay2                ; y, toggle led

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ; start address
            .end
