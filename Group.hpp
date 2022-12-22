#ifndef GROUP_H_INCLUDED
#define GROUP_H_INCLUDED

#include "File.hpp"
#include "util.hpp"

class Group {
	public:
	std::string start, end;
	
	// Constructors
	Group();
	Group(std::string start, std::string end);
	
	// Getters/Setters
	std::vector<File> get_files();
	std::string get_filename();
	unsigned long int get_size();
	std::string get_start();
	std::string get_end();
	void set_end(std::string end);
	
	// Add subitem functions
	bool add(File file);
	Group& operator += (Group b);
	
	// Print/formatting functions
	std::string get_readable_size();
	std::string get_title();
	
	// Grouping/Binning functions
	std::vector<Group> slice();
	std::vector<Group> group_by(auto &func);
	std::vector<Group> bin_alphabetical();
	std::vector<Group> bin_filetype();
	
	// Sort functions
	void sort();
	void sort_alphabetical();
	void sort_filetype();
	void sort_size();
	
	// Tests if a subitem fits in a destination bin
	bool fits(File addition);
	bool fits(Group addition);
	
	private:
	std::vector<File> files = std::vector<File>();
};

std::ostream& operator<<(std::ostream &stream, Group g);

std::vector<Group> pack_bins(Group group, bool ordered);
std::vector<Group> pack_bins(std::vector<Group> &groups, bool ordered);

void process_dir_entry(Group& elems, const fs::directory_entry& entry);
Group read_files(std::string path, bool recursive);

#endif
