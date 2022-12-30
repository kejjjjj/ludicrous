#pragma once

#ifndef __window
#define __window

#include "pch.h"

inline struct wnd_t
{
	HWND hwnd;
}wnd;

RECT GetWindowDimensions();
vi2d GetWindowPos();
vi2d GetWindowSize();
vi2d GetRealCursorPos();

#endif