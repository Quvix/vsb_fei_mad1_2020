#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>

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
	int n = arr.size() - 1;
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

int getNoneCount(std::vector<std::string> vec)
{
	int cnt = 0;
	for (const auto& e : vec)
	{
		if (e == "NONE")
		{
			cnt++;
		}
	}
	return cnt;
}

bool compareVectors(std::vector<std::string> v1, std::vector<std::string> v2)
{
	return (getNoneCount(v1) > getNoneCount(v2));
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
		for (const auto& f : e) {
			std::cout << " " << f;
		}
		std::cout << "\n";

		for (size_t i = 0; i < e.size(); i++)
		{
			if (std::find(uniqueValues[i].begin(), uniqueValues[i].end(), e[i]) == uniqueValues[i].end()) {
				uniqueValues[i].push_back(e[i]);
			}
		}
	}

	std::cout << "--------------------------" << "\n";

	for (const auto& e : uniqueValues)
	{
		for (const auto& f : e) {
			std::cout << " " << f;
		}
		std::cout << "\n";
	}

	std::vector<std::vector<std::string>> combinations = getAllCombinations(uniqueValues);

	std::cout << "--------------------------" << "\n";

	for (const auto& c : combinations)
	{
		for (const auto& e : c)
		{
			std::cout << e << " ";
		}
		std::cout << "\n";
	}

	std::vector<std::vector<std::string>> reducedCombinations;

	// check if combination is valid in while dataset and is true at least once, otherwise remove
	for (int j = 0; j < uniqueValues[uniqueValues.size() - 1].size(); j++) {
		for (const auto& c : combinations)
		{
			bool check = true;
			int matches = 0;
			for (const auto& r : records)
			{
				bool match = true;
				for (int i = 0; i < c.size(); i++)
				{
					if (c[i] != "NONE")
					{
						if (c[i] != r[i])
						{
							match = false;
							break;
						}
					}
				}

				if (match)
				{
					if (r[r.size() - 1] != uniqueValues[uniqueValues.size() - 1][j])
					{
						check = false;
						break;
					}
					matches++;
				}
			}

			if (check == true && matches > 0)
			{
				std::vector<std::string> tmp;

				for (const auto& e : c)
				{
					tmp.push_back(e);
				}

				std::vector<std::vector<std::string>>::iterator it;
				tmp.push_back(uniqueValues[uniqueValues.size() - 1][j]);
				reducedCombinations.push_back(tmp);
			}
		}
	}
	
	//std::cout << reducedCombinations.size() << "\n";

	sort(reducedCombinations.begin(), reducedCombinations.end(), compareVectors);

	/*std::cout << "--------------------------" << "\n";
	for (const auto& c : reducedCombinations)
	{
		for (const auto& e : c)
		{
			std::cout << e << " ";
		}
		std::cout << "\n";
	}

	std::cout << reducedCombinations.size() << "\n";*/


	std::vector<std::vector<std::string>> recordsCopy(records);
	std::vector<std::vector<std::string>> reducedCombinations2;

	// select combinations until whole dataset is covered
	for (const auto& c : reducedCombinations)
	{
		int removed = 0;
		std::vector<std::vector<std::string>>::iterator it = recordsCopy.begin();
		while (it != recordsCopy.end())
		{
			bool match = true;
			for (int i = 0; i < c.size() - 1; i++)
			{
				if (c[i] != (*it)[i] && c[i] != "NONE")
				{
					match = false;
				}
			}

			if (match)
			{
				removed++;
				it = recordsCopy.erase(it);
			}
			else {
				++it;
			}
		}

		if (removed > 0)
		{
			reducedCombinations2.push_back(c);
		}
	}

	std::cout << "--------------------------" << "\n";

	for (const auto& c : reducedCombinations2)
	{
		for (const auto& e : c)
		{
			std::cout << e << " ";
		}
		std::cout << "\n";
	}
	
}