
#include "pch.h"


struct LocalPlayer
{
	vi2d origin;
	vi2d mins;
	vi2d maxs;

};
const float VELOCITY = 30;
LocalPlayer lp;
bool Game::OnUserCreate()
{
	lp.mins = { 0, -10 };
	lp.maxs = { 40, 10 };
	lp.origin = { ScreenWidth() / 2, ScreenHeight() / 2 };

	engine = this;

	return true;
}
bool Game::OnUserUpdate(float fElapsedTime)
{
	if (!wnd.hwnd) {
		wnd.hwnd = FindWindowA(NULL, "EPICNESS");
		return true;
	}

	Clear(olc::WHITE);

	static std::vector<vf2d> points;
	static brush_t brush;
	if (points.empty()) {


		points.push_back({ 15.f,15.f });
		points.push_back({ 25.f,15.f });

		points.push_back({ 15.f,20.f });
		points.push_back({ 25.f,20.f });

		points.push_back({ 15.f,25.f });
		points.push_back({ 20.f,25.f });
		points.push_back({ 25.f,25.f });

		brush.Initialize(points);
	}

	//sort vertices
	if (GetAsyncKeyState(VK_NUMPAD5)&1) {

		auto verts = &brush.polygon.vertices;
		auto ye = ConvexHullAlgorithm(points);
		verts->clear();
		verts->insert(verts->begin(), ye.begin(), ye.end());

		

		//brush.Triangulate();

	}
	else if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
	
		brush.Triangulate();
	}

	
	brush.polygon.DebugDraw();
	

	return true;
}

int main()
{
	Game demo("EPICNESS");
#pragma warning(suppress : 26812)
	if (demo.Construct(1366, 768, 1, 1, false, true))
		demo.Start();
	return 0;
}