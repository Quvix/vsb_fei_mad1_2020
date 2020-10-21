#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <limits>

struct Edge {
	int node1;
	int node2;
};

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

std::vector<std::vector<int>> floyd(std::vector<std::vector<int>>& matrix)
{
	std::vector<std::vector<int>> result = matrix;

	for (int k = 0; k < result.size(); k++)
	{
		for (int i = 0; i < result.size(); i++)
		{
			for (int j = 0; j < result.size(); j++)
			{
				if (result[i][k] + result[k][j] < result[i][j])
				{
					result[i][j] = result[i][k] + result[k][j];
				}
			}
		}
	}

	return result;
}

double averagePathLength(std::vector<std::vector<int>>& matrix)
{
	int sum = 0;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			if (i != j)
			{
				sum += matrix[i][j];
			}
		}
	}

	return sum / (double)(matrix.size() * (matrix.size() - 1));
}

int graphDiameter(std::vector<std::vector<int>>& matrix)
{
	int max = 0;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			if (i != j)
			{
				if (matrix[i][j] > max)
				{
					max = matrix[i][j];
				}
			}
		}
	}
	
	return max;
}

std::map<int, double> closnessCentrality(std::vector<std::vector<int>>& matrix)
{
	std::map<int, double> centrality;

	for (int i = 0; i < matrix.size(); i++)
	{
		int sum = 0;
		for (int j = 0; j < matrix.size(); j++)
		{
			if (i != j)
			{
				sum += matrix[i][j];
			}
		}

		centrality[i + 1] = matrix.size() / (double)sum;
	}

	return centrality;
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

	int biggestNode = edges[edges.size() - 1].node1;

	std::vector<std::vector<int>> adjacencyMatrix(biggestNode, std::vector<int>(biggestNode, 0));

	for (const auto& e : edges)
	{
		adjacencyMatrix[e.node1 - 1][e.node2 - 1] = 1;
		adjacencyMatrix[e.node2 - 1][e.node1 - 1] = 1;
	}

	int inf = 1000;
	for (int i = 0; i < adjacencyMatrix.size(); i++)
	{
		for (int j = 0; j < adjacencyMatrix.size(); j++)
		{
			if (i != j)
			{
				if (adjacencyMatrix[i][j] == 0)
				{
					adjacencyMatrix[i][j] = inf;
				}
			}
		}
	}

	std::vector<std::vector<int>> afterFloyd = floyd(adjacencyMatrix);

	for (const auto& l : afterFloyd)
	{
		for (const auto& e : l)
		{
			std::cout << e << " ";
		}
		std::cout << "\n";
	}

	std::cout << "Average path length: " << averagePathLength(afterFloyd) << "\n";
	std::cout << "graph diameter: " << graphDiameter(afterFloyd) << "\n";

	std::map<int, double> centrality = closnessCentrality(afterFloyd);

	for (const auto& e : centrality)
	{
		std::cout << e.first << " " << e.second << "\n";
	}
}