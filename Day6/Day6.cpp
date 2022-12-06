#define TEST 0
#define ADVANCED 1
#include "../Headers/AOC.h"

int main()
{
	auto Input = LoadInputFile();
	std::string Line = GetNextLine(Input, 10000);
	unsigned int FirstMarker = 0;
	int MarkerSize = ADVANCED ? 14 : 4;

	for(int i = 0; i < Line.size() - MarkerSize; i++)
	{
		std::string Sequence = Line.substr(i, MarkerSize);
		bool FoundDuplicate = false;
		for(int j = 0; j < MarkerSize; j++)
		{
			if(Sequence.substr(j + 1).find(Sequence[j]) != std::string::npos)
			{
				FoundDuplicate = true;
			}

		}
		if(!FoundDuplicate && FirstMarker == 0)
		{
			std::cout << Sequence << std::endl;
			FirstMarker = i + MarkerSize;
		}
	}
	SHOW_RESULT(FirstMarker);
}