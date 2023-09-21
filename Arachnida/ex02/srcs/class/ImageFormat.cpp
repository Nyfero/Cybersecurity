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
    else if (getExtension() == "png") {
        data = getPng(data);
    }
    else if (getExtension() == "bmp") {
        data = getBmp(data);
    }

    data = getExif(data);
    
    return data;
}

t_data  ImageFormat::getJpeg(t_data data) {
    FILE *file = fopen(getFilename().c_str(), "rb");
    try {
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;

        // Initialize the JPEG decompression object
        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_decompress(&cinfo);

        // Specify the source file
        jpeg_stdio_src(&cinfo, file);

        // Read the JPEG header
        jpeg_read_header(&cinfo, TRUE);

        // Get the image dimensions
        data.width = cinfo.image_width;
        data.height = cinfo.image_height;

        // Clean up and close the file
        jpeg_destroy_decompress(&cinfo);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    fclose(file);
    return data;
}

t_data  ImageFormat::getGif(t_data data) {
    GifFileType* gifFile = DGifOpenFileName(getFilename().c_str(), nullptr);

    if (!gifFile) {
        std::cerr << "Failed to open the file: " << getFilename() << std::endl;
        return data;
    }

    data.width = gifFile->SWidth;
    data.height = gifFile->SHeight;
    
    DGifCloseFile(gifFile, nullptr);

    return data;
}

t_data  ImageFormat::getPng(t_data data) {
    // Open the PNG file for reading in binary mode
    FILE* file = fopen(getFilename().c_str(), "rb");
    if (!file) {
        std::cerr << "Failed to open the PNG file: " << getFilename() << std::endl;
        return data;
    }

    // Initialize the PNG structure
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        std::cerr << "Failed to initialize the PNG structure." << std::endl;
        fclose(file);
        return data;
    }

    // Initialize the PNG info structure
    png_infop info = png_create_info_struct(png);
    if (!info) {
        std::cerr << "Failed to initialize the PNG info structure." << std::endl;
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(file);
        return data;
    }

    // Set up error handling (if you don't set this up, it won't work)
    if (setjmp(png_jmpbuf(png))) {
        std::cerr << "An error occurred while reading the PNG file." << std::endl;
        png_destroy_read_struct(&png, &info, NULL);
        fclose(file);
        return data;
    }

    // Initialize the PNG IO
    png_init_io(png, file);

    // Read the PNG header/info
    png_read_info(png, info);

    // Get image width and height
    data.width = png_get_image_width(png, info);
    data.height = png_get_image_height(png, info);

    // Clean up
    png_destroy_read_struct(&png, &info, NULL);
    fclose(file);

    return data;
}

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t signature;  // "BM" (Bitmap identifier)
    uint32_t fileSize;   // Size of the BMP file in bytes
    uint16_t reserved1;  // Reserved (unused)
    uint16_t reserved2;  // Reserved (unused)
    uint32_t dataOffset; // Offset of image data in the file
    uint32_t headerSize; // Size of the BMP header in bytes
    int32_t width;       // Width of the image in pixels
    int32_t height;      // Height of the image in pixels
    uint16_t planes;     // Number of color planes (must be 1)
    uint16_t bitsPerPixel; // Number of bits per pixel (e.g., 24 for RGB)
};
#pragma pack(pop)

t_data  ImageFormat::getBmp(t_data data) {
    std::ifstream file(getFilename().c_str(), std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Failed to open the BMP file: " << getFilename() << std::endl;
        return data;
    }

    // Read the BMP header
    BMPHeader bmpHeader;
    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));

    if (bmpHeader.signature != 0x4D42) {
        std::cerr << "Not a valid BMP file: " << getFilename() << std::endl;
        file.close();
        return data;
    }

    data.width = bmpHeader.width;
    data.height = bmpHeader.height;

    file.close();

    return data;
}

t_data  ImageFormat::getExif(t_data data) {
     try {
        // Open the image file
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(getFilename().c_str());

        if (image.get() == 0) {
            std::cerr << "Failed to open the image: " << getFilename() << std::endl;
            return data;
        }

        // Read EXIF metadata
        image->readMetadata();

        // Get the EXIF data
        Exiv2::ExifData exifData = image->exifData();

        // Check if there is EXIF data
        if (!exifData.empty()) {
            // Iterate through the EXIF data and print it
            t_exif *tmp = new t_exif;
            data.exif = tmp;
            for (Exiv2::ExifData::const_iterator it = exifData.begin(); it != exifData.end(); ++it) {
                if (!tmp)
                    tmp = new t_exif;
                tmp->key = it->key();
                tmp->value = it->value().toString();
                tmp->next = NULL;
                tmp = tmp->next;
            }
        }
    } catch (Exiv2::AnyError& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return data;
    }

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