#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>


class Window {
public:
	struct Size {
		int width;
		int height;
	};

	Window(int width, int height, const char* title = "Juniper Game");

	// Simple getters
	Size getSize() const;
	const char* getTitle() const;

	// Rendering (happens inside the window)
	void draw(int x, int y) const;
	void update() const;
	
	// State handling
	bool checkQuit() const;
	void create();
	void close() const;
	~Window();

private:
	Size size;
	const char* title;
	SDL_Window* screen;
	SDL_Renderer* renderer;
};

#endif