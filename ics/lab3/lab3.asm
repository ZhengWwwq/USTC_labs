            .ORIG x3000
;
;Initialize
;
            LD  R1, S1_ADDR ;store the address of an character of s1
            LD  R2, S2_ADDR ;store the address of an character of s2
;
;Circulation
;
LOAD        LDR R3, R1, #0  ;store the num of an character of s1
            LDR R4, R2, #0  ;store the num of an character of s2
            AND R5, R5, #0  ;R5 initialize to 0
JUDGE       NOT R0, R4
            ADD R0, R0, #1  ;R0<- -s2
            ADD R5, R3, R0  ;R5<- s1 - s2
            BRnp STORE      ;if R5!=0 , the result of strcmp is R5
            ADD R1, R1, #1  ;R0<-R0+1 store the next character
            ADD R2, R2, #1  ;R2<-R2+1 store the next character
            ADD R3, R3, #0  ;if R3 has moverd to the NULL
            BRz STORE   
            ADD R4, R4, #0  ;if R4 has moved to the NULL as well
            BRz STORE 
            BRnzp LOAD
;
;Store the answer
;
STORE       STI R5, RESULT  ; write back the result
            HALT
            

S1_ADDR     .FILL x3100
S2_ADDR     .FILL x3200
RESULT      .FILL x3300
            .END