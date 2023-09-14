#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


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