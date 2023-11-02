#include "../../inc/ft_otp.hpp"

int store_key(std::string file) {
    // Check if the arg given is a file
    if (!std::filesystem::exists(file)) {
        std::cerr << "Error: " << file << ": does not exist" << std::endl;
        return 1;
    }

    // Check if the given file has the right format
    if (check_file(file)) {
        return 1;
    }
    
    if (encrypt(file)) {
        std::cerr << "Failed to encrypt file" << std::endl;
        return 1;
    }

    std::cout << "Key was successfully saved in ft_otp.key." << std::endl;
    return 0;
}