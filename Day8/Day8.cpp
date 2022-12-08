#define TEST 0
#define ADVANCED 1
#include "../Headers/AOC.h"

#define ADV_BREAK(Index) { SpotScore[Index]++; break; }

int main()
{
	int SizeX = 0, SizeY = 0;
	auto InputFile = LoadInputFile();
	std::vector<std::vector<unsigned char>> Input;
	while (!InputFile.eof())
	{
		std::string str = GetNextLine(InputFile, 256);
		if (str.empty())
		{
			break;
		}
		Input.push_back(std::vector<unsigned char>());
		for (char c : str)
		{
			Input[SizeY].push_back(std::stoi(std::string(1, c)));
		}
		SizeX = std::max((size_t)SizeX, str.size());
		SizeY++;
	}
	std::cout << "Done reading file with dimension of x = " << SizeX << ", y = " << SizeY << std::endl;
#if ADVANCED
	int IdealSpotScore = 0;
	for (int X = 0; X < SizeX; X++)
	{
		for (int Y = 0; Y < SizeY; Y++)
		{
			int SpotScore[4] = { 0, 0, 0, 0 };
			for (int YCheck = Y + 1; YCheck < SizeY; YCheck++)
			{
				if (Input[X][Y] > Input[X][YCheck])
				{
					SpotScore[0]++;
				}
				else ADV_BREAK(0);
			}
			for (int YCheck = Y - 1; YCheck >= 0; YCheck--)
			{
				if (Input[X][Y] > Input[X][YCheck])
				{
					SpotScore[1]++;
				}
				else ADV_BREAK(1);
			}
			for (int XCheck = X + 1; XCheck < SizeX; XCheck++)
			{
				if (Input[X][Y] > Input[XCheck][Y])
				{
					SpotScore[2]++;
				}
				else ADV_BREAK(2);
			}
			for (int XCheck = X - 1; XCheck >= 0; XCheck--)
			{
				if (Input[X][Y] > Input[XCheck][Y])
				{
					SpotScore[3]++;
				}
				else ADV_BREAK(3);
			}
			IdealSpotScore = std::max((SpotScore[0] * SpotScore[1] * SpotScore[2] * SpotScore[3]), IdealSpotScore);
		}
	}
	SHOW_RESULT(IdealSpotScore);
#else
	unsigned int Count = 0;
	for (int X = 0; X < SizeX; X++)
	{
		for (int Y = 0; Y < SizeY; Y++)
		{
			bool IsVisible = false;
			bool CanBeSeen = true;
			for (int YCheck = Y + 1; YCheck < SizeY; YCheck++)
			{
				if (Input[X][Y] <= Input[X][YCheck])
				{
					CanBeSeen = false;
				}
			}
			if (CanBeSeen)
			{
				IsVisible = true;
			}
			CanBeSeen = true; 
			for (int YCheck = Y - 1; YCheck >= 0; YCheck--)
			{
				if (Input[X][Y] <= Input[X][YCheck])
				{
					CanBeSeen = false;
				}
			}
			if (CanBeSeen)
			{
				IsVisible = true;
			}
			CanBeSeen = true; 
			for (int XCheck = X + 1; XCheck < SizeX; XCheck++)
			{
				if (Input[X][Y] <= Input[XCheck][Y])
				{
					CanBeSeen = false;
				}
			}
			if (CanBeSeen)
			{
				IsVisible = true;
			}
			CanBeSeen = true; 
			for (int XCheck = X - 1; XCheck >= 0; XCheck--)
			{
				if (Input[X][Y] <= Input[XCheck][Y])
				{
					CanBeSeen = false;
				}
			}
			if (CanBeSeen)
			{
				IsVisible = true;
			}
			if (IsVisible)
			{
				Count++;
			}
		}
	}
	SHOW_RESULT(Count);
#endif
	InputFile.close();
}