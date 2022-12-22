#include "File.hpp"
#include "Group.hpp"
#include "options.hpp"
#include "Output.hpp"
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

void print_instructions(){
	std::cout << BOLD_ESC_CODE << UNDERLINE_ESC_CODE << PROGRAM_TITLE << DEF_FORMATTING_ESC_CODE << std::endl;
	std::cout << BOLD_ESC_CODE << "Description" << DEF_FORMATTING_ESC_CODE << std::endl;
	std::cout << "Utility for bin-packing files into groups (bins) of a given size." << std::endl;
	std::cout << std::endl;
	std::cout << BOLD_ESC_CODE << "Usage" << DEF_FORMATTING_ESC_CODE << std::endl;
	std::cout << BOLD_ESC_CODE << "./binpk" << DEF_FORMATTING_ESC_CODE << " size [options]" << std::endl;
	std::cout << "	where size is the maximum bin size in bytes." << std::endl;
	std::cout << std::endl;
	std::cout << BOLD_ESC_CODE << "Options" << DEF_FORMATTING_ESC_CODE << std::endl;
	std::cout <<"--bin [mode]" << std::endl;
	std::cout <<"	where mode is one of the following binning methods:" << std::endl;
	std::cout <<"		- alphabetical: bin by starting letter (eg; a, b, c)"<< std::endl;
	std::cout <<"		- filetype: group same filetypes together in bins will fail if any group of specified type exceeds the maximum bin size."<< std::endl;
	std::cout << std::endl;
	std::cout <<"--recursive"<< std::endl;
	std::cout <<"	Explore input folder recursively for files to bin."<< std::endl;
	std::cout << std::endl;
	std::cout <<"--sort [mode]"<< std::endl;
	std::cout <<"	where mode is one of the following sort methods:"<< std::endl;
	std::cout <<"		- alphabetical"<< std::endl;
	std::cout <<"		- size" << std::endl;
	std::cout <<"	either will sort file entries in ascending order before binning, encouraging clustering of similar files at the cost of efficiency."<< std::endl;
	std::cout << std::endl;
	std::cout <<"--verbose"<< std::endl;
	std::cout <<"	print output bins description" << std::endl;
	std::cout << std::endl;
}
