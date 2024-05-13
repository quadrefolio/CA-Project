#include <stdio.h>

#define MAX_LINE_LENGTH 100
#define MAX_INSTRUCTION_LENGTH 10
#define MAX_OPERAND_LENGTH 10

void print_binary(int num, int size) {
    for (int bit = size; bit >= 0; bit--) {
        printf("%d", (num >> bit) & 1);
    }
    printf("\n");
}

int main() {
    

    FILE *file = fopen("instructions.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
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


        // sscanf(line, "%s %s %s %s", instruction, operand1, operand2, operand3);
        // printf("Instruction: %s, Operand1: %s, Operand2: %s, Operand3: %s\n", instruction, operand1, operand2, operand3);
    }

    printf("\n");

    fclose(file);
    return 0;
}
