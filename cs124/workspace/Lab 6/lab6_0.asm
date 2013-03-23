        .list
        .title    "simon.asm"
;*******************************************************************************
;   MSP430F2274 Simon
;
;   Description:
;
;      "Write a MSP430 assembly language program to play the game of Simon. Each
;      round of the game is started by flashing the LEDs several times. The
;      colored LEDs (along with the associated tones) are then flashed one at a
;      time in a random sequence. Sample the push button switches and count the
;      number of colors (tones) correctly entered in the same order as the
;      original sequence. Continue until the end of the sequence is reached or a
;      mistake is made. Play some congratulatory tune if the sequence is correct
;      or some raspberry sound if a mistake is made. If the sequence is
;      successfully reproduced, restart the game adding one more color/tone to
;      the sequence. Use Timer_B output (TB2) for hardware PWM of the transducer
;      (magnetic buzzer)." 
;
;    Bonus':
;
;      -Depressing the button on the eZ430-RF2500 board (P1.2) restarts your
;       program.
;      -Use Port 2 interrupts to detect a depressed switch.
;
;   **NOTE: ALL subroutines must be correctly implemented using Callee-Save
;           protocol!  (Some are not in this example program!)
;
;   ACLK = n/a, MCLK = SMCLK = TACLK = default DCO ~1.2MHz
;
;   Author:	Paul Roper, Brigham Young University
;           January 2010
;
;   Built with Code Composer Essentials Version: 3.2
;*******************************************************************************
;
;       A  P4.4     Left Pot  O--O  O  Servo #1
;       B  P4.5       Buzzer  O--O  O  Servo #2
;       C  P4.6   Thermistor  O  O--O  LED_4
;       D  P2.3  ADXL345 INT  O  O--O  SW_3
;       E  P2.4         SW_4  O--O  O  Servo #3 
;       F  P2.2    Backlight  O--O  O  Servo #4
;       G  P4.3    Right Pot  O--O  O  EZ0_AN
;       H  P2.1         SW_2  O--O  O  EZ0_TX
;
;                       MSP430F2274
;                    -----------------
;                   |         XIN P2.6|-->LED_1
;                   |        XOUT P2.7|-->LED_2
;                   |                 |
;         RED LED-->|P1.0         P2.0|<--SW_1 (pull-up)
;       GREEN LED-->|P1.1         P2.1|<--SW_2 (pull-up)
;    eZ430 BUTTON-->|P1.2         P2.2|<--SW_3 (pull-up)
;                   |             P2.3|<--SW_4 (pull-up)
;                   |                 |
;                   |             P3.3|-->LED_3
;                   |             P4.6|-->LED_4
;                   |                 |
;                   |             P4.5|-->BUZZER (P4SEL.5=1)
;
;    Define some LED macros
;    (See slau131b - MSP430 Assembly Language Tools v 3.0.pdf, page 67)
    .asg "bis.b    #0x40,&P4OUT",LED4_ON
    .asg "bic.b    #0x40,&P4OUT",LED4_OFF

    .asg "bis.b    #0x08,&P3OUT",LED3_ON
    .asg "bic.b    #0x08,&P3OUT",LED3_OFF

    .asg "bis.b    #0x80,&P2OUT",LED2_ON
    .asg "bic.b    #0x80,&P2OUT",LED2_OFF

    .asg "bis.b    #0x40,&P2OUT",LED1_ON
    .asg "bic.b    #0x40,&P2OUT",LED1_OFF
;
;    PWM (Tones):
;    Clock speeds:       MMB pgs. 167-170
;    Switch debounce:    MMB pgs. 225-238
;    Ports:              MMB pgs. 207-224
;    PWM:                MMB pgs. 287-289, 296-300, 330-349
;                        slau144e - MSP430x2xx Family User's Guide.pdf, Chapter 12
;                        slau144e - MSP430x2xx Family User's Guide.pdf, Chapter 12
;
;*******************************************************************************
        .nolist
        .cdecls    C,LIST,"msp430x22x4.h"
        .list

;*******************************************************************************
;    CONSTANTS
;
myCLOCK .set    8000000                 ; 8 Mhz clock
WDT_CLK .set    32000	                ; 32 khz clock (@8 Mhz)
WDT_CTL .set    WDT_MDLY_32             ; WDT SMCLK, 32 ms
WDT_CPS .set    myCLOCK/WDT_CLK         ; WD clocks / second count
;
STACK   .set    0x0600                  ; top of stack
NTONES  .set    4                       ; # of start tones
SEED    .set    21845                   ; arbitrary random seed (65536/3)

