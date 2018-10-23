#include <stdio.h>
#include <stdlib.h>
#include "../lib/parser.h"

#define QUOTE(str) #str
#define EXPAND_AND_QUOTE(str) QUOTE(str)

__attribute__ ((unused))
static const  char* version = EXPAND_AND_QUOTE(PROJECT_VERSION);

void show_usage();
	
int
main(int argc, char *argv[])
{
	__attribute__ ((unused))
	char *default_dir = ".";

	exit(EXIT_SUCCESS);
}

