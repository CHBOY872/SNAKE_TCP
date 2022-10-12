#include "GameInit/GameInit.hpp"

int main(int argc, const char **argv)
{
	GameInit *init = new GameInit(argc, argv);
    return init->Start();
}
