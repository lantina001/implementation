#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <openssl/md5.h>

int main(int argc, char *argv[])
{
	int n = 0, i = 0, k = 0;
	DIR *d;
	struct dirent *dir;
	d = opendir(".");

	//Determine the number of files
	while ((dir = readdir(d)) != NULL) {
		if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
		{

		}
		else {
			n++;
		}
	}
	rewinddir(d);

	char *filesList[n];

	//Put file names into the array
	while ((dir = readdir(d)) != NULL) {
		if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
		{
		}
		else {
			filesList[i] = (char*)malloc(strlen(dir->d_name) + 1);
			strncpy(filesList[i], dir->d_name, strlen(dir->d_name));
			i++;
		}
	}
	rewinddir(d);

	for (i = 0; i <= n; i++) {
		printf("%s\n", filesList[i]);
	}

	for (k = 0; k < sizeof(filesList) / sizeof(n); k++) {
		/* code */

		unsigned char c[MD5_DIGEST_LENGTH];
		char *filename = filesList[k];
		int j;
		FILE *inFile = fopen(filename, "rb");
		MD5_CTX mdContext;
		int bytes;
		unsigned char data[1024];

		if (inFile == NULL) {
			printf("%s can't be opened.\n", filename);
			return 0;
		}

		MD5_Init(&mdContext);
		while ((bytes = fread(data, 1, 1024, inFile)) != 0)
			MD5_Update(&mdContext, data, bytes);
		MD5_Final(c, &mdContext);
		for (j = 0; j < MD5_DIGEST_LENGTH; j++) printf("%02x", c[i]);
		printf(" %s\n", filename);
		fclose(inFile);
	}

	return 0;


}
