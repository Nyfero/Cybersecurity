#pragma once

#include <unistd.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include "../class/Parser.hpp"
// #include <mylib/Parser.hpp>

class Parser;

//parsing
int check_parsing(Parser parse);

//utils
int print_usage();