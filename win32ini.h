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

#include <map>
#include <string>
#include <vector>

#include "windows.h"

#define WIN32INI_MAX 65535

#ifdef UNICODE
#define win32ini  win32iniW
#else
#define win32ini  win32iniA
#endif

class win32iniA
{
public:
	using iniKey = std::vector<std::string>;
	using iniMap = std::map<std::string, std::map<std::string, std::string>>;

	std::string m_iniPath;
	iniMap m_iniMap;

	win32iniA(std::string iniPathA)
	{
		m_iniPath = iniPathA;
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

	const std::string GetValue(const std::string& section, const std::string& key)
	{
		char _buffer[WIN32INI_MAX];
		GetPrivateProfileStringA(section.c_str(), key.c_str(), "UNK", _buffer, WIN32INI_MAX, m_iniPath.c_str());
		return std::string(_buffer);
	}

	const iniKey GetSections()
	{
		std::vector<char> _buffer(WIN32INI_MAX);
		GetPrivateProfileStringA(nullptr, nullptr, "UNK", _buffer.data(), _buffer.size(), m_iniPath.c_str());
		iniKey sections;
		std::string word;
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

	const iniKey GetKeys(const std::string& section)
	{
		std::vector<char> _buffer(WIN32INI_MAX);
		GetPrivateProfileStringA(section.c_str(), nullptr, "UNK", _buffer.data(), _buffer.size(), m_iniPath.c_str());
		iniKey keys;
		std::string word;
		for (auto& c : _buffer)
		{
			if (c)
				word += c;
			else
			{
				if (word.empty())
					break;
				keys.push_back(word);
				word.clear();
			}
		}
		return keys;
	}
};

class win32iniW
{
public:
	using iniKey = std::vector<std::wstring>;
	using iniMap = std::map<std::wstring, std::map<std::wstring, std::wstring>>;

	std::wstring m_iniPath;
	iniMap m_iniMap;

	win32iniW(std::wstring iniPathW)
	{
		m_iniPath = iniPathW;
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

	const std::wstring GetValue(const std::wstring& section, const std::wstring& key)
	{
		wchar_t _buffer[WIN32INI_MAX];
		GetPrivateProfileStringW(section.c_str(), key.c_str(), L"UNK", _buffer, WIN32INI_MAX, m_iniPath.c_str());
		return std::wstring(_buffer);
	}

	const iniKey GetSections()
	{
		std::vector<wchar_t> _buffer(WIN32INI_MAX);
		GetPrivateProfileStringW(nullptr, nullptr, L"UNK", _buffer.data(), _buffer.size(), m_iniPath.c_str());
		iniKey sections;
		std::wstring word;
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

	const iniKey GetKeys(const std::wstring& section)
	{
		std::vector<wchar_t> _buffer(WIN32INI_MAX);
		GetPrivateProfileStringW(section.c_str(), nullptr, L"UNK", _buffer.data(), _buffer.size(), m_iniPath.c_str());
		iniKey keys;
		std::wstring word;
		for (auto& c : _buffer)
		{
			if (c)
				word += c;
			else
			{
				if (word.empty())
					break;
				keys.push_back(word);
				word.clear();
			}
		}
		return keys;
	}
};

