#include "../../inc/scorpion.h"

void print_usage() {
    std::cout << std::endl << "Usage: ./scorpion FILE1 [FILE2 ...]" << std::endl << std::endl;
    std::cout << "The file must be in this format:" << std::endl;
    std::cout << "\t• .jpg/jpeg" << std::endl;
    std::cout << "\t• .png" << std::endl;
    std::cout << "\t• .gif" << std::endl;
    std::cout << "\t• .bmp" << std::endl << std::endl;
}

void print_error_format(std::string format) {
    std::cout << "Error: " << format << ": is not a valid image format" << std::endl;
    print_usage();
}