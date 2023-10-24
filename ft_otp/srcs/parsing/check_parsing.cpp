#include "../../inc/ft_otp.hpp"

static int check_nb_arg(Parser parse) {
    try {
        parse.Check_size_is(0);
        exit(print_usage());
    }
    catch (const std::exception& e) {
        try {
            parse.Check_size_is(2);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}

static int check_flag(Parser parse) {
    std::vector<std::string> flag = {"-g", "-k"};
    parse.Set_flags(flag);
    try {

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

int check_parsing(Parser parse) {
    if (check_nb_arg(parse))
        return 1;
    if (check_flag(parse))
        return 1;
    return 0;
}