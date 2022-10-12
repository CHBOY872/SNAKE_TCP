#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "../Point/Point.hpp"
#include "../Field/Field.hpp"
#include "../Snake/Snake.hpp"
#include "../GameHandler/GameHandler.hpp"
#include "../Server/Server.hpp"
#include "GameInit.hpp"

#define HELP_INFO \
"Usage: ./main [args values]...\n" \
"ARGUMENTS: \n" \
"-w    -> set field width\n" \
"-h    -> set field height\n" \
"-f    -> set number of food\n" \
"-p    -> set server port. the standard port is 8808\n" \
"-i    -> set server ip. the standard ip sets by OS\n" \
"-help -> print help documentation\n" \

const char *args[] = {
						"-w",		// width
						"-h",		// height
						"-f",		// food count
						"-p",		// port
						"-i",		// ip
						"-help"		// help
					 };

int GameInit::Start()
{
	if (argc > max_argc)
	{
		printf("to many arguments...\n");
		return 1;
	}

	int num_args[] = { std_width, std_height, std_food_count, std_port };
	const char *ip = 0;
	int matched_argv_idx = 0;

	int i;
	for (i = 1; i < argc; i+=2)
	{
		if (IsOneOfArgv(args, argv[i], 6, &matched_argv_idx))
		{
			if (HandleArgv(i, matched_argv_idx, num_args, &ip))
				return 0;
		}
	}	
	
    srand(time(0));
    Field fld(num_args[0], num_args[1]);
    List<Food> fod;
    List<Snake> snakes;
    GameHandlerGemstone handler(&fld, &fod, &snakes);
    EventSelector *sel = new EventSelector;
    Server *serv = Server::Start(sel, &fld, &handler, num_args[2], num_args[3], ip);
    if (!serv)
    {
        perror("server");
        return 1;
    }
	printf("width      -> %d\n"
		   "height     -> %d\n"
		   "food count -> %d\n", num_args[0], num_args[1], num_args[2]);
    sel->Run();
	return 0;
}

bool GameInit::IsOneOfArgv(const char *argv[6], const char *arg, 
						   int argc, int *matched_argv_idx)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], arg))
		{
			*matched_argv_idx = i;
			return true;
		}
	}
	return false;
}

bool GameInit::HandleArgv(int argv_idx, int matched_argv, 
						  int *num_args, const char **ip)
{
	if (matched_argv < 4)
	{
		num_args[matched_argv] = atoi(argv[argv_idx + 1]);
		if (!num_args[matched_argv])
		{	
			printf("Invalid argument. Write -help for more information.\n");
			exit(2);
		}
		return false;
	}	
	if (matched_argv == 4)
	{
		*ip = argv[argv_idx + 1];
		return false;
	}
	if (matched_argv == 5)
		WriteHelp();
	return true;
}

void GameInit::WriteHelp()
{
	printf(HELP_INFO);
}
