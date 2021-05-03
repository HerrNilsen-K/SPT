#include <iostream>
#include "SPT/string.hpp"
#include <string>
#include <algorithm>

int main(int argc, char const *argv[]) {
    spt::string s("Hello ");
    spt::string ss(" World");
    spt::string s2;
    s2 += s + ss + '!';
    s2.toUpper(s2.begin() + 2, s2.end());
    s2.replace(0, ss);
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
    std::cout << std::endl;
    int pos;
    try {
        pos = s2.find(s);
        std::cout << "Found at position: " << pos << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what();
    }

    return 0;
}
