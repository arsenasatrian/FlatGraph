#include"vertex.h"
#include<memory>
#pragma once

struct path {
	std::shared_ptr<vertex>              start;
	std::shared_ptr<vertex>              end;
	int                                  length;
	std::vector<std::shared_ptr<vertex>> way;
	path()
		: start (nullptr)
		, end   (nullptr)
		, length(0)
		, way   ()
	{}
	path(std::shared_ptr<vertex> s, std::shared_ptr<vertex> e)
		: start(s)
		, end  (e)
	{
		length = (s->layer != e->layer) ? 2 : 1;
		way.push_back(s);
		way.push_back(e);
	}

	path(const path& o)
		: start (o.start)
		, end   (o.end)
		, length(o.length)
	{
		for (auto i : o.way) {
			way.push_back(i);
		}
	}
	void addWay(std::shared_ptr<vertex> e) {
		if (end->layer != e->layer) {
			length++;
		}
		end = e;
		way.push_back(e);
	}
	bool onWay(std::shared_ptr<vertex> v) {
		for (auto i : way) {
			if (i == v)return true;
		}
		return false;
	}
};
