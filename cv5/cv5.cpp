#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <numeric>

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
	std::ifstream in("iris.csv");
	std::string line;

	getline(in, line);
	auto header = split(line, ';');

	std::vector<std::vector<double>> data(4);
	while (std::getline(in, line))
	{
		std::replace(line.begin(), line.end(), ',', '.');
		auto parts = split(line, ';');
		
		for (int i = 0; i < parts.size(); i++)
		{
			if (i < 4) {
				data[i].push_back(std::stod(parts[i]));
			}
		}
	}

	for (int i = 0; i < data[0].size(); i++) 
	{
		for (int j = 0; j < data.size(); j++)
		{
			std::cout << data[j][i] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";

	std::vector<double> columnMean;
	for (int i = 0; i < data.size(); i++)
	{
		double sum = 0;
		for (const auto& e : data[i])
		{
			sum += e;
		}
		columnMean.push_back(sum / data[i].size());
		std::cout << header[i] << " mean: " << sum / data[i].size() << "\n";
	}

	std::cout << "\n";

	std::vector<double> columnVariance;
	for (int i = 0; i < data.size(); i++)
	{
		double sum = 0;
		for (const auto& e : data[i])
		{
			sum += (e - columnMean[i]) * (e - columnMean[i]);
		}
		columnVariance.push_back(sum / data[i].size());
		std::cout << header[i] << " variance: " << sum / data[i].size() << "\n";
	}

	std::cout << "\n";


	std::cout << "Total mean: (";
	for (int i = 0; i < columnMean.size(); i++)
	{
		std::cout << columnMean[i];
		if (i < columnMean.size() - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << ")\n";

	/*double sum = 0;
	for (int i = 0; i < data[0].size(); i++)
	{
		double tmp = 0;
		for (int j = 0; j < data.size(); j++)
		{
			tmp += (data[j][i] - columnMean[j]) * (data[j][i] - columnMean[j]);
		}

		sum += tmp;
	}
	
	std::cout << "Total variance: " << sum / data[0].size() << "\n";*/
	std::cout << "Total variance: " << std::accumulate(columnVariance.begin(), columnVariance.end(), 0.0) << "\n";
}


