#include <iostream>
#include "SPT/vector.hpp"
#include <vector>

#include "SPT/string.hpp"
#include <string>

int main(int argc, char const *argv[]) {
    spt::string str("Hello World");
    str = "Hello";
    str = "Super Hello World";
    for (int i = 0; i < 5; ++i) {
        str[i] = i + 65;
    }
    std::cout << str << std::endl;

    spt::string cpy(str);
    std::cout << cpy << std::endl;
    return 0;
}
