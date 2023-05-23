basm
=

### Byung Yoon's 8bit cpu & assembler

### cpu instruction

- 크기: 16bit
- 구성: 4bit operation code + 4bit operand code + 8bit 값 (즉시 값 또는 메모리 주소)

### 어셈블리 소개

> add dest [reg], source [reg/imm]

> sub dest [reg], source [reg/imm]

> cmp dest [reg], source [reg/imm]

> mov dest [reg/mem], source [reg/mem/imm]
> - mem, mem 은 허용되지 않음

### operation code table

| operation code | assembly         | result                   |
|----------------|------------------|--------------------------|
| 0 0 0 0        | nop              | no operation             |
| 0 0 0 1        | add dest, source | dest += source           |
| 0 0 1 0        | sub dest, source | dest -= source           |
| 0 0 1 1        | cmp dest, source | dest - source (set flag) |
| 0 1 0 0        | jmp              | jump to val              |
| 0 1 0 1        | ja               | jump if above            |
| 0 1 1 0        | jb               | jump if below            |
| 0 1 1 1        | je               | jump if equal            |
| 1 0 0 0        | mov dest, source | dest <- source           |

### operand code table

| operand code | meaning     |
|--------------|-------------|
| 0 0 0 0      | regiA regiA |
| 0 0 0 1      | regiA regiB |
| 0 0 1 0      | regiA regiC |
| 0 1 0 0      | regiA imm   |
| 0 1 0 0      | regiA mem   |
| 0 0 1 1      | regiB regiA |
| 0 1 0 0      | regiB regiB |
| 0 1 0 1      | regiB regiC |
| 0 1 0 1      | regiB imm   |
| 0 1 1 0      | regiC regiA |
| 0 1 1 1      | regiC regiB |
| 1 0 0 0      | regiC regiC |
| 1 0 0 0      | regiC imm   |

