;*******************************************************************************
;Ethan D. Estrada
;CS 124 Section 2
;Lab 4
;approx 4 hours of work time
;
;*******************************************************************************
			.cdecls C,LIST, "msp430x20x3.h" ; MSP430F2013

myDelay1		.equ	(2+1)				; set delay1 constant
myDelay2		.equ	47500				; set delay2 constant
delay1second	.equ	4					; set delay1second constant
delay5seconds	.equ	5					; set delay5seconds constant
delay10seconds	.equ	10					; set delay10seconds constant
toggle6seconds	.equ	6					; set toggle6seconds constant
toggle4seconds	.equ	16					; set toggle4seconds constant
portOutputSet	.equ	0x01				; set portOutputSet constant
portToggleSet	.equ	0x01				; set portToggleSet constant
;------------------------------------------------------------------------------
            .text                           ; beginning of executable code
;------------------------------------------------------------------------------
RESET:      mov.w   #0x0280,SP              ; init stack pointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; stop WDT
            bis.b	#portOutputSet,&P1DIR   ; set P1.0 as output
            bic.b   #portToggleSet,&P1OUT   ; turn P1.0 off
            	

mainloop:   call	#fiveSecondsOn			; call subroutine "fiveSecondsOn"
			call	#sixSecondToggle		; call subroutine "sixSecondToggle"
			call	#fourSecondToggle		; call subroutine "fourSecondToggle"
			call	#tenSecondsOff			; call subroutine "tenSecondOff"
			jmp		mainloop



fiveSecondsOn:
			call 	#toggleLight			; call subroutine "toggleLight"
			mov.w	#delay5seconds,r11		; make R11 a counter to count down five seconds
			
fiveSecondsOnSlave:							; delays for five seconds, one second at a time
			call	#oneSecondDelay			; call subroutine "oneSecondDelay"
			dec.w	r11						; decrement R11
			jnz		fiveSecondsOnSlave		; repeat fiveSecondsOnSlave if R12 hasn't fully decremented
			ret								; return to next instruction pointed to by stack


			
sixSecondToggle:
			mov.w	#toggle6seconds,r11		; make R11 a counter to toggle the light for six seconds (one second between each toggle)

sixSecondToggleSlave:
			call	#toggleLight			; call subroutine "toggleLight"
			call	#oneSecondDelay			; call subroutine "oneSecondDelay"
			dec.w	r11						; decrement R11
			jnz		sixSecondToggleSlave	; repeat sixSecondToggleSlave if R11 hasn't fully decremented
			ret								; return to next instruction pointed to by stack



fourSecondToggle:
			mov.w	#toggle4seconds,r11		; make R11 a counter to toggle the light for four seconds (1/4 second between each toggle)
			
fourSecondToggleSlave:
			call	#toggleLight			; call subroutine "toggleLight"
			call	#quarterSecondDelay		; call subroutine "quarterSecondDelay"
			dec.w	r11						; decrement R11
			jnz		fourSecondToggleSlave	; repeat fourSecondToggleSlave if R12 hasn't fully decremented
			ret								; return to next instruction pointed to by stack



tenSecondsOff:
			call	#toggleLight			; call subroutine "toggleLight"
			mov.w	#delay10seconds,r11		; make R11 a counter to count down ten seconds
			
tenSecondDelay:
			call	#oneSecondDelay			; call subroutine "oneSecondDelay"
			dec.w	r11						; decrement R11
			jnz		tenSecondDelay			; repeat tenSecondDelay if R12 hasn't fully decremented
			ret								; return to next instruction pointed to by stack


			
toggleLight:
			xor.b   #portToggleSet,&P1OUT   ; toggle P1.0
			ret								; return to next instruction pointed to by stack



oneSecondDelay:
			mov.w 	#delay1second,r12
			
oneSecondSlave:
			call	#quarterSecondDelay		; call subroutine "quarterSecondDelay"
			dec.w	r12						; decrement r13
			jnz		oneSecondSlave			; repeat oneSecondSlave if R13 hasn't fully decremented
			ret								; return to next instruction pointed to by stack



quarterSecondDelay:							; waste cycles until one quarter of a second has passed
            mov.w   #myDelay1,r14           ; use R14 as master delay counter
            

delayloop1:	mov.w	#myDelay2,r15			; use R15 as slave delay counter
			dec.w   r14                   	; decrement R14
              jnz	delayloop2              ; jump to delayloop2 if r14 doesn't equal zero
              ret							; return to next instruction pointed to by stack
              
delayloop2:	dec.w	r15						; decrement R15
              jnz	delayloop2				; jump to delayloop 2 if r15 doesn't equal zero
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
;*******************************************************************************
;			.cdecls C,LIST, "msp430x20x3.h" ; MSP430F2013
;			.cdecls C,LIST, "msp430x22x4.h" ; MSP430F2274
;
;delay1		.set 400							; set delay1 variable
;delay2		.set 3333						; set delay2 variable
;------------------------------------------------------------------------------
;            .text                           ; beginning of executable code
;------------------------------------------------------------------------------
;RESET:      mov.w   #0x0200,SP              ; init stack pointer (2 cycles)
;            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; stop WDT (5 cycles)
;            bis.b	#0x01,&P1DIR            ; set P1.0 as output (5 cycles)
;											; RESET takes 12 cycles to complete
;
;mainloop:   xor.b   #0x01,&P1OUT            ; toggle P1.0 (5 cycles)
;            mov.w   #delay1,r15             ; use R15 as master delay counter (2 cycles)
;            
;											; mainloop takes 9 cycles to complete
;
;delayloop1:	mov.w	#delay2,r14				; use R14 as slave delay counter (2 cycles)
;			dec.w   r15                   	; decrement R15 (1 cycle)
;              jz	mainloop               	; jump to main if r15 equals zero (2 cycles)
;											; delayloop1 takes 3 cycles to complete
;              
;delayloop2:	dec.w	r14						; decrement R14 (1 cycle)
;              jnz	delayloop2				; jump to delayloop 2 if r14 doesn't equal zero(2 cycles)
;            jmp     delayloop1             	; jump to delayloop1 (2 cycles)
;											; delayloop2 takes 3 cycles to complete
;
;											; Using the preceding code, the equation to figure out clock time is as follows
;											; (Section titles (i.e. mainloop) represent the # of cycles it takes to complete the section):
;											; mainloop+(delayloop1*delay1)+(delayloop2*delay2*delay1)+(2*delay1)
;											; The result of the above equation is then divided by the number of seconds
;											; it takes to complete one blink. This will yield the clock speed of the processor.
;											; As of now, I believe my MSP430-F2013 processor to run at around 1143316 hertz (or 1.1 MHz).
;
;
;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
;            .sect   ".reset"                ; MSP430 RESET Vector
;            .short  RESET                   ; start address
;            .end