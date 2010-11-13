#ifndef _OPCODES_H
#define _OPCODES_H
#include "cpu.h"
#include <GLUT/glut.h>

static inline void cls()
{
	short i,j;
	for (i=0;i<32;++i)
	{
		for(j=0;j<64;++j)
		{
			screen[i][j] = 0;
		}
	}
	PC+=2;
}

static inline void bcd(short opcode)
{
	byte dec = v[((opcode & 0x0F00)>>8)];
	mem[I+2] = dec % 10;
	dec /=10;
	mem[I+1] = dec % 10;
	dec /=10;
	mem[I]   = dec % 10;
	//printf("%i %X %X %X\n",((opcode & 0x0F00)>>8),mem[I],mem[I+1],mem[I+2]);
	PC+=2;
}

static inline void ldr(short opcode)
{
	
	short i;
	for(i=0;i<((opcode & 0x0F00)>>8);++i)
	{
		v[i] = mem[I];
		++I;
	}
	++I;
	PC+=2;
}

static inline void str(short opcode)
{
	
	short i;
	for(i=0;i<((opcode & 0x0F00)>>8);++i)
	{
		mem[I] = v[i];
		++I;
	}
	++I;
	PC+=2;
}

static void sprite(short opcode)
{
	short i,j;
	short x = (opcode & 0x0F00)>>8;
	short y = (opcode & 0x00F0)>>4;
	
	byte setV = 0;
	for(i=0;i<(opcode & 0x000F);++i)
	{
			if(screen[v[y]+i][v[x]+0] == 1 && ((mem[I+i]&0x80)>>7)==1)
				setV = 1;

			screen[v[y]+i][v[x]+0] ^= (mem[I+i]&0x80)>>7;
			
			if(screen[v[y]+i][v[x]+1]==1 && ((mem[I+i]&0x40)>>6)==1)
				setV = 1;

			screen[v[y]+i][v[x]+1] ^=  (mem[I+i]&0x40)>>6;
			
			if(screen[v[y]+i][v[x]+2] ==1&&  ((mem[I+i]&0x20)>>5)==1)
				setV = 1;

			screen[v[y]+i][v[x]+2] ^=  (mem[I+i]&0x20)>>5;
			
			if(screen[v[y]+i][v[x]+3]==1 &&  ((mem[I+i]&0x10)>>4)==1)
				setV = 1;

			screen[v[y]+i][v[x]+3] ^=  (mem[I+i]&0x10)>>4;
			
			if(screen[v[y]+i][v[x]+4]==1 &&  ((mem[I+i]&0x08)>>3)==1)
				setV = 1;

			screen[v[y]+i][v[x]+4] ^=  (mem[I+i]&0x08)>>3;
			
			if(screen[v[y]+i][v[x]+5]==1 &&  ((mem[I+i]&0x04)>>2)==1)
				setV = 1;

			screen[v[y]+i][v[x]+5] ^=  (mem[I+i]&0x04)>>2;
			
			if(screen[v[y]+i][v[x]+6]==1 &&  ((mem[I+i]&0x02)>>1)==1)
				setV = 1;

			screen[v[y]+i][v[x]+6] ^=  (mem[I+i]&0x02)>>1;
			
			if(screen[v[y]+i][v[x]+7]==1 &&  ((mem[I+i]&0x01))==1)
				setV = 1;

			screen[v[y]+i][v[x]+7] ^=  (mem[I+i]&0x01);

			
			//printf(((sprite[i][j] == 1)?"#":" "));
		
		
		
		
	}
	v[15] = setV==1?1:0;
	/*
	printf("\n");
	for (i=0;i<32;++i)
	{
		for(j=0;j<64;++j)
		{
			printf((screen[i][j] == 1)?"#":" ");
		}
		printf("\n");
	}*/
	//exit(0);
	//getchar();
	glutPostRedisplay();
	PC+=2;
}


#endif /* _OPCODES_H */
