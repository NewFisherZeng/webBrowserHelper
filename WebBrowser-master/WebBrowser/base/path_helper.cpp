#include "stdafx.h"
#include "path_helper.h"
std::wstring GetAppPath() {
	std::wstring sPath;
	sPath.resize(MAX_PATH);
	::GetModuleFileName(GetModuleHandle(NULL), (LPTSTR)sPath.c_str(), MAX_PATH);
	int index = sPath.find_last_of(L'\\');
	if (index >= 0) sPath = sPath.substr(0, index);
	return sPath;
}