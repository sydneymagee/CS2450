#include <stdio.h>
#include <string.h>

#define LIMIT 40
#define DREG 0x0E00
#define BASESRCREG 0x01C0
#define PCOFF9 0x01FF

void printAssembly(char filename[]);
void printAdd(int);
void printAnd(int);
void printBr(int, int);
void printJmpRet(int);
void printJsrJsrr(int, int);
void printLd(int, int);
void printLdi(int, int);
void printLdr(int);
void printLea(int, int);
void printNot(int);
void printRti(int);
void printSt(int, int);
void printSti(int, int);
void printStr(int);
void printTrap(int);

//**************************************************
//Make sure to comment main out before submitting
//**************************************************

//int main()
//{
//	char filename[] = "test1.hex";
//	printAssembly(filename);
//}



void printAssembly(char filename[])
{
	FILE *infile;	
	infile = fopen(filename, "r");
	
	if (infile == NULL)	{
		printf("File %s is null.\n", filename);			
	} else {
    int count = 0;
    int instruction = 0;
    int pc = 0;    
    //Read the initial PC as an integer and save
    fscanf(infile, "%x", &pc);
    //While not at end of file and not over the limit
    while (fscanf(infile, "%x", &instruction) != EOF && count < LIMIT) {
      count++;  //Count number of lines for limit
      pc++;
      
      //Increment the PC
      //Figure out the oppcode from the high order 4 bits of the instruction
      //Use a big if or switch to call the appropriate print function.
      //Pass the function the full instruction and the PC, but only if necessary.
      
      int opcode = (instruction >> 12) & 15;
      int instOp = instruction & 0x0FFF;
      switch (opcode)
      {
            case 0:
                printAdd(instOp);
                break;
            case 1:
                printAnd(instOp);
                break;
            case 2:
                printBr(instOp, pc);
                break;
            case 3:
                printJmpRet(instOp);
                break;
            case 4:
                printJsrJsrr(instOp, pc);
                break;
            case 5:
                printLd(instOp, pc);
                break;
            case 6:
                printLdi(instOp, pc);
                break;
            case 7:
                printLdr(instOp);
                break;
            case 8:
                printLea(instOp, pc);
                break;
            case 9:
                printNot(instOp);
                break;
            case 10:
                printRti(instOp);
                break;
            case 11:
                printSt(instOp, pc);
                break;
            case 12:
                printSti(instOp, pc);
                break;
            case 13:
                break;
	        case 14:
                printStr(instOp);
                break;
            case 15:
                printTrap(instOp);
                break;
            default:
                break;
      } 
    }
  }
}
void printAdd(int instruction)
{
    int dr = (instruction  >> 9) & 7;
    int srcRone = (instruction & BASESRCREG) >> 6; 
    printf("ADD\tR%d, R%d, ", dr, srcRone);
    if(instruction & 0x0020)
    {
    	int imm = (instruction & 0x0001F) << 27;
    	imm = imm >> 27;
    	printf("#%d\n", imm);
    } 
    else
    {
    	int srcRtwo = instruction & 0x0007;
    	printf("R%d\n", srcRtwo);
    }
}

void printAnd(int instruction)
{
  int dr = (instruction & DREG) >> 9;
  int srcRone = (instruction & BASESRCREG) >> 6;
  if((instruction & 0x0020) >> 5)
  {
    int imm = (instruction & 0x001F) << 27;
    imm = imm >> 27;
    printf("AND\tR%d, R%d, #%d\n", dr, srcRone, imm);
  }
  else
  {
    int srcRtwo = instruction & 0x0007;
    printf("AND\tR%d, R%d, R%d\n", dr, srcRone, srcRtwo);
  }
}

void printBr(int instruction, int pc)
{
    int n = (instruction & 0x0800) >> 11;
    int z = (instruction & 0x0400) >> 10;
    int p = (instruction & 0x0200) >> 9;
    int offset = (instruction & PCOFF9) << 23;
    offset = offset >> 23;
    printf("BR");
    if(n)
        printf("N");
    if(z)
        printf("Z");
    if (p)
        printf("P");
     
    printf("\tx%X\n", pc + offset);
    
}

void printJmpRet(int instruction)
{
    int br = (instruction & BASESRCREG) >> 6;
    if(br == 7)
    {
        printf("RET\n");
    }
    else
    {
        printf("JMP\tR%d\n", br);
    }
}

void printJsrJsrr(int instruction, int pc)
{
    if (instruction >> 11)
    {
    	int offset = (instruction & 0x07FF) << 21;
    	offset = offset >> 21;
    	printf("JSR\tx%X\n", pc + offset);
    }
    else
    {
    	int br = (instruction & BASESRCREG) >> 6;
     	printf("JSRR\tR%d\n", br);
    }
}

void printLd(int instruction, int pc)
{
    int dr = ((instruction & DREG) >> 9) & 7;
    int offset = (instruction & PCOFF9) << 23;
    offset = offset >> 23;
    printf("LD\tR%d, x%X\n", dr, pc + offset);
}

void printLdi(int instruction, int pc)
{
    int dr = ((instruction & DREG) >> 9) & 7;
    int offset = (instruction & PCOFF9) << 23;
    offset = offset >> 23;
    printf("LDI\tR%d, x%X\n", dr, pc + offset);
}

void printLdr(int instruction)
{
    int dr = ((instruction & DREG) >> 9) &7;
    int br = (instruction & BASESRCREG) >> 6;
    int offset = (instruction & 0x003F) << 26;
    offset = offset >> 26;
    printf("LDR\tR%d, R%d, #%d\n", dr, br, offset); 
}
    
void printLea(int instruction, int pc)
{
    int dr = ((instruction & DREG) >> 9) & 7;
    int offset = (instruction & PCOFF9) << 23;
    offset = offset >> 23;
    printf("LEA\tR%d, x%X\n", dr, pc + offset);
}

void printNot(int instruction)
{
    int dr =( (instruction & DREG) >> 9) & 7;
    int srcR = (instruction & BASESRCREG) >> 6;
    printf("NOT\tR%d, R%d\n", dr, srcR);
}

void printRti(int instruction)
{
    printf("RTI\n");
}

void printSt(int instruction, int pc)
{
    int dr = ((instruction & DREG) >> 9) & 7;
    int offset = (instruction & PCOFF9) << 23;
    offset = offset >> 23;
    printf("ST\tR%d, x%X\n", dr, pc + offset);
}

void printSti(int instruction, int pc)
{
    int srcR = (instruction & DREG) >> 9;
    int offset = (instruction & PCOFF9) << 23;
    offset = offset >> 23;
    printf("STI\tR%d, x%X\n", srcR, pc + offset);
}

void printStr(int instruction)
{
    int srcR = (instruction & DREG) >> 9;
    int br = (instruction & BASESRCREG) >> 6;
    int offset = (instruction & 0x003F) << 26;
    offset = offset >> 26;
    printf("STR\tR%d, R%d, #%d\n", srcR, br, offset);
}

void printTrap(int instruction)
{
    int trapVect = instruction & 0x00FF;
    switch(trapVect)
    {
        case 0x0020:
            printf("GETC\n");
            break;
        case 0x0021:
            printf("OUT\n");
            break;
        case 0x0022:
            printf("PUTS\n");
            break;
        case 0x0023:
            printf("IN\n");
            break;
        case 0x0024:
            printf("PUTSP\n");
            break;
        case 0x0025:
            printf("HALT\n");
            break;
        default:
            break;
    }
}














