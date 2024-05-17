#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//GO into Intellisense configuration in the C/C++ extension and config the path to be usr/bin/gcc

#define MEMORY_SIZE 2048
#define MAX_INSTRUCTION_ADDRESS 1023
#define MIN_DATA_ADDRESS 1024
#define MAX_LINE_LENGTH 100
#define MAX_INSTRUCTION_LENGTH 10
#define MAX_OPERAND_LENGTH 10

//Initializing the Main Memory and the Register File (General Purpose Registers)
int MainMemory[MEMORY_SIZE];
int RegisterFile[32];
int PC;
int numInstructions;

//Needs to be tested
void initMemory() {
    for (int i = 0; i < 2048; i++) {
        MainMemory[i] = 0;
    }
    for (int i = 0; i < 32; i++){
        RegisterFile[i] = 0; //R0 to R31
    }
    PC = 0;
}

void print_binary(int num, int size) {
    for (int bit = size - 1; bit >= 0; bit--) {
        printf("%d", (num >> bit) & 1);
    }
    printf("\n");
}

int translateFile() {

    //Initializing the memory and GPRs
    printf("Initializing the memory and the register file...\n\n");
    initMemory();

    //Instruction to be sent to the instruction part of the main memory
    int instruction;

    //Parsing file
    printf("Opening the file...\n\n");
    FILE *file = fopen("instructions.txt", "r");
    if (file == NULL) {
        perror("Could not open file\n");
        return 1;
    }

    char instructionTerm[MAX_INSTRUCTION_LENGTH];
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {

        //Fetching different formats of the instruction (R, I and J)
        int operand1;
        int operand2;
        int operand3;
        int imm;
        int shamt;
        int address;

        int num = PC + 1;


        printf("Instruction %d in address %d: %s", num, PC, line);
        //Case of ADD, SUB, MUL, AND
        if(sscanf(line, "%s R%d R%d R%d\n", instructionTerm, &operand1, &operand2, &operand3) == 4){

            if(strcmp(instructionTerm,"ADD") == 0 ||
                strcmp(instructionTerm,"SUB") == 0 ||
                strcmp(instructionTerm,"MUL") == 0||
                strcmp(instructionTerm,"AND") == 0)
            {
                printf("Instruction term : %s\n", instructionTerm);
                printf("First Register : %d\n", operand1);
                printf("Second Register : %d\n", operand2);
                printf("Third Register : %d\n", operand3);

            }
            else {
                perror("Invalid instruction: ");
                printf("%s\n", instructionTerm);
                return 1;
            }
            
        }

        //Case of JMP
        else if((sscanf(line, "%s %d\n", instructionTerm, &address) == 2)){

            if(strcmp(instructionTerm,"JMP") == 0)
            {
                printf("Instruction term : %s\n", instructionTerm);
                printf("Address : %d\n", address);

            }
            else {
                perror("Invalid instruction: ");
                printf("%s\n", instructionTerm);
                return 1;
            }
            
        }

        // //Case of MOVI
        else if(sscanf(line, "%s R%d %d\n", instructionTerm, &operand1, &imm) == 3){

            if(strcmp(instructionTerm,"MOVI") == 0)
            {
                printf("Instruction term : %s\n", instructionTerm);
                printf("First Register : %d\n", operand1);
                printf("Immediate : %d\n", imm);

            }
            else {
                perror("Invalid instruction: ");
                printf("%s\n", instructionTerm);
                return 1;
            }
            
        }

        //Case of JEQ, XORI, LSL, LSR, MOVR, MOVM
        else if(sscanf(line, "%s R%d R%d %d\n", instructionTerm, &operand1, &operand2, &imm) == 4){

            if(strcmp(instructionTerm,"JEQ") == 0 ||
                strcmp(instructionTerm,"XORI") == 0||
                strcmp(instructionTerm,"LSL") == 0||
                strcmp(instructionTerm,"LSR") == 0||
                strcmp(instructionTerm,"MOVR") == 0||
                strcmp(instructionTerm,"MOVM") == 0)
            {
                if(strcmp(instructionTerm,"MOVM") == 0) printf("\n");
                shamt = imm; //Needs to be checked
                printf("Instruction term : %s\n", instructionTerm);
                printf("First Register : %d\n", operand1);
                printf("Second Register : %d\n", operand2);
                if(strcmp(instructionTerm,"LSL") == 0||
                strcmp(instructionTerm,"LSR") == 0){
                    printf("Shamt : %d\n", shamt);
                }
                else {
                    printf("Immediate : %d\n", imm);
                }
            }
            else {
                perror("Invalid instruction: ");
                printf("%s\n", instructionTerm);
                return 1;
            } 
        }
        else {
            perror("The instruction is of an unknown format. Cannot translate the instruction.\n");
            return 1;
        }

        unsigned int opcode;

        if(strcmp(instructionTerm,"ADD") == 0){
            opcode = 0;
        }
        else if(strcmp(instructionTerm, "SUB") == 0){
            opcode = 1;
        }
        else if(strcmp(instructionTerm, "MUL") == 0){
            opcode = 2;
        }
        else if(strcmp(instructionTerm, "MOVI") == 0){
            opcode = 3;
        }
        else if(strcmp(instructionTerm, "JEQ") == 0){
            opcode = 4;
        }
        else if(strcmp(instructionTerm, "AND") == 0){
            opcode = 5;
        }
        else if(strcmp(instructionTerm, "XORI") == 0){
            opcode = 6;
        }
        else if(strcmp(instructionTerm, "JMP") == 0){
            opcode = 7;
        }
        else if(strcmp(instructionTerm,"LSL") == 0){
            opcode = 8;
        }
        else if(strcmp(instructionTerm,"LSR") == 0){
            opcode = 9;
        }
        else if(strcmp(instructionTerm, "MOVR") == 0){
            opcode = 10;
        }
        else if(strcmp(instructionTerm, "MOVM") == 0){
            opcode = 11;
        }

        //Combining the fields into the instruction
        switch(opcode){
            //ADD, SUB, MUL, AND
            case 0:
            case 1:
            case 2:
            case 5:
                instruction = (opcode << 28) | (operand1 << 23) | (operand2 << 18) | (operand3 << 13);
                break;

            //JEQ, XORI, MOVR, MOVM
            case 4:
            case 6:
            case 10:
            case 11:
                instruction = (opcode << 28) | (operand1 << 23) | (operand2 << 18) | imm;
                break;

            //LSL, LSR
            case 8:
            case 9:
                instruction = (opcode << 28) | (operand1 << 23) | (operand2 << 18) | (0b00000 << 13) | shamt;
                break;

            //MOVI
            case 3:
                instruction = (opcode << 28) | (operand1 << 23) | (0b00000 << 18) | imm;
                break;

            //JMP
            case 7:
                instruction =  (opcode << 28) | address;
                break;

            default:
                break;
        }

        //Store the instruction in the Instruction part of the main memory
        MainMemory[PC] = instruction;
        printf("Value in Main Memory : %d\n", MainMemory[PC]);
        printf("Instruction format that will be saved in the memory: ");
        print_binary(instruction, 32);
        PC++;
        printf("\n");
    }

    printf("\n");

    fclose(file);
    numInstructions = PC;
    PC = 0;
    return 0;
}

