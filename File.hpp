#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "util.hpp"

namespace fs = std::filesystem;

class File {
	private:
	fs::directory_entry directory_entry;
	
	public:
	static unsigned int file_count;
	
	// Constructors
	File(std::string filepath);
	File(fs::directory_entry dir_entry);
	
	// Getters
	std::string get_extension();
	std::string get_filename();
	fs::path get_path();
	unsigned long int get_size();
	std::string get_readable_size();
	
	char begins_with();
};

std::ostream& operator<<(std::ostream &stream, File file);


struct {
	bool operator()(File &a, File &other) const {		
		std::string filename_a = a.get_filename();
		std::string filename_b = other.get_filename();
		
		// Make filenames lowercase
		std::transform(filename_a.begin(), filename_a.end(), filename_a.begin(), ::tolower);
		std::transform(filename_b.begin(), filename_b.end(), filename_b.begin(), ::tolower);
		
		return (filename_a < filename_b);
	}
} compare_alphabetically;

struct {
	bool operator()(File &a, File &other) const {		
		std::string extension_a = a.get_extension();
		std::string extension_b = other.get_extension();
		
		// Make extensions lowercase
		std::transform(extension_a.begin(), extension_a.end(), extension_a.begin(), ::tolower);
		std::transform(extension_b.begin(), extension_b.end(), extension_b.begin(), ::tolower);
		
		return (extension_a < extension_b);
	}
} compare_filetype;

struct {
	bool operator()(File &a, File &other) const {
		return (a.get_size() < other.get_size());
	}
} compare_size;

#endif
