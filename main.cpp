#include <iostream>

extern int part_one();
extern int part_two();

int error_args()
{
    std::cerr << "ERROR args\n";
    return -1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        return error_args();
    }

    if (std::string(argv[1]).compare("1") == 0)
        std::cout << "part one: " << part_one() << "\n";
    else if (std::string(argv[1]).compare("2") == 0)
        std::cout << "part two: " << part_two() << "\n";
    else
        return error_args();

    return 0;
}
