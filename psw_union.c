#include <stdio.h>

union PSW
{
    unsigned char value;

    struct
    {
        unsigned char P  : 1;
        unsigned char OV : 1;
        unsigned char RS0 : 1;
        unsigned char RS1 : 1;
        unsigned char F0 : 1;
        unsigned char AC : 1;
        unsigned char CY : 1;
        unsigned char reserved : 1;
    } bits;
};

int main()
{
    union PSW psw;

    psw.value = 0x00;

    printf("Initial PSW : 0x%02X\n\n", psw.value);

    psw.value = 0x80;
    printf("Set Carry\n");
    printf("PSW : 0x%02X\n\n", psw.value);

    psw.value = 0x84;
    printf("Set Overflow\n");
    printf("PSW : 0x%02X\n\n", psw.value);

    psw.value = 0x94;
    printf("Select Register Bank 2\n");
    printf("PSW : 0x%02X\n\n", psw.value);

    psw.value = 0x14;
    printf("Clear Carry\n");
    printf("PSW : 0x%02X\n", psw.value);

    return 0;
}
