.define sz = 2 
MAIN: mov r3, LIST[sz] 
LOOP: jmp L1
cmp r3, sz 
mcr m_mcr 
cmp r3, #sz 
 bne END 
endmcr
bne END 
L1: inc K 
bne LOOP 
END: hlt 
 m_mcr
.define len = 4 
STR: .string "abcd"
LIST: .data 6, -9, len 
K: .data len
.extern L3
