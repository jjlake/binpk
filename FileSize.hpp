#ifndef FILESIZE_H_INCLUDED
#define FILESIZE_H_INCLUDED

#include "util.hpp"

const char SIZE_UNITS[] = {'B', 'K', 'M', 'G', 'T', 'P', 'E', 'Z'};

class FileSize{
	private:
	unsigned long int size_in_bytes;
	char get_unit_index();
	
	public:
	FileSize();
	FileSize(unsigned long int size_in_bytes);	
	unsigned long int get_size_in_bytes();
	char get_unit();
	std::string to_string();
	void set_size(unsigned long int size_in_bytes);
	std::string get_size();	
	
	FileSize operator+(FileSize size);
	auto operator <=>(const FileSize& rhs) const = default;
};

std::ostream& operator<<(std::ostream &stream, FileSize size);



#endif
