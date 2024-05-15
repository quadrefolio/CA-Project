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


        printf("Instruction %d: %s", num, line);
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

void exec (int opcode,int R1,int R2,int R3,int shamt,int immediate,int address ){
    int result;
    switch (opcode)
    {
        case 0:
            result=RegisterFile[R2]+RegisterFile[R3];
            // write back or mem not implemented yet donot forget to check for the R0 when writing back
            break;
        case 1:
            result=RegisterFile[R2]-RegisterFile[R3];
            // write back or mem not implemented yet donot forget to check for the R0 when writing back
        break;
        case 2:
            result=RegisterFile[R2]*RegisterFile[R3];
            // write back or mem not implemented yet donot forget to check for the R0 when writing back
        break;
        case 3:
        if(R1!=0){
            RegisterFile[R1]=immediate;
        }
            
        break;
        case 4:
        if(R1==R2){
            PC = PC + immediate;
        }
        break;
        case 5:
            if(R1!=0){
            RegisterFile[R1]=RegisterFile[R2]& RegisterFile[R3];
            //might be a problem when anding because the values might not be binary to be checked 
        }
        break;
        case 6:
            if(R1!=0){
            RegisterFile[R1]=RegisterFile[R2]^ immediate;
            //might be a problem when anding because the values might not be binary to be checked 
        }
        break;
        case 7:
        
            PC = (PC & 0b1111) << 28 ||address ;

        break;
        case 8:
            exec(opcode,R1,R2,0,shamt,0,0);
        break;
        case 9:
            exec(opcode,R1,R2,0,shamt,0,0);
        break;
        case 10:
            exec(opcode,R1,R2,0,0,immediate,0);
        break;
        case 11:
            exec(opcode,R1,R2,0,0,immediate,0);
        break;
        
        default:
            break;
    }

}

void decode(int instruction){
    int opcode=(instruction & 0b11110000000000000000000000000000)>>28;
    int Address=(instruction & 0b00001111111111111111111111111111);
    int R1=(instruction & 0b00001111100000000000000000000000)>>23;
    int R2=(instruction & 0b00000000011111000000000000000000)>>18;
    int R3=(instruction & 0b00000000000000111110000000000000)>>13;
    int shamt=(instruction & 0b00000000000000000001111111111111);
    int immediate=(instruction & 0b00000000000000111111111111111111);

    switch (opcode)
    {
    case 0:
            exec(opcode,R1,R2,R3,0,0,0);
        break;
    case 1:
            exec(opcode,R1,R2,R3,0,0,0);
        break;
        case 2:
            exec(opcode,R1,R2,R3,0,0,0);
        break;
        case 3:
            exec(opcode,R1,R2,0,0,immediate,0);
        break;
        case 4:
            exec(opcode,R1,R2,0,0,immediate,0);
        break;
        case 5:
            exec(opcode,R1,R2,R3,0,0,0);
        break;
        case 6:
            exec(opcode,R1,R2,0,0,immediate,0);
        break;
        case 7:
            exec(opcode,0,0,0,0,0,Address);
        break;
        case 8:
            exec(opcode,R1,R2,0,shamt,0,0);
        break;
        case 9:
            exec(opcode,R1,R2,0,shamt,0,0);
        break;
        case 10:
            exec(opcode,R1,R2,0,0,immediate,0);
        break;
        case 11:
            exec(opcode,R1,R2,0,0,immediate,0);
        break;
        
    default:
        printf("error");
        break;
    }
}

void fetch(){
    int instruction=MainMemory[PC];
    if(PC<=1023){
        decode(instruction); 
        PC++;
    }
}

int main(){

    printf("Parsing the file...\n\n");
    translateFile();
    printf("-------------------\n\n");
    printf("Fetching the instructions...\n\n");
    fetch();
    return 0;

}
