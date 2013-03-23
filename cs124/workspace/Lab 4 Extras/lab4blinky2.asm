;*******************************************************************************
;Ethan D. Estrada
;CS 124 Section 2
;Lab 4
;
;*******************************************************************************
			.cdecls C,LIST, "msp430x20x3.h" ; MSP430F2013
;			.cdecls C,LIST, "msp430x22x4.h" ; MSP430F2274

myDelay1		.equ	(2+1)				; set delay1 constant
myDelay2		.equ	2375				; set delay2 constant
delay1second	.equ	4
delay5seconds	.equ	5
delay10seconds	.equ	10
toggle6seconds	.equ	6
toggle4seconds	.equ	16
;------------------------------------------------------------------------------
            .text                           ; beginning of executable code
;------------------------------------------------------------------------------
RESET:      mov.w   #0x0200,SP              ; init stack pointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; stop WDT
            bis.b	#0x01,&P1DIR            ; set P1.0 as output	

mainloop:   call	#fiveSecondsOn			; call subroutine "fiveSecondsOn"
			call	#sixSecondToggle		; call subroutine "sixSecondToggle"
			call	#fourSecondToggle		; call subroutine "fourSecondOnandOff"
			call	#tenSecondsOff			; call subroutine "tenSecondOff"
			jmp		mainloop



fiveSecondsOn:
			call 	#toggleLight			; call subroutine "toggleLight"
			mov.w	#delay5seconds,r12		; make R12 a counter to count down five seconds
			
fiveSecondsOnSlave:							; delays for five seconds, one second at a time
			call	#oneSecondDelay			; call subroutine "oneSecondDelay"
			dec.w	r12						; decrement R12
			jnz		fiveSecondsOnSlave		; repeat fiveSecondsOnSlave if R12 hasn't fully decremented
			ret								; return to next instruction pointed to by stack


			
sixSecondToggle:
			mov.w	#toggle6seconds,r12		; make R12 a counter to toggle the light for six seconds (one second between each toggle)

sixSecondToggleSlave:
			call	#toggleLight			; call subroutine "toggleLight"
			call	#oneSecondDelay			; call subroutine "oneSecondDelay"
			dec.w	r12						; decrement R12
			jnz		sixSecondToggleSlave	; repeat sixSecondToggleSlave if R12 hasn't fully decremented
			ret								; return to next instruction pointed to by stack



fourSecondToggle:
			mov.w	#toggle4seconds,r12		; make R12 a counter to toggle the light for four seconds (1/4 second between each toggle)
			
fourSecondToggleSlave:
			call	#toggleLight			; call subroutine "toggleLight"
			call	#quarterSecondDelay		; call subroutine "quarterSecondDelay"
			dec.w	r12						; decrement R12
			jnz		fourSecondToggleSlave	; repeat fourSecondToggleSlave if R12 hasn't fully decremented
			ret								; return to next instruction pointed to by stack



tenSecondsOff:
			call	#toggleLight			; call subroutine "toggleLight"
			mov.w	#delay10seconds,r12		; make R12 a counter to count down ten seconds
			
tenSecondDelay:
			call	#oneSecondDelay			; call subroutine "oneSecondDelay"
			dec.w	r12						; decrement R12
			jnz		tenSecondDelay			; repeat tenSecondDelay if R12 hasn't fully decremented
			ret								; return to next instruction pointed to by stack


			
toggleLight:
			xor.b   #0x01,&P1OUT            ; toggle P1.0
			ret								; return to next instruction pointed to by stack



oneSecondDelay:
			mov.w 	#delay1second,r13
			
oneSecondSlave:
			call	#quarterSecondDelay		; call subroutine "quarterSecondDelay"
			dec.w	r13						; decrement r13
			jnz		oneSecondSlave			; repeat oneSecondSlave if R13 hasn't fully decremented
			ret								; return to next instruction pointed to by stack



quarterSecondDelay:							; waste cycles until one quarter of a second has passed
            mov.w   #myDelay1,r14           ; use R14 as master delay counter
            

delayloop1:	mov.w	#myDelay2,r15			; use R15 as slave delay counter
			dec.w   r14                   	; decrement R14
              jnz	delayloop2              ; jump to delayloop2 if r15 doesn't equal zero
              ret							; return to next instruction pointed to by stack
              
delayloop2:	dec.w	r15						; decrement R15
              jnz	delayloop2				; jump to delayloop 2 if r14 doesn't equal zero
            jmp     delayloop1             	; uncondtionally jump to delayloop1
            
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ; start address
            .end
            
;*******************************************************************************
; PROGRAM TO DETERMINE CLOCK SPEED AND ACOMMPANYING DOCUMENTATION!
;*******************************************************************************
;			.cdecls C,LIST, "msp430x20x3.h" ; MSP430F2013
;			.cdecls C,LIST, "msp430x22x4.h" ; MSP430F2274
;
;
;delay1		.set 40							; set delay1 variable
;delay2		.set 3333						; set delay2 variable
;------------------------------------------------------------------------------
;            .text                           ; beginning of executable code
;------------------------------------------------------------------------------
;
;RESET:      mov.w   #0x0200,SP             ; init stack pointer (2 cycles)
;            mov.w   #WDTPW+WDTHOLD,&WDTCTL ; stop WDT (5 cycles)
;            bis.b	#0x01,&P1DIR            ; set P1.0 as output (5 cycles)
;											; RESET takes 12 cycles to complete
;
;mainloop:   xor.b   #0x01,&P1OUT           ; toggle P1.0 (5 cycles)
;            mov.w   #delay1,r15            ; use R15 as master delay counter (2 cycles)
;            mov.w	#delay2,r14				; use R14 as slave delay counter (2 cycles)
;											; mainloop takes 9 cycles to complete
;
;delayloop1:	dec.w   r15                 ; decrement R15 (1 cycle)
;              jz	mainloop               	; jump to main if r15 equals zero (2 cycles)
;											; delayloop1 takes 3 cycles to complete
;              
;delayloop2:	dec.w	r14						; decrement R14 (1 cycle)
;              jnz	delayloop2				; jump to delayloop 2 if r14 doesn't equal zero(2 cycles)
;            jmp     delayloop1             	; jump to delayloop1 (2 cycles)
											; delayloop2 takes 3 cycles to complete
;
;											; The equation to figure out clock time is as follows (using preceding code).
;											; Section titles (i.e. RESET) represent the # cycles it takes to complete the section:
;											; mainloop+(delayloop1*delay1)+(delayloop2*delay2*delay1)+(2*delay1)
;											; The result of the above equation is then divided by the number of seconds
;											; it takes to complete one blink. This will yield the hertz rating of the processor.
;											; as of now I believe my MSP430-F2013 processor to run at around 57167 hertz (57 kHz).



;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
;            .sect   ".reset"                ; MSP430 RESET Vector
;            .short  RESET                   ; start address
;            .end