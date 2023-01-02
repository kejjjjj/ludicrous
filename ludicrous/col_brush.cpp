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

	const auto poly = &this->polygon;
	std::vector<vi2d> b_hull, b_rest;


	//Let left_most and right_most be the left-most and right-most points.
	const auto left_most = Grid2Screen(*std::max_element(poly->vertices.cbegin(), poly->vertices.cend(), [](const vf2d& a, const vf2d& b) { return a.x > b.x; }));
	const auto right_most = Grid2Screen(*std::max_element(poly->vertices.cbegin(), poly->vertices.cend(), [](const vf2d& a, const vf2d& b) { return a.x < b.x; }));

	// Find a lower convex hull S of the points. S contains p1, p2 and all the convex hull points that are below the line p1p2. 
	std::for_each(poly->vertices.cbegin(), poly->vertices.cend(), [&left_most, &right_most, &b_hull](const vf2d& i) {

		const auto p = Grid2Screen(i);
		if (IsBelowLine(left_most, right_most, p)) {
			b_hull.push_back(p);
		}
	});
	std::vector<vi2d> copy = b_hull;
	b_hull.clear();
	b_hull = ConvexHullAlgorithm(copy);
	copy.clear();

	//add the remaining points to the b_rest container
	std::for_each(poly->vertices.cbegin(), poly->vertices.cend(), [&b_rest, &b_hull](const vf2d& p) {

		const auto fixed = Grid2Screen(p);
		if (std::find(b_hull.cbegin(), b_hull.cend(), fixed) == b_hull.cend()) {
			b_rest.push_back(fixed);
		}
	});


	//Now sort the remaining points (those not in S (b_rest)) by their x-coordinate. 
	std::sort(b_rest.begin(), b_rest.end(), [](const vi2d& a, const vi2d& b) { return a.x < b.x; });


//	(std::sort(b_hull.cbegin(), b_hull.cend(), [](const vf2d& a, const vf2d& b) { return a.x > b.x; }));



	return true;
}

void brush_t::DebugDraw()
{
	const auto brush = this;
	if (!brush->faces)
		return;

	


}