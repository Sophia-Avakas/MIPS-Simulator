# MIPS Simulator
## INSTRUCTIONS
<br>The MIPS simulator only support the following instructions:
<br>add opr1, opr2, opr3  	: opr1 = opr2 + opr3
<br>addi opr1,opr2,value    : opr1 = opr2 + value
<br>sub opr1, opr2, opr3  	: opr1 = opr2 - opr3
<br>mul opr1, opr2, opr3  	: opr1 = opr2 x opr3
<br>div opr1, opr2, opr3  	: opr1 = opr2 / opr3
<br>b   label               : Branch/Jump to Label (Unconditional) 
<br>beq opr1, opr2, label   : Branch if Equal (opr1 == opr2) to Label
<br>bnq opr1, opr2, label   : Branch if Not Equal (opr1 != opr2) to Label
<br>end                     : End of the program
<br>
<br>Each opcode (instruction) has certain number of input operands. Opcode ‘end’ signals the end of the program in which case instructions in the pipeline must be completed(if applicable) and desired output must be printed. The Operands can either be registers, an immediate value or a label. MIPS processor is expected to have 8 registers ($0, $2,...,$7). Labels signifies the target instruction for the branches. The first lien is the final results of the registers that the program should produce. The second line in the input file is the initialization values for the 8 registers (in order $0-$7). 
<br>
<br>An example input:
<br>2,4,6,88,67,45,44,89 
<br>add $0,$1,$2 
<br>label1 sub $1,$0,$4 
<br>add $2,$3,$5 
<br>beq $0,$7,label1 
<br>end
<br>
<br>There is single blank between the label and the opcodes, and the opcodes and their operands. All label start with the keyword ‘label’ and followed by a numeric value.
<br>
###<br>Pipelining and Data Forwarding Rules:
<br>This is a 3 stage pipeline with Fetch, Execute and Write-Back as the only stages. Data forwarding happens ONLY after the execution of the preceding instruction to the execution stage of the current instruction. In case of Branches, you must STALL the pipeline till the end of the execution stage for the branch to know if branch is taken or not.
