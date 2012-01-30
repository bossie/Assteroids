#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>

namespace vector {

class Vector2D {
    double m_x, m_y;

    Vector2D(double x, double y);

public:
    virtual ~Vector2D();

    static const Vector2D carth(double x = 0.0, double y = 0.0);
    static const Vector2D polar(double length = 0.0, double angle = 0.0);

    virtual double x() const;
    virtual double y() const;

    virtual double length() const;
    virtual double angle() const;

    virtual const Vector2D operator+(const Vector2D & that) const;
    virtual const Vector2D operator-(const Vector2D & that) const;
    virtual const Vector2D operator-() const;
    virtual const Vector2D unit() const;

    virtual Vector2D & operator+=(const Vector2D & that);
    virtual Vector2D & operator-=(const Vector2D & that);

    friend const Vector2D operator*(const Vector2D & v, double d);
    friend const Vector2D operator*(double d, const Vector2D & v);

    virtual const Vector2D rotate(double theta) const;

    virtual std::string toString() const;
};

const Vector2D operator*(const Vector2D & v, double d);
const Vector2D operator*(double d, const Vector2D & v);

} // namespace vector

#endif // VECTOR2D_H
