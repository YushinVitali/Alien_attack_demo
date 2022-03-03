/// @file actor_object.hpp
/// @brief Description of the base actor.
#pragma once

#ifndef __ACTOR_OBJECT_HPP__
#define __ACTOR_OBJECT_HPP__


#include <game_objects/game_object.hpp>


namespace Engine {

namespace Actor {

/// @brief Base actor.
class ActorObject : public GameObject {
public:
	virtual ~ActorObject() override = default;

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	virtual void Load(const LoaderParams& params) override;

	virtual void Collision() override;

	virtual std::string Type() const override;

protected:
	ActorObject();
}; // class ActorObject

} // namespace Actor

} // namespace Engine


#endif // !defined(__ACTOR_OBJECT_HPP__)
