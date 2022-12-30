
#include "pch.h"

polygon_t::polygon_t(std::vector<vf2d> verts)
{
	vertices = verts;
	vertCount = vertices.size();

}

//changes the order of the verticies in the list
void polygon_t::RotateVerticies(const LineDirection direction)
{
	const auto poly = this;
	vf2d ac;
	vf2d center = Grid2Screen(std::accumulate(poly->vertices.begin(), poly->vertices.end(), ac) / poly->vertCount);
	auto topleft = std::max_element(poly->vertices.cbegin(), poly->vertices.cend(), [](const vf2d& a, const vf2d& b) { return a.mag2() > b.mag2(); });
	auto furthest = std::max_element(poly->vertices.cbegin(), poly->vertices.cend(), [&center](const vf2d& a, const vf2d& b) {return b.distSquared(center) > a.distSquared(center); });
	
	int radius = (int)furthest->dist(center) / poly->vertCount;

	
	engine->DrawString(Grid2Screen(*topleft), std::format("furthest: {}", radius), olc::BLACK);

	engine->DrawCircle(center, radius, olc::RED);

	//rotate to a direction
	//whatever vert is closest to the topleft position, push it to the stack!



}


void polygon_t::DebugDraw()
{
	const auto poly = this;
	auto begin = poly->vertices.begin();
	auto end = poly->vertices.end();


	int i = 0;
	for (i = 0; i < poly->vertCount-1; i++) {


		auto a = Grid2Screen(poly->vertices[i]);
		auto b = Grid2Screen(poly->vertices[i+1]);

		engine->DrawLine(a,b, olc::BLACK);
		engine->DrawString(a, std::to_string(i), olc::BLACK);
		//if (i == poly->vertices.back())
		//	break;
	}
	auto a = Grid2Screen(poly->vertices.back()), b = Grid2Screen(poly->vertices.front());
	engine->DrawLine(a, b, olc::BLACK);
	engine->DrawString(a, std::to_string(i), olc::BLACK);


}