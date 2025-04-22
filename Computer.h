#ifndef COMPUTER_H
#define COMPUTER_H

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <fstream>
#include <unistd.h>


#define EXIT (-99999)

/****Input/output operations: ****/
#define READ 10 // Read a word from the keyboard into a specific location in memory.
#define WRITE 11 //Write a word from a specific location in memory to the screen.
#define WRITEASCIIADDR 12 //Write a character based on the number at the address.
#define WRITEASCII 13 //Write character defined by the operand. (use the reduced ascii table defined in reduced_ascii_table.csv)

/****Load/store operations: ****/
#define LOAD 20 //Load a word from a specific location in memory into the accumulator.
#define STORE 21 //Store a word from the accumulator into a specific location in memory.
#define DIRECT_LOAD 22 //Load a given word to memory
#define MOVE 23 //Move the value of a given address to another address.

/****Arithmetic operations:****/
#define ADD 30 //Add a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator).
#define SUBTRACT 31 //Subtract a word from a specific location in memory from the word in the accumulator (leave the result in the accumulator).
#define DIVIDE 32 //Divide the word in the accumulator by a word from a specific location in memory (leave the result in the accumulator).
#define MULTIPLY 33 //Multiply a word from a specific location in memory by the word in the accumulator (leave the result in the accumulator).
#define REMAINDER 34 //Take a remainder after the division of the word in the accumulator by a word from a specific location in memory (leave the result in the accumulator).

/****Transfer-of-control operations:****/
#define BRANCH 40 //Branch to a specific location in memory.
#define BRANCHNEG 41 //Branch to a specific location in memory if the accumulator is negative.
#define BRANCHZERO 42 //Branch to a specific location in memory if the accumulator is zero.
#define JUMP 44 //Jump a given number of lines.
#define JUMPNEG 45 //Jump a given number of lines if the accumulator is negative.
#define JUMPZERO 46 //Jump a given number of lines if the accumulator is zero.
#define HALT 43 //Halt—i.e., the program has completed its task.

const char ASCII[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                      't', 'u', 'v', 'w', 'x', 'y', 'z',
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                      'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                      ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
                      ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~',
                      '\n', '\r', '\t'};

class Computer {
public:

    explicit Computer(size_t memory_size) : memory_size(memory_size), prog_size(0), accum(0), instReg(0), instCount(0),
                                            opcode(0), operand(0) {
        memory = new int[memory_size];
        init_mem();
    }

    void dump() const {
        puts("REGISTERS:");
        print_registers();
        puts("MEMORY:");
        print_memory();
    }

    void load(const std::string& file_name) {
        std::ifstream input;

        input.open(file_name);
        if (input.fail()) {
            input.close();
            exit(EXIT_FAILURE);
        }
        std::string msg;
        int mem_loc = 0;
        while (std::getline(input, msg)) {
            if (!msg.empty() && isdigit(msg[0])) {
                // atoi call ignores all alpha characters after number
                load_command(atoi(msg.c_str()), mem_loc++);
            }
        }
        puts("+++ Program loading from file completed ***");
        input.close();
    }

    int step() {
        instReg = memory[instCount++];
        opcode = instReg / 100;
        operand = (instReg % 100);
        switch (opcode) {
            case READ: // read
                std::cin >> memory[operand + prog_size];
                break;
            case WRITE: // write
                std::cout << memory[operand + prog_size];
                break;
            case WRITEASCIIADDR: // write ascii character
                std::cout << ASCII[memory[operand + prog_size]];
                break;
            case WRITEASCII:
                std::cout << ASCII[operand];
                break;
            case LOAD: // load acc
                accum = memory[operand + prog_size];
                break;
            case STORE: // read acc
                memory[operand + prog_size] = accum;
                break;
            case DIRECT_LOAD: // load next operand into operand
                memory[operand + prog_size] = (memory[instCount++] % 100) + prog_size;
                break;
            case MOVE:
                memory[operand + prog_size] = memory[(memory[instCount++] % 100) + prog_size];
                break;
            case ADD: // add
                accum += memory[operand + prog_size];
                break;
            case SUBTRACT: // sub
                accum -= memory[operand + prog_size];
                break;
            case DIVIDE: // div
                accum /= memory[operand + prog_size];
                break;
            case MULTIPLY: // mul
                accum *= memory[operand + prog_size];
                break;
            case REMAINDER:
                accum %= memory[operand + prog_size];
                break;
            case BRANCH: // jmp
                instCount = operand;
                break;
            case BRANCHNEG: // jmp if neg
                instCount = accum < 0 ? operand : instCount;
                break;
            case BRANCHZERO: // jmp if zero
                instCount = accum == 0 ? operand : instCount;
                break;
            case JUMP:
                instCount += operand - 1;
                break;
            case JUMPNEG:
                instCount += (operand - 1) * (accum < 0);
                break;
            case JUMPZERO:
                instCount += (operand - 1) * (accum == 0);
                break;
            case HALT: // halt
                return HALT;
        }
        return 0;
    }

    int run() {
        while (!step());
        return 0;
    }

private:
    int* memory;
    size_t memory_size;
    int prog_size;
    //registers
    int accum; //accumulator register
    int instReg; //current instruction
    int instCount; //the number of memory location (0 - 99)
    int opcode; //operation code
    int operand; //right most two digits of the operation

    void init_mem() {
        int i = 0;
        while (i < memory_size) {
            memory[i++] = 0;
        }
    }

    void print_registers() const {
        printf("%-20s %+05d\n", "accumulator", accum);
        printf("%-23s %02d\n", "instructionCounter", instCount);
        printf("%-20s %+05d\n", "instructionRegister", instReg);
        printf("%-23s %02d\n", "operationCode", opcode);
        printf("%-23s %02d\n\n", "operand", operand);
    }

    void print_memory() const {
        printf("%9d", 0);
        for (int i = 1; i < 10; i++) {
            printf("%7d", i);
        }
        putchar('\n');
        int row_index = 0;
        printf("%2d", row_index);
        for (int i = 0; i < memory_size; i++) {
            if (i > 0 && i % 10 == 0) {
                putchar('\n');
                printf("%2d", row_index += 10);
            }
            printf("%+7.4d", memory[i]);
        }
        putchar('\n');
    }

    void load_command(int instr, int memory_location) {
        if (instr == EXIT) {
            return;
        }
        memory[memory_location] = instr;
        prog_size++;
    }

};

#endif


