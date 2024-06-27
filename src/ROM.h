#pragma once
#include <string>

class ROM
{
public:
	ROM();
	~ROM();
	bool LoadROMFromFile(const std::string path);
};