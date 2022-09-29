#include <stdio.h>
#include "Point/Point.hpp"
#include "Field/Field.hpp"
#include "Snake/Snake.hpp"
#include "GameHandler/GameHandler.hpp"
#include "Server/Server.hpp"

static int port = 8808;

int main()
{
    Field fld(20, 20);
    List<Food> fod;
    List<Snake> snakes;
    GameHandlerGemstone handler(&fld, &fod, &snakes);
    EventSelector *sel = new EventSelector;
    Server *serv = Server::Start(port, sel, &fld, &handler);
    if (!serv)
    {
        perror("server");
        return 1;
    }
    sel->Run();
    return 0;
}
