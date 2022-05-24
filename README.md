# binpk
Utility for bin-packing files into groups (bins) of a given size.

This program is intended for situations in which files need to be archived in an organised way across many disks, optical media or otherwise non-contiguous volumes.

## Usage
binpk bin_size \[options]

where bin_size is the maximum bin size in bytes.

### Options
--bin \[bin_type]
  where bin_type is one of:
  - alphabetical: bin by starting letter (eg; a, b, c) 
  - filetype: group same filetypes together in bins
  will fail if any group of specified type exceeds the maximum bin size.

--recursive
  Explore input folder recursively for files to bin.
  
--sort \[sorting_method]
  where sorting_method is one of:
  - alphabetical
  - size
  Either will sort file entries in ascending order before binning, encouraging clustering of similar files at the cost of efficiency.

--verbose
  print output bins description

#### TBC (not yet implemented)
--input \[path to input_directory]
--keep
--output \[path_to_output_directory]
