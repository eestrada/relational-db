			.title	"Lab 4 - morse.asm"
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

END         .set    0
DOT         .set    1
DASH        .set    2
SPACE       .set    3
                            
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
            .data                       ; data section
            .bss    cnt,2               ; ISR counter
                            
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
            .text                       ; program section
RESET:      mov.w   #STACK,SP           ; initialize stack pointer
            mov.w   #WDT_MDLY_0_5,&WDTCTL   ; set Watchdog interval to ~0.5ms
            mov.b   #WDTIE,&IE1         ; enable WDT interrupt
            bis.b   #0x01,&P1DIR        ; P1.0 output
            bis.b   #0x20,&P4DIR        ; P4.5 output

            mov.w   #COUNT,&cnt         ; initialize counter
            bis.w   #LPM0+GIE,SR        ; enter LPM0 w/ interrupt
            jmp     $                   ; loop forever - interrupts do all

message:    .byte   DOT,DASH,DASH,DOT,END   ; P
            .byte   DOT,DASH,END            ; A
            .byte   DOT,DASH,DOT,END        ; R
            .byte   DOT,DOT,END             ; I
            .byte   DOT,DOT,DOT,END         ; S
            .byte   SPACE                   ; space
            .byte   END                     ; end of word/message
            .align  2

;------------------------------------------------------------------------------
;   Watchdog Timer interrupt service routine
;
WDT_ISR:    bit.w   #0x0200,&cnt        ; buzzer?
              jeq   WDT$01              ; n
            xor.b   #0x20,&P4OUT        ; y, PWM buzzer

WDT$01:     dec.w   &cnt                ; decrement counter, 0?
              jne   WDT$02              ; n
            mov.w   #COUNT,&cnt         ; y, re-initialize counter
            xor.b   #0x01,&P1OUT        ; toggle P1.0

WDT$02:     reti                        ; return from interrupt

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".int10"            ; MSP430 RESET Vector
            .word   WDT_ISR             ; Watchdog ISR

            .sect   ".reset"            ; MSP430 RESET Vector
            .word   RESET               ; Power Up ISR
            .end
