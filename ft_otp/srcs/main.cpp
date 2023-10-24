#include "../inc/ft_otp.hpp"

int main(int ac, char **av) {
    Parser parse(ac, av);

    if (check_parsing(parse))
        return 1;

    return 0;
}

