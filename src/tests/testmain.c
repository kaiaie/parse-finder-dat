#include <stdlib.h>
#include <tap.h>
#include "../lib/parser.h"

int
main (int argc, char *argv[])
{
	plan_no_plan();
	ok(parse(".") == 0, "Can parse current directory");
	exit(EXIT_SUCCESS);
}

