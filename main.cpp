#include "File.hpp"
#include "Group.hpp"
#include "options.hpp"
#include "Output.hpp"
#include "util.hpp"

int main(int argc, char **argv){
	process_args(argc, argv);
	
	if(help){
		print_instructions();
		exit(0);
	}
	
	Group elems = read_files("./", recursive);
	
	std::vector<Group> groups;
	
	if(bin_mode!=BIN_NONE)
		groups = elems.slice();
	else if(sort_mode!=SORT_NONE){
		elems.sort();
		groups = pack_bins(elems, true);
	} else {
		groups = pack_bins(elems, true);
	}
	
	for(Group group: groups)
		move_files(group, group.get_title());
	
	if(verbose){
		print_groups(groups);
	}
	
	return 0;
}
