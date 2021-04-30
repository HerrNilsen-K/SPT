#include <iostream>
#include "SPT/vector.hpp"
#include <vector>

#include <string>
#include <algorithm>

int main(int argc, char const *argv[]) {
    spt1::basic_string<char> s("Hello");
    spt1::basic_string<char> ss("Hell");
    std::cout << s << " == " << ss << ' ' << (s == ss);

    return 0;
}
