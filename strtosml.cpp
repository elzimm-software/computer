#include <string>
#include <iostream>
#include <iomanip>

const int OPCODE = 13;
const char ASCII[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                       'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                       '0','1','2','3','4','5','6','7','8','9',
                       ' ','!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/',
                       ':',';','<','=','>','?','@','[','\\',']','^','_','`','{','|','}','~',
                       '\n','\r','\t'};

int char_index(const char ch) {
    for (int i = 0; i < 100; i++) {
        if (ASCII[i] == ch) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    std::string str_in = argv[1];
    std::cout << std::setfill('0');
    for (const auto& ch: str_in) {
        int operand = char_index(ch);
        if (operand == -1) {
            std::cerr << "Invalid char: '" << ch << "'" << std::endl;
            return -1;
        }
        std::cout << std::setw(2) << OPCODE << std::setw(2) << operand << std::endl;
    }
    return 0;
}