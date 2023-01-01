
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
	const auto center = Grid2Screen(std::accumulate(poly->vertices.begin(), poly->vertices.end(), ac) / poly->vertCount);
	const auto topleft = std::max_element(poly->vertices.cbegin(), poly->vertices.cend(), [](const vf2d& a, const vf2d& b) { return a.x > b.x; });
	const auto furthest = std::max_element(poly->vertices.cbegin(), poly->vertices.cend(), [&center](const vf2d& a, const vf2d& b) {return b.x > a.x; });

	std::vector<vf2d> new_verts, needs_sorting = poly->vertices;

	const int32_t radius = (int32_t)furthest->dist(center) / poly->vertCount;
	const float fRadius = (float)radius / gGlobals.gridSize;

	//add to the new verts list
	new_verts.push_back(*topleft);
	
	//erase the closest element
	auto pos = std::distance(poly->vertices.cbegin(), topleft);
	needs_sorting.erase(needs_sorting.cbegin()+pos, needs_sorting.cbegin()+pos+1);


	engine->DrawString(Grid2Screen(*topleft), std::format("furthest: {}", radius), olc::BLACK);
	engine->DrawCircle(center, radius, olc::RED);

	while (needs_sorting.empty() == false) {

	}

	poly->vertices.clear();
	poly->vertices.insert(poly->vertices.begin(), new_verts.begin(), new_verts.end());



}


void polygon_t::DebugDraw()
{
	const auto poly = this;

	auto start = Grid2Screen(poly->vertices[0]);
	int i = 0;
	for (i = 0; i < poly->vertCount-1; i++) {


		const auto a = Grid2Screen(poly->vertices[i]);

		engine->DrawLine(start,a, olc::BLACK);

		engine->DrawString(a, std::to_string(i), olc::BLACK);

	}
	const auto a = Grid2Screen(poly->vertices.back());
	engine->DrawLine(start, a, olc::BLACK);
	engine->DrawString(a, std::to_string(i), olc::BLACK);


}


void polygon_t::Draw_As_A_Circle()
{
	const auto poly = this;
	vf2d ac;
	const auto center = Grid2Screen(std::accumulate(poly->vertices.begin(), poly->vertices.end(), ac) / poly->vertCount);
	const auto topleft = Grid2Screen(*std::max_element(poly->vertices.cbegin(), poly->vertices.cend(), [](const vf2d& a, const vf2d& b) { return a.x > b.x; }));
	const auto furthest = Grid2Screen(*std::max_element(poly->vertices.cbegin(), poly->vertices.cend(), [&center](const vf2d& a, const vf2d& b) {return b.x > a.x; }));

	const int32_t offset = 200;
	


	engine->DrawRect(topleft + vi2d{offset, 0}, furthest, olc::RED);


}
int CCW(const vf2d& a, const vf2d& b, const vf2d& c) {

	//return VAngleDifference(b, c) < VAngleDifference(a, c);

	float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

	if (area < 0) return -1;
	if (area > 0) return 1;

	return 0;
};
void SortByAngle(std::vector<vf2d>& points, vf2d& ref)
{
	std::sort(points.begin(), points.end(), [&ref](vf2d& b, vf2d& c) {

		if (b == ref) return -1;
		if (c == ref) return 1;

		int ccw = CCW(ref, b, c);

		if (ccw == 0) {

			if (b.x == c.x) {
				return b.y < c.y ? -1 : 1;
			}
			return b.x < c.x ? -1 : 1;
		}

		return ccw * -1;

		});
}
std::vector<vf2d> ConvexHullAlgorithm(std::vector<vf2d> iPoints)
{
	std::vector<vf2d> sorted, stack;
	const auto lowest = std::max_element(iPoints.cbegin(), iPoints.cend(), [](const vf2d& a, const vf2d& b) {return b.y > a.y; });
	vf2d lowestP = *lowest;
	const auto pos = std::distance(iPoints.cbegin(), lowest); //index of the lowest Y


	iPoints.erase(iPoints.begin() + pos, iPoints.begin() + pos + 1); //remove lowest Y

	const auto L_CCW = [](const vf2d& a, const vf2d& b, const vf2d& c) -> bool {

		//return VAngleDifference(b, c) < VAngleDifference(a, c);

		float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

		if (area < 0) return -1;
		if (area > 0) return 1;

		return 0;
	};

	//sort by angle
	std::sort(iPoints.begin(), iPoints.end(), [&lowestP, &L_CCW](const vf2d& a, const vf2d& b) {
		return VAngleDifference(b, lowestP) > VAngleDifference(a, lowestP); });

	//std::sort(iPoints.begin(), iPoints.end(), [&lowestP](vf2d& b, vf2d& c) {

	//	if (b == lowestP) return -1;
	//	if (c == lowestP) return 1;

	//	int ccw = CCW(lowestP, b, c);

	//	if (ccw == 0) {

	//		if (b.x == c.x) {
	//			return b.y < c.y;
	//		}
	//		return b.x < c.x;
	//	}

	//	return ccw * -1;

	//	});

	sorted.clear();
	sorted.push_back(lowestP); //add lowest Y as the first one
	sorted.insert(sorted.begin()+1, iPoints.begin(), iPoints.end());


	//const vf2d first_pos = { sorted[1].x, lowestP.y };


	//stack.push_back(sorted[1]);

	const int32_t max_size = sorted.size();

	std::cout << '\n';

	auto pop_front = [](std::vector<vf2d>* p) {
		vf2d front = p->front();
		p->erase(p->begin(), p->begin()+1);
		return front;
	};
	auto push_front = [](std::vector<vf2d>* p, vf2d elem) {
		p->insert(p->begin(), 1, elem);
		return;
	};

	push_front(&stack, lowestP);
	push_front(&stack, sorted[1]);

	for(int i = 2; i < max_size; i++){
		
		auto& next = sorted[i];
		auto p = pop_front(&stack);

		while(!stack.empty() && L_CCW(stack.front(), p, next) <= 0) {
			p = pop_front(&stack);
		}

		push_front(&stack, p);
		push_front(&stack, sorted[i]);

		
	
	}
	auto p = pop_front(&stack);

	if (L_CCW(stack.front(), p, lowestP) > 0)
		stack.push_back(p);

	return sorted;

}