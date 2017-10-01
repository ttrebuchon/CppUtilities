#include "../Tests_Helpers.h"

//#define ABC_RESULT 24;


extern "C"
{
    volatile int ABC_RESULT = 24;
    int abc123456()
    {
        return ABC_RESULT;
    }

    int abcdef()
    {
        int x = abc123456();
        return x + 439;
    }
}

extern "C" int asmFunc();
#if defined(i386) || defined(__x86_64__)
asm (".global asmFunc\n\t"
     ".type asmFunc, @function\n\t"
     "asmFunc:\n\t"
     ".cfi_startproc\n\t"
     "movl ABC_RESULT, %eax\n\t"
     "movl $10, %ecx\n\t"
     "add %ecx, %eax\n\t"
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
#else
static_assert(false, "Unknown architecture!");
#endif




DEF_TEST(ASM)
{
    if (!(asmFunc() == (abc123456()+10)) || !(asmFunc() == ABC_RESULT+10) || !(abc123456() == ABC_RESULT))
    {
        dout << "asmFunc() == " << asmFunc() << std::endl;
        dout << "abc123456() == " << abc123456() << std::endl;
        dout << "ABC_RESULT == " << ABC_RESULT << std::endl;
    }
    assert_ex(asmFunc() == (abc123456()+10));
    assert_ex(asmFunc() == ABC_RESULT+10);
    assert_ex(abc123456() == ABC_RESULT);
	return true;
}