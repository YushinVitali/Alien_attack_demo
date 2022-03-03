/// @file layer.hpp
/// @brief Description of the base layer.
#pragma once

#ifndef __LAYER_HPP__
#define __LAYER_HPP__


namespace Engine {

class Level;

/// @brief Base layer.
class Layer {
public:
	Layer() = default;
	virtual ~Layer() = default;

	virtual void Update(Level* level) = 0;
	virtual void Render() = 0;
}; // class Layer

} // namespace Engine


#endif // !defined(__LAYER_HPP__)
