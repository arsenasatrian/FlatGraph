#include"FlatGraph.h"


int main(int argc,char **filePath)
{
	/*std::string filePath;
	std::cin >> filePath;*/
	std::unordered_map<int, std::shared_ptr<vertex>>            umap;
	std::unordered_map<int, std::vector<std::shared_ptr<path>>> shortPath;
	readFromFile(umap, filePath[1]);
	findShortestPath(umap, shortPath);
	print(shortPath);            
	return 0;
}
