#include <asm_setup.S>
.text
.global PorcuPufferZ
PorcuPufferZ:
    stwu   sp, -0x20(sp)
    mflr   r0
    stw    r0, 0x24(sp)
    stw    r3, 0x1C(sp)
	lis    r3, CustomZValue@ha
	lfs    f0, CustomZValue@l(r3) 
	stfs   f0, 0xB4(r30) 
    lwz    r3, 0x1C(sp)
    lwz    r0, 0x24(sp)
    mtlr   r0
    addi   sp, sp, 0x20
    blr

.data
CustomZValue:
    .float    5000.0