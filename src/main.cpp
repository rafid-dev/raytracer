#include <iostream>
#include "data/vector.hpp"
#include "data/matrix.hpp"

int main(int argc, char const *argv[])
{

    std::cout << data::MatrixNi<10>::identity() << std::endl;    

    return 0;
}