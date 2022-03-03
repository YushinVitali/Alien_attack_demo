/// @file interface_object.hpp
/// @brief Description of the base interface object.
#pragma once

#ifndef __INTERFACE_OBJECT_HPP__
#define __INTERFACE_OBJECT_HPP__


#include <game_objects/game_object.hpp>

namespace Engine {

namespace Interface {

/// @brief Base interface object
class InterfaceObject : public GameObject {
public:
	virtual ~InterfaceObject() override = default;

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	virtual void Load(const LoaderParams& params) override;

	virtual void Collision() override;

	virtual std::string Type() const override;

protected:
	InterfaceObject();
}; // class InterfaceObject

} // namespace Interface

} // namespace Engine


#endif // !defined(__INTERFACE_OBJECT_HPP__)
