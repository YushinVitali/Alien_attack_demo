/// @file vector_2d.hpp
/// @brief Description of 2d vector.
#pragma once

#ifndef __VECTOR_2D_HPP__
#define __VECTOR_2D_HPP__


#include <math.h>
#include <cstdint>


namespace Engine {

/// @brief Vector in two dimensions.
class Vector2D {
public:
	Vector2D() : m_x{ 0.0f }, m_y{ 0.0f } {};
	Vector2D(float x, float y)
		: m_x{ x }, m_y{ y } {}
	Vector2D(int32_t x, int32_t y)
		: m_x(static_cast<float>(x)),
		  m_y(static_cast<float>(y)) {}

	/// @brief Get the length of the vector.
	/// @details sqrt(x^2 + y^2).
	float Length() const;

	/// @brief Vector normalization.
	/// @details vector * 1 / length.
	void Normalize();

	Vector2D operator+(const Vector2D& v2) const;
	friend Vector2D& operator+=(Vector2D& v1, Vector2D& v2);

	Vector2D operator-(const Vector2D& v2) const;
	friend Vector2D& operator-=(Vector2D& v1, Vector2D& v2);

	Vector2D operator*(float scalar) const;
	Vector2D& operator*=(float scalar);

	Vector2D operator/(float scalar) const;
	Vector2D& operator/=(float scalar);

public:
	float GetX() const noexcept;
	float GetY() const noexcept;

	void SetX(float x);
	void SetY(float y);

private:
	float m_x;
	float m_y;
}; // class Vector2D

} // namespace Engine


#endif // !defined(__VECTOR_2D_HPP__)
