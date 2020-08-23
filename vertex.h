#include<vector>

#pragma once

struct vertex {

	int              layer;
	int              shape;
	int              textVer;
	std::vector<int> neighbor;

	vertex()
		: layer   (0)
		, shape   (0)
		, neighbor(std::vector<int>())
		, textVer (0)
	{}
	vertex(int l, int s, std::vector<int> n = {}, int tV = -1)
		: layer(l)
		, shape(s)
	{
		for (auto i : n) {
			neighbor.push_back(i);
		}
		textVer = tV;
	}
};
