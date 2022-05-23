#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <fmt/core.h>
#include <vector>

std::string get_size_string(unsigned long int size_in_bytes);

extern unsigned int max_filename_length, max_filesize_length;
extern unsigned long int bin_max_size;

#endif
