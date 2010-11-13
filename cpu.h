#ifndef _CPU_H
#define _CPU_H

typedef unsigned char byte;
byte mem[0xFFF];
byte v[0xF];
byte sndTmr;
byte delayTmr;
short I;
short stack[16];
byte screen[32][64];
short PC;
short stackPtr;

#endif /* _CPU_H */
