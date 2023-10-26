#include "../../inc/ft_otp.hpp"

static int check_nb_arg(Parser data) {
    try {
        data.Check_size_is(0);
        exit(print_usage());
    }
    catch (const std::exception& e) {
        try {
            data.Check_size_is(2);
            return 0;
        }
        catch (const std::exception& e) {
            std::cerr << "./ft_otp: error: " << e.what() << std::endl;
            return 1;
        }
    }
};

static int check_file(Parser data) {
    try {
        data.Check_args_file_i(1);
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "./ft_otp: error: " << data.Get_args_i(1) << ": " << e.what() << std::endl;
        return 1;
    }
};

static int check_flag(Parser data) {
    std::vector<std::string> flag = {"-g", "-k"};
    data.Set_flags(flag);
    try {
        data.Check_args_flags_i(0);
        if (data.Get_args_i(0) == "-k") {
            return (check_file(data));
        }
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "./ft_otp: error: " << data.Get_args_i(0) << ": " << e.what() << std::endl;
        return 1;
    }
};

int check_parsing(Parser data) {
    if (check_nb_arg(data))
        return 1;
    if (check_flag(data))
        return 1;
    return 0;
};