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

void print_binary(int num, int size) {
    for (int bit = size - 1; bit >= 0; bit--) {
        printf("%d", (num >> bit) & 1);
    }
    printf("\n");
}

//Initializing the Main Memory and the Register File (General Purpose Registers)
int MainMemory[MEMORY_SIZE];
int RegisterFile[32];
int PC;

void initMemory() {
    for (int i = 0; i < 2048; i++) {
        MainMemory[i] = 0;
    }
    for (int i = 0; i < 32; i++){
        RegisterFile[i] = 0; //R0 to R31
    }
    PC = 0;
}


int main() {
    initMemory();
    printf("%d \n",PC);
    // //Instruction to be sent to the instruction part of the main memory
    int instruction;

    //Parsing of file
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

        //Case of ADD, SUB, MUL, AND
        if(sscanf(line, "%s R%d R%d R%d\n", instructionTerm, &operand1, &operand2, &operand3) == 4){

            if(strcmp(instructionTerm,"ADD") == 0 ||
                strcmp(instructionTerm,"SUB") == 0 ||
                strcmp(instructionTerm,"MUL") == 0||
                strcmp(instructionTerm,"AND") == 0)
            {
                printf("%s\n", instructionTerm);
                printf("First Register is :%d\n", operand1);
                printf("Second Register is :%d\n", operand2);
                printf("Third Register is :%d\n", operand3);

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
                printf("%s\n", instructionTerm);
                printf("Address is :%d\n", address);

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
                printf("%s\n", instructionTerm);
                printf("First Register is :%d\n", operand1);
                printf("Immediate is :%d\n", imm);

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
                shamt = imm;
                printf("%s\n", instructionTerm);
                printf("First Register is :%d\n", operand1);
                printf("Second Register is :%d\n", operand2);
                printf("Shamt is :%d\n", shamt);
                printf("Immediate is :%d\n", imm);

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
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm, "SUB") == 0){
            opcode = 1;
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm, "MUL") == 0){
            opcode = 2;
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm, "MOVI") == 0){
            opcode = 3;
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm, "JEQ") == 0){
            opcode = 4;
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm, "AND") == 0){
            opcode = 5;
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm, "XORI") == 0){
            opcode = 6;
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm, "JMP") == 0){
            opcode = 7;
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm,"LSL") == 0){
            opcode = 8;
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm,"LSR") == 0){
            opcode = 9;
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm, "MOVR") == 0){
            opcode = 10;
            // print_binary(opcode, 3);
        }
        else if(strcmp(instructionTerm, "MOVM") == 0){
            opcode = 11;
            // print_binary(opcode, 3);
        }

        //Combining the fields into the instruction
        switch(opcode){
            case 0:
            case 1:
            case 2:
            case 5:
                instruction = (opcode << 28) | (operand1 << 23) | (operand2 << 18) | (operand3 << 13);
                break;
            case 4:
            case 6:
            case 8:
            case 9:
            case 10:
            case 11:
                instruction = (opcode << 28) | (operand1 << 23) | (operand2 << 18) | imm;
                break;
            case 3:
                instruction = (opcode << 28) | (operand1 << 23) | (0b00000 << 18) | imm;
                break;
            case 7:
                instruction =  (opcode << 28) | address;
                break;
            default:break;

            //Store the instruction in the Instruction part of the main memory
            MainMemory[PC] = instruction;
            PC++;
            printf("%d\n", PC);
        }

        
    }

    printf("\n");

    fclose(file);
    return 0;
}
