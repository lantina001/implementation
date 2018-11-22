#include <stdio.h>
#include <openssl/md5.h>
#include <windows.h>
#include <iostream>

int main()
{
	if (lstrcmpi(argv[1], TEXT("install")) == 0)
	{
		SvcInstall();
		return;
	}
	unsigned char c[MD5_DIGEST_LENGTH];
	char *filename = "test";
	int i;
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
	for (i = 0; i < MD5_DIGEST_LENGTH; i++) printf("%02x", c[i]);
	printf(" %s\n", filename);
	fclose(inFile);
	return 0;

	// Een timer die ervoor zorgt dat de service elke seconden gaat vernieuwen
	System.Timers.Timer timer = new System.Timers.Timer();
	timer.Interval = 600; // 0,6 seconden
	timer.Elapsed += new System.Timers.ElapsedEventHandler(this.OnTimer);
	timer.Start();
}
