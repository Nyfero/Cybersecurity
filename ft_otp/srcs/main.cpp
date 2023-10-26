#include "../inc/ft_otp.hpp"

int main(int ac, char **av) {
    Parser data(ac, av);

    if (check_parsing(data))
        return 1;
    if (data.Get_args_i(0) == "-g")
        return (store_key(data.Get_args_i(1)));
    return (generate_code(data.Get_args_i(1)));
}

