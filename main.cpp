#include <iostream>
#include "SPT/vector.hpp"
#include <vector>

#include "SPT/string.hpp"
#include <string>
#include <algorithm>

//Test comment
int main(int argc, char const *argv[]) {
    spt1::vector<int> v;
    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
    }
    std::cout << "Old Vector: ";
    for (auto x : v) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    v.erase(v.begin(), v.begin() + 3);

    std::cout << "New Vector: ";
    for (auto x : v) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    std::string s("Hello");
    s.erase( 2, 1);
    std::cout << s << std::endl;
    spt1::string ss("Hello");
    ss.erase(2, 1);
    std::cout << ss << std::endl;
    for(auto c : ss){
        std::cout << c;
    }

    spt2::vector<int> v2;
    v2.push_back(5);

    return 0;
}
