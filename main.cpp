#include <iostream>
#include "SPT/vector.hpp"
#include <vector>

int main(int argc, char const *argv[]) {
    spt::vector<int> v;
    for (int i = 0; i < 10000; i++) {
        v.push_back(i);
    }

    for (auto &&i : v)
        std::cout << i << ' ';
    std::cout << std::endl;
    std::cout << v.front() << ' ' << v.back() << std::endl;

    std::vector<int> sv;
    sv.resize(10);
    spt::vector<int> mv;
    mv.resize(10);
    std::cout << "Capacity of std::vector after resize(10)\t" << sv.capacity() << std::endl;
    std::cout << "Capacity of spt::vector after resize(10)\t" << mv.capacity() << std::endl;

    return 0;
}
