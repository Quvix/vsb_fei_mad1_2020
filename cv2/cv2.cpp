#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>

double getSupp(int r, int N)
{
	return r / (double)N;
}

double getConf(int r, int cMax)
{
	return r != 0 ? cMax / (double)r : 0;
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

template <typename T>
std::vector<std::vector<T>> getAllCombinations(std::vector<std::vector<T>>& arr) {
	int n = arr.size();
	int* indices = new int[n];
	std::vector<std::vector<T>> result;

	for (int i = 0; i < n; i++)
		indices[i] = 0;

	while (1)
	{
		std::vector<T> tmp;
		for (int i = 0; i < n; i++)
		{
			tmp.push_back(arr[i][indices[i]]);
			//std::cout << arr[i][indices[i]] << " ";
		}
		result.push_back(tmp);

		//std::cout << "\n";

		int next = n - 1;
		while (next >= 0 && (indices[next] + 1 >= arr[next].size()))
			next--;

		if (next < 0)
			return result;

		indices[next]++;

		for (int i = next + 1; i < n; i++)
			indices[i] = 0;
	}

	return result;
}

int main(int argc, char** argv)
{
	std::string inFile(argv[1]);
	std::ifstream in(inFile);
	std::string line;
	std::vector<std::vector<std::string>> records;
	std::vector<std::vector<std::string>> result;
	while (getline(in, line))
	{
		auto parts = split(line, ',');
		records.push_back(parts);
	}

	size_t columns = records[0].size();

	std::vector<std::vector<std::string>> uniqueValues(columns);

	for (size_t i = 0; i < uniqueValues.size() - 1; i++)
	{
		uniqueValues[i].push_back("NONE");
	}

	for (const auto& e : records)
	{
		for (size_t i = 0; i < e.size(); i++)
		{
			if (std::find(uniqueValues[i].begin(), uniqueValues[i].end(), e[i]) == uniqueValues[i].end()) {
				uniqueValues[i].push_back(e[i]);
			}
		}
	}

	std::vector<std::vector<std::string>> combinations = getAllCombinations(uniqueValues);


	for (const auto& c : combinations)
	{
		int r = 0;
		int cMax = 0;
		for(const auto& record : records)
		{
			bool match = true;
			bool match2 = true;
			for (int i = 0; i < c.size(); i++)
			{
				if (c[i] != record[i] && c[i] != "NONE")
				{
					match = false;
				}
			}

			for (int i = 0; i < c.size() - 1; i++)
			{
				if (c[i] != record[i] && c[i] != "NONE")
				{
					match2 = false;
				}
			}

			if (match)
			{
				cMax++;
			}
			if (match2)
			{
				r++;
			}
		}

		for (const auto& e : c)
		{
			std::cout << e << " ";
		}
		std::cout << "| r=" << r << " c_max=" << cMax << " supp=" << getSupp(r, records.size()) << " conf=" << getConf(r, cMax) << "\n";
	}
}