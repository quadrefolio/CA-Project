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
    for (int bit = size; bit >= 0; bit--) {
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

    // //Instruction to be sent to the instruction part of the main memory
    int instruction;

    //Parsing of file
    FILE *file = fopen("instructions.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    char instructionTerm[10];
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        int field1;
        int field2;
        int field3;
        sscanf(line, "%s R%d, R%d, R%d", instructionTerm, &field1, &field2, &field3);

        printf("Field1 is :%d\n", field1);
        printf("Field2 is :%d\n", field2);
        printf("Field3 is :%d\n", field3);

        int opcode;
        int operand1 = field1;
        int operand2 = field2;
        int operand3 = field3;
        int imm = field3;
        int shamt = field3;
        int address = field1;

        printf("Field1 is :%d\n", operand1);
        printf("Field1 is :%d\n", operand2);
        printf("Field1 is :%d\n", operand3);
        printf("Field1 is :%d\n", imm);
        printf("Field1 is :%d\n", shamt);
        printf("Field1 is :%d\n", address);
        char instructionWord[MAX_INSTRUCTION_LENGTH];
        unsigned int opcode;
        int operand1;
        int operand2;
        int operand3;
        int shamt;
        int imm;
        int address;

        // char operand1[MAX_OPERAND_LENGTH];
        // char operand2[MAX_OPERAND_LENGTH];
        // char operand3[MAX_OPERAND_LENGTH];

        sscanf(line, "%s ", instructionWord);
        printf("%s\n", instructionWord);


        if(strcmp(instructionWord,"ADD") == 0){
            opcode = 0b0000; //opcode = 0
            print_binary(opcode, 3);
            printf("Add instruction\n");
        }
        else if(strcmp(instructionWord, "SUB") == 0){
            opcode = 0b0001; // opcode = 1
            print_binary(opcode, 3);
            printf("Sub instruction\n");
        }
        else if(strcmp(instructionWord, "MUL") == 0){
            opcode = 0b0010; // opcode = 2
            print_binary(opcode, 3);
            printf("Mul instruction\n");
        }
        else if(strcmp(instructionWord, "MOVI") == 0){
            opcode = 0b0011; // opcode = 3
            print_binary(opcode, 3);
            printf("Movi instruction\n");
        }
        else if(strcmp(instructionWord, "JEQ") == 0){
            opcode = 0b0100; // opcode = 4
            print_binary(opcode, 3);
            printf("Jeq instruction\n");
        }
        else if(strcmp(instructionWord, "AND") == 0){
            opcode = 0b0101; // opcode = 5
            print_binary(opcode, 3);
            printf("And instruction\n");
        }
        else if(strcmp(instructionWord, "XORI") == 0){
            opcode = 0b0110; // opcode = 6
            print_binary(opcode, 3);
            printf("Xori instruction\n");
        }
        else if(strcmp(instructionWord, "JMP") == 0){
            opcode = 0b0111; // opcode = 7
            print_binary(opcode, 3);
            printf("Jmp instruction");
        }
        else if(strcmp(instructionWord,"LSL") == 0){
            opcode = 0b1000; // opcode = 8
            print_binary(opcode, 3);
            printf("Lsl instruction\n");
        }
        else if(strcmp(instructionWord,"LSR") == 0){
            opcode = 0b1001; // opcode = 9
            print_binary(opcode, 3);
            printf("Lsr instruction\n");
        }
        else if(strcmp(instructionWord, "MOVR") == 0){
            opcode = 0b1010; // opcode = 10
            print_binary(opcode, 3);
            printf("Movr instruction\n");
        }
        else if(strcmp(instructionWord, "MOVM") == 0){
            opcode = 0b1011; // opcode = 11
            print_binary(opcode, 3);
            printf("Movm instruction\n");
        }
        else {
            printf("Invalid instruction\n");
        }
        
        // if
        // (
        //     strcmp(instructionTerm, "ADD") || strcmp(instructionTerm, "SUB") || strcmp(instructionTerm, "MUL") || strcmp(instructionTerm, "AND") ||
        //     strcmp(instructionTerm, "LSL") || strcmp(instructionTerm, "LSR")
        // ){
        //     sscanf(line, "");
            // printf("%s", operand1);
            // printf("%s", operand2);
            // printf("%s", operand3);

        //     if (strcmp(instructionTerm, "ADD") == 0) {
        //         opcode = 0;
        //     } else if (strcmp(instructionTerm, "SUB") == 0) {
        //         opcode = 1;
        //     } else if (strcmp(instructionTerm, "MUL") == 0) {
        //         opcode = 2;
        //     } else if (strcmp(instructionTerm, "AND") == 0) {
        //         opcode = 5;
        //     } else if (strcmp(instructionTerm, "LSL") == 0) {
        //         opcode = 8;
        //     } else if (strcmp(instructionTerm, "LSR") == 0) {
        //         opcode = 9;
        //     }
        //     MainMemory[PC] = (opcode << 22) | (operand1 << 17) | (operand2 << 12) | (operand3 << 7);
        //     PC++;
        // } else if (strcmp(instructionTerm, "ADDI") || strcmp(instructionTerm, "SUBI") || strcmp(instructionTerm, "MULI") || strcmp(instructionTerm, "ANDI")){
        //     sscanf(line, "%s R%d, R%d, #%d", instructionTerm, &operand1, &operand2, &imm);
        //     if (strcmp(instructionTerm, "ADDI") == 0) {
        //         opcode = 6;
        //     } else if (strcmp(instructionTerm, "SUBI") == 0) {
        //         opcode = 7;
        //     } else if (strcmp(instructionTerm, "MULI") == 0) {
        //         opcode = 8;
        //     } else if (strcmp(instructionTerm, "ANDI") == 0) {
        //         opcode = 9;
        //     }
        //     MainMemory[PC] = (opcode << 22) | (operand1 << 17) | (operand2 << 12) | (imm << 7);
        //     PC++;
        // } else if (strcmp(instructionTerm, "LD") || strcmp(instructionTerm, "ST")){
        //     sscanf(line, "%s R%d, #%d", instructionTerm, &operand1, &address);
        //     if (strcmp(instructionTerm, "LD") == 0) {
        //         opcode = 10;
        //     } 
        //     // else if (strcmp(instructionTerm, "ST") == 0) {
        //     //     opcode

        // }
    }

    printf("\n");

    fclose(file);
    return 0;
}
