/// @file player.cpp
/// @brief Implementation of the player actor.
#include <game_objects/actor/player.hpp>

#include <logger.hpp>

#include <game.hpp>

#include <controllers/input_handler.hpp>
#include <texture_manager.hpp>

#include <game_objects/actor/bullet_handler.hpp>

#include <sound/sound_manager.hpp>


namespace Engine {

namespace Actor {

Player::Player()
	: ShooterObject() {}


void Player::Draw() {
	const SDL_RendererFlip flip{
		(0 > m_velocity.GetX()) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL
	};

	TextureManager::Instance()->DrawFrame(m_textureId,
										  static_cast<int32_t>(m_position.GetX()),
										  static_cast<int32_t>(m_position.GetY()),
										  m_width, m_height,
										  m_currentRow, m_currentFrame,
										  Game::Instance()->GetRenderer(),
										  m_angle, m_alpha, flip);
}


void Player::Update() {
	if(Game::Instance()->IsLevelComplete()) {
		if(Game::Instance()->GetWindowSize().width <= m_position.GetX()) {
			Game::Instance()->SetCurrentLevel(Game::Instance()->GetCurrentLevel() + 1);
		} else {
			m_velocity.SetX(3);
			m_velocity.SetY(0);

			ShooterObject::Update();

			HandleAnimation();
		}
	} else {
		if(0 > m_position.GetX()) {
			m_position.SetX(0);
		}
		if(0 > m_position.GetY()) {
			m_position.SetY(0);
		}

		if(!m_isDying) {
			m_velocity.SetX(0);
			m_velocity.SetY(0);

			HandleInput();

			if(Game::Instance()->GetWindowSize().width - 10 <= m_position.GetX() + m_width &&
					0 < m_velocity.GetX()) {
				m_velocity.SetX(0);
			}

			ShooterObject::Update();

			HandleAnimation();
		} else {
			m_currentFrame = static_cast<int32_t>((SDL_GetTicks() / 100) % m_frameCount);
			if(m_dyingCounter == m_dyingTime) {
				Ressurect();
			}
			++m_dyingCounter;
		}
	}
}


void Player::Clean() {
	loutd("Clean player...");
}


void Player::Load(const LoaderParams &params) {
	ShooterObject::Load(params);

	m_bulletFiringSpeed = 13;
	m_moveSpeed = 3;

	m_bulletCounter = m_bulletFiringSpeed;

	m_dyingTime = 100;
}


void Player::Collision() {
	if(m_invulnerable || Game::Instance()->IsLevelComplete()) {
		return;
	}

	m_textureId = "large_explosion";
	m_currentFrame = 0;
	m_frameCount = 9;
	m_width = 60;
	m_height = 60;
	m_isDying = true;
}


std::string Player::Type() const {
	return "Player";
}


void Player::Scroll(float scrollSpeed) {
	return;
}


void Player::HandleInput() {
	OnKeyboard();

	OnJoystick();
}


void Player::HandleAnimation() {
	if(m_invulnerable) {
		HandleDyingAnimation();
	}

	if(!m_isDead) {
		HandleMovingAnimation();
	}
}


void Player::HandleDyingAnimation() {
	if(m_invulnerableCounter != m_invulnerableTime) {
		m_alpha = (m_alpha == 255) ? 0 : 255;
	} else {
		m_invulnerable = false;
		m_invulnerableCounter = 0;
		m_alpha = 255;
	}
	++m_invulnerableCounter;
}


void Player::HandleMovingAnimation() {
	if(m_velocity.GetX() < 0) {
		m_angle = -10.0;
	} else if(m_velocity.GetX() > 0) {
		m_angle = 10.0;
	} else {
		m_angle = 0.0;
	}

	m_currentFrame = static_cast<int32_t>((SDL_GetTicks() / 100) % m_frameCount);
}


void Player::Ressurect() {
	Game::Instance()->SetPlayerLives(Game::Instance()->GetPlayerLives() - 1);

	m_position.SetX(10);
	m_position.SetY(200);

	m_isDying = false;

	m_textureId = "player";

	m_currentFrame = 0;
	m_frameCount = 5;

	m_width = 128;
	m_height = 55;

	m_dyingCounter = 0;
	m_invulnerable = true;
}


void Player::OnKeyboard() {
	if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT) ) {
		m_velocity.SetX(m_baseVelocity * -1);
	}
	if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT) ) {
		m_velocity.SetX(m_baseVelocity);
	}

	if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN) ) {
		m_velocity.SetY(m_baseVelocity);
	}
	if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP) ) {
		m_velocity.SetY(m_baseVelocity * -1);
	}

	if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_SPACE) ) {
		if(!m_isDying && m_bulletCounter >= m_bulletFiringSpeed) {
			SoundManager::Instance()->PlaySound("shoot", 0);
			BulletHandler::Instance()->AddPlayerBullet(
				m_position.GetX() + m_width, m_position.GetY() + m_height / 2,
				11, 11, "bullet1", 1, { 10, 0 });
			m_bulletCounter = 0;
		}
	} else {
		m_bulletCounter += 100;
	}
}


void Player::OnJoystick() {
	if(!InputHandler::Instance()->IsJoysticksInitialised()) {
		return;
	}

	const int32_t leftStickXValue{
		InputHandler::Instance()->GetAxisValue(m_joystickNumber,
											   SDL_CONTROLLER_AXIS_LEFTX) };
	if(0 != leftStickXValue) {
		m_velocity.SetX(1 * leftStickXValue);
	}

	const int32_t leftStickYValue{
		InputHandler::Instance()->GetAxisValue(m_joystickNumber,
											   SDL_CONTROLLER_AXIS_LEFTY) };
	if(0 != leftStickYValue) {
		m_velocity.SetX(1 * leftStickYValue);
	}
}

} // namespace Actor

} // namespace Engine
