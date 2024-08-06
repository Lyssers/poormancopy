#include <stdio.h>

int main(int argc, char* argv[]) {
	char line[1000];

	FILE *hand;

	hand=fopen(argv[1], "r");

	if (hand == NULL){
		printf("%s: %s: No such file or dir", argv[0], argv[1]);
		return 1;
	}
	else{

		while (fgets (line, 1000, hand) != NULL) {
			printf("%s", line);
		}

	return 0;

	}
}

