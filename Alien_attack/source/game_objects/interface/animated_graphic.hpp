/// @file animated_graphic.hpp
/// @brief Description of the animated interface graphics.
#pragma once

#ifndef __ANIMATED_GRAPHIC_HPP__
#define __ANIMATED_GRAPHIC_HPP__


#include <loader_params.hpp>

#include <game_objects/game_object_factory.hpp>
#include <game_objects/interface/interface_object.hpp>


namespace Engine {

namespace Interface {

/// @brief Animated interface graphics.
class AnimatedGraphic : public InterfaceObject {
public:
	AnimatedGraphic();
	~AnimatedGraphic() override = default;

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	virtual void Load(const Engine::LoaderParams& params) override;

	virtual std::string Type() const override;

private:
	int32_t m_animSpeed;
}; // class AnimatedGraphic


class AnimatedGraphicCreator : public Engine::BaseCreator {
	virtual Engine::GameObject* CreateGameObject() const override {
		return new AnimatedGraphic();
	}
};

} // namespace Interface

} // namespace Engine


#endif // !defined(__ANIMATED_GRAPHIC_HPP__)
