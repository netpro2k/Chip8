/* Created by Anjuta version 1.2.2 */
/*	This file will not be overwritten */

#include <stdio.h>
#include <ctype.h>
#include "cpu.h"
#include "opcodes.h"
#include <stdlib.h>
//#include <GL/glut.h>
#include <GLUT/glut.h> // had to switch this to build on mac
#include <string.h>

int readRom(char* file);
void reset();
 int c = 0; 
 #define lookX -20;
 #define lookY -20;
 #define DEBUG
 byte keys[16];
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	short i,j;
	for (i=0;i<32;++i)
	{
		for(j=0;j<64;++j)
		{
			if(screen[i][j] == 1)
			{
		
				
				glPushMatrix();
					glTranslated(j,i,0);
					glutSolidCube(1);
					/*
					glBegin(GL_QUADS);
						glVertex2i(0, 0);
						glVertex2i(1, 0);
						glVertex2i(1, 1);
						glVertex2i(0, 1);
					glEnd()*/
				glPopMatrix();
				
			}
		}
	}

	
  glutSwapBuffers();

}

void runCPU()
{
	short opcode = (mem[PC]<<8)|mem[PC+1];
		#ifdef DEBUG
		printf("0x%X: ",PC);
		#endif
		switch(opcode & 0xF000)
		{
			case 0x0000:
					switch(opcode & 0x00FF)
					{
						case 0x00E0:
							#ifdef DEBUG
							printf("cls");
							#endif
							cls();
							break;
						case 0x00EE:
							#ifdef DEBUG
							printf("rts");
							#endif
							stackPtr--;
							PC=stack[stackPtr];
						
							break;
						case 0x00FB:
							#ifdef DEBUG
							printf("scright");
							#endif
							//PC+=2;
							break;
						case 0x00FC:
							#ifdef DEBUG
							printf("scleft");
							#endif
							//PC+=2;
							break;
						case 0x00FE:
							#ifdef DEBUG
							printf("low");
							#endif
							//PC+=2;
							break;
						case 0x00FF:
							#ifdef DEBUG
							printf("high");
							#endif
							//PC+=2;
							break;
						default:
						#ifdef DEBUG
							printf("%X %X :: scdown %X", (opcode & 0xFF00)>>8,opcode & 0x00FF,opcode & 0x000F);
						#endif	
						PC+=2;
							break;
					}
					break;
			case 0x1000:
				#ifdef DEBUG
					printf("jmp %X ",opcode & 0x0FFF);
				#endif
					PC=(opcode & 0x0FFF);
			
					break;
			case 0x2000:
				#ifdef DEBUG
					printf("jsr %X",opcode & 0x0FFF);
				#endif
					stack[stackPtr] = PC+2;
					++stackPtr;
					PC=(opcode & 0x0FFF);
			
					break;
			case 0x3000:
				#ifdef DEBUG
					printf("skeq v%X,%X",(opcode & 0x0F00)>>8,opcode & 0x00FF);
					printf("\n %X == %X ? %i",v[(opcode & 0x0F00)>>8],opcode & 0x00FF,((v[((opcode & 0x0F00)>>8)]) == (opcode & 0x00FF)));
							#endif
			
					if((v[((opcode & 0x0F00)>>8)]) == (opcode & 0x00FF))
						PC+=4;
					else
						PC+=2;
			
					break;
			case 0x4000:
				#ifdef DEBUG
					printf("skne v%X,%X",(opcode & 0x0F00)>>8,opcode & 0x00FF);
							#endif
			
					if((v[((opcode & 0x0F00)>>8)]) != (opcode & 0x00FF))
						PC+=4;
					else
						PC+=2;
					
					break;
			case 0x5000:
				#ifdef DEBUG
					printf("skeq v%X,v%X",(opcode & 0x0F00)>>8,(opcode & 0x00F0)>>4);
							#endif
			
					if((v[((opcode & 0x0F00)>>8)]) == v[((opcode & 0x00F0)>>4)])
						PC+=4;
					else
						PC+=2;
			
					break;
			case 0x6000: 
				#ifdef DEBUG
					printf("mov v%X,%X",(opcode&0x0F00)>>8,opcode&0x00FF);
							#endif
			
					v[((opcode&0x0F00)>>8)] = (opcode&0x00FF);
					PC+=2;
			
					break;
			case 0x7000:
				#ifdef DEBUG
					printf("add v%X,%X",(opcode & 0x0F00)>>8,opcode & 0x00FF);
							#endif
			
					v[((opcode&0x0F00)>>8)] += (opcode&0x00FF);
					PC+=2;	
			
					break;
			case 0x8000:
					switch(opcode & 0x000F)
					{
						case 0x0000:
							#ifdef DEBUG
								printf("mov v%X,v%X",(opcode & 0x0F00)>>8,(opcode & 0x00F0)>>4);
							#endif
						
								v[((opcode&0x0F00)>>8)] = v[((opcode & 0x00F0)>>4)];
								PC+=2;
						
								break;
						case 0x0001:
							#ifdef DEBUG
								printf("or v%X,v%X",(opcode & 0x0F00)>>8,(opcode & 0x00F0)>>4);
							#endif
						
								v[((opcode&0x0F00)>>8)] |= v[((opcode & 0x00F0)>>4)];
								PC+=2;
						
								break;
						case 0x0002:
							#ifdef DEBUG
								printf("and v%X,v%X",(opcode & 0x0F00)>>8,(opcode & 0x00F0)>>4);
							#endif
						
								v[((opcode&0x0F00)>>8)] &= v[((opcode & 0x00F0)>>4)];
								PC+=2;
						
								break;
						case 0x0003:
							#ifdef DEBUG
								printf("xor v%X,v%X",(opcode & 0x0F00)>>8,(opcode & 0x00F0)>>4);
							#endif
						
								v[((opcode&0x0F00)>>8)] ^= v[((opcode & 0x00F0)>>4)];
								PC+=2;
						
								break;
						case 0x0004:
							#ifdef DEBUG
								printf("add v%X,v%X",(opcode & 0x0F00)>>8,(opcode & 0x00F0)>>4);
							#endif
						
								if((v[((opcode&0x0F00)>>8)] + v[((opcode & 0x00F0)>>4)]) > 255) //carry needs to be set 
								{
									v[15] = 1;
								}
								v[((opcode&0x0F00)>>8)] += v[((opcode & 0x00F0)>>4)];
								
								PC+=2;
								
								break;
						case 0x0005:
							#ifdef DEBUG
								printf("sub v%X,v%X",(opcode & 0x0F00)>>8,(opcode & 0x00F0)>>4);
							#endif
						
								if(((v[((opcode&0x0F00)>>8)] >= v[((opcode & 0x00F0)>>4)]))) //carry needs to be set 
								{
									v[15] = 1;
								} else {
									v[15] = 0;
								}
								v[((opcode&0x0F00)>>8)] -= v[((opcode & 0x00F0)>>4)];
								
								PC+=2;
						
								break;
						case 0x0006:
							#ifdef DEBUG
								printf("shr v%X",(opcode & 0x0F00)>>8);
							#endif
						
								v[15] = (v[((opcode & 0x0F00)>>8)] & 0x01);
								v[((opcode & 0x0F00)>>8)] >>= 1;
						
								PC+=2;
								break;
						case 0x0007:
							#ifdef DEBUG
								printf("rsb v%X,v%X",(opcode & 0x0F00)>>8,(opcode & 0x00F0)>>4);
							#endif
						
								if((v[((opcode & 0x00F0)>>4)] - v[((opcode&0x0F00)>>8)]) < 0) //carry needs to be set 
								{
									v[15] = 1;
								}
								
								v[((opcode&0x0F00)>>8)] = v[((opcode & 0x00F0)>>4)] - v[((opcode&0x0F00)>>8)] ;
								
								PC+=2;
						
								break;
						case 0x000e:
							#ifdef DEBUG
								printf("shl v%X",(opcode & 0x0F00)>>8);
							#endif
						
								v[15] = (v[((opcode & 0x0F00)>>8)] & 0x80)>>7;
								v[((opcode & 0x0F00)>>8)] <<= 1;
								PC+=2;
						
								break;
					}
					break;
			case 0x9000:
							#ifdef DEBUG
					printf("skne v%X, v%X : ",(opcode & 0x0F00)>>8,(opcode & 0x00F0) >> 4);
							#endif
					
					if(v[(opcode & 0x0F00)>>8] != v[(opcode & 0x00F0) >> 4])
						PC+=4;
					else
						PC+=2;
			
					break;
			case 0xA000:
							#ifdef DEBUG
					printf("mvi %x",opcode&0x0FFF);
							#endif
			
					I = (opcode&0x0FFF);
					PC+=2;			
			
					break;
			case 0xB000:
							#ifdef DEBUG
					printf("jmi %X",opcode & 0x0FFF);
							#endif
					
					PC = (opcode & 0x0FFF) + v[0];
			
					break;
			case 0xC000:
							#ifdef DEBUG
					printf("rand v%X,%X",(opcode & 0x0F00)>>8,opcode & 0x00FF);
							#endif
			
					v[(opcode & 0x0F00)>>8] = rand()/(int)(((unsigned)RAND_MAX + 1) / (opcode & 0x00FF));
					PC+=2;
			
					break;
			case 0xD000:
							#ifdef DEBUG
					printf("sprite v%X,v%X,%X",(opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4,opcode & 0x000F);
					#endif
					sprite(opcode);
					
					break;
			case 0xE000:
					if((opcode & 0x00FF) == 0x009E)
					{
						
							#ifdef DEBUG
						printf("skpr %X",(opcode & 0x0F00)>>8);
							#endif
						//printf("skpr %X\n",v[(opcode & 0x0F00)>>8]);
						if(keys[v[(opcode & 0x0F00)>>8]])
							PC+=4;
						else
							PC+=2;
					}
					else
					{
							#ifdef DEBUG
						printf("skup %X",(opcode & 0x0F00)>>8);
							#endif
						//getchar();
						//printf("skup %X\n",v[(opcode & 0x0F00)>>8]);
						if(keys[v[(opcode & 0x0F00)>>8]])
							PC+=2;
						else
							PC+=4;
					}
					break;
			case 0xF000:
					switch(opcode & 0x00FF)
					{
						case 0x0007:
							#ifdef DEBUG
								printf("gdeleay v%X",(opcode & 0x0F00)>>8); 
							#endif
								v[(opcode & 0x0F00)>>8] = delayTmr;
								PC+=2;
								break;
						case 0x000a:
							#ifdef DEBUG
								printf("key v%X",(opcode & 0x0F00)>>8); 
							#endif
								
								short i;
								for(i =0; i<16;++i)
								{
									if(keys[i] == 1)
									{
										v[(opcode & 0x0F00)>>8] = i;
										PC+=2;
										break;
									}
								}
							
								//getchar();
								//
								
								break;
						case 0x0015:
							#ifdef DEBUG
								printf("sdeleay v%X",(opcode & 0x0F00)>>8); 
							#endif
								delayTmr = v[(opcode & 0x0F00)>>8];
								PC+=2;
								break;
						case 0x0018:
							#ifdef DEBUG
								printf("ssound v%X",(opcode & 0x0F00)>>8); 
							#endif
								sndTmr = v[(opcode & 0x0F00)>>8];
								PC+=2;
								break;
						case 0x001e:
							#ifdef DEBUG
								printf("adi v%X",(opcode & 0x0F00)>>8); 
							#endif
						
								I += v[(opcode & 0x0F00)>>8];
						
								PC+=2;
								break;
						case 0x0029:
							#ifdef DEBUG
								printf("font v%X",(opcode & 0x0F00)>>8);
							#endif
								I=v[(opcode & 0x0F00)>>8]*5;	
								PC+=2;						
								break;
						case 0x0030:
							#ifdef DEBUG
								printf("xfont v%X",(opcode & 0x0F00)>>8); 
							#endif
								break;
						case 0x0033:
							#ifdef DEBUG
								printf("bcd v%X",(opcode & 0x0F00)>>8); 
							#endif
								bcd(opcode);
								break;
						case 0x0055:
							#ifdef DEBUG
								printf("str v0-v%X",(opcode & 0x0F00)>>8); 
								str(opcode);
							#endif
								break;
						case 0x0065:
							#ifdef DEBUG
								printf("ldr v0-v%X",(opcode & 0x0F00)>>8); 
							#endif
								ldr(opcode);
								break;
					}
					break;
		}
		if(delayTmr >0)
			--delayTmr;
		if(sndTmr > 0)
		{
			--sndTmr;
			//system("aplay /usr/kde/3.2/share/sounds/KDE_Beep_Beep.wav &> /dev/null &"); //
			system("afplay beep.aiff  &> /dev/null &"); // changed this to the mac equivilent
		}
		
		#ifdef DEBUG
				printf("\n");
		#endif
			int i;
			for(i=0;i<16;++i)
			{
				printf("v%X=%X\t",i,v[i]);
			}
			printf("\nI=%X\n---------------------------\n",I);
	
	
	glutTimerFunc(2,runCPU,c);
}

void processNormalKeys(unsigned char key, int x, int y) {
	//printf(key);
	switch (key)
	{
		case '0': keys[0] = 1; break;
		case '1': keys[1] = 1;  break;
		case '2': keys[8] = 1;  break;
		case '3': keys[3] = 1;  break;
		case '4': keys[4] = 1;  break;
		case '5': keys[5] = 1;  break;
		case '6': keys[6] = 1;  break;
		case '7': keys[7] = 1;  break;
		case '8': keys[2] = 1;  break;
		case '9': keys[9] = 1;  break;
		case 'a': keys[10] = 1;  break;
		case 'b': keys[11] = 1;  break;
		case 'c': keys[12] = 1;  break;
		case 'd': keys[13] = 1;  break;
		case 'e': keys[14] = 1;  break;
		case 'f': keys[15] = 1;  break;
		case 'r': reset(); break;
	}
}
void keyUp(unsigned char key, int x, int y) {
	printf("up %i\n",key);
	switch (key)
	{
		case '0': keys[0] = 0; break;
		case '1': keys[1] = 0;  break;
		case '2': keys[8] = 0;  break;
		case '3': keys[3] = 0;  break;
		case '4': keys[4] = 0;  break;
		case '5': keys[5] = 0;  break;
		case '6': keys[6] = 0;  break;
		case '7': keys[7] = 0;  break;
		case '8': keys[2] = 0;  break;
		case '9': keys[9] = 0;  break;
		case 'a': keys[10] = 0;  break;
		case 'b': keys[11] = 0;  break;
		case 'c': keys[12] = 0;  break;
		case 'd': keys[13] = 0;  break;
		case 'e': keys[14] = 0;  break;
		case 'f': keys[15] = 0;  break;
	}
}

GLfloat light_diffuse[] = {1, 1, 1, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */

void
init(void)
{
  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 1000.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(-20, -30, -80.0,  /* eye is at (0,0,5) */
    32, 16, 0.0,      /* center is at (0,0,0) */
    0.0, -1.0, 0.);      /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
 // glTranslatef(0.0, 0.0, -1.0);
  //glRotatef(60, 1.0, 0.0, 0.0);
 // glRotatef(-20, 0.0, 0.0, 1.0);
}

//#define DEBUG
int main(int argc, char** argv)
{
	if (argc < 2) {
		printf("usage: chip8 gameName.ch8\n");
		return 0;
	}
	
	
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Chip8 emu");
  glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(keyUp);
  //glutIdleFunc(runCPU);
  glutTimerFunc(2,runCPU,c);



	glClearColor(0, 0, 0, 0);
    glColor3f(0.0, 0.75, 0.0);
    //glMatrixMode(GL_PROJECTION); 
    //glOrtho(0.0, 65.0, 33.0, 0.0, 0.0, 1.0); 
	init();
	int progSize = readRom(argv[1]);//addtest.ch8");

	progSize = readFontRom("CHIP8.ROM");//addtest.ch8");
	reset();
  	glutMainLoop();
	
	short i,j;
	/*
	for (i=0;i<32;++i)
	{
		for(j=0;j<64;++j)
		{
			printf("%i",screen[i][j]);
		}
		printf("\n");
	}*/
	for(i=0;i<16;++i)
	{
		printf("v%X = %X\n",i,v[i]);
	}
	return (0);
}

void reset()
{
	cls();
	PC = 0x200;
	stackPtr = 0;
	srand (time (0));
	int i;
	for(i=0;i<16;++i)
	{
		v[i] = 0;
	}
	I=0;
	
}

int readFontRom(char* file)
{
	int f, n,i;
	int count = 0;
	char buffer[0x200];
	f = open(file,0);
	if ( f > 0 ) {
		while( (n=read(f, buffer, 0x200)) > 0 ) {
		
			for(i=0; i<n;++i)
			{
				mem[count+i] = buffer[i];
			}
			count+=n;
		}
		close( f );
		return count;
	}
	else
	{
		printf("error");
		return 0;
	}
}

int readRom(char* file)
{
	int f, n,i;
	int count = 0;
	char buffer[0xFFF - 0x200];
	f = open(file,0);
	if ( f > 0 ) {
		while( (n=read(f, buffer, 0xFFF - 0x200)) > 0 ) {
		
			for(i=0; i<n;++i)
			{
				mem[0x200+count+i] = buffer[i];
			}
			count+=n;
		}
		close( f );
		return count;
	}
	else
	{
		printf("error");
		return 0;
	}
}
