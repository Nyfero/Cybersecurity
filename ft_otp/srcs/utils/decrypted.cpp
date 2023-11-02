#include "../../inc/ft_otp.hpp"

std::string decrypt(std::string file) {
    
    std::fstream fin;
    fin.open(file, std::fstream::in);
    std::string fileContent((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();

    int key = 3;
    int i = 0;
    while (fileContent[i]) {
        if (i % 2 == 0) {
            fileContent[i] = (fileContent[i] - key - i);
        }
        else {
            fileContent[i] = (fileContent[i] - key - (i * 2));
        }
        i++;
    }
    // std::cout << fileContent << std::endl;
    return (fileContent);
}