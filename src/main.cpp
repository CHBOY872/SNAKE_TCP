#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Point/Point.hpp"
#include "Field/Field.hpp"
#include "Snake/Snake.hpp"
#include "GameHandler/GameHandler.hpp"
#include "Server/Server.hpp"

static int port = 8808;

enum {
    std_width = 100,
    std_height = 40,
    std_food_count = 15
};

int main()
{
    srand(time(0));
    Field fld(std_width, std_height);
    List<Food> fod;
    List<Snake> snakes;
    GameHandlerGemstone handler(&fld, &fod, &snakes);
    EventSelector *sel = new EventSelector;
    Server *serv = Server::Start(port, sel, &fld, &handler, std_food_count);
    if (!serv)
    {
        perror("server");
        return 1;
    }
    sel->Run();
    return 0;
}
