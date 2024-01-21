; Unfortunately we have not YET installed Windows or Linux on the LC-3,
; so we are going to have to write some operating system code to enable
; keyboard interrupts. The OS code does three things:
;
;    (1) Initializes the interrupt vector table with the starting
;        address of the interrupt service routine. The keyboard
;        interrupt vector is x80 and the interrupt vector table begins
;        at memory location x0100. The keyboard interrupt service routine
;        begins at x1000. Therefore, we must initialize memory location
;        x0180 with the value x1000.
;    (2) Sets bit 14 of the KBSR to enable interrupts.
;    (3) Pushes a PSR and PC to the system stack so that it can jump
;        to the user program at x3000 using an RTI instruction.

            .ORIG   x800
            ; (1) Initialize interrupt vector table.
            LD      R0, VEC
            LD      R1, ISR
            STR     R1, R0, #0
    
            ; (2) Set bit 14 of KBSR.
            LDI     R0, KBSR
            LD      R1, MASK
            NOT     R1, R1
            AND     R0, R0, R1
            NOT     R1, R1
            ADD     R0, R0, R1
            STI     R0, KBSR
    
            ; (3) Set up system stack to enter user space.
            LD      R0, PSR
            ADD     R6, R6, #-1
            STR     R0, R6, #0
            LD      R0, PC
            ADD     R6, R6, #-1
            STR     R0, R6, #0
            ; Enter user space.
            RTI
        
VEC         .FILL   x0180
ISR         .FILL   x1000
KBSR        .FILL   xFE00
MASK        .FILL   x4000
PSR         .FILL   x8002
PC          .FILL   x3000
            .END


            .ORIG   x3000
            ;Print the ID continuosly
LOOPPRINT   ;R3 is the signal to check whether to stop circulation
            ADD     R3, R3, #0
            BRp     CONTINUE
            LEA     R0, ID          ;print the ID
            PUTS
            LD      R1, DELAY       ;the leap between printings (to avoid printing too fast)
WAIT        ADD     R1, R1, #-1
            BRp     WAIT
            BRnzp   LOOPPRINT
            
            ;Finally to output the answer
CONTINUE    LD      R4, LOCA_N      ;read the memory of the N we store before
            LDR     R0, R4, #0
            ADD     R4, R0, R4
            LDR     R1, R4, #1      ;R1 is the location of the N!
            LD      R4, ASCII       ;there is a leap between a number and its ASCII code
            ADD     R2, R0, #-7     ;Check if N is bigger than 7
            BRp     OVER
            ADD     R0, R0, R4
            OUT
            LEA     R0, ANSWER
            PUTS
            ADD     R0, R1, #0
            PUTS
            BRnzp   FINALL
            
OVER        ADD     R0, R0, R4
            OUT
            LEA     R0, TOO_MUCH
            PUTS

FINALL      HALT
            
            
ID          .STRINGZ    " PB22051082"
DELAY       .FILL   #2500
ASCII       .FILL   #48
LOCA_N      .FILL   x3FFF
ANSWER      .STRINGZ    "! = "
TOO_MUCH    .STRINGZ    " is too large for LC3"
            .END



            .ORIG   x3FFF
            ; *** Begin factorial data here ***
FACT_N      .FILL   xFFFF           ;the location to store N
            .FILL   x4008   ;0!
            .FILL   x400A   ;1!
            .FILL   x400C   ;2!
            .FILL   x400E   ;3!
            .FILL   x4010   ;4!
            .FILL   x4013   ;5!
            .FILL   x4017   ;6!
            .FILL   x401B   ;7!
LOCA_0      .STRINGZ    "1"
LOCA_1      .STRINGZ    "1"
LOCA_2      .STRINGZ    "2"
LOCA_3      .STRINGZ    "6"
LOCA_4      .STRINGZ    "24"
LOCA_5      .STRINGZ    "120"
LOCA_6      .STRINGZ    "720"
LOCA_7      .STRINGZ    "5040"
            ; *** End factorial data here ***
            .END



            .ORIG   x1000
            
            ;If the keyboard has a new character
            LD      R1, KBDR
            LDR     R0, R1, #0
            ADD     R5, R0, #0      ;store R0 in R5 temperaly
            ;Check if the input character is not a decimal digit
            LD      R1, LOWER_LIMIT ;the upper limit
            LD      R2, UPPER_LIMIT ;the lower limit
            ADD     R3, R0, R1
            BRn     ND
            ADD     R4, R0, R2
            BRp     ND      
            
            ;Show the hint on the console
            AND     R0, R0, #0 
            ADD     R0, R0, #10
            OUT                     ;a line feed (for more tidy output)
            ADD     R0, R5, #0      ;get R0 back
            OUT
            LEA     R0, IS_DECIMAL
            PUTS
            ;Store or change some important parameter
            AND     R3, R3, #0
            ADD     R3, R3, #1      ;R3 is the pointer to determine whether to continue to loop
            LD      R4, N_LOCA
            ADD     R0, R5, R1
            STR     R0, R4, #0      ;store N in x3FFF
            BRnzp   LINE_FEED
            
ND          AND     R0, R0, #0 
            ADD     R0, R0, #10
            OUT                     ;a line feed
            ADD     R0, R5, #0
            OUT
            LEA     R0, NOT_DECIMAL
            PUTS
            AND     R3, R3, #0
LINE_FEED   AND     R0, R0, #0
            ADD     R0, R0, #10
            OUT

            RTI

KBDR        .FILL   xFE02
LOWER_LIMIT .FILL   #-48
UPPER_LIMIT .FILL   #-57
NOT_DECIMAL .STRINGZ    " is not a decimal digit."
IS_DECIMAL  .STRINGZ    " is a decimal digit."
N_LOCA      .FILL   x3FFF
            .END