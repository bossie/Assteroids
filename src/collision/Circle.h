#include "../vector/Vector2D.h"

namespace collision {

class Circle {
 public:
	Circle(const vector::Vector2D & center, double radius);
	virtual ~Circle();

	virtual const vector::Vector2D center() const;
	virtual double radius() const;
	virtual bool overlaps(const Circle & that) const;

	virtual void move(const vector::Vector2D & offset);

 private:
	vector::Vector2D m_center;
	double m_radius;
};

} // namespace collision