;*******************************************************************************
;    external references
;
        .ref    initRand16              ; init random # generator
        .ref    rand16                  ; get 16-bit random #
        .ref    setRandSeed             ; set random # seed
        .ref    getRandSeed             ; get current random # seed

;*******************************************************************************
;    data section
;
        .bss    gameSeed,2              ; random seed
        .bss    WDTSecCnt,2             ; WDT second counter
        .bss    matchCnt,2              ; match counter
        .bss	whichLEDTone,2			; which LED and tone to trip
        .bss	whichSwitch,2			; which Switch got tripped
                              
;*******************************************************************************
;    code section
;
        .text                           ; code Section
; Initialize ports, timers, system clock, and random number generator. 
reset:  mov.w   #STACK,SP               ; Initialize stack pointer
										
										; MSP430 Clock - Set DCO to 8 MHz:
     	mov.b   &CALBC1_8MHZ,&BCSCTL1  	; Set range
     	mov.b   &CALDCO_8MHZ,&DCOCTL   	; Set DCO step + modulation
     	
        call    #eZ430X_init            ; initialize board
        call    #initGame               ; initialize game
        bis.w   #GIE,SR                 ; enable interrupts

restartGame:                            ; start/restart game of simon
        call    #initRand16             ; Initialize generator
        mov.w   #NTONES,&matchCnt       ; init starting # of tones counter

;    Begin your game of Simon by rapidly flashing all four LEDs several times. 
;    Start with a four LED/tone sequence. 

startGame:
        call    #newGame                ; start new game (w/some ditty)
        call    #saveRandomSeed         ; save random seed to check against
        mov.w   &matchCnt,r15           ; init # of tones counter
   
;    After a short pause, individually flash the LEDs (and associated tones) one
;    at a time in a random sequence. 

LEDtones:
        call    #rand16                 ; get random # (returned in r12)
        call	#refineRand				; refine number down to between 1-4 and place in whichLEDTone
        call    #outLEDtone             ; output LED/tone
        call    #delay                  ; delay
        sub.w   #1,r15                  ; done?
          jne   LEDtones                ; n

;    reset, get user switch responses

        call    #restoreRandomSeed      ; y, start again with restored seed
        mov.w   &matchCnt,r15           ; and counter
   
;    At the completion of the above sequence, sample the push bottom switches
;    and output the corresponding LED/tone as each button is pressed. 
;    Continue sampling and comparing the push button sequence with the computer
;    generated sequence until either the end of the sequence is reached or a
;    mistake is made. 

switchLoop:
        call    #rand16                 ; get random # (returned in r12)
        call    #getSwitch              ; wait for switch
        mov.w	&whichSwitch,&whichLEDTone	; play LED/Tone of corresponding switch
        call    #outLEDtone
        call	#refineRand				; refine number down to between 1-4 and place in whichLEDTone
        cmp.w	&whichSwitch,&whichLEDTone	; pressed switch same as the correct LEDTone?
          jne	switchLoop2				; no
        sub.w   #1,r15                 ; done with pattern yet?
          jne   switchLoop             ; nope, keep going


        call    #success                ; pattern done
        add.w   #1,&matchCnt            ; add 1 more tone to sequence
        call    #delay                  ; delay
        jmp     startGame				; start new game with new sequence


switchLoop2:
        call    #failure                ; failure
        call    #delay                  ; delay
        jmp     restartGame             ; start over at four tone pattern

;*******************************************************************************

success:        ; CONGRATULATORY DITTY
		call	#delay
		call	#toneWin
		call	#delay
		call	#toneOFF
		ret

failure:		; RASPBERRY SOUND
		call	#delay
		call	#toneRAZZ
		call	#delay
		call	#toneOFF
        ret


;*******************************************************************************
;    initialize game
;
initGame:
;        Set Watchdog interval
        mov.w   #WDT_CTL,&WDTCTL        ; Set Watchdog interrupt interval
        mov.w   #WDT_CPS,&WDTSecCnt
        mov.b   #WDTIE,&IE1             ; Enable WDT interrupt

