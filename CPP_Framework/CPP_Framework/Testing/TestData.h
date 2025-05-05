#include <iostream>
#include <vector>
#include <fstream>

class TestData
{
public:
	TestData()
	{
	}
	~TestData()
	{
		data.pop_back();

		outData.open("TestData.txt");
		if (!outData)
		{
			std::cout << "Could not open file\n";
			return;
		}

		//for (int i : data)
		//{
		//	outData << i << "ms" << ",";
		//}

		outData << GetAverage() << "ms,";
		outData << GetOnePercentLow() << "ms,";
		outData << GetOnePercentHigh() << "ms,";
		outData << data.size() << " sample size";

		outData.close();
	}

	void AddData(int pData)
	{
		data.push_back(pData);
	}

	int GetAverage()
	{
		int total = 0;

		for (int i : data)
		{
			total += i;
		}

		return total / data.size();
	}

	int GetOnePercentLow()
	{
		std::sort(data.begin(), data.end());

		int onePercent = int(data.size() / 100);

		if (onePercent == 0)
			onePercent = 1;

		int total = 0;
		for (size_t i = 0; i < onePercent; i++)
		{
			total += data[i];
		}

		return total / onePercent;
	}

	int GetOnePercentHigh()
	{
		std::sort(data.begin(), data.end(), std::greater<int>());

		int onePercent = int(data.size() / 100);

		if (onePercent == 0)
			onePercent = 1;

		int total = 0;
		for (size_t i = 0; i < onePercent; i++)
		{
			total += data[i];
		}

		return total / onePercent;
	}

private:
	std::vector<int> data;
	std::ofstream outData;
};