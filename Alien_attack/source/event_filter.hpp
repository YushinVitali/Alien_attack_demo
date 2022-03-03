/// @file event_filter.hpp
/// @brief Description of the event filtering system.
#pragma once

#ifndef __EVENT_FILTER_HPP__
#define __EVENT_FILTER_HPP__


#include <SDL.h>


namespace Engine {

/// @brief Event filtering system.
class EventFilter {
public:
	static int SDLCALL WindowResized(void* window, SDL_Event* event);

private:
	EventFilter() = delete;

	static void ChangeWindowSizeValue(void* window);
}; // class EventFilter

} // namespace Engine


#endif // !defined(__EVENT_FILTER_HPP__)
