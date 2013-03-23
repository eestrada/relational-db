;*******************************************************************************
;Ethan D. Estrada
;CS 124 Section 2
;Lab 4
;
;*******************************************************************************
			.cdecls C,LIST, "msp430x20x3.h" ; MSP430F2013
;			.cdecls C,LIST, "msp430x22x4.h" ; MSP430F2274

delay1		.set 400							; set delay1 variable
delay2		.set 3333						; set delay2 variable
;------------------------------------------------------------------------------
            .text                           ; beginning of executable code
;------------------------------------------------------------------------------
RESET:      mov.w   #0x0200,SP              ; init stack pointer (2 cycles)
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; stop WDT (5 cycles)
            bis.b	#0x01,&P1DIR            ; set P1.0 as output (5 cycles)
											; RESET takes 12 cycles to complete

mainloop:   xor.b   #0x01,&P1OUT            ; toggle P1.0 (5 cycles)
            mov.w   #delay1,r15             ; use R15 as master delay counter (2 cycles)
            
											; mainloop takes 9 cycles to complete

delayloop1:	mov.w	#delay2,r14				; use R14 as slave delay counter (2 cycles)
			dec.w   r15                   	; decrement R15 (1 cycle)
              jz	mainloop               	; jump to main if r15 equals zero (2 cycles)
											; delayloop1 takes 3 cycles to complete
              
delayloop2:	dec.w	r14						; decrement R14 (1 cycle)
              jnz	delayloop2				; jump to delayloop 2 if r14 doesn't equal zero(2 cycles)
            jmp     delayloop1             	; jump to delayloop1 (2 cycles)
											; delayloop2 takes 3 cycles to complete

											; The equation to figure out clock time is as follows (using preceding code).
											; Section titles (i.e. RESET) represent the # cycles it takes to complete the section:
											; mainloop+(delayloop1*delay1)+(delayloop2*delay2*delay1)+(2*delay1)
											; The result of the above equation is then divided by the number of seconds
											; it takes to complete one blink. This will yield the clock speed of the processor.
											; As of now, I believe my MSP430-F2013 processor to run at around 1143316 hertz (or 1.1 MHz).



;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ; start address
            .end