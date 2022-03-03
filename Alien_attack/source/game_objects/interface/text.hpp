/// @file text.hpp
/// @brief Description of the text object.
#pragma once

#ifndef __TEXT_HPP__
#define __TEXT_HPP__


#include <loader_params.hpp>

#include <game_objects/game_object_factory.hpp>
#include <game_objects/interface/interface_object.hpp>


namespace Engine {

namespace Interface {

/// @brief Text object.
class Text : public InterfaceObject {
public:
	Text();
	~Text() override = default;

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	virtual void Load(const Engine::LoaderParams& params) override;

	virtual std::string Type() const override;
}; // class Text


class TextCreator : public Engine::BaseCreator {
	virtual Engine::GameObject* CreateGameObject() const override {
		return new Text();
	}
};

} // namespace Interface

} // namespace Engine


#endif // !defined(__TEXT_HPP__)
