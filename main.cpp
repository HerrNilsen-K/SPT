#include <iostream>
#include "SPT/string.hpp"
#include <string>
#include <algorithm>

int main(int argc, char const *argv[]) {
    spt::string s("Hello");
    spt::string ss(" World");
    spt::string s2;
    s2 += s + ss + '!';
    std::cout << s2 + ' ' + "?" << std::endl;
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
