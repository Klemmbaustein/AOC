#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <set>
#include <map>
#include <vector>

#if TEST
const bool IS_TEST = true;
#else
const bool IS_TEST = false;
#endif

#define SHOW_RESULT(result) std::cout << "Result: " << result << std::endl // Is this really necessary? No.

std::ifstream LoadInputFile()
{
	std::string InputFile = IS_TEST ? "TestInput.in" : "Input.in";
	if (!std::filesystem::exists(InputFile))
	{
		std::cout << "Error: Input file does not exist." << std::endl;
		throw "Input read failure";
	}
	return std::ifstream(InputFile);
}

int GetNextInt(std::ifstream& Stream)
{
	char Line[64];
	Stream.getline(Line, 64);
	return std::stoi(Line);
}

std::string GetNextLine(std::ifstream& Stream, unsigned int MaxLineSize = 64)
{
	char* Line = new char[MaxLineSize + 1];
	Stream.getline(Line, MaxLineSize);
	Line[MaxLineSize] = '\0';
	std::string LineString = Line;
	delete[] Line;
	return LineString;
}