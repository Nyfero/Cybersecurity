#include "../../inc/ft_otp.hpp"

int print_usage() {
    std::cout << "Usage: ./ft_otp [-g hexadecimal key]  [-k ft_otp.key]" << std::endl;
    std::cout << "\t-g: The program receives as argument a hexadecimal key of at least 64 characters. The program stores this key safely in a file called ft_otp.key, which is encrypted." << std::endl;
    std::cout << "\t-k: The program generates a new temporary password based on the key given as argument and prints it on the standard output." << std::endl;
    return 0;
}