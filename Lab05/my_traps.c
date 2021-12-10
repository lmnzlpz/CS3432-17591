#include <stdint.h>
#include "syscall.h"
#include <stdlib.h>
#include <stdio.h>

uintptr_t handle_trap(uintptr_t epc, uintptr_t cause, uintptr_t tval, uintptr_t
regs[32])
{
    /* Extract low-order bits of exception code as positive int */
    int code = cause & ((1UL << ((sizeof(int)<<3)-1)) - 1);
    /* Encode interrupt as negative value */
    code = ((intptr_t)cause < 0) ? -code : code;
    if (code == 11) {
            if (regs[10] == 1){
                printf("%ld\n", regs [11]);
                return(epc+4);
            }
            else if (regs[10] == 9)
                return ((intptr_t) _sbrk(regs[11]));
            else if (regs[10] == 10)
                _exit(0);
    }
    _exit(code);
    __builtin_unreachable();
}
