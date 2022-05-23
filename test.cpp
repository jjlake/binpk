#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include "Group.hpp"
#include "options.hpp"
#include "Output.hpp"
#include <string>
#include <vector>

std::vector<std::vector<std::string>> get_titles(std::vector<Group> groups) {
	std::vector<std::vector<std::string>> grouped_titles;
	std::vector<std::string> titles;
	for(Group group: groups){
		for(File file: group.get_files()){
			titles.push_back(file.get_path().stem());
			std::sort(titles.begin(), titles.end());
		}
		grouped_titles.push_back(titles);
		std::sort(grouped_titles.begin(), grouped_titles.end());
		titles.clear();
	}
	return grouped_titles;
}

void create_files(std::string file_path, std::vector <std::pair <std::string, unsigned long int >>& files_to_create ){
	for(auto file: files_to_create){
		std::ofstream output(file_path + "/" + file.first);
		output << std::string(file.second, 0);
	}
}

void teardown(std::string tmp_file_path){
	fs::remove_all(tmp_file_path);
	fs::remove(tmp_file_path);
}

TEST_CASE( "correct/efficient binning of files", "[bin]" ){
	std::string file_path = "./test";
	bin_max_size = 1e5;
	
	std::vector<std::pair<std::string, unsigned long int>> files_to_create = {
		std::pair<std::string, unsigned long int>("a.txt", 1e4),
		std::pair<std::string, unsigned long int>("b.txt", 9e4+1),
		std::pair<std::string, unsigned long int>("c.txt", 2e4),
		std::pair<std::string, unsigned long int>("d.txt", 1e4),
		std::pair<std::string, unsigned long int>("e.txt", 9e4+1),
		std::pair<std::string, unsigned long int>("f.txt", 2e4),
		std::pair<std::string, unsigned long int>("g.txt", 1e4),
		std::pair<std::string, unsigned long int>("h.txt", 9e4+1),
		std::pair<std::string, unsigned long int>("i.txt", 2e4),
		std::pair<std::string, unsigned long int>("j.txt", 1e4),
		std::pair<std::string, unsigned long int>("k.txt", 9e4+1)
	};
	
	
	SECTION("Bin correctly without constraints"){
		std::vector<std::vector<std::string>> expected_output = {{"a", "c", "d", "f", "g", "i", "j"},
																 {"b"}, {"e"}, {"h"}, {"k"}};
		fs::create_directory(file_path);
		output_loc = file_path;
		create_files(file_path, files_to_create);
		auto elems = read_files(file_path, true);
		std::vector<Group> groups = pack_bins(elems, true);
		REQUIRE(get_titles(groups)==expected_output);
		for(int count=0; count<groups.size(); count++){
			move_files(groups[count], std::to_string(count));
		}
		groups.clear();
		for(auto dir: fs::directory_iterator(file_path)){
			groups.push_back(read_files(dir.path(), false));
		}
		REQUIRE(get_titles(groups)==expected_output);
		teardown(file_path);
	}
}
