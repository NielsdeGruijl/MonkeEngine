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

		outData << GetAverage() << "fps,";
		outData << GetOnePercentLow() << "fps,";
		outData << GetOnePercentHigh() << "fps";
		//outData << data.size() << " sample size";

		outData.close();
	}

	void AddData(float pData)
	{
		data.push_back(pData);
	}

	float GetAverage()
	{
		float total = 0;

		for (float i : data)
		{
			total += i;
			//std::cout << i << "\n";
		}

		//std::cout << total << ", " << data.size() << "\n";

		float frameTime = total / data.size();

		std::cout << frameTime << "\n";

		return 1 / frameTime;
	}

	float GetOnePercentLow()
	{
		std::sort(data.begin(), data.end());

		int onePercent = int(data.size() / 100);

		if (onePercent == 0)
			onePercent = 1;

		float total = 0;

		for (size_t i = data.size() - 1; i > data.size() - onePercent; i--)
		{
			total += data[i];
		}

		float frameTime = total / onePercent;

		std::cout << frameTime << "\n";

		return 1 / frameTime;
	}

	float GetOnePercentHigh()
	{
		std::sort(data.begin(), data.end());
		int onePercent = int(data.size() / 1000);

		if (onePercent == 0)
			onePercent = 1;

		float total = 0;
		for (size_t i = data.size() - 1; i > data.size() - onePercent - 1; i--)
		{
			total += data[i];
		}

		float frameTime = total / onePercent;

		std::cout << frameTime << "\n";

		return 1 / frameTime;
	}

private:
	std::vector<float> data;
	std::ofstream outData;
};