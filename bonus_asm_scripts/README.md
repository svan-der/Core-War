# Test script

## Usage for mac
>./run_mac.sh [-v | -i | -av | -ai | -a] name_of_assembly_file_WITHOUT_EXTENSION

## Usage for mac
>./run_linux.sh [-v | -i | -av | -ai | -a | -k | -ak]  name_of_assembly_file_WITHOUT_EXTENSION

## Example on linux
>./run_linux.sh -v barriere

since barriere.s is a valid file and it is located in the valid folder

Assembly files need to be present in the folder testfiles/valid folder or testfiles/invalid

Files run by our ASM are called OurAsm_XXXX.txt
Files run by Original ASM are called OriginalAsm_XXXX.txt

## NEW OPTIONS

### To run for folder -> valid

to run one filename from valid folder
>./run_mac.sh -v name_of_assembly_file_WITHOUT_EXTENSION

to run all files from valid folder
>./run_mac.sh -av 

### To run for folder -> invalid

to run one filename from invalid folder
>./run_mac.sh -i name_of_assembly_file_WITHOUT_EXTENSION

to run all files from invalid folder
>./run_mac.sh -ai

### To run for folder -> invalid_s_files
to run one filename from invalid_s_files folder
>./run_mac.sh -k name_of_assembly_file_WITHOUT_EXTENSION

to run all files from invalid_s_files folder
>./run_mac.sh -ak

### To run for ALL folders

to run all files from valid, invalid & invalid_s_files folder
>./run_mac.sh -a

### To CLEAN

to clean up all generated files
>./run_mac.sh -c

While running the clean option, if you get error message like the example below 
rm: ../testfiles/valid/*.cor: No such file or directory
rm: ../testfiles/invalid/*.cor: No such file or directory

it means it didnt findd anything to delete