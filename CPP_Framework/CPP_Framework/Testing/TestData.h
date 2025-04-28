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
		outData.open("TestData.txt");
		if (!outData)
		{
			std::cout << "Could not open file\n";
			return;
		}

		for (int i : data)
		{
			outData << i << "\n";
		}

		std::cout << sizeof(int) << ", " << data.size() << "\n";

		outData.close();
	}

	void AddData(int pData)
	{
		data.push_back(pData);
	}

private:
	std::vector<int> data;
	std::ofstream outData;
};