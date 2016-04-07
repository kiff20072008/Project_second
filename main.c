#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_ALLOC_MEMORY 128

#define SIZE_BLOCK_ALLOC_MEMORY 10

int getstring(FILE *file, char **buffer)
{
	int number_of_blocks = 1;
	int ch;
	int sch = 0;
	if (feof(file))
		return 1;
	*buffer = (char*)malloc(SIZE_ALLOC_MEMORY*sizeof(char)*number_of_blocks);
	if (*buffer == NULL)
	{
		if ((ch = fgetc(file)) == EOF)
			return 1;
		else
			return 2;
	}

	while ((ch = fgetc(file)) != '\n')
	{
		if (ch == EOF)
			break;
		if (ch > 127 || ch < 32)
		{
			return 0;
		}

		if (sch >= (SIZE_ALLOC_MEMORY*number_of_blocks - 1))
		{
			char *temp;
			++number_of_blocks;
			temp = (char*)realloc(*buffer, SIZE_ALLOC_MEMORY*number_of_blocks*sizeof(char));
			if (temp == NULL)
			{
				if (ch == EOF)
					return 1;
				return 2;
			}
			*buffer = temp;
		}
		(*buffer)[sch] = (char)ch;
		++sch;
	}
	if (sch <= (SIZE_ALLOC_MEMORY*number_of_blocks - 1))
		(*buffer)[sch] = '\0';
	return 0;
}




int main(int Argc, char *Argv[])
{
	FILE *file;
	char *buffer = NULL;
	int is_in = 0;
	char **bufferTemp;
	int sch = 0;
	int choice = 0;
	int counter = 1;

	bufferTemp = (char**)malloc(SIZE_BLOCK_ALLOC_MEMORY*counter*sizeof(char*));

	fopen_s(&file,Argv[1], "rt");
	if (file == NULL)
	{
		printf("Error no such file\n");
		return 1;
	}

	while ((choice = getstring(file, &buffer)) != 1)
	{
		if (sch >= SIZE_BLOCK_ALLOC_MEMORY*counter - 1)
		{
			counter++;
			char **temp;
			temp = (char**)realloc(*bufferTemp, SIZE_BLOCK_ALLOC_MEMORY*counter*sizeof(char*));
			if (temp == NULL)
			{
					return 1;
			}
			bufferTemp = temp;
		}

		bufferTemp[sch] = buffer;
		sch++;
	}


	for (;;)
	{
		is_in = 0;
		getstring(stdin, &buffer);
		if (strstr("exit", buffer))
			break;
		for (int i = 0; i < sch; i++)
			if (strstr(bufferTemp[i], buffer) != NULL)
			{
				printf("YES\n");
				is_in = 1;
				break;
			}
		if(!is_in)
			printf("NO\n");
	}

	return 0;
}