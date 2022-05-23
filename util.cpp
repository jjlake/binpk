#include "util.hpp"

unsigned int max_filename_length = 0;
unsigned int max_filesize_length = 0;
unsigned long int bin_max_size = 1000000;

std::string get_size_string(unsigned long int size_in_bytes){
	const char SIZE_UNITS[] = {'B', 'K', 'M', 'G', 'T', 'P', 'E', 'Z'};
	
	double size = size_in_bytes;
	char unit_index = 0;
	while(size >= 1024.0){
		size /= 1024.0;
		unit_index++;
	}
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << size << " " << SIZE_UNITS[unit_index];
	std::string s = stream.str();
	return s;
}
