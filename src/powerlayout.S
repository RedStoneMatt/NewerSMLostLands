.text
#include <asm_setup.S>
.align 4
.extern powerlayout__14dGameDisplay_c
.global powerthing_entry
powerthing_entry:
    # save registers to stack
    bl powerlayout__14dGameDisplay_c
    # restore regs
    # place patched instruction here
    stwu r1, -0x10(r1)