;        eZ430X buzzer (use Timer B to PWM buzzer)
        clr.w   &TBR                    ; Timer B SMCLK, /1, up mode
        mov.w   #TBSSEL_2+ID_0+MC_1,&TBCTL
        bis.b   #0x20,&P4DIR            ; P4.5 output (buzzer)
        bis.b   #0x20,&P4SEL            ; P4.5 uses alternate function (TB2)
        mov.w   #OUTMOD_3,&TBCCTL2      ; output mode = set/reset

;        reset random seed
        mov.w   #SEED,r12               ; get good seed
        call    #setRandSeed            ; set current random seed
        ret


;*******************************************************************************
;    save random seed
;
saveRandomSeed:
        push    r12
        call    #getRandSeed            ; get current random seed
        mov.w   r12,&gameSeed           ; save random seed
        pop     r12
        ret


;*******************************************************************************
;    restore random seed
;
restoreRandomSeed:
        push    r12
        mov.w   &gameSeed,r12           ; reset random seed
        call    #setRandSeed
        pop     r12
        ret


;*******************************************************************************
;    wait for switch to be pressed
;
getSwitch:
        push	r4

switchCheck:        
        mov.b   &P2IN,r4                ; wait for a switch
        and.b   #0x0f,r4
        xor.b   #0x0f,r4                ; any switch?
          jeq   switchCheck             ; n
        
        bic.w	#0xffff,&whichSwitch	; empty out whichSwitch variable
        cmp.w	#1,r4
          jeq	switchPress_1
        cmp.w	#2,r4
          jeq	switchPress_2
        cmp.w	#4,r4
          jeq	switchPress_3
        cmp.w	#8,r4
          jeq	switchPress_4
        
        xor.b   #0x0f,r4                ; any switch?
          jeq   getSwitch               ; n
        ret                             ; y, return

switchPress_1:
		mov.w	#0,&whichSwitch
		  jmp	switchDone
switchPress_2:
		mov.w	#1,&whichSwitch
		  jmp	switchDone
switchPress_3:
		mov.w	#2,&whichSwitch
		  jmp	switchDone
switchPress_4:
		mov.w	#3,&whichSwitch

switchDone:
		bis.b	#0x0f,&P2IN
		call	#quarterDelay
		pop		r4
		ret
		
;*******************************************************************************
;    new game
;
newGame:
        LED1_ON                 ; turn on all LEDs
        LED2_ON
        LED3_ON
        LED4_ON
        
        call	#delay
        
        call	#toneON_1		; plays an intro ditty with flashing lights
        LED1_OFF
        call	#delay
        
        call	#toneON_3
        LED1_ON
        LED3_OFF
        call	#halfDelay
        
        call	#toneON_2
        LED3_ON
        LED2_OFF
        call	#halfDelay
        
        call	#toneON_4
        LED2_ON
        LED4_OFF
        call	#delay
        
        call	#toneON_1
        LED4_ON
        LED1_OFF
        call	#halfDelay
        
        call	#toneON_3
        LED1_ON
        LED3_OFF
        call	#halfDelay
        
        call	#toneON_4
        LED3_ON
        LED4_OFF
        call	#delay
        
        call	#toneOFF
        
        LED1_OFF				; turn off all LEDs
        LED2_OFF
        LED3_OFF
        LED4_OFF
        
        call	#delay			; delay before start of game
        call	#delay
        call	#delay
        call	#delay
        
        ret						; return

;*******************************************************************************
; refine number down to between 1-4 and place in whichLEDTone

refineRand:
		bic.w	#0xffff,&whichLEDTone		
		mov.w	r12,&whichLEDTone
		bic.w	#0xfffc,&whichLEDTone		
		ret

;*******************************************************************************
;    output LED/tone
;
outLEDtone:

		cmp.w	#0,whichLEDTone
		  jeq	outLEDtone_1
		cmp.w	#1,whichLEDTone
		  jeq	outLEDtone_2
		cmp.w	#2,whichLEDTone
		  jeq	outLEDtone_3
		cmp.w	#3,whichLEDTone
		  jeq	outLEDtone_4

outLEDtone_1:
        LED1_ON                         ; turn on LED #1
        call    #toneON_1               ; output tone
        call    #delay
        LED1_OFF                        ; turn off LED #1
        call    #toneOFF
        ret

