#pragma once
#include <iosfwd>

class vector2d
{
public:
	float_t x;
	float_t y;
	vector2d operator* (float_t coef);
	vector2d operator+ (vector2d v2);
	vector2d operator- (vector2d v2);
	vector2d operator* (vector2d v2);
	vector2d operator/ (vector2d v2);
	vector2d operator/ (float_t devideBy);
	bool operator< (vector2d v2);
	float_t magnitude() const;

	float_t distance(const vector2d& vec2d) const;
	vector2d normalizedVec();
	void makeNormalized();

	vector2d();
	vector2d(float_t _x, float_t _y);

	bool operator== (const vector2d v2) const;

	friend bool operator<(const vector2d& v1, const vector2d& v2);
	friend vector2d operator*(const float_t coef, vector2d v);
	friend std::ostream& operator<<(std::ostream& os, const vector2d& v);
};