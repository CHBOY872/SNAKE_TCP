List.o: List/List.cpp List/List.hpp
Snake.o: Snake/Snake.cpp Snake/../GameHandler/GameHandler.hpp \
 Snake/../GameHandler/../Snake/Snake.hpp \
 Snake/../GameHandler/../Snake/../Field/Field.hpp \
 Snake/../GameHandler/../Snake/../Food/Food.hpp \
 Snake/../GameHandler/../Snake/../Food/../MoveAndPosition/MoveAndPosition.hpp \
 Snake/../GameHandler/../Snake/../Food/../MoveAndPosition/../Point/Point.hpp \
 Snake/../GameHandler/../Snake/../MoveAndPosition/MoveAndPosition.hpp \
 Snake/../GameHandler/../List/List.hpp \
 Snake/../GameHandler/../Food/Food.hpp Snake/Snake.hpp
Field.o: Field/Field.cpp Field/Field.hpp
Server.o: Server/Server.cpp Server/Server.hpp Server/../Snake/Snake.hpp \
 Server/../Snake/../Field/Field.hpp Server/../Snake/../Food/Food.hpp \
 Server/../Snake/../Food/../MoveAndPosition/MoveAndPosition.hpp \
 Server/../Snake/../Food/../MoveAndPosition/../Point/Point.hpp \
 Server/../Snake/../MoveAndPosition/MoveAndPosition.hpp \
 Server/../List/List.hpp Server/../Field/Field.hpp \
 Server/../Food/Food.hpp Server/../GameHandler/GameHandler.hpp \
 Server/../GameHandler/../Snake/Snake.hpp \
 Server/../GameHandler/../List/List.hpp \
 Server/../GameHandler/../Food/Food.hpp
GameHandler.o: GameHandler/GameHandler.cpp GameHandler/GameHandler.hpp \
 GameHandler/../Snake/Snake.hpp GameHandler/../Snake/../Field/Field.hpp \
 GameHandler/../Snake/../Food/Food.hpp \
 GameHandler/../Snake/../Food/../MoveAndPosition/MoveAndPosition.hpp \
 GameHandler/../Snake/../Food/../MoveAndPosition/../Point/Point.hpp \
 GameHandler/../Snake/../MoveAndPosition/MoveAndPosition.hpp \
 GameHandler/../List/List.hpp GameHandler/../Food/Food.hpp
MoveAndPosition.o: MoveAndPosition/MoveAndPosition.cpp \
 MoveAndPosition/MoveAndPosition.hpp MoveAndPosition/../Point/Point.hpp
GameInit.o: GameInit/GameInit.cpp GameInit/../Point/Point.hpp \
 GameInit/../Field/Field.hpp GameInit/../Snake/Snake.hpp \
 GameInit/../Snake/../Field/Field.hpp GameInit/../Snake/../Food/Food.hpp \
 GameInit/../Snake/../Food/../MoveAndPosition/MoveAndPosition.hpp \
 GameInit/../Snake/../Food/../MoveAndPosition/../Point/Point.hpp \
 GameInit/../Snake/../MoveAndPosition/MoveAndPosition.hpp \
 GameInit/../GameHandler/GameHandler.hpp \
 GameInit/../GameHandler/../Snake/Snake.hpp \
 GameInit/../GameHandler/../List/List.hpp \
 GameInit/../GameHandler/../Food/Food.hpp GameInit/../Server/Server.hpp \
 GameInit/../Server/../Snake/Snake.hpp \
 GameInit/../Server/../List/List.hpp \
 GameInit/../Server/../Field/Field.hpp \
 GameInit/../Server/../Food/Food.hpp \
 GameInit/../Server/../GameHandler/GameHandler.hpp GameInit/GameInit.hpp
Point.o: Point/Point.cpp Point/Point.hpp
Food.o: Food/Food.cpp Food/Food.hpp \
 Food/../MoveAndPosition/MoveAndPosition.hpp \
 Food/../MoveAndPosition/../Point/Point.hpp Food/../List/List.hpp
