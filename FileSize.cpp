#include "File.hpp"
#include "FileSize.hpp"
#include "util.hpp"

char FileSize::get_unit_index(){
	unsigned int unit_index = 0;
	
	double tmp = this->get_size_in_bytes();
	while(tmp>=1000.0){
		unit_index++;
		tmp/=1000.0;
	}
	
	return unit_index;
}

FileSize::FileSize(){
	this->size_in_bytes = 0;
}

FileSize::FileSize(unsigned long int size_in_bytes){
	this->set_size(size_in_bytes);
}

void FileSize::set_size(unsigned long int size_in_bytes){
	this->size_in_bytes = size_in_bytes;
}

unsigned long int FileSize::get_size_in_bytes(){
	return this->size_in_bytes;
}

char FileSize::get_unit(){
	return SIZE_UNITS[this->get_unit_index()];
}

std::string FileSize::get_size(){
	return this->to_string();
}

std::string FileSize::to_string(){
	double size = 0.0;
	if(this->get_unit_index()>0){
		size = this->get_size_in_bytes()/(this->get_unit_index()*1000.0);
	} else {
		size = this->get_size_in_bytes();
	}
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << size << " " << this->get_unit();
	std::string s = stream.str();
	return s;
}

std::ostream& operator<<(std::ostream &stream, FileSize size) {
    return stream << size.to_string();
}

FileSize FileSize::operator+(FileSize size) {
	return FileSize(this->get_size_in_bytes()+size.get_size_in_bytes());
}


