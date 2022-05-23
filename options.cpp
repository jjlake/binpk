#include "options.hpp"

// Namespaces:
using namespace std;

enum BIN_MODE bin_mode = BIN_NONE;
enum SORT_MODE sort_mode = SORT_NONE;

std::string input_loc;
std::string output_loc;
bool write_bins = false;
bool zip = false;

bool preserve_directories = false;
bool recursive = false;
bool verbose = false;
bool keep = false;

void process_args(int argc, char **argv) {
    int opt;
    
	static struct option long_options[] = {
		{"bin", required_argument, NULL, 'b'},
		{"input", required_argument, NULL, 'i'},
		{"keep", no_argument, NULL, 'k'},
		{"output", required_argument, NULL, 'o'},
		{"recursive", no_argument, NULL, 'r'},
		{"sort", required_argument, NULL, 's'},
		{"verbose", no_argument, NULL, 'v'},
		//{"zip", no_argument, NULL, 'z'},
		{0,0,0,0}
	};

      /* getopt_long stores the option index here. */
      int option_index = 0;
      
    // Retrieve the options:
    
    while ( (opt = getopt_long(argc, argv, "b:dio:O:rs:wz", long_options, &option_index)) != -1 ) {  // for each option...
        switch ( opt ) {
			// Bin mode option
			case 'b':{
				if(strcmp(optarg, "alphabetical")==0)
					bin_mode = BIN_ALPHABETICAL;
				////else if(strcmp(optarg, "date_modified")==0)
					////bin_mode = BIN_DATE_MODIFIED;
				else if(strcmp(optarg, "filetype")==0)
					bin_mode = BIN_FILETYPE;
				else
					goto invalid_option;
				break;
			}
						
			case 'i':
				input_loc = optarg;
				break;
			
			case 'k':
				keep = true;
				break;
			
			case 'o':
				output_loc = optarg;
				break;
						
			case 'r':
				recursive = true;
				break;
			
			case 's':{
				if(bin_mode!=BIN_NONE){
					std::cout << "cannot use both bin and sort modes" << std::endl;
					exit(EINVAL);
				} else if(strcmp(optarg, "alphabetical")==0)
					sort_mode = SORT_ALPHABETICAL;
				else if(strcmp(optarg, "size")==0)
					sort_mode = SORT_SIZE;
				else
					goto invalid_option;
				break;
			}
			
			case 'v':
				verbose = true;
				break;
						
			//case 'z':
				//zip = true;
				//break;
			
			case '?':
				exit(EINVAL);
				
			invalid_option:{
				cout << BOLD_ESC_CODE << long_options[option_index].name << DEF_FORMATTING_ESC_CODE << " option parameter not found: " << optarg << std::endl;
				exit(EINVAL);
			}
        }
    }
}
