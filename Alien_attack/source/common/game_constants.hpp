/// @file game_constants.hpp
/// @brief Description of the basic default constants.
#pragma once

#ifndef __GAME_CONSTANTS_HPP__
#define __GAME_CONSTANTS_HPP__


#include <cstdint>


namespace Engine {

constexpr auto DEFAULT_LOGFILE{ "./everything.log" };

constexpr auto    DEFAULT_WINDOW_NAME{ "Alien Attack" };
constexpr int32_t DEFAULT_WINDOW_POSITION_X{ 100 };
constexpr int32_t DEFAULT_WINDOW_POSITION_Y{ 100 };
constexpr int32_t DEFAULT_WINDOW_WIDTH{ 640 };
constexpr int32_t DEFAULT_WINDOW_HEIGHT{ 480 };

constexpr uint32_t FPS{ 60 };
constexpr uint32_t DELAY_TIME{ static_cast<int32_t>(1000.0f / FPS) };

constexpr auto DEFAULT_SCROLL_SPEED{ 1 };
constexpr auto DEFAULT_LEVEL{ 0 };
constexpr auto DEFAULT_LIVES{ 5 };

} // namespace Engine


#endif // !defined(__GAME_CONSTANTS_HPP___
