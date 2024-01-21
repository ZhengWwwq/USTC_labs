        .ORIG X3000
;step1 Initial prompt        
STEP1   LEA R0, Welc        ;show the welcome and wait for input 'W'
        TRAP x22
        AND R1, R1, #0
        ADD R1, R1, #3      ;R1 represents the ability to try left
WAIT    TRAP x23            ;wait for input 'W'
        LD R2, W
        ADD R0, R0, R2      ;compare if input is 'W'
        BRnp WAIT           ;if it is not 'W', continue to wait
;step2 Password input
        LEA R0, Inpu        ;show the requirement that to input the password
        TRAP x22
;step3 Password verification
STEP3   ADD R1, R1, #-1     ;ability -1
        BRn FAILURE
        LEA R3, PASS        ;R3 stores the address of our input
        LD R4, Y
;first to input all the characters
INPUT   TRAP x20            ;input a character
        ADD R5, R0, R4      ;compare if the character is 'Y'
        BRz COMPARE         ;we have finished input
        STR R0, R3, #0      
        ADD R3, R3, #1
        BRnzp INPUT         ;continue to input
;then we need to compare the password with the ID
COMPARE AND R0, R0, #0
        STR R0, R3, #0      ;before we start to compare, we should add a \0 at the end of the password
        JSR STRCMP
        ADD R6, R6, #0  
        BRp SUCCESS         ;the password is correct
        AND R0, R0, #0
        ADD R0, R0, #10
        TRAP x21
        LEA R0, Remain1     ;show the attempts we left
        TRAP x22
        LD R3, ASCII
        ADD R0, R1, R3
        TRAP x21
        LEA R0, Remain2
        TRAP x22
        BRnzp   STEP3       ;continue to try
        
FAILURE AND R0, R0, #0      ;line feed
        ADD R0, R0, #10
        TRAP x21
        LEA R0, Fail
        TRAP x22
        AND R0, R0, #0
        ADD R0, R0, #10
        TRAP x21
        BRnzp STEP1
SUCCESS AND R0, R0, #0
        ADD R0, R0, #10
        TRAP x21
        LEA R0, Succ
        TRAP x22
        HALT

;the Compare function (similar to lab3, just change some registers)
;input is string start in PASS and string in ID, output is R6 (1 means true, 0 means wrong)
STRCMP  LEA R2, PASS
        LEA R3, ID          ;store the address of the two string
        AND R6, R6, #0      ;R6 stores the answer
LOAD    LDR R4, R2, #0      ;store the num of an character of PASS
        LDR R5, R3, #0      ;store the num of an character of ID
JUDGE   NOT R5, R5
        ADD R5, R5, #1      ;R5<- -R5
        ADD R5, R4, R5      ;R5<- PASS - ID
        BRnp WRONG          ;if R5!=0 , means s1 != s2
        ADD R4, R4, #0
        BRz TRUE
        ADD R2, R2, #1
        ADD R3, R3, #1      ;continue to compare next character
        BRnzp LOAD
WRONG   AND R6, R6, #0      
        RET
TRUE    ADD R5, R5, #0      ;if R4 == R5 == 0,it means s1 == s2
        BRnp WRONG
        ADD R6, R6, #1
        RET
  
W       .FILL       #-87
Y       .FILL       #-89
ASCII   .FILL       #48
Welc    .STRINGZ    "Welcome to the bank system! Type 'W' to withdraw some fund."
Inpu    .STRINGZ    "Please input your password:"
Remain1 .STRINGZ    "Incorrect password! "
Remain2 .STRINGZ    " attempt(s) remain."
Fail    .STRINGZ    " Fails."
Succ    .STRINGZ    " Success!"
ID      .STRINGZ    "PB22051082"
PASS    .BLKW       11  ;the password we input

        .END
