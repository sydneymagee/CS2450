#include <stdio.h>
#include <string.h>
#define LIMIT 40
#define DREG 0x0E00
#define PCOFF9 0x01FF
#define BASESRCREG 0x01C0

void printAssembly(char filename[]);
void printBr(int, int);
void printAdd(int);
void printLd(int, int);
void printSt(int, int);
void printJsrJsrr(int, int);
void printAnd(int);
void printLdr(int);
void printStr(int);
void printRti(int);
void printNot(int);
void printLdi(int, int);
void printSti(int, int);
void printJmpRet(int);
void printLea(int, int);
void printTrap(int);

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
    fscanf(infile, "%x", &pc); //Read the first hex val as the starting pc.
    while (fscanf(infile, "%x", &instruction) != EOF && count < LIMIT) {
      count++;  //Count number of lines for limit
      pc++; //Increment the PC
      int opcode = instruction >> 12; //Figure out the opcode from the high 4 bits. 
      int instOp = instruction & 0x0FFF; //Trim the opcode from the instruction to pass.
      switch(opcode)
      {
        case 0:
          printBr(instOp, pc);
          break;
        case 1:
          printAdd(instOp);
          break;
        case 2:
          printLd(instOp, pc);
          break;
        case 3:
          printSt(instOp, pc);
          break;
        case 4:
          printJsrJsrr(instOp, pc);
          break;
        case 5:
          printAnd(instOp);
          break;
        case 6:
          printLdr(instOp);
          break;
        case 7:
          printStr(instOp);
          break;
        case 8:
          printRti(instOp);
          break;
        case 9:
          printNot(instOp);
          break;
        case 10:
          printLdi(instOp, pc);
          break;
        case 11:
          printSti(instOp, pc);
          break;
        case 12:
          printJmpRet(instOp);
          break;
        case 13:
          break;
        case 14:
          printLea(instOp, pc);
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

void printBr(int instruction, int pc)
{
  int n = (instruction & 0x0800) >> 11;
  int z = (instruction & 0x0400) >> 10;
  int p = (instruction & 0x0200) >> 9;
  int offset = (instruction & PCOFF9) << 23; //Mask off offset bits, then shift to correct sign extension.
  offset = offset >> 23;
  printf("BR");
  if(n)
    printf("N");
  if(z)
    printf("Z");
  if(p)
    printf("P");
  printf("\tx%X\n", pc + offset);
}

void printAdd(int instruction)
{
  int dr = (instruction & DREG) >> 9; //Mask off destination register and shift right to get decimal val.
  int srcRone = (instruction & BASESRCREG) >> 6; 
  printf("ADD\tR%d, R%d, ", dr, srcRone);
  if(instruction & 0x0020) //check if bit 5 is set to 1
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

void printLd(int instruction, int pc)
{
  int dr = (instruction & DREG) >> 9;
  int offset = (instruction & PCOFF9) << 23;
  offset = offset >> 23;
  printf("LD\tR%d, x%X\n", dr, pc + offset);
}

void printSt(int instruction, int pc)
{
  int dr = (instruction & DREG) >> 9;
  int offset = (instruction & PCOFF9) << 23;
  offset = offset >> 23;
  printf("ST\tR%d, x%X\n", dr, pc + offset);
}

void printJsrJsrr(int instruction, int pc)
{
  if(instruction >> 11) //check bit 12 to determine if JSR or JSRR was called.
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

void printLdr(int instruction)
{
  int dr = (instruction & DREG) >> 9;
  int br = (instruction & BASESRCREG) >> 6;
  int offset = (instruction & 0x003F) << 26;
  offset = offset >> 26;
  printf("LDR\tR%d, R%d, #%d\n", dr, br, offset); 
}

void printStr(int instruction)
{
  int srcR = (instruction & DREG) >> 9;
  int br = (instruction & BASESRCREG) >> 6;
  int offset = (instruction & 0x003F) << 26;
  offset = offset >> 26;
  printf("STR\tR%d, R%d, #%d\n", srcR, br, offset);
}

void printRti(int instruction)
{
  printf("RTI\n");
}

void printNot(int instruction)
{
  int dr = (instruction & DREG) >> 9;
  int srcR = (instruction & BASESRCREG) >> 6;
  printf("NOT\tR%d, R%d\n", dr, srcR);
}

void printLdi(int instruction, int pc)
{
  int dr = (instruction & DREG) >> 9;
  int offset = (instruction & PCOFF9) << 23;
  offset = offset >> 23;
  printf("LDI\tR%d, x%X\n", dr, pc + offset);
}

void printSti(int instruction, int pc)
{
  int srcR = (instruction & DREG) >> 9;
  int offset = (instruction & PCOFF9) << 23;
  offset = offset >> 23;
  printf("STI\tR%d, x%X\n", srcR, pc + offset);
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

void printLea(int instruction, int pc)
{
  int dr = (instruction & DREG) >> 9;
  int offset = (instruction & PCOFF9) << 23;
  offset = offset >> 23;
  printf("LEA\tR%d, x%X\n", dr, pc + offset);
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
