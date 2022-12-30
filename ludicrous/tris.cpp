
#include "pch.h"

bool TriangulateBrush(const brush_t& brush, ftriangles_t* triangles)
{
	ftris_t triangle;
	const int32_t possible_triangles = brush.faces - 2;

	for (int32_t i = 0; i < possible_triangles; i++) {



	}

	return {};
}
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

bool TriangleIntersection(const itris_t& a, const itris_t& b)
{

	//if (PointIsWithinTriangle(a, b.a) || PointIsWithinTriangle(a, b.b) || PointIsWithinTriangle(a, b.c) ||	//b intersects with a
	//	PointIsWithinTriangle(b, a.a) || PointIsWithinTriangle(b, a.b) || PointIsWithinTriangle(b, a.c)) { 	//a intersects with b
	//	return true;
	//}

	//offset = 0;
	//return false;
	
	//left triangle is hugging right triangle if this is false
	int matches = 0;

	
	if (!IsIntersecting(a.b, a.c, b.a, b.b)) {
		//either hugging or not near

		if (IsIntersecting(a.b, a.c, b.a, b.c))
			matches++;

		if (IsIntersecting(a.b, a.c, b.b, b.c))
			matches++;

		//not hugging, but intersecting
		if (matches != 0 && a.b != b.a && a.c != b.b)
			return true;
	}
	matches = 0;

	if (!IsIntersecting(a.a, a.c, b.a, b.c)) {
		//either hugging or not near

		if (IsIntersecting(a.a, a.b, b.a, b.b))
			matches++;

		if (IsIntersecting(a.b, a.c, b.b, b.c))
			matches++;

		//not hugging, but intersecting
		if (matches != 0 && a.a != b.a && a.c != b.c)
			return true;
	}

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