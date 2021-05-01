#include <iostream>
#include "SPT/string.hpp"
#include <string>
#include <algorithm>

int main(int argc, char const *argv[]) {
    spt1::basic_string<char> s("Hello");
    spt1::basic_string<char> ss("Hell");
    std::cout << s << " == " << ss << ' ' << (s == ss) << std::endl;

    for (auto i = s.rbegin(); i < s.rend(); ++i) {
        std::cout << *i << std::flush;
    }

    return 0;
}
