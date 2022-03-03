/// @file bullet.cpp
/// @brief Implementation of the bullet actor.
#include <game_objects/actor/bullet.hpp>


namespace Engine {

namespace Actor {

PlayerBullet::PlayerBullet()
		: ShooterObject() {
	m_dyingTime = 5;
}


void PlayerBullet::Update() {
	if(!m_isDying) {
		m_velocity.SetX(m_heading.GetX());
		m_velocity.SetY(m_heading.GetY());

		ShooterObject::Update();
	} else {
		m_velocity.SetX(0);
		m_velocity.SetY(0);
		DoDyingAnimation();
	}
}


void PlayerBullet::Draw() {
	ShooterObject::Draw();
}


void PlayerBullet::Clean() {
	ShooterObject::Clean();
}


void PlayerBullet::Load(const LoaderParams& params, Vector2D heading) {
	ShooterObject::Load(params);
	m_heading = heading;
}


void PlayerBullet::Collision() {
	m_textureId = "smallexplosion";
	m_currentFrame = 0;
	m_frameCount = 2;
	m_width = 20;
	m_height = 20;
	m_isDying = true;
}


std::string PlayerBullet::Type() const {
	return "PlayerBullet";
}


EnemyBullet::EnemyBullet()
	: PlayerBullet() {}


std::string EnemyBullet::Type() const {
	return "EnemyBullet";
}

} // namespace Actor

} // namespace Engine
