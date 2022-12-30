#include "pch.h"

RECT GetWindowDimensions()
{
	RECT rect{};

	GetWindowRect(wnd.hwnd, &rect);

	return rect;
}
vi2d GetWindowPos()
{
	RECT rect = GetWindowDimensions();

	return { rect.left, rect.top };
}
vi2d GetWindowSize()
{
	RECT rect = GetWindowDimensions();

	return { rect.right - rect.left, rect.bottom - rect.top };
}
vi2d GetRealCursorPos()
{
	RECT rect = GetWindowDimensions();


	tagPOINT r;
	GetCursorPos(&r);

	ScreenToClient(wnd.hwnd, &r);

	vi2d p = { r.x, r.y };
	
	p.clamp({ 0,0 }, { rect.right - rect.left, rect.bottom - rect.top });

	return p;
}