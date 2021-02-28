#include <iostream>
#include "SPT/vector.hpp"
#include <vector>

int main(int argc, char const *argv[]) {
    std::vector<int> sv(20);
    sv.resize(10);
    spt::vector<int> mv(20);
    mv.resize(10);
    sv.shrink_to_fit();
    mv.shrink_to_fit();
    std::cout << "Capacity of std::vector after resize(10)\t" << sv.capacity() << std::endl;
    std::cout << "Capacity of spt::vector after resize(10)\t" << mv.capacity() << std::endl;

    return 0;
}
