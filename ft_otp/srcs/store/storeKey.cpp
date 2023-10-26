#include "../../inc/ft_otp.hpp"

int store_key(std::string arg) {
    // Check if the arg given is a file
    if (std::filesystem::exists(arg)) {
        return (key_store(arg));
    }

    if (check_arg(arg)) {
        std::cerr << "./ft_otp: error: key must be 64 hexadecimal characters." << std::endl;
        return 1;
    }

    // Handle file
    std::ofstream outputFile("ft_otp.key"); // Creates or overwrites the file

    // Check for error while opening file
    if (!outputFile.is_open()) {
        std::cerr << "Error: Failed to open: ft_otp.key" << std::endl;
    }

    // Copies arg into outputFile (arg => ft_otp.key)
    outputFile << arg << std::endl;

    // Encrypt ft_otp.key
    // TO DO

    // Close file
    outputFile.close();

    std::cout << "Key was successfully saved in ft_otp.key." << std::endl;
    return 0;
}

int key_store(std::string file) {
    // Check if the given file has the right format
    if (check_file(file)) {
        return 1;
    }
    
    // Handle files
    std::ifstream inputFile(file);
    std::ofstream outputFile("ft_otp.key"); // Creates or overwrites the file

    // Check for error while opening files
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error: Failed to open files" << std::endl;
    }

    // Copies inputFile into outputFile (file => ft_otp.key)
    char c;
    while (inputFile.get(c)) {
        outputFile.put(c);
    }

    // Encrypt ft_otp.key
    // TO DO

    // Close files
    inputFile.close();
    outputFile.close();

    std::cout << "Key was successfully saved in ft_otp.key." << std::endl;
    return 0;
}