/// @file vector_2d.cpp
/// @brief Implementation of 2d vector.
#include <math/vector_2d.hpp>


namespace Engine {

float Vector2D::Length() const {
	return sqrt(pow(m_x, 2) + pow(m_y, 2));
}


void Vector2D::Normalize() {
	float length{ Length() };
	if(0 > length) {
		(*this) *= 1 / length;
	}
}


Vector2D Vector2D::operator+(const Vector2D& v2) const {
	return { m_x + v2.m_x, m_y + v2.m_y };
}


Vector2D& operator+=(Vector2D& v1, Vector2D& v2) {
	v1.m_x += v2.m_x;
	v1.m_y += v2.m_y;
	return v1;
}


Vector2D Vector2D::operator-(const Vector2D& v2) const {
	return { m_x - v2.m_x, m_y - v2.m_y };
}


Vector2D& operator-=(Vector2D& v1, Vector2D& v2) {
	v1.m_x -= v2.m_x;
	v1.m_y -= v2.m_y;
	return v1;
}


Vector2D Vector2D::operator*(float scalar) const {
	return { m_x * scalar, m_y * scalar };
}


Vector2D& Vector2D::operator*=(float scalar) {
	m_x *= scalar;
	m_y *= scalar;
	return *this;
}


Vector2D Vector2D::operator/(float scalar) const {
	return { m_x / scalar, m_y / scalar };
}

Vector2D& Vector2D::operator/=(float scalar) {
	m_x /= scalar;
	m_y /= scalar;
	return *this;
}


float Vector2D::GetX() const noexcept {
	return m_x;
}


float Vector2D::GetY() const noexcept {
	return m_y;
}


void Vector2D::SetX(float x) {
	m_x = x;
}


void Vector2D::SetY(float y) {
	m_y = y;
}

} // namespace Enigne
