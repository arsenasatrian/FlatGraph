#include<iostream>
#include"path.h"
#include<fstream>
#include<queue>
#include<unordered_map>

#pragma once
using  um = std::unordered_map<std::string, std::shared_ptr<vertex>>;

void readFromFile(um& umap, std::string& filename) {
	std::ifstream file;
	file.open(filename);
	if (file.is_open()) {
		std::string s;
		std::string n1;
		std::string n2;
		std::string n3;
		int    ver[3];
		while (getline(file, s)) {
			int j = 0;
			if (s[0] != ' ') {
				for (int i = 0; i < s.length(); ++i) {
					if (s[i] == ' ' || s[i] == 'T')continue;
					ver[j] = s[i] - '0';
					j++;
				}
				std::shared_ptr<vertex> v(new vertex(ver[0], ver[1]));
				v->textVer = (j == 3) ? ver[2] : -1;
				n1 = ver[0] + '0';
				n2 = ver[1] + '0';
				n3 = n1 + n2;
				umap.insert({ n3, v });
			}
			else {
				std::string n;
				for (int i = 0; i < s.length(); ++i)
					if (s[i] != ' ') {
						n += s[i];
					}
				umap[n3]->neighbor.push_back(n);
			}
		}
	}
	else {
		std::cout << "0";
	}
	file.close();
}

void makePathName(std::shared_ptr<path>& p, std::string& s) {
	std::string l1;
	std::string s1;
	std::string l2;
	std::string s2;
	if (p->start->layer > p->end->layer || p->start->shape > p->end->shape) {
		l1 = p->end->layer + '0';
		s1 = p->end->shape + '0';
		l2 = p->start->layer + '0';
		s2 = p->start->shape + '0';
	}
	else {
		l1 = p->start->layer + '0';
		s1 = p->start->shape + '0';
		l2 = p->end->layer + '0';
		s2 = p->end->shape + '0';
	}
	s = l1 + s1 + l2 + s2;
}
std::string pathName;
void findShortestPath(um& umap, std::unordered_map<std::string, std::shared_ptr<path>>&  v) {
	std::queue<std::shared_ptr<path>>  q;

	for (auto it : umap) {
		if (it.second->textVer != -1) {
			for (auto i : it.second->neighbor) {
				std::shared_ptr<path> p(new path(it.second, umap[i]));
				if (umap[i]->textVer != -1 && umap[i]->layer != it.second->layer) {
					makePathName(p, pathName);
					v[pathName]=p;
				}
				q.push(p);
			}
		}
	}

	while (!q.empty()) {
		for (auto i : q.front()->end->neighbor) {
			if (!q.front()->onWay(umap[i])) {
				std::shared_ptr<path> p(new path(*q.front()));
				p->addWay(umap[i]);
				q.push(p);
				if (p->end->textVer != -1 && p->end->textVer != p->start->textVer) {
					makePathName(p, pathName);
					if (v.find(pathName) != v.end()) {
						if (p->length < v[pathName]->length) {
							v[pathName] = p;
						}
						else {
							continue;
						}
					}
					else {
						v[pathName] = p;
					}
				}
			}
		}
		q.pop();
	}
}

void print(std::unordered_map<std::string, std::shared_ptr<path>>& v) {
	for (auto i : v) {
		for (auto it : i.second->way) {
			std::cout << "(" << it->layer << "," << it->shape << ")";
		}
		std::cout << std::endl;
	}
}