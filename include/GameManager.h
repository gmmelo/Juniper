#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Window.h"

class GameManager {
public:
	GameManager(const Window &mainWindow, int scene = 0);
private:
	int scene;
	Window mainWindow;
};

#endif