#include "win32ini.h"
#include <iostream>
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

void PrintMapA(win32iniA::iniMapA)
{
	std::string iniPathA = GetIniPathA();
	auto ai = win32iniA(iniPathA);
	auto& map = ai.GetMapA();
	for (auto& section : map)
	{
		std::cout << "section " << section.first << '\n';
		for (auto& value : section.second)
		{
			std::cout << "value " << value.first << '\n';
			//map[section][value] = value.second;
			std::cout << "map[" << section.first << "][" << value.first << "] = " << value.second << '\n';
		}
	}
}

void PrintMapW(win32iniW::iniMapW)
{
	std::wstring iniPathW = GetIniPathW();
	auto wi = win32iniW(iniPathW);
	auto& map = wi.GetMapW();
	for (auto& section : map)
	{
		std::wcout << "section " << section.first << '\n';
		for (auto& value : section.second)
		{
			std::wcout << "value " << value.first << '\n';
			//map[section][value] = value.second;
			std::wcout << "map[" << section.first << "][" << value.first << "] = " << value.second << '\n';
		}
	}
}

int main()
{
	// don't forget GetCurrentDirectory requires the full path of the ini file. NOT THE LOCAL ONES!
	auto & iniPathA = GetIniPathA();
	auto ai = win32iniA(iniPathA);
	auto& ra = ai.GetMapA();
	PrintMapA(ra);

	auto & iniPathW = GetIniPathW();
	auto wi = win32iniW(iniPathW);
	auto& rw = wi.GetMapW();
	PrintMapW(rw);

	system("pause");
	return 0; // add a breakpoint here and check the local variables
}
