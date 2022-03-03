/// @file enemy.cpp
/// @brief Implementation of the base actor of the enemy.
#include <game_objects/actor/enemy.hpp>

#include <logger.hpp>


namespace Engine {

namespace Actor {

Enemy::Enemy()
	: ShooterObject() {}


void Enemy::Draw() {
	ShooterObject::Draw();
}


void Enemy::Update() {
	ShooterObject::Update();
}


void Enemy::Clean() {
	ShooterObject::Clean();
}


void Enemy::Load(const LoaderParams &params) {
	ShooterObject::Load(params);
}


std::string Enemy::Type() const {
	return "Enemy";
}

} // namespace Actor

} // namespace Engine
