# win32ini
header-only ini reader via win32 api using c++ with unicode support

There are two available classes. `win32iniA` and `win32iniW`:
```cpp
using win32iniA = win32ini<std::string, char>;
using win32iniW = win32ini<std::wstring, wchar_t>;
```

How to use it:
```cpp
std::map<std::wstring, std::map<std::wstring, std::wstring>> translations;
std::wstring iniPathW = GetIniPathW(); // absolute path of the .ini

// you may properly need to allow unicode in your console to properly display the values
auto wi = win32iniW(iniPathW);
auto& map = wi.GetMap();
for (auto& section : map)
{
	std::wcout << "section " << section.first << '\n';
	for (auto& key : section.second)
	{
		std::wcout << "key " << key.first << '\n';
		translations[section.first][key.first] = key.second;
		std::wcout << "translations[" << section.first << "][" << key.first << "] = " << key.second << '\n';
	}
}
```
