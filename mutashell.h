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




#define UNUSED(x) (void)(x)


/************* STRUCTURES **************/

/**
 * struct program_info- struct for the program's data
 * @code_tag: the executable command name
 * @prompt_user: input that is read with _getline
 * @command_tag: pointer to the first user command input
 * @command_count: counts the commands executed
 * @file_d: file descriptor to the input of commands
 * @toks: pointer to array of parsed input
 * @environ: copy of the environ
 * @mt_list_alias: pointer array of aliases.
 */
typedef struct attributes
{
	char *code_tag;
	char *prompt_user;
	char *command_tag;
	int command_count;
	int fd;
	char **toks;
	char **environ;
	char **mt_list_alias;
} mt_code_data;

/**
 * struct  mt_internalCommands - struct for the builtins
 * @ mt_internalCommand: the name of the builtin
 * @fn: the associated function to be called for each builtin
 */
typedef struct mt_internalCommands
{
	char *mt_internalCommand;
	int (*fn)(mt_code_data *mtdata);
}  mt_internalCommands;


/**************String helpers function ***************/
int mutaStrlen(char *str); /* function to count the length of the string */
char *mutaStrclone(char *str); /* function to duplicate the string */
int mutaStrcomp(char *str1, char *str2, int x); /* function compare string*/
char *mutaStrlink(char *str1, char *str2); /* function to concatenate strings */
void mutaRev_str(char *str); /* function to reverse the strings */


/****************Alias management functions*****************/
int mtalias_printing(mt_program_data *mtdata, char *mtalias);
char *find_alias(mt_program_data *mtdata, char *alias_name);
int position_alias(char *mtalias_str, mt_program_data *data);



#endif
