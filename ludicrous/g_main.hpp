#pragma once

#ifndef __gmain
#define __gmain

#include "pch.h"

inline std::vector<std::string> compilerlog;

inline void G_Error()
{
	std::string beg;
	for (const auto& i : compilerlog) {
		beg += i;
	}

	MessageBoxA(NULL, beg.c_str(), "Compile Error!", MB_ICONERROR);

	compilerlog.clear();
	exit(-1);
	return;
}

template<typename t, typename ... Param>
void G_Error(const t& _, Param... param) 
{
	std::stringstream ss;
	ss << _;
	compilerlog.push_back(ss.str());

	//std::cout << t << '\n';
	G_Error(param...);
}


//globals
inline olc::PixelGameEngine* engine;

#endif