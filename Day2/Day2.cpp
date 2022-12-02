#define ADVANCED 1
#define TEST 0
#include "../Headers/AOC.h"

#if ADVANCED

std::map<char, unsigned int> Values =
{
	std::pair('A', 1),
	std::pair('B', 2),
	std::pair('C', 3)
};

std::map<char, std::map<char, char>> Matches =
{
	std::pair('A', std::map({ std::pair('X', 'C'), std::pair('Y', 'A'), std::pair('Z', 'B') })),
	std::pair('B', std::map({ std::pair('X', 'A'), std::pair('Y', 'B'), std::pair('Z', 'C') })),
	std::pair('C', std::map({ std::pair('X', 'B'), std::pair('Y', 'C'), std::pair('Z', 'A') })),
};

std::map<char, unsigned int> MatchResultValues =
{
	std::pair('X', 0),
	std::pair('Y', 3),
	std::pair('Z', 6)
};

int main()
{
	unsigned int TotalScore = 0;
	auto Input = LoadInputFile();
	while (!Input.eof())
	{
		std::string Commands[2];
		Input >> Commands[0];
		Input >> Commands[1];

		// This "funny" looking line calculates the value of the move we are going to take
		TotalScore += Values[Matches[Commands[0][0]][Commands[1][0]]]; 
		TotalScore += MatchResultValues[Commands[1][0]]; // Then add the score for the result of the match
	}

	SHOW_RESULT(TotalScore);
}

#else

std::map<char, unsigned int> Values =
{
	std::pair('X', 1),
	std::pair('Y', 2),
	std::pair('Z', 3)
};

std::map<char, char> Matches =
{
	std::pair('A', 'Y'),
	std::pair('B', 'Z'),
	std::pair('C', 'X')
};

std::map<char, char> Equivalents =
{
	std::pair('A', 'X'),
	std::pair('B', 'Y'),
	std::pair('C', 'Z')
};


int main()
{
	unsigned int TotalScore = 0;
	auto Input = LoadInputFile();
	while (!Input.eof())
	{
		std::string Commands[2];
		Input >> Commands[0];
		Input >> Commands[1];
		TotalScore += Values[Commands[1][0]];
		bool IsDraw = Equivalents[Commands[0][0]] == Commands[1][0];
		TotalScore += (Matches[Commands[0][0]] == Commands[1][0]) ? 6 : (3 * IsDraw);
	}

	SHOW_RESULT(TotalScore);
}

#endif