#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#define MAX_WORD 50
#define LENGTH 50

/*
   char** _strtok(const char* s, const char *delim, int* counter)
   {

   char **temp = (char**)malloc(MAX_WORD * sizeof(char*));
   if (temp == NULL)
   {
   return NULL;
   }

   char* copy = strdup(s);
   if (copy == NULL)
   {
   free(temp);
   return NULL;
   }

   int count = 0;
   char* tok = strtok(copy, delim);
   while (tok != NULL)
   {
   temp[count] = strdup(tok);
   tok = strtok(NULL, delim);
   count++;
   }

   free(copy);
 *counter = count;
 return temp;
 }

 */



char* _strtok(char *restrict s, const char* restrict delim)
{

	int i = 0;
	char *temp;

	if (s == NULL) 
	{
		return NULL;
	}
	temp = malloc(sizeof(char) * strlen(s) + 1);

	if (temp == NULL)
	{
		return 	NULL;
	}

	if (*s == *delim)
	{

		for (int index = 0; index < strlen(delim); index++)
		{

			if (s[i] == delim[index] && s[i] != 0)
			{
				temp[i] = s[i - 1];
				s[i - 1] = '\0';
			}
		}
	}

	free(temp);
	return temp;
}



int main()
{
    char str[] = "Geeks  for  Geeks";
 
    // Returns first token
    char* token = strtok(str, "  ");
 
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL) {
       printf("%s\n", token);
        token = strtok(NULL, "  ");
    }
 
    return 0;
}




/* for (i = 0; s[i] != '\0'; i++)
   {
   if (s[i] != delim)
   {
   temp[i] = s[i];
   }

   if (s[i] == ' ' || s[i] == s[i - 1])
   {
   temp[i] = s[i - 1];
   s[i - 1] = '\0';
   }
   }
   return temp;
   }

 

int main(void)
{
	int i, counter;

	char str[] = "Geeks-for-Geeks";

	char* token = _strtok(str, "-");

	if (token != NULL)
	{
		printf("Token from the strtok\n");

		for (i = 0; i < counter; i++)
		{ 
			printf("%s\n", token[i]);
			free(token[i]);
		}
		free (token);
	}
	else
	{
		printf("Memory allocation error\n");
	}
	return 0;

}*/