int Memory(int destination,int value,int write){
    printf("\n");
    printf("Memory Access Phase....\n");
    if(write == 1){
        MainMemory[destination]=value;
        return 0;
    } 
    return MainMemory[destination];
}

void writeback (int reg,int value){
    printf("\n");
    printf("Write back Phase.....\n");
    printf("Writing back the result to the destination register: R%d\n", reg);
    RegisterFile[reg]=value;
}

void exec (int oPCode,int R1,int R2,int R3,int shamt,int immediate,int address ){
    int result;
    switch (oPCode)
    {
        case 0:
            if(R1 !=0 ){
                result=RegisterFile[R2]+RegisterFile[R3];
                printf("value of result inside the exec add %d \n",result);
                printf("\nNo memory access is required....\n");
                writeback(R1,result);
                printf("value of register after the write back in the register file exec add %d \n",RegisterFile[R1]);
                }

                // write back or mem not implemented yet donot forget to check for the R0 when writing back
                break;
        case 1:
            if(R1 !=0){
                result=RegisterFile[R2] - RegisterFile[R3];
                printf("value of result inside the exec sub %d \n",result);
                printf("\nNo memory access is required....\n");
                writeback(R1,result);
                printf("value of register after the write back in the register file exec sub %d \n",RegisterFile[R1]);
                }
                // write back or mem not implemented yet donot forget to check for the R0 when writing back
                break;
        case 2:
                if(R1 !=0){
                result=RegisterFile[R2] * RegisterFile[R3];
                printf("value of result inside the exec mul %d \n",result);
                printf("\nNo memory access is required....\n");
                writeback(R1,result);
                printf("value of register after the write back in the register file exec mul %d \n",RegisterFile[R1]);
                }
                    // write back or mem not implemented yet donot forget to check for the R0 when writing back
                break;
        case 3:
                if(R1!=0){
                    printf("value of result inside the exec movi %d \n",RegisterFile[R1]);
                    printf("\nNo memory access is required....\n");
                    writeback(R1,immediate);
                    printf("value of register after the write back in the register file exec movi %d \n",RegisterFile[R1]);
                }
                    
                break;
        case 4:
                if(R1==R2){
                    printf("value of PC before the jeq exec  %d \n",PC);
                    PC=PC+immediate;
                    printf("value of PC after the jeq exec  %d \n",PC);
                }
                break;
        case 5:
                if(R1!=0){
                    result=RegisterFile[R2] & RegisterFile[R3];
                    printf("value of result inside the exec And %d \n",result);
                    printf("\nNo memory access is required....\n");
                    writeback(R1,result);
                    printf("value of register after the write back in the register file exec And %d \n",RegisterFile[R1]);

                //might be a problem when anding because the values might not be binary to be checked 
                }
                break;
        case 6:
                if(R1!=0){
                    result=RegisterFile[R2]^ immediate;
                    printf("value of result inside the exec Xori %d \n",result);
                    printf("\nNo memory access is required....\n");
                    writeback(R1,result);
                    printf("value of register after the write back in the register file exec Xori %d \n",RegisterFile[R1]);
                //might be a problem when anding because the values might not be binary to be checked 
                }
                break;
        case 7:
                printf("value of PC inside the exec before jump %d \n",PC);
                PC=(PC & 0b11110000000000000000000000000000)  + address ;
                printf("value of PC inside the exec after jump %d \n",PC);
                break;
        case 8:
                if(R1!=0){
                    result=RegisterFile[R2]<< shamt;
                    printf("value of result inside the exec lsl %d \n",result);
                    printf("\nNo memory access is required....\n");
                    writeback(R1,result);
                    printf("value of register after the write back in the register file exec lsl %d \n",RegisterFile[R1]);
                    //might be a problem when anding because the values might not be binary to be checked 
                }
                
                break;
        case 9:
                if(R1!=0){
                    result=RegisterFile[R2]>> shamt;
                    printf("value of result inside the exec lsr %d \n",result);
                    printf("\nNo memory access is required....\n");
                    writeback(R1,result);
                    printf("value of register after the write back in the register file exec lsr %d \n",RegisterFile[R1]);
                //might be a problem when anding because the values might not be binary to be checked 
                }
                break;
        case 10:
                if(R1!=0){
                    int temp=RegisterFile[R2] + immediate;
                    printf("value of address inside the exec movr %d \n",temp);
                    result=Memory(temp,0,0);
                    printf("value of result read from memory exec  movr  %d \n",result);
                    printf("\nNo memory access is required....\n");
                    writeback(R1,result);
                    printf("value of result inside the register file after the write back exec  movr  %d \n",RegisterFile[R1]);
                    }
                break;
        case 11:
                int temp2 =RegisterFile[R2] + immediate;
                printf("value of address inside the exec movw %d \n",temp2);
                result=RegisterFile[R1];
                printf("value of result inside the before the write in memory exec  movw  %d \n",result);
                Memory(temp2,result,1);
                printf("value of result inside the memory the write in memory exec  movw  %d \n",MainMemory[R1]);
                break;
        
        default:
            printf("e4ma3 yabn el");
            break;
    }

}

