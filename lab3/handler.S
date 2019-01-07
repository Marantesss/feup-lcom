#include  <machine/asm.h>

#include "i8042.h"

.global _C_LABEL(kbc_asm_ih)
.global _C_LABEL(scancode)

.data

.text
_C_LABEL(kbc_asm_ih):
	xor %eax, %eax            // inicia o registo a 0- uint8_t stat em c
	inb $STAT_REG             // sys_inb(STAT_REG , &stat)
	jnz NOTPOSSIBLE           // verifica se nao 0
	test $STAT_REG_OBF, %al   // se eax = 0, buffer esta vazio
	jz NOTPOSSIBLE
	test $STAT_REG_TIMEOUT, %al 
	jnz NOTPOSSIBLE
	test $STAT_REG_PAR, %al 
	jnz NOTPOSSIBLE
	inb $OUT_BUF              // em c sys_inb_cnt(OUT_BUF, &scancode);
	jnz NOTPOSSIBLE           // verifica se nao 0
	movb %al, scancode
	jmp END
NOTPOSSIBLE:
	movb $-1, scancode
END:
	ret
