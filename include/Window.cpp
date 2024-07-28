#include "Window.h"
#include <iostream>

Window::Window(int width, int height, const char* title) : title(title) {
	size.width = width;
	size.height = height;
}

Window::Size Window::getSize() const {
	return size;
}

const char* Window::getTitle() const {
	return title;
}

void Window::create() {
	// Check for SDL video support
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL couldn't initiate video:" << std::endl << SDL_GetError() << std::endl;
		return;
	}
	// Try to create window, error if unable
	screen = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.width, size.height, 0);
	if (!screen) {
		std::cerr << "Could not create window" << std::endl;
		return;
	}
	// Instantiate renderer, error if unable
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Could not create renderer" << std::endl;
		return;
	}

	std::cout << size.width << "x" << size.height << " window created successfully" << std::endl;
}

void Window::draw(int x, int y) const {
	// Error handling
	if (renderer == nullptr) {
		std::cerr << "Renderer not instantiated. Draw call failed." << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}

void Window::update() const {
	// Draw whatever is in the render queue
	SDL_RenderPresent(renderer);
	// Set window to erase last frame
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
}

bool Window::checkQuit() const {
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) {
		return true;
	}
	return false;
}

void Window::close() const {
	if (screen) {SDL_DestroyWindow(screen);} // Don't destroy if window wasn't created
	SDL_Quit();

	std::cout << "Closed " << size.width << "x" << size.height << " window" << std::endl;
}

Window::~Window() {
	close();
}