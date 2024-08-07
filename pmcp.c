#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char * argv[]){
	char * DYNAMIC_PROGRAM_NAME = argv[0];
	char * bytes;

	FILE *input;
	FILE *output;
	input=fopen(argv[1], "rb");

	output=fopen(argv[2], "w");

	void usage();
	void block_size();
	if (argc != 3){
		usage();
		return 1;
	}

        if (input == NULL){
                printf("%s: %s: No such file or dir for source", DYNAMIC_PROGRAM_NAME, argv[1]);
                return 1;
        }
	else if (output == NULL) {
		fclose(input);
		printf("%s: %s: Couldn't open destination file.", DYNAMIC_PROGRAM_NAME, argv[2]);
		return 1;
	}

        else{

		fseek(input, 0, SEEK_END); //SEEKS TO END
		long long size = ftell(input); //SIZE OF FILE
		//printf("File Size: %lu Bytes", size); //Print file size
		fseek(input, 0, SEEK_SET); //Seeks back to start
		double one_percent = ((double) 1 / size); //ONE PERCENT OF FILESIZE FOR PROGRESS

		//Determine blocksize based on filesize (very dumb):
		unsigned long blocksize;
		block_size(&size, &blocksize);
		bytes = malloc(blocksize);
		unsigned long long remaining_size = size;

		//bc is block counter, if block counter * times blocksize is less than size and remaining size is more than zero, increment block counter		
		for (int bc = 0; bc*blocksize < size && remaining_size > 0; bc++){

			//printf("\nProgress: %.2f%%", bc * blocksize * one_percent * 100); //PRINT PROG
			if (remaining_size < blocksize) block_size(&remaining_size, &blocksize); //IF LAST BLOCK IS LESS THAN BLOCKSIZE THEN SET BLOCKSIZE TO REMAINING SIZE
				fread(bytes, blocksize, 1, input); //READ TO BYTES BLOCKSIZE-SIZE CHUNK, QUANTITY: 1, FROM INPUT
				//printf("\nReading");
				remaining_size = remaining_size - blocksize;
				//printf("\nRemaining Size: %lu", remaining_size);
				//printf("\nBlock Size: %i", blocksize);
				fwrite(bytes, blocksize, 1, output); //READ FROM BYTES 1-BYTE-SIZE CHUNK, QUANTITY: 1, TO OUTPUT
				//printf("\nWriting:");
		}
		//printf("\nDone!");
		fclose(input);
		fclose(output);
		free(bytes);
		bytes = NULL;
		return 0;
	}
	

}

void usage(){
       printf("Usage: pmcp <input_file> <destination_file");
}       

void block_size(unsigned long long * size, unsigned long * blocksize){
	
	if (*size > 524288) *blocksize = 524288;
	else if (*size > 262144) *blocksize = 262144;
	else if (*size > 131072) *blocksize = 131072;
	else if (*size > 65536) *blocksize = 65536;
	else if (*size > 32768) *blocksize = 32768;
	else if (*size > 16384) *blocksize = 16384;
	else if (*size > 4096) *blocksize = 4096;
	else if (*size > 2048) *blocksize = 2048;
	else if (*size > 1024) *blocksize = 1024;
	else if (*size < 1024) *blocksize = 1;

}
