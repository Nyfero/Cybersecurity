#include "../../inc/scorpion.h"

int create_path_folder(std::string path) {
    std::string cmd = "mkdir -p " + path;
    if (system(cmd.c_str())) {
        std::cout << "Error: can't create the folder " << path << std::endl;
        return 1;
    }

    return 0;
}