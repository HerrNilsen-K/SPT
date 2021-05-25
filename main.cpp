#include <iostream>
#include "SPT/string.hpp"
#include <algorithm>
#include <random>
#include <chrono>

int main(int argc, char const *argv[]) {
    //DEMO
    spt::string str("Hello ");
    str += spt::toString((int) 55);
    spt::string ss(" World");
    spt::string s2;
    s2 += str + ss + '!';
    //Finding substrings
    int pos;
    try {
        pos = (int)s2.find(str);
        std::cout << "Substring found at position: " << pos << std::endl;
    } catch (...) {
        std::cout << "Substring not found" << std::endl;
    }
    //Transformation
    s2.toLower(s2.begin() + 2, s2.end());
    s2.replace(0, ss);
    std::cout << s2 + ' ' + "?" << std::endl;
    std::cout << s2 << std::endl;
    std::cout << std::endl;

    //Capability with the stl
    std::shuffle(s2.begin(), s2.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    for(auto c : s2)
        std::cout << c;
    std::cout << std::endl;

    //Mr. Hardys example
    spt::string A("Hallo"), B;
    A = "Guten Tag,";
    B = A + " wie gehts es?";
    std::cout << B << std::endl;
    A = "Es ist ";
    B = "Uhr";
    A = A + spt::toString(14);
    A += B;
    std::cout << A << std::endl;

    return 0;
}
