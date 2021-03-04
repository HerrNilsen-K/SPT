#include <iostream>
#include "SPT/vector.hpp"
#include <vector>

#include "SPT/string.hpp"
#include <string>
#include <algorithm>

//Test comment
int main(int argc, char const *argv[]) {
    spt::vector<int> v;
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
    spt::string ss("Hello");
    ss.erase(2, 1);
    std::cout << ss << std::endl;
    for(auto c : ss){
        std::cout << c;
    }
    return 0;
}
