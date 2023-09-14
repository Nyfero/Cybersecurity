#include "../../class/BMP.hpp"

BMP::BMP(std::string filename): _filename(filename) {
    this->_signature = new unsigned char[2];
    this->_signature[0] = 0x42;
    this->_signature[1] = 0x4D;
}

BMP::~BMP() {
    delete [] this->_signature;
}

//BMP : {0x42, 0x4D}
int BMP::getMetaData() {
    std::cout << "BMP::getMetaData() called for " << this->_filename << std::endl;
    
    std::ifstream file(this->_filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error: could not open file " << this->_filename << std::endl;
        return 1;
    }

    char buf[2] = "\0";
    file.read(buf, 2);
    for (int i = 0; i < 2; i++) {
        if (static_cast<unsigned char>(buf[i]) != this->_signature[i]) {
            std::cout << "\e[91mThe file " << this->_filename << " isn't valid BMP.\e[39m" << std::endl;
            return 1;
        }
    }
    std::cout << "\e[92mThe file " << this->_filename << " is a valid BMP.\e[39m" << std::endl;
    
    return 0;
}