#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

// C/C++ Libraries:
#include <string>
#include <iostream>
#include <getopt.h>
#include <unistd.h>
#include <string>
#include <string.h>

#define EINVAL 22

#define BOLD_ESC_CODE "\x1b[1m" 
#define UNDERLINE_ESC_CODE "\x1b[4m" 
#define DEF_FORMATTING_ESC_CODE "\x1b[0m" 

extern enum BIN_MODE {
	BIN_NONE,
	BIN_ALPHABETICAL,
	//BIN_DATE_MODIFIED,
	BIN_FILETYPE
} bin_mode;

extern enum SORT_MODE {
	SORT_NONE,
	SORT_ALPHABETICAL,
	SORT_SIZE
} sort_mode;

extern enum ORDER_MODE {
	ASCENDING,
	DESCENDING
} order_mode;

extern bool inplace;
extern std::string input_loc;
extern std::string output_loc;
extern bool write_bins;
extern bool zip;

extern bool preserve_directories;
extern bool recursive;
extern bool verbose;

extern bool keep;
extern bool help;
extern unsigned long int bin_max_size;

void process_args(int argc, char **argv);

#endif
