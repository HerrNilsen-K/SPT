#include <iostream>
#include "SPT/string.hpp"
#include <string>
#include <algorithm>

int main(int argc, char const *argv[]) {
    spt::string str("Hello ");
    str += spt::toString((int) 55);
    spt::string ss(" World");
    spt::string s2;
    s2 += str + ss + '!';
    s2.toLower(s2.begin() + 2, s2.end());
    s2.replace(0, ss);
    std::cout << s2 + ' ' + "?" << std::endl;
    std::cout << s2 << std::endl;
    std::cout << std::endl;
    int pos;
    try {
        pos = s2.find(str);
        std::cout << "Found at position: " << pos << std::endl;
    } catch (...) {
        std::cout << "Substring not found" << std::endl;
    }

    spt::string A("Hallo"), B;
    A = "Guten Tag,";
    B = A + " wie gehts es?";
    std::cout << B << std::endl;
    A = "Es ist ";
    B = "Uhr";
    A = A + spt::toString(14);
    A += B;
    std::cout << A << std::endl;


    spt::string mstr("Hello");
    std::cout << mstr + 'e' + 'e';
    std::cout << mstr;



    return 0;
}
