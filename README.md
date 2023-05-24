basm
=

### Byung Yoon's 8bit cpu & assembler

### cpu instruction

- 크기: 8bit
- 구성: 4bit operation code + 4bit operand code

### operation code table

| operation code | assembly                 | result                                       |
|----------------|--------------------------|----------------------------------------------|
| 0 0 0 0        | **nop**                  | ```no operation```                           |
| 0 0 0 1        | **cmp** *reg*, *reg/imm* | ```dest - source (set flag)```               |
| 0 0 1 0        | **add** *reg*, *reg/imm* | ```dest += source ```                        |
| 0 0 1 1        | **sub** *reg*, *reg/imm* | ```dest -= source ```                        |
| 0 1 0 0        | **ja** *label*           | ```jump if above (zf = 0, cf = 0)```         |
| 0 1 0 1        | **jb** *label*           | ```jump if below (zf = 0, cf = 1)```         |
| 0 1 1 0        | **je** *label*           | ```jump if equal (zf = 1, cf = 0)```         |
| 0 1 1 1        | **jmp** *label*          | ```jump to label (jmp들은 모두 src가 imm이어야 함)``` |
| 1 0 0 0        | **mov** *mem*, *reg*     | ```mem <- source```                          |
| 1 0 1 0        | **mov** *reg*, *reg/imm* | ```dest <- source```                         |
| 1 0 1 1        | **mov** *reg*, *mem*     | ```dest <- mem```                            |

### operand code table

구성: dest 2bit + source 2bit

- dest는 imm이 될 수 없음

| operand code | meaning |
|--------------|---------|
| 0 0          | regiA   |
| 0 1          | regiB   |
| 1 0          | regiC   |
| 1 1          | imm     |
