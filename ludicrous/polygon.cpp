
#include "pch.h"

polygon_t::polygon_t(std::vector<vf2d> verts)
{
	vertices = verts;
	vertCount = vertices.size();

}
void polygon_t::Initialize(std::vector<vf2d> verts)
{
	vertices = verts;
	vertCount = vertices.size();

	vertex_t vert;

	//first vertex gets angle from first and last

	float m2 = VLineSlope(vertices[0], vertices[1]);
	float m1 = VLineSlope(vertices[1], vertices[2]);

	float lengthA = vertices[0].dist(vertices[1]);
	float lengthB = vertices[1].dist(vertices[2]);
	float lengthC = vertices[0].dist(vertices[2]);

	std::cout << std::format("0 -> 1 = {}\n1 -> 2 = {}\n0 -> 2 = {}\n", lengthA, lengthB, lengthC);


	float abtl = atan(	abs((m2 - m1) / (1.f + m1 * m2))	) * 180.f / PI;

	vert.interiorAngles = abtl;
	vert.exteriorAngles = 180.f - vert.interiorAngles;
	vert.isConvex == vert.interiorAngles < 180;
	vertex.push_back(vert);

	//for (int i = 2; i < vertices.size()-1; i+=2) {



	//}

}
//changes the order of the verticies in the list
void polygon_t::RotateVerticies(const LineDirection direction)
{
	//const auto poly = this;
	//vf2d ac;
	//const auto center = Grid2Screen(std::accumulate(poly->vertices.begin(), poly->vertices.end(), ac) / poly->vertCount);
	//const auto topleft = std::max_element(poly->vertices.cbegin(), poly->vertices.cend(), [](const vf2d& a, const vf2d& b) { return a.x > b.x; });
	//const auto furthest = std::max_element(poly->vertices.cbegin(), poly->vertices.cend(), [&center](const vf2d& a, const vf2d& b) {return b.x > a.x; });

	//std::vector<vf2d> new_verts, needs_sorting = poly->vertices;

	//const int32_t radius = (int32_t)furthest->dist(center) / poly->vertCount;
	//const float fRadius = (float)radius / gGlobals.gridSize;

	////add to the new verts list
	//new_verts.push_back(*topleft);
	//
	////erase the closest element
	//auto pos = std::distance(poly->vertices.cbegin(), topleft);
	//needs_sorting.erase(needs_sorting.cbegin()+pos, needs_sorting.cbegin()+pos+1);


	//engine->DrawString(Grid2Screen(*topleft), std::format("furthest: {}", radius), olc::BLACK);
	//engine->DrawCircle(center, radius, olc::RED);

	//while (needs_sorting.empty() == false) {

	//}

	//poly->vertices.clear();
	//poly->vertices.insert(poly->vertices.begin(), new_verts.begin(), new_verts.end());



}


void polygon_t::DebugDraw()
{
	const auto poly = this;

	if (poly->vertices.empty())
		return;

	//auto start = Grid2Screen(poly->vertices[0]);
	int i = 0;
	for (i = 0; i < poly->vertCount-1; i++) {


		const auto a = Grid2Screen(poly->vertices[i]);
		const auto start = Grid2Screen(poly->vertices[i+1]);

		engine->DrawLine(start,a, olc::BLACK);

		engine->DrawString(a, std::to_string(i), olc::BLACK);

	}
	const auto a = Grid2Screen(poly->vertices.back());
	const auto b = Grid2Screen(poly->vertices.front());
	engine->DrawLine(b, a, olc::BLACK);
	engine->DrawString(a, std::to_string(i), olc::BLACK);


}

