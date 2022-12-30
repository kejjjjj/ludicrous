
#include "pch.h"


float normalize(float& a, float& b, float& c, float& d)
{
	float length = sqrt(a * a + b * b + c * c + d * d);

	if (length) {
		float ilength = 1 / length;

		a *= ilength;
		b *= ilength;
		c *= ilength;
		d *= ilength;

	}
	return length;
}
bool PointIsWithinTriangle(const itris_t& tris, const vi2d& p)
{
	const auto TriangleArea = [](const vi2d& a, const vi2d& b, const vi2d& c) -> float {
		return abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y-b.y)) / 2.0);
	};
	const auto& a = tris.a, &b = tris.b, &c = tris.c;

	float a1 = TriangleArea(a, b, c);
	float a2 = TriangleArea(p, b, c);
	float a3 = TriangleArea(a, p, c);
	float a4 = TriangleArea(a, b, p);

	//normalize(a1, a2, a3, a4);

	auto center = (tris.a + tris.b + tris.c) / 3;

	offset += 30;
	engine->DrawString({ 100, 500 + offset }, std::format("{}, {}", a1, (a2 + a3 + a4)), olc::BLACK);

	return a1 == (a2 + a3 + a4);


}
//assumes ABC order from left to right on the screen
bool TriangleIntersection(const itris_t& a, const itris_t& b)
{



	//offset = 0;
	//return false;
	
	//left triangle is hugging right triangle if this is false
	int matches = 0;

	//hugging
	if (a.a == b.a && a.c == b.c)	return false;

	if (a.b == b.a && a.c == b.b)	return false;

	if (a.a == b.b && a.b == b.c)	return false;

	if (PointIsWithinTriangle(a, b.a) || PointIsWithinTriangle(a, b.b) || PointIsWithinTriangle(a, b.c) ||	//b intersects with a
		PointIsWithinTriangle(b, a.a) || PointIsWithinTriangle(b, a.b) || PointIsWithinTriangle(b, a.c)) { 	//a intersects with b
		return true;
	}

	if (IsIntersecting(a.a, a.b, b.a, b.b))
		return true;

	if (IsIntersecting(a.b, a.c, b.b, b.c))
		return true;

	if (IsIntersecting(a.b, a.c, b.b, b.c))
		return true;

	return false;

}
bool OnLine(const vi2d& lineA, const vi2d& lineB, const vi2d& p)
{
	return (
			p.x <= std::max(lineA.x, lineB.x) 
		&&	p.x <= std::min(lineA.x, lineB.x) 
		&&	p.y <= std::max(lineA.y, lineB.y) 
		&&	p.y <= std::min(lineA.y, lineB.y));		
}
LineDirection GetLineDirection(const vi2d& a, const vi2d& b, const vi2d& c)
{

	const int32_t dir = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

	if (!dir)
		return COLINEAR;
	else if (dir < 0)
		return CLOCKWISE;
	return ANTI_CLOCKWISE;
}
//ab = line1, cd = line2
bool IsIntersecting(const vi2d& a, const vi2d& b, const vi2d& c, const vi2d& d)
{

	const LineDirection d1 = GetLineDirection(a, b, c);
	const LineDirection d2 = GetLineDirection(a, b, d);
	const LineDirection d3 = GetLineDirection(c, d, a);
	const LineDirection d4 = GetLineDirection(c, d, b);

	if (d1 != d2 && d3 != d4)
		return true;

	if (!d1 && OnLine(a, b, c))
		return true;

	if (!d2 && OnLine(a, b, d))
		return true;

	if (!d3 && OnLine(c, d, a))
		return true;

	if (!d4 && OnLine(c, d, b))
		return true;


	return false;
}