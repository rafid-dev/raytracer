#include <iostream>
#include "data/vector.hpp"

int main(int argc, char const *argv[])
{

    data::Vector3f vec1 (2, 2, 2);
    data::Vector3f vec2 (3, 3, 3);

    std::cout << "vec1 = " << vec1 << std::endl;
    std::cout << "vec2 = " << vec2 << std::endl;

    // All vector-vector arithmatic operations printed
    std::cout << "vec1 + vec2 = " << vec1 + vec2 << std::endl;
    std::cout << "vec1 - vec2 = " << vec1 - vec2 << std::endl;
    std::cout << "vec1 * vec2 = " << vec1 * vec2 << std::endl;
    std::cout << "vec1 / vec2 = " << vec1 / vec2 << std::endl;

    // All vector-scalar arithmatic operations printed
    std::cout << "vec1 + 2 = " << vec1 + 2 << std::endl;
    std::cout << "vec1 - 2 = " << vec1 - 2 << std::endl;
    std::cout << "vec1 * 2 = " << vec1 * 2 << std::endl;
    std::cout << "vec1 / 2 = " << vec1 / 2 << std::endl;

    return 0;
}