std::vector<vi2d>ConvexHullAlgorithm(std::vector<vi2d> iPoints)
{
	std::vector<vf2d> _iPoints;

	std::for_each(iPoints.begin(), iPoints.end(), [&_iPoints](vi2d p){
		_iPoints.push_back(Screen2Grid(p)); }); //convert to floats

	auto hull = ConvexHullAlgorithm(_iPoints);

	iPoints.clear();
	iPoints.resize(0);

	std::for_each(hull.begin(), hull.end(), [&iPoints](vi2d p) {
		iPoints.push_back(Grid2Screen(p)); }); //convert back to ints

	return iPoints;

}
std::vector<vf2d> ConvexHullAlgorithm(std::vector<vf2d> iPoints)
{
	std::vector<vf2d> sorted, stack, needs_sorting;
	const auto lowest = BottomMostLeft(iPoints);
	//const auto lowest = std::max_element(iPoints.cbegin(), iPoints.cend(), [](const vf2d& a, const vf2d& b) {
	//	if (b.x < a.x)
	//		return b > a;

	//	return b.y > a.y; });
	vf2d lowestP = *lowest;
	const auto pos = std::distance(iPoints.begin(), lowest); //index of the lowest Y


	iPoints.erase(iPoints.begin() + pos, iPoints.begin() + pos + 1); //remove lowest Y

	//TODO:
	//ERASE ELEMENTS WITH SAME X || Y COORDINATE AS THE REFERENCE, BECAUSE THEN THEY CAN BE SORTED PROPERLY!!!!

	int32_t ipos = 0;
	for (const auto& i : iPoints) {
		if (i.y == lowestP.y && i.x > lowestP.x) { //same horizontal level
			needs_sorting.push_back(i);
			if (i != iPoints.back())
				iPoints.erase(iPoints.begin() + ipos, iPoints.begin() + ipos + 1);
			else
				iPoints.pop_back();

		} /*else if (i.x == lowestP.x) { //same vertical level
			needs_sorting.push_back(i);
			iPoints.erase(iPoints.begin() + ipos, iPoints.begin() + ipos + 1);
		}*/

		ipos++;
	}

	const auto L_CCW = [](const vf2d& prev, const vf2d& next, const vf2d& ref) -> bool {
		return GetLineDirection(prev, next, ref) == LineDirection::ANTI_CLOCKWISE;};

	//sort by angle
	std::sort(iPoints.begin(), iPoints.end(), [&lowestP, &L_CCW](const vf2d& a, const vf2d& b) {
		return VAngleDifference(b, lowestP) > VAngleDifference(a, lowestP); });
	
	//sort the horizontal similarities

	std::sort(needs_sorting.begin(), needs_sorting.end(), [&lowestP, &L_CCW](const vf2d& a, const vf2d& b) { return a.x < b.x; });


	sorted.push_back(lowestP); //add lowest Y as the first one
	sorted.insert(sorted.end(), needs_sorting.begin(), needs_sorting.end()); //add the horizontally sorted elements at the front
	sorted.insert(sorted.end(), iPoints.begin(), iPoints.end()); //add the rest

	const size_t max_size = sorted.size();

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

	stack.push_back(sorted[1]);
	stack.push_back(lowestP);
	

	const auto L_IndexFor_vf2d = [&sorted](const vf2d& pos) -> int32_t {
		
		int i = 0;
		for (const auto& s : sorted) {
			if (s == pos)
				return i;

			i++;
		}
		return -1;
	};

	for(int i = 2; i < max_size; i++){

		auto& next = sorted[i];
		auto p = pop_front(&stack);



		while (stack.size() > 1 && !L_CCW(stack.front(), p, next)) {
			std::cout << std::format("{} is CW to {}\n", L_IndexFor_vf2d(next), L_IndexFor_vf2d(p));

			p = pop_front(&stack);
		}
		
		std::cout << std::format("{} is CCW to {}\n", L_IndexFor_vf2d(next), L_IndexFor_vf2d(p));
		push_front(&stack, p);
		push_front(&stack, sorted[i]);
	
	}
	auto p = pop_front(&stack);

	if (L_CCW(stack.front(), p, lowestP)) {
		std::cout << std::format("{} is CCW to {}\n", L_IndexFor_vf2d(lowestP), L_IndexFor_vf2d(p));
		stack.push_back(p);
	}else
		std::cout << std::format("{} is CW to {}\n", L_IndexFor_vf2d(lowestP), L_IndexFor_vf2d(p));

	std::sort(stack.begin(), stack.end(), [&L_IndexFor_vf2d](const vf2d& a, const vf2d& b) {
		return L_IndexFor_vf2d(b) > L_IndexFor_vf2d(a); });

	std::cout << '\n';
	for (auto& i : stack) {

		if(i == stack.back())
			std::cout << std::format("[{}]\n", L_IndexFor_vf2d(i));
		else
			std::cout << std::format("[{}] -> ", L_IndexFor_vf2d(i));

	}

	return sorted;

}

std::vector<vf2d>::iterator BottomMostLeft(std::vector<vf2d>& points)
{

	auto begin = points.begin();
	auto end = points.end();
	std::vector<vf2d>::iterator min = points.begin();

	for (auto it = points.begin(); it != end; it++) {

		if (it->y >= min->y) {

			if (it->y > min->y)
				min = it;
			else if (it->x < min->x)
				min = it;
		}
	}

	return min;
}