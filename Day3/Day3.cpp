#define TEST 0
#define ADVANCED 1
#include "../Headers/AOC.h"

int GetCharPriority(char Letter)
{
	if(Letter > 96 && Letter < 123) // ASCII range between the lowercase 'a' to 'z'
	{
		return Letter - 96; // Map their range to 1 - 26
	}
	if(Letter > 64 && Letter < 91) // ASCII range between the uppercase 'A' to 'Z'
	{
		return Letter - 38; // Map their range to 27 - 52
	}
	return 0;
}

#if ADVANCED

int main()
{
	int Priorities = 0;
	std::ifstream File = LoadInputFile();
	while (!File.eof())
	{
		std::string CurrentLines[3] = 
		{
			GetNextLine(File),
			GetNextLine(File),
			GetNextLine(File)
		};
		char CommonItemType = 0;
		for(char c : CurrentLines[0])
		{
			if(CurrentLines[1].find_first_of(c) != std::string::npos &&
			   CurrentLines[2].find_first_of(c) != std::string::npos)
			{
				CommonItemType = c;
				break;
			}
		}
		Priorities += GetCharPriority(CommonItemType);

	}
	SHOW_RESULT(Priorities);
}

#else


int main()
{
	int Priorities = 0;
	std::ifstream File = LoadInputFile();
	while (!File.eof())
	{
		std::string CurrentLine = GetNextLine(File);
		std::string SplitStrings[2] = 
		{
			CurrentLine.substr(0, CurrentLine.size() / 2),
			CurrentLine.substr(CurrentLine.size() / 2)
		};
		std::set<char> DuplicateChars; // So we do not evaluate a char twice

		for(char c : SplitStrings[0])
		{
			size_t FoundIndex = SplitStrings[1].find_first_of(c);
			if(FoundIndex != std::string::npos)
			{
				if(!DuplicateChars.contains(c))
				{
					DuplicateChars.insert(c);
					Priorities += GetCharPriority(c);
				}
			}
		}
	}
	SHOW_RESULT(Priorities);
}

#endif