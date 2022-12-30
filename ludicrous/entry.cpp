
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

	//std::list<vf2d> points;

	//points.push_back({ 10.f,11.f });
	//points.push_back({ 10.f,10.f });

	//points.push_back({ 11.f,10.f });
	//points.push_back({ 11.f,11.f });

	//points.push_back({ 10.f,10.f });
	//points.push_back({ 11.f,10.f });

	//points.push_back({ 10.f,11.f });
	//points.push_back({ 11.f,11.f });

	//brush_t brush(points);
	
	itris_t tris;
	static itris_t tris2;
	vi2d p = GetRealCursorPos();



	static bool useMouse = false;

	//if(useMouse)
	//	pf = GetRealCursorPos();

	//vf2d p = Screen2Grid(pf);


	tris.a = { 300, 300};
	tris.b = { 400, 500};
	tris.c = { 500, 300};

	//tris2.a = { 14.f, 14.f };
	//tris2.b = { 18.f, 10.f };
	//tris2.c = { 18.f, 18.f };

	if (GetMouse(olc::Mouse::MIDDLE).bPressed)
		useMouse = !useMouse;
	if (GetMouse(olc::Mouse::RIGHT).bPressed) {
		useMouse = false;

		//above
		tris2.a = { 300, 300 };
		tris2.b = { 400, 100 };
		tris2.c = { 500, 300 };

		//right side
		//tris2.a = { 400, 500 };
		//tris2.b = { 500, 300 };
		//tris2.c = { 600, 500 };
	}

	//right side
	/*
	
		tris2.a = { 400, 300 };
		tris2.b = { 500, 500 };
		tris2.c = { 600, 300 };
	
	*/

	if (useMouse) {
		tris2.a = { p.x + 100, p.y + 100 };
		tris2.b = { p.x + 200, p.y - 100 };
		tris2.c = { p.x + 300, p.y + 100};
	}
	

	DrawTriangle((tris.a), (tris.b), (tris.c), olc::RED);
	DrawTriangle((tris2.a), (tris2.b), (tris2.c), olc::RED);

	DrawCircle((tris.a + tris.b + tris.c) / 3, 10, olc::BLACK);

	//DrawTriangle(tris2.a, tris2.b, tris2.c, olc::RED);


	//DrawString({ 100, 200 }, std::format("{},{}", p.x, p.y), olc::BLACK);

	
	//vi2d a{p}, b{p.x + 500, p.y + 500}, c{100, 500}, d{500,100};

	//DrawLine(a, b, olc::RED);
	//DrawLine(c, d, olc::GREEN);



	if (TriangleIntersection(tris, tris2)) {
		DrawString({ 100, 100 }, "yep", olc::BLACK);

	}

	//if (PointIsWithinTriangle(tris, p)) {
	//	DrawString({100, 100}, "yep", olc::BLACK);
	//}

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