outLEDtone_2:
        LED2_ON                         ; turn on LED #2
        call    #toneON_2               ; output tone
        call    #delay
        LED2_OFF                        ; turn off LED #2
        call    #toneOFF
        ret

outLEDtone_3:
        LED3_ON                       ; turn on LED #3
        call    #toneON_3                 ; output tone
        call    #delay
        LED3_OFF                        ; turn off LED #3
        call    #toneOFF
        ret

outLEDtone_4:
        LED4_ON                         ; turn on LED #4
        call    #toneON_4               ; output tone
        call    #delay
        LED4_OFF                        ; turn off LED #4
        call    #toneOFF
        ret                


;*******************************************************************************
;    enable/disable tone
;
LOW_TONE	.set    16000				; low frequency buzzer tone

; chromatic scale (12 just intonation intervals)
C4      .set    myCLOCK*1000/261626      ; C  (261.626 Hz)
CS4     .set    C4*15/16                 ; C# (minor 2nd)
D4      .set    C4*8/9                   ; D  (major 2nd)
DS4     .set    C4*5/6                   ; D# (minor 3rd)
E4      .set    C4*4/5                   ; E  (major 3rd)
F4      .set    C4*3/4                   ; F  (perfect 4th)
FS4     .set    C4*5/7                   ; F# (diminished 5th)
G4      .set    C4*2/3                   ; G  (perfect 5th)
GS4     .set    C4*5/8                   ; G# (minor 6th)
A4      .set    C4*3/5                   ; A  (major 6th)
AS4     .set    C4*4/7                   ; A# (minor 7th)
B4      .set    C4*8/15                  ; B  (major 7th)
C5      .set    C4*1/2                   ; C  (perfect octave)
C6      .set    C5*1/2                   ; C  (perfect octave)
C7      .set    C6*1/2                   ; C  (perfect octave)	

;toneON:
;        mov.w   #LOW_TONE/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
;        mov.w   #LOW_TONE,&TBCCR0      	; start clock
;        ret

toneON_1:
        mov.w   #C4/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
        mov.w   #C4,&TBCCR0      	; start clock
        ret

toneON_2:
        mov.w   #D4/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
        mov.w   #D4,&TBCCR0      	; start clock
        ret

toneON_3:
        mov.w   #E4/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
        mov.w   #E4,&TBCCR0      	; start clock
        ret

toneON_4:
        mov.w   #G4/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
        mov.w   #G4,&TBCCR0      	; start clock
        ret

toneRAZZ:
		push	r13
		
		mov.w	#8,r13
		mov.w   #C4/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
        mov.w   #C4,&TBCCR0      	; start clock
        
Raz_01:
		add.w  	#2000,&TBCCR2
		add.w	#4000,&TBCCR0
		call	#quarterDelay
		dec.w	r13
		  jnz	Raz_01
        
        pop		r13
        ret

toneWin:
		LED2_ON
		LED3_ON
		LED4_ON
		
		mov.w   #D4/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
        mov.w   #D4,&TBCCR0      	; start clock
        call	#delay
		
		LED1_ON
		LED2_OFF
		mov.w   #C4/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
        mov.w   #C4,&TBCCR0      	; start clock
        call	#halfDelay
		
		LED2_ON
		LED3_OFF
		mov.w   #D4/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
        mov.w   #D4,&TBCCR0      	; start clock
        call	#delay
        
        LED3_ON
        LED4_OFF
		mov.w   #E4/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
        mov.w   #E4,&TBCCR0      	; start clock
        call	#delay
        
        LED4_ON
        LED1_OFF
		mov.w   #A4/2,&TBCCR2    	; use TBCCR2 as 50% duty cycle
        mov.w   #A4,&TBCCR0      	; start clock
        call	#delay
        call	#delay
        
        LED1_OFF
        LED2_OFF
        LED3_OFF
        LED4_OFF
        
        ret

toneOFF:
        mov.w   #0,&TBCCR0              ; Timer B off
        ret


;*******************************************************************************
;    software delay
;
DELAY_CNT 	.set 16                        	; delay count
DELAY_CNT2	.set myCLOCK/24					; 1/24 of a second

delay:  push    r14
        push    r15
        
        mov.w   #DELAY_CNT,r15          ; set delay
        mov.w   #0,r14                  ; x 65536
          jmp	delay2

