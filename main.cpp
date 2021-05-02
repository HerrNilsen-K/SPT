#include <iostream>
#include "SPT/string.hpp"
#include <string>
#include <algorithm>

int main(int argc, char const *argv[]) {
    spt1::basic_string<char> s("Hello");
    spt1::basic_string<char> ss(" World");
    spt1::basic_string<char> s2;
    s2 = s + ss;
    std::cout << s2 << std::endl;
    std::string r;
    for (auto i : s2) {
        r += i;
    }
    std::cout << r << std::endl;
    for (auto i : r) {
        std::cout << (int) i << ' ';
    }

    return 0;
}
