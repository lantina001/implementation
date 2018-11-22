#include <dirent.h>
#include <stdio.h>

int main(void) {
	const char *array[] = {};
	int i = 0;
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	int file_count = 0;
	DIR * dirp;
	struct dirent * entry;

	dirp = opendir("."); /* There should be error handling after this */
	while ((entry = readdir(dirp)) != NULL) {
		if (entry->d_type == DT_REG) { /* If the entry is a regular file */
			file_count++;
		}
	}
	closedir(dirp);

	if (d) {
		while ((dir = readdir(d)) != NULL) {

			//printf("%s\n", dir->d_name);
			if (sizeof(array) < file_count) {
				array[i] = dir->d_name;
				i = i + 1;
			}
		}
		closedir(d);
		//for(int j = 0; j < (sizeof( my_array ) / sizeof( my_array[0] )); j++) {
		printf("%s\n", array[10]);
		//}
	}
	return(0);
}
