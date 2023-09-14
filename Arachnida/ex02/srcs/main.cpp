#include "../inc/scorpion.h"
#include "../class/ImageFormat.hpp"

int main(int ac, char **av) {

    if (parsing(ac, av))
        return 1;
    std::vector<std::string> files;
    for (int i = 1; i < ac; i++)
        files.push_back(av[i]);
    ImageFormat img(files);
    if (img.getMetaData())
        return 1;

    return (0);
}