halfDelay:  
		push    r14
        push    r15
        
        mov.w   #DELAY_CNT/2,r15        ; set half delay
        mov.w   #0,r14                  ; x 65536
          jmp	delay2
		
quarterDelay:  
		push    r14
        push    r15
        
        mov.w   #DELAY_CNT/4,r15         ; set quarter delay
        mov.w   #DELAY_CNT2,r14         ; 
          jmp	delay2

delay2: dec.w   r14                  ; minor loop done?
          jne   delay2                  ; n
        dec.w   r15                  ; y, major loop done?
          jne   delay2                  ; n
        pop     r15
        pop     r14
        ret                             ; y, return


;*******************************************************************************
;    General initialization of eZ430X board
;
;                       MSP430F2274
;                    -----------------
;                /|\|         XIN P2.6|-->LED_1
;                 | |        XOUT P2.7|-->LED_2
;                 --|RST              |
;                   |                 |
;         RED LED-->|P1.0         P2.0|<--SW_1 (pull-up)
;       GREEN LED-->|P1.1         P2.1|<--SW_2 (pull-up)
;    eZ430 BUTTON-->|P1.2         P2.2|<--SW_3 (pull-up)
;                   |             P2.3|<--SW_4 (pull-up)
;                   |             P2.4|-->LCD BACKLIGHT
;                   |                 |
;                   |             P2.6|-->LED_1
;                   |             P2.7|-->LED_2
;                   |             P3.3|-->LED_3
;                   |             P4.6|-->LED_4
;                   |                 |
;                   |             P4.5|-->BUZZER (P4SEL.5=1)
;
eZ430X_init:
        mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

;        LCD Reset
        bis.b   #0x01,&P3DIR            ; LCD Reset
        bic.b   #0x01,&P3OUT
        bis.b   #0x01,&P3OUT

;        eZ430 LED's
        bis.b   #0x03,&P1DIR            ; eZ430 LED's
        bic.b   #0x03,&P1OUT

;        eZ430 push button
        bic.b   #0x04,&P1DIR            ; eZ430 push button
        bis.b   #0x04,&P1IE             ; Interrupt Enable in P1.2
        bis.b   #0x04,&P1IES            ; P1.2 Interrupt on H-L transition
        bic.b   #0x04,&P1IFG            ; P1.2 IFG Cleared
        bis.b   #0x04,&P1REN            ; P1.2 Pull-Up/Down Resistor enable

;        eZ430X push buttons
        bic.b   #0x0f,&P2SEL            ; eZ430X push buttons
        bic.b   #0x0f,&P2DIR            ; Configure P2.0-3 as Inputs
        bis.b   #0x0f,&P2OUT            ; pull-ups
        bis.b   #0x0f,&P2IES            ; h to l
        bis.b   #0x0f,&P2REN            ; Enable pull-ups

;        eZ430X LEDs
        bis.b   #0x40,&P4DIR            ; LED_4 P4.6 enabled
        bic.b   #0x40,&P4OUT			; initially turned to off  
        bis.b   #0x08,&P3DIR            ; LED_3 P3.3 enabled
        bic.b   #0x08,&P3OUT			; initially turned to off
        bic.b   #0xc0,&P2SEL            ; LED_2 (P2.7) & LED_1 (P2.6) enabled
        bis.b   #0xc0,&P2DIR			
        bic.b   #0xc0,&P2OUT			; initially turned to off

        ret


;*******************************************************************************
;        Interrupt Service Routines
;*******************************************************************************
;    Port 2 (switches) ISR
;
P2_ISR:
        reti


;*******************************************************************************
;    Watchdog Timer ISR
;
WDT_ISR:
        dec.w   &WDTSecCnt              ; decrement counter, 0?
          jne   WDT_04                  ; n
        mov.w   #WDT_CPS,&WDTSecCnt     ; y, re-initialize counter
        xor.b   #0x01,&P1OUT            ; toggle P1.0

WDT_04: reti                            ; return from interrupt


;*******************************************************************************
;        Interrupt Vectors
;*******************************************************************************

        .sect   ".int03"                ; P2 (switches) vector section
        .word   P2_ISR                  ; address of P2 ISR

        .sect   ".int10"                ; WDT vector section
        .word   WDT_ISR                 ; address of WDT ISR

        .sect   ".reset"                ; reset vector section
        .word   reset                   ; address of reset
        .end
