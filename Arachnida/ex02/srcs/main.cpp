#include "../inc/scorpion.h"
#include "../class/ImageFormat.hpp"

int main(int ac, char **av) {

    if (parsing(ac, av))
        return 1;
    t_data data = init_data();
    for (int i = 1; i < ac; i++) {
        ImageFormat img(av[i]);
        try {
            data = img.getMetaData(data);
            print_data(data);
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        data = clear_data(data);
    }

    return (0);
}
