#include <iostream>
#include "Computer.h"

int main(int argc, char* argv[]) {
    Computer comp(200);
    std::cout << "Initialized" << std::endl;
    comp.load(argv[1]);
    std::cout << "Program read" << std::endl;
    comp.dump();
    comp.run();
    comp.dump();
    return 0;
}
