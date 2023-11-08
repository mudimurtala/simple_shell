#ifndef MUTASHELL_H
#define MUTASHELL_H

/* Header files */
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/


/************* All MACROS used are here *************/

#include "muta_macro.h"




/**************String helpers function ***************/
int mutaStrlen(char *str);
char *mutaStrclone(char *str);
int mutaStrcomp(char *str1, char *str2, int x);
char *mutaStrlink(char *str1, char *str2);
void mutaRev_str(char *str);



#define UNUSED(x) (void)(x)


/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *code_title;
	char *enter_line;
	char *com_title;
	int do_count;
	int file_d;
	char **toks;
	char **environ;
	char **mt_list_alias;
} mt_program_data;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct mtBuiltins
{
	char *builtinn;
	int (*fn)(mt_program_data *mtdata);
} mtBuiltins;



#endif
