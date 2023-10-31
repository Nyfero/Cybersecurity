#pragma once

#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <string>
#include <sstream>
#include <string.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include "Parser.hpp"


/**************/
/*  generate  */
/**************/

//checkKey.cpp
int check_key(std::string file);

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

// decrypted.cpp
int decryptFile(const char* inputFile, const char* outputFile, const unsigned char* key, const unsigned char* iv);

// encrypted.cpp
int encryptFile(const char* inputFile, const char* outputFile, const unsigned char* key, const unsigned char* iv);

//print.cpp
int print_usage();