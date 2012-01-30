#include "Vector2D.h"

#include <cmath>
#include <sstream>

namespace vector {

Vector2D::Vector2D(double x, double y):
    m_x(x),
    m_y(y) {
}

Vector2D::~Vector2D() {
}

const Vector2D Vector2D::carth(double x, double y) {
    return Vector2D(x, y);
}

const Vector2D Vector2D::polar(double length, double angle) {
    return Vector2D(length * cos(angle), length * sin(angle));
}

double Vector2D::x() const {
    return m_x;
}

double Vector2D::y() const {
    return m_y;
}

double Vector2D::length() const {
    return sqrt(m_x * m_x + m_y * m_y);
}

double Vector2D::angle() const {
    return atan2(m_y, m_x);
}

const Vector2D Vector2D::operator+(const Vector2D & that) const {
    return Vector2D(this->m_x + that.m_x, this->m_y + that.m_y);
}

const Vector2D Vector2D::operator-() const {
    return Vector2D(-m_x, -m_y);
}

const Vector2D Vector2D::operator-(const Vector2D & that) const {
    return -that + *this;
}

const Vector2D Vector2D::unit() const {
    return Vector2D(m_x / length(), m_y / length());
}

Vector2D & Vector2D::operator+=(const Vector2D & that) {
    this->m_x += that.m_x;
    this->m_y += that.m_y;

    return *this;
}

Vector2D & Vector2D::operator-=(const Vector2D & that) {
    this->m_x -= that.m_x;
    this->m_y -= that.m_y;

    return *this;
}

const Vector2D operator*(const Vector2D & v, double d) {
    return Vector2D(v.m_x * d, v.m_y * d);
}

const Vector2D operator*(double d, const Vector2D & v) {
    return v * d;
}

const Vector2D Vector2D::rotate(double theta) const {
    return polar(length(), angle() + theta);
}

std::string Vector2D::toString() const {
    std::ostringstream out;

    out << "[" << m_x << ", " << m_y << "] (" << length() << " @ " << angle() << ")";

    return out.str();
}

} // namespace vector
