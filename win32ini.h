// MIT License

// Copyright (c) 2020 martysama0134

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE
#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "windows.h"

#define WIN32INI_MAX 65535
#define WIN32INI_FORCE_LOWER

template <class T, class V> class win32ini
{
public:
	using iniKey = std::vector<T>;
	using iniMap = std::map<T, std::map<T, T>>;

	T m_iniPath;
	iniMap m_iniMap;

	win32ini(const T iniPath)
	{
		m_iniPath = iniPath;
	}

	void ClearMap()
	{
		m_iniMap.clear();
	}

	const iniMap GetMap()
	{
		if (m_iniMap.empty())
		{
			auto& sections = GetSections();
			for (auto& section : sections)
			{
				auto& keys = GetKeys(section);
				for (auto& key : keys)
					m_iniMap[section][key] = GetValue(section, key);
			}
		}
		return m_iniMap;
	}

	const T GetValue(const T& section, const T& key)
	{
		V _buffer[WIN32INI_MAX];
		_GetPrivateProfileString(section.c_str(), key.c_str(), nullptr, _buffer, WIN32INI_MAX, m_iniPath.c_str());
		return T(_buffer);
	}

	const iniKey GetSections()
	{
		std::vector<V> _buffer(WIN32INI_MAX);
		_GetPrivateProfileString(nullptr, nullptr, nullptr, _buffer.data(), _buffer.size(), m_iniPath.c_str());
		iniKey sections;
		T word;
		for (auto& c : _buffer)
		{
			if (c)
				word += c;
			else
			{
				if (word.empty())
					break;
				sections.push_back(word);
				word.clear();
			}
		}
		return sections;
	}

	const iniKey GetKeys(const T& section)
	{
		std::vector<V> _buffer(WIN32INI_MAX);
		_GetPrivateProfileString(section.c_str(), nullptr, nullptr, _buffer.data(), _buffer.size(), m_iniPath.c_str());
		iniKey keys;
		T word;
		for (auto& c : _buffer)
		{
			if (c)
				word += c;
			else
			{
				if (word.empty())
					break;
#ifdef WIN32INI_FORCE_LOWER
				ToLower(word);
#endif
				keys.push_back(word);
				word.clear();
			}
		}
		return keys;
	}

	void ToLower(T& word);

	int _GetPrivateProfileString(
		const V* lpAppName,
		const V* lpKeyName,
		const V* lpDefault,
		V* lpReturnedString,
		DWORD nSize,
		const V* lpFileName);
};

using win32iniA = win32ini<std::string, char>;
using win32iniW = win32ini<std::wstring, wchar_t>;

template <> inline void win32ini<std::string, char>::ToLower(std::string& word)
{
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
}

template <> inline void win32ini<std::wstring, wchar_t>::ToLower(std::wstring& word)
{
	std::transform(word.begin(), word.end(), word.begin(), ::towlower);
}

template <> inline int win32ini<std::string, char>::_GetPrivateProfileString(
	const char* lpAppName,
	const char* lpKeyName,
	const char* lpDefault,
	char* lpReturnedString,
	DWORD nSize,
	const char* lpFileName)
{
	return GetPrivateProfileStringA(lpAppName, lpKeyName, lpDefault ? lpDefault : "", lpReturnedString, nSize, lpFileName);
}

template <> inline int win32ini<std::wstring, wchar_t>::_GetPrivateProfileString(
	const wchar_t* lpAppName,
	const wchar_t* lpKeyName,
	const wchar_t* lpDefault,
	wchar_t* lpReturnedString,
	DWORD nSize,
	const wchar_t* lpFileName)
{
	return GetPrivateProfileStringW(lpAppName, lpKeyName, lpDefault ? lpDefault : L"", lpReturnedString, nSize, lpFileName);
}
