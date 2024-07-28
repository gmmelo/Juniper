// Juniper.cpp : Defines the entry point for the application.
//

#include <cmath>
#include "Juniper.h"
#include "include/Window.h"
#include "include/GameManager.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Window size
	int width = 1600;
	int height = 900;

	// Starting game window and manager
	Window mainWindow(width, height);
	GameManager gameLoop(mainWindow);
	mainWindow.create();
	mainWindow.update(); // Clears window
	
	// Setting "etch-a-sketch" location in time (goes from 0 to 2pi for trigonometric reasons)
	double curT = 0;
	int curX, curY;

	// Setting anchor point for middle of screen
	int middleX = int(width / 2);
	int middleY = int(height / 2);

	// Loop parameters
	int pointCount = 1000;
	int fps = 60;
	double lineOffset = 0.1; // How much of the route will be avanced every second
	double lineLength = 0.5; // Range (0, 1)
	
	double pointOffset = 2 * M_PI * lineLength / pointCount; // Makes sure the point will fill a lineLength part of the screen
	lineOffset = lineOffset * 2 * M_PI; // How much the line will advance in curT units every second
	lineOffset = lineOffset / fps; // How much the line will advance in curT units every frame
	double lineRetreat = pointOffset * pointCount - lineOffset; // Calculates the total movement after a frame and subtracts the desired offset
	
	// Main loop - infinity sign rendering
	while (!mainWindow.checkQuit()) {
		for (int i = 0; i < 1000; ++i) {

			double sinX = sin(curT - M_PI / 2);
			double sinY = sin(2 * curT);

			curX = int(middleX + (sinX * middleX));
			curY = int(middleY + (sinY * middleY));

			mainWindow.draw(curX, curY);
			// std::cout << curX << ", " << curY << std::endl;

			curT += pointOffset;

			if (curT >= 2 * M_PI) {
				curT = 2 * M_PI - curT;
			}
		}
		SDL_Delay(1000.0 / fps); // ms delay to (nearly) achieve the target fps
		curT -= lineRetreat;
		mainWindow.update();
	}

	return 0;
}
