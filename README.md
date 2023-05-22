basm
=

### Byung Yoon's assembler

### instruction 
- size: 32bit
- configuration: 8bit opcode + 8bit operand type + 16bit operand value (for immediate value or memory)

### opcode table

| opcode          | assembly | result |
|-----------------|----------|--------|
| 0 0 0 0 0 0 0 0 | NOP      | NOP    |
| 0 0 0 0 0 0 0 1 | MOV      | NOP    |
| 0 0 0 0 0 0 1 0 | ADD      | NOP    |
| 0 0 0 0 0 0 1 1 | SUB      | NOP    |
| 0 0 0 0 0 0 0 0 | NOP      | NOP    |
| 0 0 0 0 0 0 0 0 | NOP      | NOP    |

- operand type: 4bit operand 1 type (3 reg + 1 imm) + 2bit operand 2 type (3 reg + 1 imm)