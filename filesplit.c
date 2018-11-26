/*
 * @file fs.c
 * @author Shawn Shadrix
 * filesplit <infilename> [splitLength]
 * Default split length is approximately 200MB
 * Splits input file into separate files in the same directory named "out_#.txt"
 */

#include <stdio.h>
#include <stdlib.h>
#if TIMEPROG
#include <time.h>
#endif
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define BUFFERSIZE 256
#define BUFFERPERMB 5882 //this is approximate
#define DEFAULTSIZESPLIT 200

/*
 * Prints usage information to console, then exits with failure status.
 */
void usage(){
    printf("Usage: filesplit <infilename> [splitLength]\n");
    exit(EXIT_FAILURE);
}

/*
 * @param fileCounter the number of the file to be written
 * @return file pointer
 * Opens a file for writing
 */
FILE *openforwrite(unsigned int fileCounter) {
	char fileOutputName[15];

	sprintf(fileOutputName, "out_%u.txt", fileCounter);
	return fopen(fileOutputName, "w");
}

/*
 * Program backbone, handles input parameters and error checking.
 */
int main(int argc,char *argv[]) {
    #if TIMEPROG
        time_t rawTime;
        time_t newTime;
        time ( &rawTime );
    #endif
	if(argc < 2 || argc > 3){
		usage();
	}
	FILE *ptr_readfile;
	FILE *ptr_writefile;
	char buf [BUFFERSIZE];
	unsigned int splitLength = DEFAULTSIZESPLIT, bufferCounter=1, fileCounter=1;
	//input error checking:
	if(argc == 3){
		if(*argv[2] == '-'){
			printf ("error - negative integer length\n");
            usage();
		}
		if (sscanf (argv[2], "%u", &splitLength)!=1) {
			printf ("error - splitLength not an integer\n");
            usage();
		}
	}
	//end error checking
    
    splitLength *= BUFFERPERMB;
	ptr_readfile = fopen(argv[1],"r");
	if (!ptr_readfile) {
        printf("Unable to open readfile: %s\n", argv[1]);
		exit(EXIT_FAILURE);
    }
	ptr_writefile = openforwrite(fileCounter);

	while (fgets(buf, sizeof buf, ptr_readfile)!=NULL) {
		if (bufferCounter == splitLength) {
			fclose(ptr_writefile);
			bufferCounter = 1;
			fileCounter++;
			ptr_writefile = openforwrite(fileCounter);
			if (!ptr_writefile) {
                printf("Unable to open writefile: out_%u.txt\n", fileCounter);
                exit(EXIT_FAILURE);
            }
		}
		fprintf(ptr_writefile,"%s", buf);
		bufferCounter++;
	}
	fclose(ptr_readfile);
    #if TIMEPROG
        time ( &newTime );
        printf("Execution time is: %.f seconds\n", difftime(newTime, rawTime));
    #endif
	return EXIT_SUCCESS;
}
