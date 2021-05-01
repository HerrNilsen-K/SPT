#include <iostream>
#include "SPT/string.hpp"
#include <string>
#include <algorithm>

int main(int argc, char const *argv[]) {
    spt1::basic_string<char> s("Hello");
    spt1::basic_string<char> ss("Hell");
    std::cout << s << " == " << ss << ' ' << (s == ss) << std::endl;

    spt1::vector<int> v{1, 2, 3};
    for (auto i : v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl << v.size() << ' ' << v.capacity();

    return 0;
}
