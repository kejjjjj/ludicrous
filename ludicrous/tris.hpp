#pragma once

#ifndef __Tris
#define __Tris

template <typename t> 
struct tris_t
{



	t a;
	t b;
	t c;
};

using ftris_t = tris_t<vf2d>;
using itris_t = tris_t<vi2d>;

template <typename t>
struct triangles_t
{
	t* tris;
	int16_t count;
};

using ftriangles_t = triangles_t<vf2d>;
using itriangles_t = triangles_t<vi2d>;

enum LineDirection
{
	COLINEAR,
	ANTI_CLOCKWISE,
	CLOCKWISE
};

bool TriangulateBrush(const brush_t& brush, ftriangles_t* triangles);
bool PointIsWithinTriangle(const itris_t& tris, const vi2d& p);
bool TriangleIntersection(const itris_t& a, const itris_t& b);
LineDirection GetLineDirection(const vi2d& a, const vi2d& b, const vi2d& c);
bool OnLine(const vi2d& lineA, const vi2d& lineB, const vi2d& p);
bool IsIntersecting(const vi2d& a, const vi2d& b, const vi2d& c, const vi2d& d);
#endif