#include <system_error>

#include <SDL.h>

#include <game.hpp>
#include <logger.hpp>
#include <engine_error_code.hpp>

#include <common/game_constants.hpp>


int main(int argc, char* args[]) {
	Logger::Instance()->SetLogfile(Engine::DEFAULT_LOGFILE);

#ifdef BUILD_TYPE_RELEASE
	Logger::Instance()->SetMaxLogLevel(LOG_TYPE::INFO);
#else
	Logger::Instance()->SetMaxLogLevel(LOG_TYPE::MAX);
#endif

	const std::error_code errorCode{
		Engine::Game::Instance()->Initialization(Engine::DEFAULT_WINDOW_NAME,
												 Engine::DEFAULT_WINDOW_POSITION_X,
												 Engine::DEFAULT_WINDOW_POSITION_Y,
												 Engine::DEFAULT_WINDOW_WIDTH,
												 Engine::DEFAULT_WINDOW_HEIGHT,
												 false)
	};
	if(errorCode) {
		lout(LOG_TYPE::ERROR, "An error occurred while initializing the game engine!");
		return static_cast<int32_t>(errorCode.value());
	}

	uint32_t frameStart;
	uint32_t frameTime;

	while(Engine::Game::Instance()->IsRunning()) {
		frameStart = SDL_GetTicks();

		Engine::Game::Instance()->Update();
		Engine::Game::Instance()->Render();

		Engine::Game::Instance()->HandleEvents();

		frameTime = SDL_GetTicks() - frameStart;

		if(Engine::DELAY_TIME > frameTime) {
			SDL_Delay(static_cast<uint32_t>(Engine::DELAY_TIME - frameTime));
		}
	}

	Engine::Game::Instance()->Clean();
	return 0;
}

