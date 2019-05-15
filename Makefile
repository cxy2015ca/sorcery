CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -g -MMD -I/usr/X11R6/include/
EXEC = sorcery
OBJECTS = main.o enchantment/enchantment.o enchantment/enrage.o enchantment/giantstrength.o enchantment/haste.o enchantment/magicfatigue.o enchantment/silence.o abstractminion.o card.o display.o ascii_graphics.o match.o minion.o player.o ritual.o spells.o triggerspell.o graphics.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L/usr/X11R6/lib -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
