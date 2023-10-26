#pragma once

#include <unistd.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include "Parser.hpp"


/**************/
/*  generate  */
/**************/

//checkKey.cpp

//generateCode.cpp
int generate_code(std::string file);


/*************/
/*  parsing  */
/*************/

//checkParsing.cpp
int check_parsing(Parser data);


/***********/
/*  store  */
/***********/

//checkHexa.cpp
int check_file(std::string file);
int check_file_size(std::string file);
int check_hexa(std::string file);
int check_arg(std::string arg);

//storeKey.cpp
int store_key(std::string arg);
int key_store(std::string file);

/***********/
/*  utils  */
/***********/

//print.cpp
int print_usage();