#include "x86.h"
#include "proc.h"
#include <stdio.h>

CPU cpu = {};

int main(int argc, char* argv[]) {

    cpu.eax = 0x12345678;
    printf("cpu.eax = %x  %x  %x\n", cpu.gpr[0]._32, cpu.gpr[0]._16, cpu.gpr[0]._8[1]);
    printf("cpu.eax = %x  %x  %x\n", cpu.eax, cpu.ax, cpu.al);
    cpu.eflags = 0x2;
    printf("eflags = %x \n", cpu.test2);

    int x = 50;
    int* ptr_x = &x;
    long long prt_v = (long long) ptr_x;
    printf("the address is: %p, the value is %lld\n", ptr_x, prt_v);

    printf("sub = %x\n", 0x1a7e60 - 0xc);

    struct struct_proc proc;
    proc.pid = 1;
    proc.link = 987;

    printf("struct poin = %p\n", &proc);
    size_t offset = (size_t)(&(((struct struct_proc *) 0)->link));
    struct struct_proc* proc_m = (struct struct_proc *)((char *)(&proc.link) - offset);
    printf("offset by member %p, %ld\n", proc_m, offset);
}