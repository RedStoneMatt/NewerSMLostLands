#include <asm_setup.S>
.text
.global PorcuPufferZ
PorcuPufferZ:
    stwu   sp, -0x20(sp)
    mflr   r0
    stw    r0, 0x24(sp)
    stw    r3, 0x1C(sp)
	lis    r3, CustomZValue@ha #don't touch anything here
	lfs    f0, CustomZValue@l(r3) #f0 has to be the fX from the original value
	stfs   f0, 0xB4(r30) ##f0 has to be the fX from the original value, 0xB4 has to be the 0x<something> and r30 has to be the rXX
    lwz    r3, 0x1C(sp)
    lwz    r0, 0x24(sp)
    mtlr   r0
    addi   sp, sp, 0x20
    blr

.data
CustomZValue:
    .float    5000.0