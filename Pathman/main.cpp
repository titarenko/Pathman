#include "Game.h"
#include "InitializationException.h"
#include "NotImplementedException.h"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(lib, "irrKlang.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
	Game* game;

#ifndef DEBUG
	try {
#endif
		game = new Game("config.xml");
#ifndef DEBUG
	} catch (InitializationException) {
		return 1;
	} catch (NotImplementedException) {
		return -1;
	}
#endif

	while (game->update());

	delete game;

	return 0;
}