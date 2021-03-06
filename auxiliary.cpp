#include "auxiliary.h"
#include <windows.h>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

void GetAllFolders(const string& path, std::vector<string> &folderList) {
	HANDLE handle;
	WIN32_FIND_DATAA fileData;

	if ((handle = FindFirstFileA((path + "/*.*").c_str(), &fileData)) == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			continue;
		const string dir_name = fileData.cFileName;
		if (dir_name.data()[0] == '.')// || dir_name == "..")
			continue;
		const string full_file_name = path + "/" + dir_name;
		folderList.push_back(full_file_name);
	} while (FindNextFileA(handle, &fileData));
	FindClose(handle);
}

void GetFilesInFolder(const string& dirPath, std::vector<string> &filesList, const char* ext)
{
    HANDLE handle;
    WIN32_FIND_DATAA fileData;

    if ((handle = FindFirstFileA((dirPath + "/*." + ext).c_str(), &fileData)) == INVALID_HANDLE_VALUE)
	{
    	return; 
		
	}
    do 
	{
    	const string file_name = fileData.cFileName;
    	const string full_file_name = dirPath + "/" + file_name;
		filesList.push_back(full_file_name);
    } 
	while (FindNextFileA(handle, &fileData));
    FindClose(handle);
}

void InitRandomBoolVector(vector<bool>& mask, double prob)
{
	RNG rng = theRNG();
	for (size_t i = 0; i < mask.size(); i++)
	{
		mask[i] = (rng.uniform(0.0, 1.0) < prob) ? true : false;
	}
}