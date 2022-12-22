#include "File.hpp"
#include "util.hpp"

unsigned int File::file_count = 0;

File::File(fs::directory_entry dir_entry){
	this->directory_entry = dir_entry;
	this->file_count++;
};

File::File(std::string filename){
	fs::path path = filename;
	this->directory_entry = fs::directory_entry(path);
	this->file_count++;
};

fs::path File::get_path(){
	return this->directory_entry.path();
}

unsigned long int File::get_size(){
	return this->directory_entry.file_size();
}

std::string File::get_filename(){
	return this->get_path().filename();
}

std::string File::get_extension(){
	std::string extension = this->get_path().extension();
	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
	return extension;}

char File::begins_with(){
	return (char) tolower(this->get_filename()[0]);
}

std::string File::get_readable_size(){
	return get_size_string(this->get_size());
}

std::ostream& operator<<(std::ostream &stream, File file) {
	// print filename on left
    stream << std::left;
    stream << std::setw(max_filename_length) << file.get_filename();
    // print filesize on right
    stream << std::right;
    stream << std::setw(max_filesize_length) << file.get_readable_size();
    return stream;
}
