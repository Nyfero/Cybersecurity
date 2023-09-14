#include "../../class/JPG.hpp"

JPG::JPG(std::string filename): _filename(filename) {
    this->_signature = new unsigned char[2];
    this->_signature[0] = 0xFFu;
    this->_signature[1] = 0xD8u;
}

JPG::~JPG() {
    delete [] this->_signature;
}

int JPG::getMetaData() {
    std::cout << "JPG::getMetaData() called for " << this->_filename << std::endl;
    
    std::ifstream file(this->_filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error: could not open file " << this->_filename << std::endl;
        return 1;
    }

    char buf[2] = "\0";
    file.read(buf, 2);
    for (int i = 0; i < 2; i++) {
        if (static_cast<unsigned char>(buf[i]) != this->_signature[i]) { 
            std::cout << "\e[91mThe file " << this->_filename << " isn't valid JPG.\e[39m" << std::endl;
            return 1;
        }
    }
    std::cout << "\e[92mThe file " << this->_filename << " is a valid JPG.\e[39m" << std::endl;
    
    char c = 0;
    while(file.read(buf, 2)) {
        std::cout << "buf: " << std::hex << (int)buf[0] << std::endl;
        std::cout << "buf: " << std::hex << (int)buf[1] << std::endl;

        if (buf[0] == '\xFF' && buf[1] == '\xE1') {
            std::cout << "perfect match" << std::endl;
            return 0;
        }
        else if (c == '\xFF' && buf[0] == '\xE1') {
            std::cout << "match" << std::endl;
            return 0;
        }
        else {
            std::cout << "no match" << std::endl;
            c = buf[1];
        }

    }

    return 0;
}