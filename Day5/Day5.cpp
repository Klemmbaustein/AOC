#define TEST 0
#define ADVANCED 1
#include "../Headers/AOC.h"
#include <stack>
#include <sstream>

int main()
{
	std::map<int, std::vector<char>> Stacks;
	auto InputFile = LoadInputFile();
	std::string CurrentLine = GetNextLine(InputFile);
	size_t SquareBracket = CurrentLine.find_first_of('[');

	// if there is a '[' in our line, that means we're still reading the initial stack positions
	while (SquareBracket != std::string::npos)
	{
		for (int i = 0; i < CurrentLine.size(); i++)
		{
			// 65 - 90 are the uppercase letters in ASCII
			if (CurrentLine[i] > 64 && CurrentLine[i] < 91)
			{
				if (Stacks.contains(i / 4))
				{
					//insert new item onto existing stack
					Stacks[i / 4].push_back(CurrentLine[i]);
				}
				else
				{
					//Create a new stack
					Stacks.insert(std::pair(i / 4, std::vector<char>({ CurrentLine[i] })));
				}
			}
		}
		CurrentLine = GetNextLine(InputFile);
		SquareBracket = CurrentLine.find_first_of('[');
	}

	//the stacks will be in the wrong order (lowest item first, highest item last)
	for (auto& i : Stacks)
	{
		std::reverse(i.second.begin(), i.second.end());
	}

	// We dont care about the next line, so we skip it
	GetNextLine(InputFile);

	while (!InputFile.eof())
	{
		std::stringstream LineStream = std::stringstream(GetNextLine(InputFile));

		std::string LineSegments[6];
		for (auto& i : LineSegments)
		{
			LineStream >> i;
		}

		// move 3 from 2 to 1 
		//      ^      ^    ^
		//     [1]    [3]  [5]
		int Instruction[3] =
		{
			std::stoi(LineSegments[1]),
			std::stoi(LineSegments[3]) - 1, // arrays start at 0, but the indices in the instructions start at 1
			std::stoi(LineSegments[5]) - 1
		};
#if ADVANCED
		auto& Vec = Stacks[Instruction[1]];
		// create a new vector with the crates we want to transport
		std::vector<char> NewVector = std::vector<char>(
			Vec.begin() + std::max((int)Vec.size() - Instruction[0], 0),
			Vec.begin() + Vec.size()
		);
		// append that vector to the other stack
		Stacks[Instruction[2]].insert(Stacks[Instruction[2]].end(), NewVector.begin(), NewVector.end());
		// remove the old crates
		Vec.erase(Vec.begin() + std::max((int)Vec.size() - Instruction[0], 0),
			Vec.begin() + Vec.size());
#else
		for (int i = 0; i < Instruction[0]; i++)
		{
			// copy from stack 1 to 2
			Stacks[Instruction[2]].push_back(Stacks[Instruction[1]].at(Stacks[Instruction[1]].size() - 1));
			// then remove the item from stack 1
			Stacks[Instruction[1]].pop_back();
		}
#endif
	}

	for (auto i : Stacks)
	{
		std::cout << i.second.at(i.second.size() - 1) << std::endl;
	}
}

