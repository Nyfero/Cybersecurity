#include "../../inc/ft_otp.hpp"

int check_file(std::string file) {
    // Check if the file is strictly hexadecimal
    if (check_hexa(file)) {
        std::cerr << "./ft_otp: error: key must be 64 hexadecimal characters." << std::endl;
        return 1;
    }

    // Check the size of the file
    if (check_file_size(file)) {
        std::cerr << "./ft_otp: error: key must be 64 hexadecimal characters." << std::endl;
        return 1;
    }

    return 0;
}

int check_hexa(std::string file) {
    // Open the given file
    std::ifstream inputFile(file);

    // Check for error while opening file
    if (!inputFile.is_open()) {
        std::cerr << "Error: Failed to open: " << file << std::endl;
        return 1; 
    }

    // Check if the file is only hexadecimal
    char c;
    while (inputFile.get(c)) {
        if (!isxdigit(static_cast<unsigned char>(c))) {
            inputFile.close();
            return 1;
        }
    }

    inputFile.close();
    return 0;
}

int check_file_size(std::string file) {
    // Open the given file
    std::ifstream inputFile(file);

    // Check for error while opening file
    if (!inputFile.is_open()) {
        std::cerr << "Error: Failed to open: " << file << std::endl;
        return 1; 
    }

    // Go to the end and count the numbers of bytes read
    inputFile.seekg(0, std::ios::end);
    std::streampos bytesRead = inputFile.tellg();
    if (bytesRead < 64) {
        inputFile.close();
        return 1;
    }

    inputFile.close();
    return 0;
}

int check_arg(std::string arg) {
    size_t i = 0;
    while (i < arg.size()) {
        if (!isxdigit(static_cast<unsigned char>(arg[i]))) {
            return 1;
        }
        i++;
    }

    if (i < 64) {
        return 1;
    }
    return 0;
}