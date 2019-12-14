#include "vector2d.h"
#include <cmath>
#include <ostream>

vector2d vector2d::operator+(vector2d v2)
{
	return vector2d(this->x + v2.x, this->y + v2.y);
}
vector2d vector2d::operator-(vector2d v2)
{
	return vector2d(this->x - v2.x, this->y - v2.y);
}
vector2d vector2d::operator*(vector2d v2)
{
	return vector2d(this->x * v2.x, this->y * v2.y);
}
vector2d vector2d::operator*(float_t coef)
{
	return vector2d(this->x * coef, this->y * coef);
}
bool vector2d::operator==(const vector2d v2) const
{
	return (this->x == v2.x) && (this->y == v2.y);
}
vector2d vector2d::operator/(vector2d v2)
{
	return vector2d(this->x / v2.x, this->y / v2.y);
}
vector2d vector2d::operator/(float_t devideBy)
{
	return vector2d(this->x / devideBy, this->y / devideBy);
}
bool vector2d::operator<(vector2d v2)
{
	return this->x < v2.x && this->y < v2.y;
}
float_t vector2d::magnitude() const
{
	return sqrt(pow(x, 2) + pow(y, 2));
}
float_t vector2d::distance(const vector2d& vec2d) const
{
	return sqrt(pow(vec2d.x - x, 2) + pow(vec2d.y - y, 2));
}
vector2d vector2d::normalizedVec()
{
	return *this / magnitude();
}
void vector2d::makeNormalized()
{
	*this = *this / magnitude();
}
vector2d::vector2d() : x{ 0 }, y{ 0 } {}
vector2d::vector2d(float_t _x, float_t _y) : x{ _x }, y{ _y } {}

bool operator<(const vector2d& v1, const vector2d& v2)
{
	return v1.x < v2.x && v1.y < v2.y;
}
vector2d operator*(const float_t coef, vector2d v)
{
	return vector2d(v.x * coef, v.y * coef);
}

std::ostream& operator<<(std::ostream& os, const vector2d& v)
{
	os << "(" << v.x << ";" << v.y << ")";
	return os;
}