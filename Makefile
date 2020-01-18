CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -MMD -I/SFML-2.5.1/include
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}
LDFLAGS = -L/SFML-2.5.1/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDES = -I/SFML-2.5.1/include
OBJS = main.o game.o grid.o cell.o states.o
DEPENDS = ${OBJS:.o=.d}
EXEC = a.out

.PHONY : clean

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} $^ -o $@ ${LDFLAGS} ${LDLIBS}

${OBJS} : ${MAKEFILE_NAME}

-include ${DEPENDS}

clean:
	${RM} ${EXEC} ${OBJS} ${DEPENDS}
