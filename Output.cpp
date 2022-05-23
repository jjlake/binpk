#include "File.hpp"
#include "Group.hpp"
#include "options.hpp"
#include "util.hpp"

void move_files(Group& group, std::string folder_name){
	fs::path dest = fs::path(output_loc+'/'+folder_name);
	if(!fs::exists(dest)){
		fs::create_directory(dest);
	}
	
	if(fs::is_directory(dest)){
		for(File file: group.get_files()){
			fs::path file_dest = dest;
			file_dest /= fs::path(file.get_filename());
			if(keep)
				fs::copy(file.get_path(), file_dest);
			else
				fs::rename(file.get_path(), file_dest);
		}
	}
}

void print_groups(std::vector<Group> &groups){
	for(auto i: groups){
		std::cout << i << std::endl;
	}
}

