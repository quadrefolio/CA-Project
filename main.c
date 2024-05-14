#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMORY_SIZE 2048
#define MAX_INSTRUCTION_ADDRESS 1023
#define MIN_DATA_ADDRESS 1024


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

void print_binary(int num, int size) {
    for (int bit = size; bit >= 0; bit--) {
        printf("%d", (num >> bit) & 1);
    }
    printf("\n");
}


int main() {

    //Parsing of file
    FILE *file = fopen("instructions.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    char line[256]; // Buffer to hold each line
    char instructionTerm[10];
    int instruction;

    while (fgets(line, sizeof(line), file)) {
        int field1;
        int field2;
        int field3;
        sscanf(line, "%s R%d, R%d, R%d", instructionTerm, &field1, &field2, &field3);

        int opcode;
        int operand1 = field1;
        int operand2 = field2;
        int operand3 = field3;
        int imm = field3;
        int shamt = field3;
        int address = field1;

        printf("%d\n", operand1);
        printf("%d\n", operand2);
        printf("%d\n", operand3);
        printf("%d\n", imm);
        printf("%d\n", shamt);
        printf("%d\n", address);
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
