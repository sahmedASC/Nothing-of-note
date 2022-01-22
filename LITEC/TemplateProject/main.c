// ENGR-2350 Template Project
// Name: XXXX
// RIN: XXXX
// This is the base project for several activities and labs throughout
// the course.  The outline provided below isn't necessarily *required*
// by a C program; however, this format is required within ENGR-2350
// to ease debugging/grading by the staff.

// We'll always add this include statement. This basically takes the
// code contained within the "engr_2350_msp432.h" file and adds it here.
#include "engr2350_msp432.h"

// Add function prototypes here, as needed.


// Add global variables here, as needed.


// Main Function
int main(void)
{
    // Add local variables here, as needed.
    unsigned char a;
    unsigned char b;
    unsigned char c;

    unsigned char d;

    // We always call the "SysInit()" first to set up the microcontroller
    // for how we are going to use it.

    SysInit();

    // Place initialization code (or run-once) code here


    a=0x80;
    b=0x1E;
    c=0xC3;

    printf("First Set Of Questions:\n\r");
    d=a&b;
    int i = 1;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i +1;

    d =  b&c;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  b&0xF0;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  c&0x01;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  c&~b;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  c&!b;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    printf("Second Set Of Questions:\n\r");
    d =  a|b;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  b|c;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  b|0xF0;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  c|0x01;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  c|!b;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    printf("Third Set Of Questions:\n\r");
    d =  b<<1;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  b<<4;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  b<<8;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  b>>1;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  b>>4;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    printf("Fourth set of Questions\n\r");
    d =  ~b;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  !b;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  !(!b);
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  a&&b;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  b&&c;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  a||b;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  (a+b)==(a|b);
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    d =  ~b!=b;
    printf("Questions %u\n\rd = 0x%x\n\r\n\r", i,d);
    i= i + 1;

    printf("End of program.");

    while(1){
        // Place code that runs continuously in here

    }
}

// Add function declarations here as needed

// Add interrupt functions last so they are easy to find
