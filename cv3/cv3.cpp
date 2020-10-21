#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

struct Edge {
	int node1;
	int node2;
};

int degree(std::vector<int> line)
{
	int degree = 0;
	for (const auto& e : line)
	{
		degree += e;
	}

	return degree;
}

int minDegree(std::vector<std::vector<int>> &adjacencyMatrix)
{
	int result = INT16_MAX;
	for (const auto& l : adjacencyMatrix)
	{
		int degree = 0;
		for (const auto& e : l)
		{
			degree += e;
		}

		if (degree < result)
		{
			result = degree;
		}
	}

	return result;
}

int maxDegree(std::vector<std::vector<int>>& adjacencyMatrix)
{
	int result = 0;
	for (const auto& l : adjacencyMatrix)
	{
		int degree = 0;
		for (const auto& e : l)
		{
			degree += e;
		}

		if (degree > result)
		{
			result = degree;
		}
	}

	return result;
}

double avgDegree(std::vector<std::vector<int>>& adjacencyMatrix)
{
	double result = 0;
	int cnt = 0;
	for (const auto& l : adjacencyMatrix)
	{
		int degree = 0;
		for (const auto& e : l)
		{
			degree += e;
		}

		cnt++;
		result += degree;
	}

	return result / cnt;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> splits;
	std::string split;
	std::istringstream ss(s);
	while (getline(ss, split, delimiter))
	{
		splits.push_back(split);
	}
	return splits;
}

int main(int argc, char** argv)
{
	std::ifstream in("KarateClub.csv");
	std::string line;
	std::vector<Edge> edges;

	while (std::getline(in, line))
	{
		auto parts = split(line, ';');
		Edge e = { std::stoi(parts[0]), std::stoi(parts[1]) };
		edges.push_back(e);
	}

	std::cout << edges.size() << "\n";

	int biggestNode = edges[edges.size() - 1].node1;

	std::vector<std::vector<int>> adjacencyMatrix(biggestNode, std::vector<int>(biggestNode, 0));

	for (const auto& e : edges)
	{
		adjacencyMatrix[e.node1 - 1][e.node2 - 1] = 1;
		adjacencyMatrix[e.node2 - 1][e.node1 - 1] = 1;
	}

	for (const auto& l : adjacencyMatrix)
	{
		for (const auto& e : l)
		{
			std::cout << e << " ";
		}
		std::cout << "\n";
	}

	std::cout << "min: " << minDegree(adjacencyMatrix) << "\n";
	std::cout << "max: " << maxDegree(adjacencyMatrix) << "\n";
	std::cout << "avg: " << avgDegree(adjacencyMatrix) << "\n";


	std::ofstream out("degree_centrality.csv");

	std::map<int, int> degreeCentrality;

	for (int i = 1; i <= maxDegree(adjacencyMatrix); i++)
	{
		degreeCentrality[i] = 0;
	}

	for (int i = 0; i < adjacencyMatrix.size(); i++)
	{
		int d = degree(adjacencyMatrix[i]);

		degreeCentrality[d] = degreeCentrality[d] + 1;

	}

	for (auto i = degreeCentrality.begin(); i != degreeCentrality.end(); i++) 
	{
		std::cout << i->first << " : " << i->second << " : " << i->second / (double)biggestNode <<  '\n';
		out << i->first << ";" << i->second << "\n";
	}
}