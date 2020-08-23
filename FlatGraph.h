#include<iostream>
#include"path.h"
#include<fstream>
#include<queue>
#include<unordered_map>


#pragma once


void str2Int(const std::string& s, int* ver, int& j) {
	int temp = 0;
	int i = 0;
	j = 0;
	if (s[0] == ' ') {
		i = 4;
	}
	for (i; i != s.length(); ++i) {
		if (s[i] != ' ' && s[i] != 'T') {
			temp += (s[i] - '0');
			ver[j] = temp;
			temp *= 10;
		}
		else {
			++j;
			temp = 0;
			while (s[i] == ' ' || s[i] == 'T') {
				++i;
			}
			--i;
		}
	}
}


//kantor function make unique key of unordered_map 
int kantor(const int& a, const int& b) {
	int unique = 0;
	unique = ((a + b) * (a + b + 1))/2 + b;
	return unique;
}

void readFromFile(std::unordered_map<int, std::shared_ptr<vertex>>& umap,const  std::string& filename) {
	std::ifstream file;
	file.open(filename);
	if (file.is_open()) {
		std::string s;
		int n;
		int    ver[3];
		while (getline(file, s)) {
			int j = 0;
			if (s[0] != ' ') {
				str2Int(s, ver, j);
				std::shared_ptr<vertex> v(new vertex(ver[0], ver[1]));
				v->textVer = (j == 2) ? ver[2] : -1;
				n = kantor(ver[0], ver[1]);		
				umap.insert({ n, v });
			}
			else {
				int nn;
				str2Int(s, ver, j);
				nn = kantor(ver[0], ver[1]);
				umap[n]->neighbor.push_back(nn);
			}
		}
		

	}
	else {
		std::cout << "0";
	}
	file.close();
}




void makePathName(std::shared_ptr<path>& p, int& s) {
	/*makePathName function is make a name the given path,
	if the path start and end is same as another path end and start it is the same path 
	then for them is make a same name*/
	int t1 = kantor(p->start->layer, p->start->shape);
	int t2 = kantor(p->end->layer, p->end->shape);
	if (t1 > t2) {
		std::swap(t1, t2);
	}
	s = kantor(t1,t2);
}



void findShortestPath(std::unordered_map<int, std::shared_ptr<vertex>>& umap, std::unordered_map<int,std::vector<std::shared_ptr<path>>>&  v) {
	
	std::queue<std::shared_ptr<path>>  q;
	int u = 0;
	int pathName;
	for (auto it : umap) {
		if (it.second->textVer != -1) {
			for (auto i : it.second->neighbor) {
				if (umap.find(i) == umap.end())continue;
				std::shared_ptr<path> p(new path(it.second, umap[i]));
				if (umap[i]->textVer != -1 && umap[i]->layer != it.second->layer) {
					makePathName(p, u);
					v[u].push_back(p);
				}
				q.push(p);
			}
		}
	}
	/*In lines 97-109 finds the text vertices of the graph from an unordered map. It forms a path with all the neighbors and push a queue*/


	while (!q.empty()) {
		for (auto i : q.front()->end->neighbor) {
			if (umap.find(i) == umap.end())continue;
			if (!q.front()->onWay(umap[i])) {
				std::shared_ptr<path> p(new path(*q.front()));
				p->addWay(umap[i]);
				q.push(p);
				if (p->end->textVer != -1 && p->end->textVer != p->start->textVer) {
					makePathName(p, pathName);
					v[pathName].push_back(p);
				}
			}
		}
		q.pop();
	}
}

/*In lines 113-128 runs over the queue, where there are all separate paths from the text vertices to their adjacent vertices,
Each step creates a new path by adding the adjacent vertices of the end of the previous path.
The new path push the queue and if the vertice end of path is text vertice it  push back the vector.Vector is value of v(unordered_map).
The first path in the vector will be the shortest for a given pair of text vertices.
Previous path pop the queue.*/


void print(std::unordered_map<int,std::vector<std::shared_ptr<path>>>& v) {
	for (auto i : v) {
		std::cout << "Candidates for (";
		std::cout << i.second.front()->start->layer << " ";
		std::cout << i.second.front()->start->shape << " T ";
		std::cout << i.second.front()->start->textVer;
		std::cout << ") <-> (";
		std::cout << i.second.front()->end->layer << " ";
		std::cout << i.second.front()->end->shape << " T ";
		std::cout << i.second.front()->end->textVer << ")";
		std::cout << std::endl;
		int k = 1;
		for (auto it : i.second) {
			std::cout <<"Short path "<< k++<<" : length = "<< it->length << ", ";
			for (auto ite : it->way) {
				std::cout << " (" << ite->layer << " " << ite->shape;
				if (ite->textVer != -1) {
					std::cout << " T " << ite->textVer << ") ";
				}
				else {
					std::cout << ") ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Optimal short path for (";
		std::cout << i.second.front()->start->layer << " ";
		std::cout << i.second.front()->start->shape << " T ";
		std::cout << i.second.front()->start->textVer;
		std::cout << ") <-> (";
		std::cout << i.second.front()->end->layer << " ";
		std::cout << i.second.front()->end->shape << " T ";
		std::cout << i.second.front()->end->textVer << ")";
		std::cout << std::endl;
		int minLen = i.second.front()->length;
		k = 1;
		for (auto it : i.second) {
			if (minLen >= it->length) {
				std::cout << "Short path " << k++ << " : length = " << it->length << ", ";
				for (auto ite : it->way) {
					std::cout << " (" << ite->layer << " " << ite->shape;
					if (ite->textVer != -1) {
						std::cout << " T " << ite->textVer << ") ";
					}
					else {
						std::cout << ") ";
					}
				}
				std::cout << std::endl;
			}
			else {
				continue;
			}
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}
