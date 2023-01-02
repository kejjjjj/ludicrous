#include "pch.h"


brush_t::brush_t(const std::vector<vf2d> points) : polygon(points) {

	//const size_t realsize = points.size();
	const size_t size = points.size() / 2;

	faces = size;

}
void brush_t::Initialize(const std::vector<vf2d> points)
{
	const size_t size = points.size() / 2;

	faces = size;
	polygon.Initialize(points);
}
bool brush_t::Triangulate()
{
	if (this->faces == 0)
		return false;

	
	//Step 1: Compute the interior angles on each vertex of P. If the interior angle on
	//a vertex is less than 180°, the vertex is convex; Otherwise, reflex.



	return true;
}

void brush_t::DebugDraw()
{
	const auto brush = this;
	if (!brush->faces)
		return;

	


}