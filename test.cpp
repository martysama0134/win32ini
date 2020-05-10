#include "win32ini.h"
#include <iostream>
#include <fcntl.h>
#include <io.h>

const std::string GetIniPathA()
{
	char buffer[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, buffer);
	std::string iniPath(buffer);
	iniPath += "\\configA.ini";
	return iniPath;
}

const std::wstring GetIniPathW()
{
	wchar_t buffer[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, buffer);
	std::wstring iniPath(buffer);
	iniPath += L"\\configW.ini";
	return iniPath;
}

void PrintMapA(win32iniA::iniMap)
{
	std::string iniPathA = GetIniPathA();
	auto ai = win32iniA(iniPathA);
	auto& map = ai.GetMap();
	for (auto& section : map)
	{
		std::cout << "section " << section.first << '\n';
		for (auto& key : section.second)
		{
			//map[section][key] = key.second;
			std::cout << "map[" << section.first << "][" << key.first << "] = " << key.second << '\n';
		}
	}
}

void PrintMapW(win32iniW::iniMap)
{
	auto oldmode = _setmode(_fileno(stdout), _O_WTEXT); // windows console is not able to properly display unicode strings if you don't change mode and font
	std::wstring iniPathW = GetIniPathW();
	auto wi = win32iniW(iniPathW);
	auto& map = wi.GetMap();
	for (auto& section : map)
	{
		std::wcout << "section " << section.first << '\n';
		for (auto& key : section.second)
		{
			//map[section][key] = key.second;
			std::wcout << "map[" << section.first << "][" << key.first << "] = " << key.second << '\n';
		}
	}
	_setmode(_fileno(stdout), oldmode); // reset
}

int main()
{
	// don't forget GetCurrentDirectory requires the full path of the ini file. NOT THE LOCAL ONES!
	auto & iniPathA = GetIniPathA();
	auto ai = win32iniA(iniPathA);
	auto& ra = ai.GetMap();
	PrintMapA(ra);

	auto & iniPathW = GetIniPathW();
	auto wi = win32iniW(iniPathW);
	auto& rw = wi.GetMap();
	PrintMapW(rw);

	system("pause");
	return 0; // add a breakpoint here and check the local variables
}
