#include "pch.h"


brush_t::brush_t(const std::list<vf2d> points) : polygon(new plane_t[points.size() / 2]) {

	const size_t realsize = points.size();
	const size_t size = points.size() / 2;
	if (realsize % 2 != 0 && realsize != 1) {
		G_Error("brush_t::constructor(): invalid plane, (", size, ")\n");
		return;
	}

	int j = 0;
	for (auto points_it = points.begin(); points_it != points.end(); points_it++) {

		
		polygon[j].s = *points_it;
		points_it++;
		polygon[j].e = *points_it;
		polygon[j].SetNormal();

		j++;
	}

	faces = size;

}

bool brush_t::Triangulate()
{
	

	return true;
}

void brush_t::DebugDraw()
{
	const auto brush = this;
	if (!brush->faces)
		return;

	for (plane_t* pol = &brush->polygon[0]; pol != &brush->polygon[brush->faces]; pol++) {
		engine->DrawLine(Grid2Screen(pol->s), Grid2Screen(pol->e), olc::RED);
	}
}