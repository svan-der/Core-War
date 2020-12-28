# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    run_linux.sh                                       :+:    :+:             #
#                                                      +:+                     #
#    By: dsaripap <dsaripap@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/12 10:26:08 by dsaripap      #+#    #+#                  #
#    Updated: 2020/09/18 08:48:14 by dsaripap      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

os="linux"

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

OurOutput="OurCorFiles"
OriginalOutput="OriginalCorFiles"
Diffs="Diffs"

# Check if directories exists and if not create them
if [ ! -d "$OurOutput" ]; then
    `mkdir $OurOutput`
fi

if [ ! -d "$OriginalOutput" ]; then
    `mkdir $OriginalOutput`
fi

if [ ! -d "$Diffs" ]; then
    `mkdir $Diffs`
fi

# function executed when given eg. : > ./run_mac.sh -v 42
run_diff_for_one_vfile ()
{
	dfile="$2diff"
	command="$(./vm-champ-$1/asm ./testfiles/$3/$2.s)"
	command="$(xxd ./testfiles/$3/$2.cor > $OriginalOutput/$2xxd_orig)"
	command="$(rm -f ./testfiles/$3/$2.cor)"
	command="$(../asm ./testfiles/$3/$2.s)"
	command="$(xxd ./testfiles/$3/$2.cor > $OurOutput/$2xxd_our)"
	command="$(rm -f ./testfiles/$3/$2.cor)"
	command="$(diff -c $OriginalOutput/$2xxd_orig $OurOutput/$2xxd_our > $Diffs/$dfile)"
	command="$(cat $Diffs/$dfile)"
	# echo "$command"
	if [ -s $Diffs/$dfile ]
		then
			printf "$RED Diffs in $dfile -> FAIL \n $RESET"
		else
			printf "$GREEN No Diffs in $dfile -> PASS \n $RESET"
	fi
}

run_diff_for_one_ifile () 
{
	command="$(./vm-champ-$1/asm ./testfiles/$3/$2.s > $OriginalOutput/OriginalAsm_$2.txt)"
	command="$(../asm ./testfiles/$3/$2.s > $OurOutput/OurAsm_$2.txt)"
	filecor="./testfiles/$3/$2.cor"
	if test -f "$filecor"; then
		printf "$RED $filecor is Present -> FAIL \n $RESET"
	else
		printf "$GREEN $filecor Not Present -> PASS \n $RESET"
	fi
}

run_valid ()
{
	folder="valid"
	for file in ./testfiles/valid/*; do
		filename=$(basename -- "$file")
		extension="${filename##*.}"
		filename="${filename%.*}"
		echo $filename
		run_diff_for_one_vfile $os $filename $folder
	done
}

run_invalid ()
{
	folder="invalid"
	for file in ./testfiles/invalid/*; do
		filename=$(basename -- "$file")
		extension="${filename##*.}"
		filename="${filename%.*}"
		# echo $filename
		run_diff_for_one_ifile $os $filename $folder
	done
}

run_invalid_s ()
{
	folder="invalid_s_files"
	for file in ./testfiles/invalid_s_files/*; do
		filename=$(basename -- "$file")
		extension="${filename##*.}"
		filename="${filename%.*}"
		# echo $filename
		run_diff_for_one_ifile $os $filename $folder
	done
}

run_all ()
{
	run_valid
	run_invalid
}

count=`ls -1 ./testfiles/valid/*.cor 2>/dev/null | wc -l`

clean_up ()
{	
	# delete all generated files
	count=`ls -1 ./$Diffs/* 2>/dev/null | wc -l`
	if [ "$(ls -A $Diffs/)" ] && [ $count != 0 ] 
	then
  		`rm $Diffs/*diff`
	fi
	count=`ls -1 ./testfiles/valid/*.cor 2>/dev/null | wc -l`
	if [ "$(ls -A ./testfiles/valid/)" ] && [ $count != 0 ] 
	then
  		`rm ./testfiles/valid/*.cor`
	fi
	count=`ls -1 ./testfiles/invalid/*.cor 2>/dev/null | wc -l`
	if [ "$(ls -A ./testfiles/invalid/)" ] && [ $count != 0 ] 
	then
  		`rm ./testfiles/invalid/*.cor`
	fi
	count=`ls -1 ./testfiles/invalid_s_files/*.cor 2>/dev/null | wc -l`
	if [ "$(ls -A ./testfiles/invalid_s_files/)" ] && [ $count != 0 ] 
	then
  		`rm ./testfiles/invalid_s_files/*.cor`
	fi
	count=`ls -1 $OriginalOutput/* 2>/dev/null | wc -l`
	if [ "$(ls -A $OriginalOutput/)" ] && [ $count != 0 ] 
	then
  		`rm $OriginalOutput/*`
	fi
	count=`ls -1 $OurOutput/* 2>/dev/null | wc -l`
	if [ "$(ls -A $OurOutput/)" ] && [ $count != 0 ] 
	then
		`rm $OurOutput/*`
	fi
}

ask_clean ()
{
	echo "Do you want to delete all generated files in current folder? [y/n]"
	read response

	if [ "$response" = "y" ]
	then
		clean_up
	fi
}

if [ "$1" == "-av" ]
then
	run_valid
	ask_clean
elif [ "$1" == "-ai" ]
then
	run_invalid
	ask_clean
elif [ "$1" == "-a" ]
then
	run_all
	ask_clean
elif [ "$1" == "-v" ]
then
	folder="valid"
	run_diff_for_one_vfile $os $2 $folder
	ask_clean
elif [ "$1" == "-i" ]
then
	folder="invalid"
	run_diff_for_one_ifile $os $2 $folder
	ask_clean
elif [ "$1" == "-k" ]
then
	folder="invalid_s_files"
	run_diff_for_one_ifile $os $2 $folder
	ask_clean
elif [ "$1" == "-ak" ]
then
	run_invalid_s
	ask_clean
elif [ "$1" == "-c" ]
then
	clean_up
else
	printf "$RED Heyo!!! You put the wrong option! $RESET \n"
	printf "usage : ./run_xxx [-v | -i | -av | -ai | -a | -k | -ak]"
fi
