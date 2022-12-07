#define TEST 0
#define ADVANCED 1
#include "../Headers/AOC.h"

// Files can be folders by containing 'SubDirectories'
struct File
{
	std::string Name;
	size_t Size = 0;
	std::vector<File> SubDirectories;
};

size_t UsedSize = 0;
std::vector<size_t> CurrentDirectory; // The path to the current directory from root
std::vector<File> Files;
size_t UpdateSize = 30000000ull;
size_t FileSystemSize = 70000000ull;

std::vector<File*> Folders;

File* GetDirectory(std::vector<size_t> dir)
{
	if (!dir.size()) return nullptr;
	File* File = &Files[dir[0]];
	dir.erase(dir.begin(), dir.begin() + 1);
	for (auto i : dir)
	{
		File = &File->SubDirectories.at(i);
	}
	return File;
}

std::vector<File>& GetContentOfDirectory(std::vector<size_t> dir)
{
	std::vector<File>* vec = &Files;
	for (auto i : dir)
	{
		vec = &vec->at(i).SubDirectories;
	}
	return *vec;
}

void CalculateDirectorySize(std::vector<size_t> Directory, size_t Depth)
{
	size_t TotalDirectorySize = 0;
	size_t FileIndex = 0;
	for (auto& f : GetContentOfDirectory(Directory))
	{
		if (f.SubDirectories.size())
		{
			auto NewVector = Directory;
			NewVector.push_back(FileIndex);
			CalculateDirectorySize(NewVector, Depth + 1);
		}
		TotalDirectorySize += f.Size;
		FileIndex++;
	}
	auto CurrentDirectory = GetDirectory(Directory);
	if (CurrentDirectory)
	{
		CurrentDirectory->Size = TotalDirectorySize;
	}
#if !ADVANCED
	if (TotalDirectorySize < 100000) UsedSize += TotalDirectorySize;
#else
	// Deleting root might be a bad idea
	if (CurrentDirectory)
	{
		Folders.push_back(CurrentDirectory);
	}
#endif
}

void PrintDirectory(std::vector<size_t> Directory, size_t Depth)
{

	size_t FileIndex = 0;
	for (auto& f : GetContentOfDirectory(Directory))
	{
		for (size_t i = 0; i < Depth; i++)
		{
			std::cout << ((i == Depth - 1) ? (f.SubDirectories.size() ? "[+]-[" : " |-> ") : " |  ");
		}
		if (f.SubDirectories.size())
		{
			std::cout << f.Name << "]" << " (Size = " << f.Size << ")" << std::endl;
			auto NewVector = Directory;
			NewVector.push_back(FileIndex);
			PrintDirectory(NewVector, Depth + 1);
		}
		else
		{
			std::cout << f.Name << " (Size = " << f.Size << ")" << std::endl;
		}
		FileIndex++;
	}
}

int main()
{
	auto InFile = LoadInputFile();

	while (!InFile.eof())
	{
		std::string CurrentLine = GetNextLine(InFile);
		if (CurrentLine.empty()) continue;
		if (CurrentLine.substr(0, 6) == "$ cd /")
		{
			CurrentDirectory.clear();
		}
		else if (CurrentLine.substr(0, 7) == "$ cd ..")
		{
			CurrentDirectory.pop_back();
		}
		else if (CurrentLine.substr(0, 4) == "$ cd")
		{
			auto& OpenedDirectory = GetContentOfDirectory(CurrentDirectory);
			OpenedDirectory.push_back(File(CurrentLine.substr(5), 0));
			CurrentDirectory.push_back(OpenedDirectory.size() - 1);
		}
		else if (CurrentLine.substr(0, 1) != "$" && CurrentLine.substr(0, 3) != "dir")
		{
			std::string FileInfo[2];
			std::stringstream LineStream;
			LineStream << CurrentLine;
			LineStream >> FileInfo[0];
			LineStream >> FileInfo[1];

			try
			{
				GetContentOfDirectory(CurrentDirectory).push_back(File(FileInfo[1], std::stoul(FileInfo[0])));
			}
			catch (std::exception& e)
			{
				std::cout << "Error while parsing: " << e.what() << " probably related to the number " << FileInfo[0] << " > " << ULONG_MAX << std::endl;
				std::cout << "Line: " << CurrentLine << std::endl;
				exit(0);
			}
		}
	}
	
	CalculateDirectorySize({}, 1);

	std::cout << "[/]" << std::endl;
	PrintDirectory({}, 1);
	
	std::cout << std::endl << std::endl;
#if !ADVANCED
	SHOW_RESULT(UsedSize);
#else
	size_t RootSize = 0;
	for (auto& f : Files)
	{
		RootSize += f.Size;
	}

	std::set<size_t> PossibleDirectories;
	size_t UnusedSize = FileSystemSize - RootSize;
	size_t RequiredSize = UpdateSize - UnusedSize;
	std::cout << " ____________________________________________" << std::endl;
	std::cout << " |Root size " << RootSize << std::endl;
	std::cout << " |Minimum size a file must have: " << RequiredSize << std::endl << std::endl;
	std::cout << "Possible results (root not included): " << std::endl;
	for (auto* f : Folders)
	{
		if (f->Size > RequiredSize)
		{
			std::cout << "    [" << f->Name << "] with a size of " << f->Size << std::endl;
			PossibleDirectories.insert(f->Size);
		}
	}
	std::cout << std::endl;
	SHOW_RESULT(*PossibleDirectories.begin());
#endif
}