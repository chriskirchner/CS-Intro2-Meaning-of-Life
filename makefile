CXX = g++
CXXFLAGS = -std=c++0x -Wall -pedantic-errors -g
SRCS = Main.cpp Rooms.cpp Display.cpp Things.cpp Map.cpp
OBJS = Main.o Rooms.o Display.o Things.o Map.o
HEADERS = Rooms.hpp Display.hpp Things.hpp Map.hpp

mol: ${OBJS} ${HEADERS}
	${CXX} ${SRCS} ${HEADERS} -o mol

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} ${SRCS} -c ${@:.o=.cpp}

clean:
	rm -f *.o *~ mol
