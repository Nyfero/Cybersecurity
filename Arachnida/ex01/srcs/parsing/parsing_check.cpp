#include "../../inc/spider.h"

static int check_flags(int ac, char **av) {
    int r_flag = 0;
    int l_flag = 0;
    int p_flag = 0;
    for (int i = 1; i < ac; i++) {
        if (av[i][0] == '-') {
            if (av[i][1] != 'r' && av[i][1] != 'l' && av[i][1] != 'p') {
                print_error_flag(av[i]);
                return 1;
            }
            if (av[i][1] == 'r')
                r_flag++;
            if (av[i][1] == 'l')
                l_flag++;
            if (av[i][1] == 'p')
                p_flag++;
        }
        else
            break;
    }
    if (r_flag > 1 || p_flag > 1 || l_flag > 1) {
        print_error_to_much_flag();
        return 1;
    }
    if (l_flag && !r_flag) {
        print_error_flag((char *)"-l");
        return 1;
    }

    return 0;
}

int check_arg(int ac, char **av) {
    if (ac < 2) {
        print_usage();
        return 1;
    }
    if (check_flags(ac, av))
        return 1;
    return 0;
}