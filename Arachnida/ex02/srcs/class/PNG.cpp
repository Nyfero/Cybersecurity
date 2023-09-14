#include "../../class/PNG.hpp"

PNG::PNG(std::string filename): _filename(filename) {
    this->_signature = new unsigned char[8];
    this->_signature[0] = 0x89;
    this->_signature[1] = 0x50;
    this->_signature[2] = 0x4E;
    this->_signature[3] = 0x47;
    this->_signature[4] = 0x0D;
    this->_signature[5] = 0x0A;
    this->_signature[6] = 0x1A;
    this->_signature[7] = 0x0A;
}

PNG::~PNG() {
    delete[] this->_signature;
}

int PNG::getMetaData() {
    std::cout << "PNG::getMetaData() called for " << this->_filename << std::endl;
    
    std::ifstream file(this->_filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error: could not open file " << this->_filename << std::endl;
        return 1;
    }

    char buf[8] = "\0";
    file.read(buf, 8);
    for (int i = 0; i < 8; i++) {
        if (static_cast<unsigned char>(buf[i]) != this->_signature[i]) {
            std::cout << "\e[91mThe file " << this->_filename << " isn't valid PNG.\e[39m" << std::endl;
            return 1;
        }
    }
    std::cout << "\e[92mThe file " << this->_filename << " is a valid PNG.\e[39m" << std::endl;
    
    return 0;
}