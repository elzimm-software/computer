#include <iostream>
#include "Computer.h"

int main() {
    Computer comp(100);
    std::cout << "Initialized" << std::endl;
    comp.load("add.sml");
    std::cout << "Program read" << std::endl;
    comp.dump();

    return 0;
}
