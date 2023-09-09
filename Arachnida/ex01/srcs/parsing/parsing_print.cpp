#include "../../inc/spider.h"

void print_usage() {
    std::cout << std::endl << "Usage: ./spider [-rlp] URL" << std::endl << std::endl;
    std::cout << "Option -r: recursively downloads the images in a URL received as a parameter." << std::endl;
    std::cout << "Option -r -l [N]: indicates the maximum depth level of the recursive download. If not indicated, it will be 5." << std::endl;
    std::cout << "Option -p [PATH] : indicates the path where the downloaded files will be saved. If not specified, ./data/ will be used." << std::endl << std::endl;
}

void print_error_flag(char *flag) {
    std::cout << "Error: flag " << flag << " is not valid." << std::endl;
    print_usage();
}

void print_error_to_much_flag() {
    std::cout << "Error: too much flags." << std::endl;
}

void print_error_to_much_arg() {
    std::cout << "Error: too much arguments." << std::endl;
    print_usage();  
}

void print_error_depth() {
    std::cout << "Error: depth is not valid." << std::endl;
    print_usage();
}

void print_error_url() {
    std::cout << "Error: url is not valid." << std::endl;
    print_usage();
}