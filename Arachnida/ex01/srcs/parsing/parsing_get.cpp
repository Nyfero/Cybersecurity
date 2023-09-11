#include "../../inc/spider.h"

static std::string get_url(int ac, char **av) {
    std::string url = av[ac - 1];
    size_t  res = url.find('/', url.find_first_not_of('/', url.find('/', 0)));

    if (res == std::string::npos || res == url.size() - 1)
        if (res == std::string::npos)
            url.push_back('/');
    return url;
}


static int is_number(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

static int get_depth(int ac, char **av) {
    for (int i = 1; i < ac - 1; i++) {
        if (av[i][1] == 'l') {
            if (av[i + 1][0] == '-' || i + 1 == ac - 1)
                return 5;
            else {
                if (!is_number(av[i + 1])) {
                    print_error_depth();
                    return -1;
                }
                int tmp = atoi(av[i + 1]);
                if (tmp < 0)
                    return 5;
                return tmp;
            }
        }
    }

    for (int i = 1; i < ac - 1; i++) {
        if (av[i][1] == 'r')
            return 1;
    }
    
    return 0;
}

static std::string get_path(int ac, char **av) {
    for (int i = 1; i < ac - 1; i++) {
        if (av[i][1] == 'p') {
            if (av[i + 1][0] == '-' || i + 1 == ac - 1)
                return "./data";
            return av[i + 1];
        }
    }

    return "./data";
}

t_data *init_data(int ac, char **av) {
    t_data *data = new t_data;

    data->url = get_url(ac, av);
    data->depth = get_depth(ac, av);
    if (data->depth == -1) {
        delete data;
        return NULL;
    }
    data->path = get_path(ac, av);
    return data;
}