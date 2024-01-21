        .ORIG x3000
;main function
        LDI R1, NLOCA   ;R1 stores n
        LD  R3, NLOCA   ;R3 stores the destination of the output
        ADD R3, R3, #1
        JSR REMOVE
        TRAP x25
;remove function
REMOVE  ADD R6, R6, #-1
        STR R7, R6, #0  ;push R7 into stack
        ADD R2, R1, #-1 ;if n == 1
        BRz REMO1
        ADD R2, R1, #0  ;if n == 0
        BRz REMO0
        ADD R1, R1, #-2
        JSR REMOVE      ;R(n-2)
        ADD R1, R1, #2  ;get n back
        AND R4, R4, #0
        ADD R4, R4, #1  ;R4 = 1
        ADD R5, R1, #0  ;R5 = n
REMON   ADD R5, R5, #-1 ;circulate until R5 == 0
        BRz GOONR
        ADD R4, R4, R4  ;R4 = R4 * 2
        BRnzp REMON
GOONR   ADD R0, R0, R4  ;remove the nth ring
        STR R0, R3, #0  ;store the state
        ADD R3, R3, #1
        ADD R1, R1, #-2
        JSR PUT         ;P(n-2)
        ADD R1, R1, #1
        JSR REMOVE      ;R(n-1)
        ADD R1, R1, #1  ;get n back
        BRnzp REMO0     ;end R(n)
REMO1   LDR R7, R6, #0  
        ADD R6, R6, #1  ;pop the R7
        ADD R0, R0, #1  ;remove the 1st ring
        STR R0, R3, #0  ;store the state
        ADD R3, R3, #1
        RET
REMO0   LDR R7, R6, #0  
        ADD R6, R6, #1  ;pop the R7
        RET             ;do nothing

;put function
PUT     ADD R6, R6, #-1
        STR R7, R6, #0  ;push R7 into stack
        ADD R2, R1, #-1 ;if n == 1
        BRz PUT1
        ADD R2, R1, #0  ;if n == 0
        BRz PUT0
        ADD R1, R1, #-1
        JSR PUT         ;P(n-1)
        ADD R1, R1, #-1
        JSR REMOVE      ;R(n-2)
        ADD R1, R1, #2  ;get n back
        AND R4, R4, #0
        ADD R4, R4, #1  ;R4 = 1
        ADD R5, R1, #0  ;R5 = n
PUTN    ADD R5, R5, #-1 ;circulate until R5 == 0
        BRz GOONP
        ADD R4, R4, R4  ;R4 = R4 * 2
        BRnzp PUTN
GOONP   NOT R4, R4
        ADD R4, R4, #1  ;R4 = -R4
        ADD R0, R0, R4  ;put the nth ring
        STR R0, R3, #0  ;store the state
        ADD R3, R3, #1
        ADD R1, R1, #-2
        JSR PUT         ;P(n-2)
        ADD R1, R1, #2  ;get n back
        BRnzp PUT0      ;end P(n)
PUT1    LDR R7, R6, #0  
        ADD R6, R6, #1  ;pop the R7
        ADD R0, R0, #-1 ;put the 1st ring
        STR R0, R3, #0  ;store the state
        ADD R3, R3, #1
        RET
PUT0    LDR R7, R6, #0  
        ADD R6, R6, #1  ;pop the R7
        RET             ;do nothing
        
NLOCA   .FILL x3100
.END