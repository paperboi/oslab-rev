#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

char res[26];
int rescnt[126], k, p;
int fsize;

void* histogram( void* c)
{
	ch = (char * )c;
	rescnt[ch - 'a']++;
	pthread_exit(NULL);
}

int main()
{
	FILE *fp;
	fp = fopen("loremipsum.txt", "r");
	if (fp = NULL)
	{
		printf("\nFile did not open!");
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	char s[fsize];
	rewind(fp);
	char c;
	int cnt=0;

	while(fscanf(fp, "%c", &c) == 1)
		s[cnt++] = c;

	k=0;

	pthread_t th[strlen(s)];

	for (int i = 0; i < strlen(s); ++i)
		pthread_create(&th[i], NULL, histogram, s[i]);
	for (int i = 0; i < strlen(s); ++i)
		pthread_join(th[i], NULL);


	printf("%s%13s%19s\n", "Element/Index", "Value", "Histogram");
	for (int i = 0; i < strlen(res); ++i)
	{
		printf("%8c%16d\t\t", res[i], rescnt[i]);
		for (int j = 0; j < rescnt[i]; ++j)
			printf("*");
		printf("\n");
	}
	printf("\n");
	return 0;
}