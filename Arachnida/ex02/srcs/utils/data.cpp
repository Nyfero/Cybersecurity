#include "../../inc/scorpion.h"

t_exif *clear_exif(t_exif *exif) {
    t_exif *tmp;
    while (exif) {
        tmp = exif;
        exif = exif->next;
        tmp->key = "";
        tmp->value = "";
        tmp->next = NULL;
    }
    return exif;
}

t_data clear_data(t_data data) {
    data.filename = "";
    data.extension = "";
    data.height = 0;
    data.width = 0;
    data.size = "";
    data.exif = clear_exif(data.exif);
    return data;
}

t_data init_data() {
    t_data data;
    data.filename = "";
    data.extension = "";
    data.height = 0;
    data.width = 0;
    data.size = "";
    data.exif = NULL;
    return data;
}

void    print_data(t_data data) {
    std::string border = std::string(50, '*');
    std::cout << border << std::endl;
    std::cout << "* Filename: " << data.filename << std::endl;
    std::cout << "* Extension: " << data.extension << std::endl;
    std::cout << "* Width: " << data.width << " pixels" << std::endl;
    std::cout << "* Height: " << data.height << " pixels" << std::endl;
    std::cout << "* Size: " << data.size << " bytes" << std::endl;
    std::cout << "* Exif: " << std::endl;
    if (data.exif) {
        t_exif *tmp = data.exif;
        while (tmp) {
            std::cout << "*\t" << tmp->key << ": " << tmp->value << std::endl;
            tmp = tmp->next;
        }
    }
    else
        std::cout << "*\tNo exif data found." << std::endl;
    std::cout << border << std::endl;
}