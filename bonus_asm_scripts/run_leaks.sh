#!/bin/bash

YELLOW="\x1b[38;2;253;253;150m"
RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

run_valgrind ()
{
	command="$(valgrind --leak-check=full ../asm ../testfiles/$2/$1.s)"
}

run_leaks_valid ()
{
	folder="valid"
	for file in ../testfiles/$folder/*; do
		filename=$(basename -- "$file")
		extension="${filename##*.}"
		filename="${filename%.*}"
		# echo $filename
		printf "\n\n $filename \n\n"
		run_valgrind $filename $folder
	done
}

run_leaks_invalid ()
{
	folder="invalid"
	for file in ../testfiles/$folder/*; do
		filename=$(basename -- "$file")
		extension="${filename##*.}"
		filename="${filename%.*}"
		# echo $filename
		printf "\n\n $filename \n\n"
		run_valgrind $filename $folder
	done
}

run_leaks_s_invalid ()
{
	folder="invalid_s_files"
	for file in ../testfiles/$folder/*; do
		filename=$(basename -- "$file")
		extension="${filename##*.}"
		filename="${filename%.*}"
		# echo $filename
		printf "\n\n $filename \n\n"
		run_valgrind $filename $folder
	done
}

if [ "$1" == "-av" ]
then
	run_leaks_valid
	ask_clean
elif [ "$1" == "-ai" ]
then
	run_leaks_invalid
	ask_clean
# elif [ "$1" == "-a" ]
# then
# 	run_all
# 	ask_clean
# elif [ "$1" == "-v" ]
# then
# 	folder="valid"
# 	run_diff_for_one_vfile $os $2 $folder
# 	ask_clean
# elif [ "$1" == "-i" ]
# then
# 	folder="invalid"
# 	run_diff_for_one_ifile $os $2 $folder
# 	ask_clean
# elif [ "$1" == "-k" ]
# then
# 	folder="invalid_s_files"
# 	run_diff_for_one_ifile $os $2 $folder
# 	ask_clean
elif [ "$1" == "-ak" ]
then
	run_leaks_s_invalid
	ask_clean
elif [ "$1" == "-c" ]
then
	clean_up
else
	printf "$RED Heyo!!! You put the wrong option! $RESET \n"
	printf "usage : ./run_xxx [-v | -i | -av | -ai | -a | -k | -ak]"
fi