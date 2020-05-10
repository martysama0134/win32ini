#include "win32ini.h"

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

int main()
{
	// don't forget GetCurrentDirectory requires the full path of the ini file. NOT THE LOCAL ONES!
	auto & iniPathA = GetIniPathA();
	auto ai = win32iniA(iniPathA);
	auto& ra = ai.GetMapA();

	auto & iniPathW = GetIniPathW();
	auto wi = win32iniW(iniPathW);
	auto& rw = wi.GetMapW();
	return 0; // add a breakpoint here and check the local variables
}
