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
myCLOCK .set    8000000                 ; 1.2 Mhz clock
WDT_CLK .set    32000                   ; 32 khz clock (@1 Mhz)
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
                              
;*******************************************************************************
;    code section
;
        .text                           ; code Section
; Initialize ports, timers, system clock, and random number generator. 
reset:  mov.w   #STACK,SP               ; Initialize stack pointer
										;  MSP430 Clock - Set DCO to 12 MHz:
     	mov.b   &CALBC1_8MHZ,&BCSCTL1  ; Set range
     	mov.b   &CALDCO_8MHZ,&DCOCTL   ; Set DCO step + modulation
        
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
        call    #outLEDtone             ; y, output LED/tone
;    << check for correct switch pressed >>
        sub.w   #1,r15                 ; done?
          jne   switchLoop             ; n, keep going

;    If all the LEDs/tones are correctly reproduced in the correct order, output
;    some congratulatory tune (such as "charge!") and restart the game with one
;    more LED/tone added to the sequence. 

        call    #success                ; y
        add.w   #1,&matchCnt            ; add 1 more tone to sequence
        call    #delay                  ; delay
        call    #delay                  ; delay
        jmp     startGame

;    Otherwise, immediately output a raspberry sound and restart the game with
;    a four LED/tone sequence

switchLoop2:
        call    #failure                ; failure
        jmp     restartGame             ; start over

;*******************************************************************************

success:        ; << ADD CODE FOR CONGRATULATORY DITTY >>
failure:        ; << ADD CODE FOR RASPBERRY SOUND >>
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
        mov.b   &P2IN,r4                ; wait for a switch
        and.b   #0x0f,r4
        xor.b   #0x0f,r4                ; any switch?
          jeq   getSwitch               ; n
        ret                             ; y, return


;*******************************************************************************
;    new game
;
newGame:
        LED1_OFF                        ; turn off all LEDs
        LED2_OFF
        LED3_OFF
        LED4_OFF
        ret


;*******************************************************************************
;    output LED/tone
;
outLEDtone:
        LED1_ON                         ; turn on LED #1
        call    #toneON                 ; output tone
        call    #delay
        LED1_OFF                        ; turn off LED #1
        call    #toneOFF
        ret


;*******************************************************************************
;    enable/disable tone
;
DEMO_TONE   .set    4000                ; buzzer tone

toneON:
        mov.w   #DEMO_TONE/2,&TBCCR2    ; use TBCCR2 as 50% duty cycle
        mov.w   #DEMO_TONE,&TBCCR0      ; start clock
        ret

toneOFF:
        mov.w   #0,&TBCCR0              ; Timer B off
        ret


;*******************************************************************************
;    software delay
;
DELAY_CNT .set 2                        ; delay count

delay:  push    r14
        push    r15
        mov.w   #DELAY_CNT,r15          ; get delay count
        mov.w   #0,r14                  ; x 65536

delay2: add.w   #1,r14                  ; minor loop done?
          jne   delay2                  ; n
        sub.w   #1,r15                  ; y, major loop done?
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
        bis.b   #0x40,&P4DIR            ; LED_4 P4.6
        bic.b   #0x40,&P4OUT 
        bis.b   #0x08,&P3DIR            ; LED_3 P3.3
        bic.b   #0x08,&P3OUT
        bic.b   #0xc0,&P2SEL            ; LED_2 (P2.7) & LED_1 (P2.6)
        bis.b   #0xc0,&P2DIR
        bic.b   #0xc0,&P2OUT

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
