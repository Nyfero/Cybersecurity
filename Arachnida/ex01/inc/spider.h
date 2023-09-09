#pragma once
#include <iostream>
#include <string>
#include <fstream>

typedef struct s_data {

    // store the url to extract from
    std::string url;

    // store the max depth level
    int depth;

    // store the path where the downloaded files will be saved
    std::string path;

}   t_data;


/*******************/
/*     PARSING     */
/*******************/

// parsing_check.cpp
int     parsing(int ac, char **av);

// parsing_print.cpp
void    print_usage();
void    print_error_flag(char *flag);
void    print_error_to_much_flag();
void    print_error_to_much_arg();
void    print_error_depth();
void    print_error_url();

// parsing_get.cpp
t_data  *init_data(int ac, char **av);

/*****************/
/*     UTILS     */
/*****************/

// create_folder.cpp
int create_path_folder(std::string path);

// exit.cpp
int exit_failure(t_data *data);
int exit_success(t_data *data); 