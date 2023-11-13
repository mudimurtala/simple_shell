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
 * struct elements- struct for the program's data
 * @code_tag: the executable command name
 * @prompt_user: input that is read with _getline
 * @command_tag: pointer to the first user command input
 * @cmdExec_count: counts the commands executed
 * @fd: file descriptor to the input of commands
 * @toks: pointer to array of parsed input
 * @environ: copy of the environ
 * @mt_list_alias: pointer array of aliases.
 */
typedef struct elements
{
	char *code_tag;
	char *prompt_user;
	char *command_tag;
	int cmdExec_count;
	int fd;
	char **parsed_items;
	char **environ;
	char **mt_listAlias;
} mt_code_info;

/**
 * struct  mt_internalCommands - struct for the builtins
 * @ mt_internalCommand: the name of the builtin
 * @fn: the associated function to be called for each builtin
 */
typedef struct mt_internalCommands
{
	char *mt_internalCommand;
	int (*fn)(mt_code_info *_info);
}  mt_internalCommands;


/**************String helpers function ***************/
int _strlen(char *str); /* function to count the length of the string */
char *_strclone(char *str); /* function to duplicate the string */
int _strcomp(char *str1, char *str2, int x); /* function compare string*/
char *_strlink(char *str1, char *str2); /* function to concatenate strings */
void _revstr(char *str); /* function to reverse the strings */



/****************Functions that handle memory operations****************/
void deallocate_data_space(mt_code_info *info);
void deallocate_pointer_elements(char **array);
void deallocate_repeated_data(mt_code_info *info);


/****************Functions that handle Alias operations*****************/
int mt_manageAlias(mt_code_info *info, char *alias_name);
char *mt_findAlias(mt_code_info *info, char *alias_name);
int mt_positionAlias(char *mtalias_str, mt_code_info *info);


/****************Getline function**********************************/
int _accessline(mt_code_info *info);
int inspect_logical_con(char *handle_array_inputs[], int m, char     handle_array_operators[]);


/*******************Handles shell environment**************************/
char *obtain_environment_secret(char *secret, mt_code_info *info);
void display_environment(mt_code_info *info);
int clear_environment_secret(char *secret, mt_code_info *info);
int config_environment_secret(char *secret, char *element, mt_code_info *info);


/********************matches shell's command with the function****************/
int handle_shell_list(mt_code_info *info);

/*********************Handles the exit command**************************/
int handle_shell_exit(mt_code_info *info);
int handle_shell_help(mt_code_info *info);
int handle_shell_cd(mt_code_info *info);
int handle_shell_alias(mt_code_info *info);

/*********************Positions the working directory************************/
int define_curr_dir(mt_code_info *info, char *createdDir);


int _display(char *content);
int _displayerror(char *content);
int showError(int errorcode, mt_code_info *info);

int mt_execute_action(mt_code_info *info);


int handle_shell_env(mt_code_info *info);
int set_env_var(mt_code_info *info);
int unset_env_var(mt_code_info *info);


void integerToString(long numeral, char *content, int bottom);
int eval_chars(char *content, char *code);
int _atoi(char *z);


char *_strsplit(char *phrase, char *divider);

void segment(mt_code_info *info);

int validate_file(char *absolute_file_path);
int locate_prog(mt_code_info *info);
char **breakdownPath(mt_code_info *info);


void resolve_vars(mt_code_info *data);
int append_to_buffer(char *cache, char *joinStrings);
void mt_resolveAlias(mt_code_info *info);


void persevere(char *userQuery, mt_code_info *info);
void load_data(mt_code_info *info, int argc, char *argv[], char **env);
void terminate_gracefully(int opr IGNORED_PARAM);




#endif
