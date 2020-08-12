#include"FlatGraph.h"


int main()
{
	std::string fileName = "C:/Users/Arsen/desktop/f1.txt";
	std::unordered_map<std::string, std::shared_ptr<vertex>> umap;
	std::unordered_map<std::string, std::shared_ptr<path>> shortPath;

	readFromFile(umap, fileName);
	findShortestPath(umap, shortPath);
	print(shortPath);
	                   
	return 0;
}