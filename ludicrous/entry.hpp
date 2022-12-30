#pragma once

#include "pch.h"


class Game : public olc::PixelGameEngine
{

public:
	Game(const std::string_view& name) {
		sAppName = name;
	}

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

};