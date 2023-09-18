#pragma once
#include "../inc/scorpion.h"

class ImageFormat {

    private:
        std::string     _filename;
        std::string     _extension;
        unsigned char   *_signature;
    
    public:

    // Constructors
    ImageFormat(std::string filename);
    ~ImageFormat();

    // Getters
    std::string getFilename() const;
    std::string getExtension() const;
    unsigned char *getSignature() const;

    // Methods
    t_data getMetaData(t_data data);
    t_data getJpeg(t_data data);
    t_data getGif(t_data data);
    // t_data getPng(t_data data);
    // t_data getBmp(t_data data);
};

unsigned char *init_signature(std::string extension);
