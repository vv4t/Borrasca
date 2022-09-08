#include <iostream>

#include "game.hpp"

int main(int argc, char* argv[]) {
	game g;
	g.init();
	g.init_game();
	
	g.clean();
	
	return 0;
}
