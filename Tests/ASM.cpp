#include "../Tests_Helpers.h"

extern "C"
{

int abc123456()
{
	return 24;
}

int abcdef()
{
	int x = abc123456();
	return x + 439;
}
}

extern "C" int asmFunc();
#if defined(i386)
asm (".global asmFunc\n\t"
     ".type asmFunc, @function\n\t"
     "asmFunc:\n\t"
     ".cfi_startproc\n\t"
     "movl $7, %eax\n\t"
     "ret\n\t"
     ".cfi_endproc");
#elif defined(__aarch64__)
asm (".align 2\n"
     ".global asmFunc\n\t"
     ".type asmFunc, %function\n\t"
     "asmFunc:\n"
     ".cfi_startproc\n\t"
     "stp x29, x30, [sp, -16]!\n\t"
     "bl abc123456\n\t"
     "add w0, w0, #10\n\t"
     "ldp x29, x30, [sp], 16\n\t"
     "ret\n\t"
     ".cfi_endproc\n\t"
     ".size asmFunc, .-asmFunc\n");
#elif defined(__arm__)
#endif




DEF_TEST(ASM)
{
	assert_ex(asmFunc() == (abc123456()+10));
	return true;
}