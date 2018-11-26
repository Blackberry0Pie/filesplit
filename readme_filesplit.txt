RUNNING:
-----------------------------------------
Splits input file into separate files in the same directory named "out_#.txt"
Usage: filesplit <infilename> [splitLength]
Default split length is approximately 200MB


example: filesplit bigfile.log
    will split bigfile.log into files of size ~200MB
example: filesplit bigfile.log 150
    will split bigfile.log into files of size ~150MB
-----------------------------------------

-----------------------------------------
COMPILING:
-----------------------------------------
Use make if your system supports it, otherwise:
Compile using gcc -Wall -std=c99 [-D TIMEPROG] filesplit.c -o filesplit
If your system does not have either make or gcc installed, then
you probably should only be reading the above section on running the program.
TIMEPROG will time the program execution time (including wait time for execution)
-----------------------------------------

