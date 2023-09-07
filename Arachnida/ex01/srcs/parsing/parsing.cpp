#include "../../inc/spider.h"

int parsing(int ac, char **av) {
    if (check_arg(ac, av))
        return 1;

    return 0;
}