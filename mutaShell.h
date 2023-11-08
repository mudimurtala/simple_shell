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


#endif
