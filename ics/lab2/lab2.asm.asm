;Initialization 
        .ORIG   x3000
        LDI     R0, NLOCA   ;R0读取x3102存储N的值
        AND     R1, R1, #0  ;R1置0，用于存储v_n
        ADD     R1, R1, #3  ;v_n初始值为3
        AND     R2, R2, #0  ;R2置0用于表示d_n
        ADD     R2, R2, #2  ;d_n初始为正
;
;Circulation
;
CALCU   ADD     R0, R0, #-1 ;计数器减1
        BRnz    OUTPUT      ;计数器为0跳到结束
        ADD     R1, R1, R1  ;计算v_(n+1)
        ADD     R1, R1, R2
;
;Determine whether to change the signal of d_n
;
DETERCH ADD     R3, R1, #0  ;R3临时存储R1(v_n+1)用于判断是否用将d_n变号
EIGHT   ADD     R3, R3, #-8 ;反复减8用于得到是否为8的倍数
        BRp     EIGHT       ;为正的话继续减8
        BRz     CHANGE      ;为0说明刚好为8的倍数
        ADD     R3, R1, #-8 ;继续判断是否为10的倍数
TEN     ADD     R3, R3, #-10;反复减10
        BRp     TEN         ;为正继续减10
        BRz     CHANGE      ;为0说明刚好为10的倍数
        BRnzp   SMOD        ;都不满足，说明不给d_n改变，继续下一步给fn取模
CHANGE  ADD     R2, R2, #0  
        BRp     POSI        ;d_n若为正，就改成负的
        BRn     NEG         ;d_n为负，就改成正的
POSI    ADD     R2, R2, #-4
        BRnzp   SMOD
NEG     ADD     R2, R2, #4
        BRnzp   SMOD
;
;FN = FN mod 4096
;        
SMOD    LD      R4, MLOCA   ;R4为4096
        NOT     R5, R4
        ADD     R5, R5, #1  ;R5为-4096
MOD     ADD     R6, R1, R5  ;R6 = v_(n+1) - 4096
        BRnz    CALCU       ;继续下一次循环
        ADD     R1, R1, R5  ;v_(n+1) = v_(n+1) - 4096
        BRnzp   MOD
;Output the answer  
;
OUTPUT  STI     R1, FLOCA        
        TRAP    x25

MLOCA   .FILL   #4096        
NLOCA   .FILL   x3102
FLOCA   .FILL   x3103
        .END