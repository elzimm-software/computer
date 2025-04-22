#include "Computer.h"
#include <fstream>
#include <string>
#include <unistd.h>

const int PATH_MAX = 100;

Computer::Computer(size_t mem_size) 
    : memory_size(mem_size), accum(0), instReg(0),
      instCount(0), opcode(0), operand(0)
{
    memory = new int[memory_size];
    init_mem();
}

void Computer::init_mem() {
    int i = 0;
    while (i < memory_size) {
        memory[i++] = 0;
    }
}

void Computer::print_registers() const {
    printf("%-20s %+05d\n", "accumulator", accum);
    printf("%-23s %02d\n", "instructionCounter", instCount);
    printf("%-20s %+05d\n", "instructionRegister", instReg);
    printf("%-23s %02d\n", "operationCode", opcode);
    printf("%-23s %02d\n\n", "operand", operand);
}

void Computer::print_memory() const {
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

void Computer::load(std::string file_name) {
    std::ifstream input;
    char cwd[PATH_MAX];
    //get cur dir path
    get_cur_dir_path(cwd, PATH_MAX);
    strcat(cwd, file_name.c_str());

    input.open(cwd);
    if (input.fail()) {
        input.close();
        exit(EXIT_FAILURE);
    }
    std::string msg;
    int mem_loc = 0;
    while (std::getline(input, msg)) {
        load_command(atoi(msg.c_str()), mem_loc++);
    }
    puts("*** Program loading from file completed ***");
 //   puts("*** Program execution begins            ***");
    input.close();
}
void Computer::get_cur_dir_path(char * cwd, size_t size) const {
    if (getcwd(cwd, size) != NULL) {
        strcat(cwd, "/");
    } 
    else {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
}

void Computer::load_command(int instr, int memory_location) {
    if (instr == EXIT || (instr <= MIN_INSTR && instr >= MAX_INSTR)) {
        return;
    }
    memory[memory_location] = instr;
}

void Computer::dump() const {
    puts("REGISTERS:");
    print_registers();
    puts("MEMORY:");
    print_memory();
}

void Computer::run() {
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
