#include "File.hpp"
#include "Group.hpp"
#include "options.hpp"
#include "Output.hpp"
#include "util.hpp"

int main(int argc, char **argv){
	bin_max_size = std::stoul(argv[1]); // MOVE
	process_args(argc, argv);
	
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
