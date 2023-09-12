#include "../../inc/scorpion.h"

static int check_extension(int ac, char **av) {
    for (int i = 1; i < ac; i++) {
        std::string file = av[i];
        std::string extension = file.substr(file.find_last_of(".") + 1);
        if (extension != "jpg" && extension != "jpeg" && extension != "png" && extension != "gif" && extension != "bmp") {
            print_error_format(extension.c_str());
            return 1;
        }
    }
    return 0;
}

int parsing(int ac, char **av) {
    if (ac < 2) {
        print_usage();
        return 1;
    }
    if (check_extension(ac, av))
        return 1;
    return 0;
}