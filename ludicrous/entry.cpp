
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

	wnd.hwnd = FindWindowA(NULL, "EPICNESS");

	Clear(olc::WHITE);

	static std::vector<vf2d> points;

	if (points.empty()) {

		points.push_back({ 2.f,2.f });
		points.push_back({ -2.f,3.f });
		points.push_back({ 1.f,1.f });


		//points.push_back({ 5.f,15.f });
		//points.push_back({ 20.f,15.f });
		//points.push_back({ 10.f,17.f });
		//points.push_back({ 15.f,17.f });
		//points.push_back({ 10.f, 30.f });

		

		auto ye = ConvexHullAlgorithm(points);
		points.clear();
		points.insert(points.begin(), ye.begin(), ye.end());


	}


	static polygon_t poly(points);

	poly.DebugDraw();
	if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
		//poly.RotateVerticies(CLOCKWISE);
		auto ye =  ConvexHullAlgorithm(points);

		points.clear();
		points.insert(points.begin(), ye.begin(), ye.end());

	}

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