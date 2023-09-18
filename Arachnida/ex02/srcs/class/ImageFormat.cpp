#include "../../class/ImageFormat.hpp"

/***********************/
/*     CONSTRUCTOR     */
/***********************/

ImageFormat::ImageFormat(std::string filename): _filename(filename) {
    this->_extension = filename.substr(filename.find_last_of(".") + 1);
    this->_signature = init_signature(this->_extension);
}

ImageFormat::~ImageFormat() {
    delete [] this->_signature;
}


/*******************/
/*     GETTERS     */
/*******************/

std::string ImageFormat::getFilename() const {
    return this->_filename;
}

std::string ImageFormat::getExtension() const {
    return this->_extension;
}

unsigned char *ImageFormat::getSignature() const {
    return this->_signature;
}


/*******************/
/*     METHODS     */
/*******************/

t_data  ImageFormat::getMetaData(t_data data) {
    
    std::ifstream file(getFilename(), std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error: could not open file " << getFilename() << std::endl;
        return data;
    }

    int  len = strlen(reinterpret_cast<const char *>(getSignature()));
    char buf[len];
    file.read(buf, len);
    for (int i = 0; i < len; i++) {
        if (static_cast<unsigned char>(buf[i]) != getSignature()[i]) {
            std::cout << "\e[91mThe file " << getFilename() << " isn't valid " << getExtension() << ".\e[39m" << std::endl;
            return data;
        }
    }
    data.filename = getFilename();
    data.extension = getExtension();
    file.seekg(0, std::ios::end);
    data.size = std::to_string(file.tellg());
    file.close();

    if (getExtension() == "jpg" || getExtension() == "jpeg") {
        data = getJpeg(data);
    }
    else if (getExtension() == "gif") {
        data = getGif(data);
    }
    // else if (getExtension() == "png") {
    //     data = getPng(data);
    // }
    // else if (getExtension() == "bmp") {
    //     data = getBmp(data);
    // }
    
    return data;
}

t_data  ImageFormat::getJpeg(t_data data) {
    FILE *file = fopen(getFilename().c_str(), "rb");
    try {
        struct jpeg_decompress_struct cinfo;
        (void)cinfo;
        struct jpeg_error_mgr jerr;
        cinfo.err = jpeg_std_error(&jerr);

        jpeg_create_decompress(&cinfo);
        jpeg_stdio_src(&cinfo, file);
        jpeg_read_header(&cinfo, TRUE);

        data.width = cinfo.image_width;
        data.height = cinfo.image_height;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    fclose(file);
    return data;
}

t_data  ImageFormat::getGif(t_data data) {
    std::ifstream imageFile(getFilename(), std::ios::binary);

    if (!imageFile.is_open()) {
        std::cerr << "Failed to open the file: " << getFilename() << std::endl;
        return data;
    }

    // Read the GIF header
    char header[10];
    if (!imageFile.read(header, sizeof(header))) {
        std::cerr << "Failed to read the GIF header." << std::endl;
        return data;
    }

    // Check if it's a GIF file
    if (header[0] != 'G' || header[1] != 'I' || header[2] != 'F') {
        std::cerr << "Not a valid GIF file: " << getFilename() << std::endl;
        return data;
    }

    // Get the width and height from the header
    data.width = (static_cast<unsigned int>(header[7]) << 8) | static_cast<unsigned int>(header[6]);
    data.height = (static_cast<unsigned int>(header[0]) << 8) | static_cast<unsigned int>(header[1]);

    uint16_t width = (static_cast<uint16_t>(header[7]) << 8) | static_cast<uint16_t>(header[6]);
    uint16_t height = (static_cast<uint16_t>(header[8]) << 8) | static_cast<uint16_t>(header[9]);

    // Output image dimensions
    std::cout << "Image dimensions: " << width << "x" << height << " pixels" << std::endl;

    // Close the file
    imageFile.close();

    return data;
}


/*****************/
/*     UTILS     */
/*****************/

unsigned char   *init_signature(std::string extension) {
    unsigned char *signature;
    if (extension == "png") {
        signature = new unsigned char[8];
        signature[0] = 0x89;
        signature[1] = 0x50;
        signature[2] = 0x4E;
        signature[3] = 0x47;
        signature[4] = 0x0D;
        signature[5] = 0x0A;
        signature[6] = 0x1A;
        signature[7] = 0x0A;
    }
    else if (extension == "gif") {
        signature = new unsigned char[3];
        signature[0] = 0x47;
        signature[1] = 0x49;
        signature[2] = 0x46;
    }
    else {
        signature = new unsigned char[2];
        if (extension == "bmp") {
            signature[0] = 0x42;
            signature[1] = 0x4D;
        }
        else if (extension == "jpg" || extension == "jpeg") {
            signature[0] = 0xFF;
            signature[1] = 0xD8;
        }
    }
    return signature;
}