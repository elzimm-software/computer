#ifndef COMPUTER_H
#define COMPUTER_H

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <fstream>
#include <unistd.h>


#define EXIT -99999
#define MIN_INSTR -9999
#define MAX_INSTR 9999

/****Input/output operations: ****/
#define READ 10 // Read a word from the keyboard into a specific location in memory.
#define WRITE 11 //Write a word from a specific location in memory to the screen.

/****Load/store operations: ****/
#define LOAD 20 //Load a word from a specific location in memory into the accumulator.
#define STORE 21 //Store a word from the accumulator into a specific location in memory.
#define DIRECT_LOAD 22 //Load a given word to memory //TODO

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
#define HALT 43 //Halt—i.e., the program has completed its task.

class Computer {
    public:

        Computer(size_t memory_size): memory_size(memory_size), accum(0), instReg(0), instCount(0), opcode(0),operand(0) {
            memory= new int[memory_size];
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
            char cwd[PATH_MAX];
            get_cur_dir_path(cwd,PATH_MAX);
            strcat(cwd, file_name.c_str());

            input.open(cwd);
            if (input.fail()) {
                input.close();
                exit(EXIT_FAILURE);
            }
            std::string msg;
            int mem_loc = 0;
            while (std::getline(input,msg)) {
                load_command(atoi(msg.c_str()), mem_loc);
            }
            puts("+++ Program loading from file completed ***");
            input.close();
        }
    private:
        int* memory;
        size_t memory_size;
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
            for(int i = 1; i < 10; i++) {
                printf("%7d", i);
            }
            putchar('\n');
            int row_index = 0;
            printf("%2d", row_index);
            for(int i = 0; i < memory_size; i++) {
                if (i > 0 && i % 10 == 0) {
                    putchar('\n');
                    printf("%2d", row_index += 10);
                }
                printf("%+7.4d", memory[i]);
            }
            putchar('\n');
        }

        void get_cur_dir_path(char* cwd, size_t size) const {
            if (getcwd(cwd, size) != NULL) {
                strcat(cwd,"/");
            } else {
                perror("getcwd() error");
                exit(EXIT_FAILURE);
            }
        }

        void load_command(int instr, int memory_location) {
            if (instr == EXIT || (instr <= MIN_INSTR && instr >= MAX_INSTR)) {
                return;
            }
            memory[memory_location] = instr;
        }

    void run() {
        int op = 00;
        int addr = 00;
        while (op != 43) {
            switch (op) {
                case 10: // read

                    break;
                case 11: // write

                    break;
                case 20: // load acc

                    break;
                case 21: // read acc

                    break;
                case 30: // add

                    break;
                case 31: // sub

                    break;
                case 32: // div

                    break;
                case 33: // mul

                    break;
                case 40: // jmp

                    break;
                case 41: // jmp if neg

                    break;
                case 42: // jmp if zero

                    break;
                case 43: // halt

                    break;
                default:
                    break;
            }
        }
    }
};

#endif