void decode(int instruction){
int oPCode=(instruction & 0b11110000000000000000000000000000)>>28;
int Address=(instruction & 0b00001111111111111111111111111111);
int R1=(instruction & 0b00001111100000000000000000000000)>>23;
int R2=(instruction & 0b00000000011111000000000000000000)>>18;
int R3=(instruction & 0b00000000000000111110000000000000)>>13;
int shamt=(instruction & 0b00000000000000000001111111111111);
int immediate=(instruction & 0b00000000000000111111111111111111);
int check=(0b00000000000000100000000000000000 & immediate)>> 17;
if(check==1)
{
immediate=immediate | 0b11111111111111000000000000000000;                   
}
switch (oPCode)
{
case 0:
        exec(oPCode,R1,R2,R3,shamt,immediate,Address);
        printf("value of oPCode inside the decode ADD %d \n",oPCode);
        printf("value of R1 inside the decode ADD %d \n",R1);
        printf("value of R2 inside the decode ADD %d \n",R2);
        printf("value of R3 inside the decode ADD %d \n",R3);
        
    break;
case 1:
        exec(oPCode,R1,R2,R3,shamt,immediate,Address);
        printf("value of oPCode inside the decode sub %d \n",oPCode);
        printf("value of R1 inside the decode sub %d \n",R1);
        printf("value of R2 inside the decode sub %d \n",R2);
        printf("value of R3 inside the decode sub %d \n",R3);
    break;
    case 2:
        exec(oPCode,R1,R2,R3,shamt,immediate,Address);
         printf("value of oPCode inside the decode mul %d \n",oPCode);
        printf("value of R1 inside the decode mul %d \n",R1);
        printf("value of R2 inside the decode mul %d \n",R2);
        printf("value of R3 inside the decode mul %d \n",R3);

            break;

        case 3:// the value of r2 must be 0
            printf("value of oPCode inside the decode movi %d \n",oPCode);
            printf("value of R%d inside the decode movi %d \n",R1, RegisterFile[R1]);
            printf("value of R%d inside the decode movi %d \n",R2, RegisterFile[R2]);
            printf("value of immediate inside the decode movi %d \n",immediate);
            break;

        case 4:
            printf("value of oPCode inside the decode jeq %d \n",oPCode);
            printf("value of R%d inside the decode jeq %d \n",R1, RegisterFile[R1]);
            printf("value of R%d inside the decode jeq %d \n",R2, RegisterFile[R2]);
            printf("value of immediate inside the jeq  %d \n",immediate);
            break;

        case 5:
            printf("value of oPCode inside the decode And %d \n",oPCode);
            printf("value of R%d inside the decode And %d \n",R1, RegisterFile[R1]);
            printf("value of R%d inside the decode And %d \n",R2, RegisterFile[R2]);
            printf("value of immediate inside the And %d \n",RegisterFile[R3]);
            break;

        case 6:
            printf("value of oPCode inside the decode xori %d \n",oPCode);
            printf("value of R%d inside the decode xori %d \n",R1, RegisterFile[R1]);
            printf("value of R%d inside the decode xori %d \n",R2, RegisterFile[R2]);
            printf("value of immediate inside the xori  %d \n",immediate);
            break;

        case 7:
            printf("value of oPCode inside the decode jmp %d \n",oPCode);
            printf("value of immediate inside the decode jmp %d \n",Address);
            break;

        case 8:
            printf("value of oPCode inside the decode lsl %d \n",oPCode);
            printf("value of R%d inside the decode lsl %d \n",R1, RegisterFile[R1]);
            printf("value of R%d inside the decode lsl %d \n",R2, RegisterFile[R2]);
            printf("value of immediate inside the decode lsl %d \n",shamt);
            break;

        case 9:
            printf("value of oPCode inside the decode lsr %d \n",oPCode);
            printf("value of R%d inside the decode lsr %d \n",R1, RegisterFile[R1]);
            printf("value of R%d inside the decode lsr %d \n",R2, RegisterFile[R2]);
            printf("value of immediate inside the decode lsr %d \n",shamt);
            break;

        case 10:
            printf("value of oPCode inside the decode movr %d \n",oPCode);
            printf("value of R%d inside the decode movr %d \n",R1, RegisterFile[R1]);
            printf("value of R%d inside the decode movr %d \n",R2, RegisterFile[R2]);
            printf("value of immediate inside the decode movr %d \n",immediate);
            break;

        case 11:
            printf("value of oPCode inside the decode movm %d \n",oPCode);
            printf("value of R%d inside the decode movm %d \n",R1, RegisterFile[R1]);
            printf("value of R%d inside the decode movm %d \n",R2, RegisterFile[R2]);
            printf("value of immediate inside the decode movm %d \n",immediate);
            break;
        
        default:
            perror("error in the decode");
            return 1;
    }

    printf("\n");
    printf("Executing the instruction...\n");
    exec(oPCode,R1,R2,R3,shamt,immediate,Address);
}

void fetch(){
    int instruction = MainMemory[PC];
    printf("Fetching instruction from address %d: ", PC); print_binary(instruction, 32);
    printf("\n");
    if(PC <= 1023){
        printf("Decoding instruction : "); print_binary(instruction, 32);
        decode(instruction);
        printf("\nIncrementing PC...\n");
        PC++;
    }
}

int main(){

    printf("Parsing the file...\n\n");
    translateFile();

    printf("-------------------\n\n");

    fetch();

    return 0;
    
}
