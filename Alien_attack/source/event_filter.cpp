/// @file event_filter.cpp
/// @brief Implementation of the event filtering system

#include <event_filter.hpp>

#include <game.hpp>
#include <common/common.hpp>


namespace Engine {

int SDLCALL EventFilter::WindowResized(void* window, SDL_Event* event) {
	if(SDL_WINDOWEVENT == event->type &&
			SDL_WINDOWEVENT_RESIZED == event->window.event) {
		ChangeWindowSizeValue(window);
	}

	return 0;
}


void EventFilter::ChangeWindowSizeValue(void* window) {
	RectangleSize windowSize;
	SDL_GetWindowSize(static_cast<SDL_Window*>(window),
					  &windowSize.width,
					  &windowSize.height);
	Game::Instance()->SetWindowSize(windowSize);
}

} // namespace Engine
