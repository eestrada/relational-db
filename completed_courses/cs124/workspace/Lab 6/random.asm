 	.title	"random.asm"
;*******************************************************************************
;   MSP430F2274 random.asm
;
;   Description:
;
;  June 2009
;  Built with Code Composer Essentials Version: 3.1
;*******************************************************************************
		.cdecls	C,LIST,"msp430x22x4.h"

;------------------------------------------------------------------------------
;	external references
;
		.def	initRand16			; init random # generator
		.def	rand16				; get 16-bit random #
		.def	setRandSeed			; set random # seed
		.def	getRandSeed			; get current random # seed

;------------------------------------------------------------------------------
; INITIALIZATION CONSTANTS FOR RANDOM NUMBER GENERATION
;
SEED	.set	21845				; Arbitrary seed value (65536/3)
MULT	.set	31821				; Multiplier value (last 3 Digits are even21)
INC		.set	13849				; 1 and 13849 have been tested


;------------------------------------------------------------------------------
		.data						; Data Section
;------------------------------------------------------------------------------
		.bss	RandSeed,2			; random seed

;------------------------------------------------------------------------------
		.text						; Program Section
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; SUBROUTINE: INITIALIZE RANDOM NUMBER GENERATOR:
;
;	IN:		r12 = random seed
;
initRand16:
		push	r4
;		mov.w	r12,RandSeed		; init seed
		mov.w	#20,r4

init_01:
		call	#rand16				; get random #
		dec.w	r4
		  jne	init_01
		pop		r4
		ret

;------------------------------------------------------------------------------
; SUBROUTINE: SET RANDOM SEED

setRandSeed:
		mov.w	r12,RandSeed		; set seed
		ret


;------------------------------------------------------------------------------
; SUBROUTINE: GET RANDOM SEED

getRandSeed:
		mov.w	RandSeed,r12		; return seed
		ret
		

;------------------------------------------------------------------------------
; SUBROUTINE: GENERATES NEXT RANDOM NUMBER
;
;	OUT:	r12 = 0-32767
;			random seed updated
;
rand16:
		push	r4					; save registers
		push	r5
		push	r6
		push	r7

		mov.w	RandSeed,r5			; Prepare multiplication
		mov.w	#MULT,r4			; Prepare multiplication
		call	#MPYU				; Call unsigned MPY (5.1.1)
		add.w	#INC,r7				; Add INC to low word of product
		mov.w	r7,RandSeed			; Update RandSeed
		mov.w	r7,r12				; return in r12
		swpb	r12

		pop		r7					; restore registers
		pop		r6
		pop		r5
		pop		r4
		ret							; Random number in Rndnum


;------------------------------------------------------------------------------
; Integer Subroutines Definitions: Software Multiply
; See SLAA024 - MSP430 Family Mixed-Signal Microcontroller Application Reports
;
; UNSIGNED MULTIPLY: r4 x r5 > r6|r7
;
MPYU:	clr.w	r7					; 0 > LSBs RESULT
		clr.w	r6					; 0 > MSBs RESULT

; UNSIGNED MULTIPLY AND ACCUMULATE: (r4 x r5) + r6|r7 > r6|r7
;
MACU:	push	r8
		clr.w	r8					; MSBs MULTIPLIER

L$01:	bit.w	#1,r4				; TEST ACTUAL BIT 5-4
		  jz	L$02				; IF 0: DO NOTHING
		add.w	r5,r7				; IF 1: ADD MULTIPLIER TO RESULT
		addc.w	r8,r6

L$02:	rla.w	r5					; MULTIPLIER x 2
		rlc.w	r8					;
		rrc.w	r4					; NEXT BIT TO TEST
		  jnz	L$01				; IF BIT IN CARRY: FINISHED

L$03:	pop		r8
		ret

		.end
