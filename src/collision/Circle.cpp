#include "Circle.h"

using vector::Vector2D;

namespace collision {

	Circle::Circle(const Vector2D & center, double radius):
		m_center(center),
		m_radius(radius) {
	}

	Circle::~Circle() {}

	const Vector2D Circle::center() const {
		return m_center;
	}

	double Circle::radius() const {
		return m_radius;
	}

	bool Circle::overlaps(const Circle & that) const {
		return (this->m_center - that.m_center).length() < this->m_radius + that.m_radius;
	}

	 void Circle::move(const Vector2D & offset) {
		m_center += offset;
	 }

}; // namespace collision
