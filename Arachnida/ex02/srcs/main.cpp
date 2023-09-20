#include "../inc/scorpion.h"
#include "../class/ImageFormat.hpp"

int main(int ac, char **av) {

    if (parsing(ac, av))
        return 1;
    for (int i = 1; i < ac; i++) {
        t_data data = init_data();
        std::cout << "\e[92m" << av[i] << "\e[39m" << std::endl;
        ImageFormat img(av[i]);
        try {
            data = img.getMetaData(data);
            print_data(data);
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        // data = clear_data(data);
    }

    return (0);
}
