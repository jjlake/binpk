#include "File.hpp"
#include "Group.hpp"
#include "options.hpp"
#include "Output.hpp"
#include "util.hpp"

bool Group::add(File file){
	this->files.push_back(file);
	return true;
}

std::vector<File> Group::get_files(){
	return this->files;
}

std::string Group::get_filename(){
	return (this->get_files()[0].get_filename());
}

unsigned long int Group::get_size(){
	unsigned long int size = 0;
	for(File &file: this->files){
		size += file.get_size();
	}
	return size;
}

Group::Group(std::string start, std::string end){
	this->start = start;
	this->end = end;
}

std::string Group::get_readable_size(){
	return get_size_string(this->get_size());
}

std::vector<Group> Group::slice(){
	switch(bin_mode){
		case BIN_ALPHABETICAL:
			return this->bin_alphabetical();
			
		//case BIN_DATE_MODIFIED:
			//return this->bin_date_modified();
			
		case BIN_FILETYPE:
			return this->bin_filetype();
			
	}
	return bin_alphabetical(); // default
}

std::vector<Group> Group::group_by(auto &func){
	auto curr = func(this->get_files()[0]);
	
	std::vector<Group> groups;
	std::string start{curr};
	std::string end{curr};
	Group group = Group(start, end);
	
	for(File f: this->get_files()){
		if(curr!=func(f)){
			curr = func(f);
			if(!group.get_files().empty()){
				group.set_end(end);
				groups.push_back(group);
				curr = func(f);
				start = curr;
				end = start;
				group = Group(start, end);
			}
		}
		group.add(f);
		end = std::string{curr};
	}
	
	if(!group.get_files().empty()){
		groups.push_back(group);
	}
	
	return groups;
}

void Group::sort(){
	switch(sort_mode){
		case SORT_ALPHABETICAL:
			this->sort_alphabetical();
			break;
		case SORT_SIZE:
			this->sort_size();
	}
}

void Group::sort_alphabetical(){
	std::sort(this->files.begin(), this->files.end(), compare_alphabetically);
}

void Group::sort_filetype(){
	std::sort(this->files.begin(), this->files.end(), compare_filetype);
}

void Group::sort_size(){
	std::sort(this->files.begin(), this->files.end(), compare_size);
}

std::vector<Group> Group::bin_alphabetical(){
	this->sort_alphabetical();
	auto first_char = [](File &f){return f.begins_with();};
	auto groups = this->group_by(first_char);
	return groups;
}

std::vector<Group> Group::bin_filetype(){
	this->sort_filetype();
	auto filetype = [](File f){return f.get_extension();};
	return this->group_by(filetype);
}

bool Group::fits(File addition){
	if ((this->get_size()+addition.get_size()) <= bin_max_size){
		return true;
	}
	return false;
}

bool Group::fits(Group addition){
	if ((this->get_size()+addition.get_size()) <= bin_max_size){
		return true;
	}
	return false;
}

Group& Group::operator += (Group b){
	std::vector<File> new_files = b.get_files();
	for(auto i: b.get_files()){
		this->add(i);
	}
	return *this;
}	

std::ostream& operator<<(std::ostream &stream, Group g) {
	stream << g.get_title() << std::endl;
	stream << std::string(max_filename_length + max_filesize_length, '=') << std::endl;
	for(File f: g.get_files()){
		stream << f << std::endl;
	}
	stream << std::string(max_filename_length + max_filesize_length, '-') << std::endl;
	
	stream << std::left << std::setw(max_filename_length) << "TOTAL: ";
	stream << std::right << std::setw(max_filesize_length) << g.get_readable_size() << std::endl;
	
	stream << std::string(max_filename_length + max_filesize_length, '=') << std::endl;
	return stream;
}

std::vector<Group> pack_bins(Group group, bool ordered){
	std::vector<Group> bins;
	bool found = false;
	for(File file: group.get_files()){
		found = false;
		for(Group &bin: bins){
			if(bin.fits(file)){
				bin.add(file);
				found = true;
				break;
			} else if(file.get_size() > bin_max_size){
				std::cout << "Item exceeds bin size." << std::endl;
				exit(0);
			}
		}
		
		if(!found){
			Group bin = Group(group.get_start(), group.get_end());
			bin.add(file);
			bins.push_back(bin);
		}
	}
	return bins;
}

std::vector<Group> pack_bins(std::vector<Group> &groups, bool ordered){
	std::vector<Group> bins;
	bool found = false;
	for(Group group: groups){
		found = false;
		for(Group &bin: bins){
			if(bin.fits(group)){
				for(auto i: group.get_files()){
					bin.add(i);
				}
				//bin += group;
				found = true;
				break;
			} else if(group.get_size() > bin_max_size){
				std::cout << "Item exceeds bin size." << std::endl;
				exit(0);
			}
		}
		
		if(!found){
			Group bin = Group(group.get_start(), group.get_end());
			bin += group;
			bins.push_back(bin);
		}
	}
	return bins;
}

std::string Group::get_start(){
	return this->start;
}

std::string Group::get_end(){
	return this->end;
}

void Group::set_end(std::string end){
	this->end = end;
}

std::string Group::get_title(){
	std::string title = this->get_start();
	if(this->get_end()!=this->get_start())
		title = title + " - " + this->get_end();
	transform(title.begin(), title.end(), title.begin(), ::toupper);
	return title;
}


Group::Group(){
	
}


void process_dir_entry(Group& elems, const fs::directory_entry& entry){
	if(entry.is_regular_file()){
		//std::cout << entry.path() << entry.file_size() << std::endl;
		std::string filename = entry.path().string();
		if(max_filename_length < filename.length()+1)
			max_filename_length = filename.length()+1;
		unsigned int filesize_length = std::to_string(entry.file_size()).length();
		if(max_filesize_length < filesize_length+1)
			max_filesize_length = filesize_length+1;
		elems.add(File(entry.path()));
	}
}


Group read_files(std::string path, bool recursive){
	Group elems = Group();
	if(recursive){
		for (const auto & entry : fs::recursive_directory_iterator(path)){
			process_dir_entry(elems, entry);
		}
	} else {
		for (const auto & entry : fs::directory_iterator(path)){
			process_dir_entry(elems, entry);
		}
	}
	return elems;
}
