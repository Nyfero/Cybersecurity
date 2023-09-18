#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <jpeglib.h>

typedef struct s_exif {
    std::string     key;
    std::string     value;
    struct s_exif   *next;
}   t_exif;

typedef struct s_data {
    std::string     filename;
    std::string     extension;
    unsigned int     height;
    unsigned int     width;
    std::string     size;
    t_exif          *exif;
}   t_data;

/*******************/
/*     PARSING     */
/*******************/

// parsing_check.cpp
int     parsing(int ac, char **av);

// parsing_print.cpp
void    print_usage();
void    print_error_format(std::string format);


/*****************/
/*     UTILS     */
/*****************/

// create_folder.cpp
int     create_path_folder(std::string path);

// data.cpp
t_exif  *clear_exif(t_exif *exif);
t_data  clear_data(t_data data);
t_data  init_data();
void    print_data(t_data data);