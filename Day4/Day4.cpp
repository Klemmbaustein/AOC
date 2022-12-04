#define TEST 0
#define ADVANCED 1
#include "../Headers/AOC.h"

struct Assignement
{
	int Begin;
	int End;
};

Assignement GetAssigmenentFromString(std::string str)
{
	std::string SplitLine[] = 
	{
		str.substr(0, str.find_first_of("-")),
		str.substr(str.find_first_of("-") + 1)
	};
	return Assignement(std::stoi(SplitLine[0]), std::stoi(SplitLine[1]));
}

#if ADVANCED

int main()
{
	std::ifstream Input = LoadInputFile();
	unsigned int NumOverlaps = 0;
	while (!Input.eof())
	{
		std::string CurrentLine = GetNextLine(Input);
		std::string SplitLine[] = 
		{
			CurrentLine.substr(0, CurrentLine.find_first_of(",")),
			CurrentLine.substr(CurrentLine.find_first_of(",") + 1)
		};
		Assignement a = GetAssigmenentFromString(SplitLine[0]);
		Assignement b = GetAssigmenentFromString(SplitLine[1]);
		for(int i = a.Begin; i <= a.End; i++)
		{
			if(i >= b.Begin && i <= b.End)
			{
				NumOverlaps++;
				break;
			}
		}
	}
	SHOW_RESULT(NumOverlaps);
}

#else

int main()
{
	std::ifstream Input = LoadInputFile();
	unsigned int NumOverlaps = 0;
	while (!Input.eof())
	{
		std::string CurrentLine = GetNextLine(Input);
		std::string SplitLine[] = 
		{
			CurrentLine.substr(0, CurrentLine.find_first_of(",")),
			CurrentLine.substr(CurrentLine.find_first_of(",") + 1)
		};
		Assignement a = GetAssigmenentFromString(SplitLine[0]);
		Assignement b = GetAssigmenentFromString(SplitLine[1]);
		if(a.Begin <= b.Begin && a.End >= b.End)
		{
			NumOverlaps++;
		}
		else if(b.Begin <= a.Begin && b.End >= a.End)
		{
			NumOverlaps++;
		}
	}
	SHOW_RESULT(NumOverlaps);
}

#endif