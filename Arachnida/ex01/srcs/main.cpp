#include "../inc/spider.h"

int main(int ac, char **av) {

    (void)ac;
    (void)av;
    if (parsing(ac, av))
        return 1;
    return 0;
}