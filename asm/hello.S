.section .data

.section .text
.global start
start:
    mov $0x70, %al
    int $0x21

seta20.2:
    inc %al
    int $0x21
