#include<stdint.h>
typedef union x86_reg
{
    uint32_t _32;
    uint16_t _16;
    uint8_t _8[2];
} GPR;

typedef struct eflags
{
    uint8_t CF :1;
    uint8_t ZF :1;
    uint8_t SF :1;
} EFLAGS;


typedef struct x86_cpu
{
    union {
        GPR gpr[8];
        union
        {
            uint32_t eax;
            uint16_t ax;
            uint8_t ah;
            uint8_t al;
        };
        
        uint32_t ecx;
        uint32_t edx;
        uint32_t ebx;
        uint32_t esp;
        uint32_t ebp;
        uint32_t esi;
        uint32_t edi;
    };
    uint32_t pc;
    union
    {
        uint32_t eflags;
        struct 
        {
            uint16_t test: 1;
            uint8_t test2: 1;
            uint8_t test3: 4;
            uint8_t IF :1;
            uint8_t CF :1;
            uint8_t ZF :1;
            uint8_t SF :1;
        };
        
    };
    
} CPU;

