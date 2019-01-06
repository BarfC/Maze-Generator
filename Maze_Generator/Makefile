LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS = -g

maze: cell.o main.o maze.o ResourcePath.o player.o
	g++ -g -o maze $+ $(LIBS)

run: maze
	./maze

# these are created by: g++ -MM *.cpp
cell.o: cell.cpp ResourcePath.hpp cell.hpp
main.o: main.cpp maze.hpp cell.hpp ResourcePath.hpp player.hpp
maze.o: maze.cpp maze.hpp cell.hpp ResourcePath.hpp
player.o: player.hpp player.cpp maze.hpp

ResourcePath.o: ResourcePath.cpp ResourcePath.hpp
