/// @file button.hpp
/// @brief Description of the interface button.
#pragma once

#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__


#include <loader_params.hpp>

#include <game_objects/game_object_factory.hpp>
#include <game_objects/interface/interface_object.hpp>


namespace Engine {

namespace Interface {

/// @brief Interface button.
class Button : public InterfaceObject {
public:
	Button();
	virtual ~Button() override = default;

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	virtual void Load(const Engine::LoaderParams& params) override;

	virtual std::string Type() const override;
public:
	void SetCallback(void (*callback)());
	int32_t GetCallbackId();

private:
	void (*m_OnClick)();

	int32_t m_callbackId;

	bool m_isReleased{ false };
}; // class Button


class ButtonCreator : public Engine::BaseCreator {
	virtual Engine::GameObject* CreateGameObject() const override {
		return new Button();
	}
};

} // namespace Interface

} // namespace Engine


#endif // !defined(__BUTTON_HPP__)
