#ifndef FILE_UTILITY_H
#define FILE_UTILITY_H

#include <string>
#include <list>

#ifdef __APPLE__
    #include <sys/param.h>
	#include <sys/stat.h>
    #include <unistd.h>
	#include <dirent.h>
#endif // __APPLE__

#ifdef _WIN32
	#include <Windows.h>
	#include "Shlwapi.h"
#endif

using namespace std;

namespace FileUtility
{
	//--------------------------------------------------------------------- 
	// Name: StringEndsWith
	// Desc: 
	//---------------------------------------------------------------------
	// TODO: this shouldn't be here
	static bool StringEndsWith(const string& str, const string& end)
	{
		if (str.length() < end.length()) {
			return false; 
		}

		return std::equal(str.end() - end.length(), str.end(), end.begin());
	}

	//-------------------------------------------------------------------------------------------
	// Name: DirectoryContents
	// Desc: 
	//-------------------------------------------------------------------------------------------
	static list<string> DirectoryContents(const string& directory, const string& extension = "")
	{
		
		list<string> files;
#ifdef __APPLE__
		auto dir = opendir(directory.c_str()); 

		if (dir != nullptr) {

			dirent* ep;
			while(ep = readdir(dir)) {
				files.push_back(string(ep->d_name)); 
			}

			closedir(dir); 
		}
#endif 
		
#ifdef _WIN32
		// TODO: implement

#endif
		if (!extension.empty()) {
			files.remove_if([extension](const string& file) {return !StringEndsWith(file, extension); });
		}
		
		return files; 
	}

	//-------------------------------------------------------------------------------------------
	// Name: DirectoryExists
	// Desc: 
	//-------------------------------------------------------------------------------------------
	static bool DirectoryExists(const string& dir)
	{
#ifdef __APPLE__
		
		struct stat sb;
		if (stat(dir.c_str(), &sb) == 0) {
			return S_ISDIR(sb.st_mode); 
		}

		return false; 
#endif

#ifdef _WIN32
	DWORD ftyp = GetFileAttributesA(dir.c_str()); 
	if (ftyp == INVALID_FILE_ATTRIBUTES) {
		return false; 
	}

	if(ftyp & FILE_ATTRIBUTE_DIRECTORY) {
		return true; 
	}

	return false; 
#endif
	}

	//-------------------------------------------------------------------------------------------
	// Name: FileExists
	// Desc: 
	//-------------------------------------------------------------------------------------------
#ifdef __APPLE__
	static bool FileExists(const string& filename) 
	{
		struct stat sb;
		return (stat(filename.c_str(), &sb) == 0); 
	}
#endif	

#ifdef _WIN32
	static bool FileExists(string path)
	{

		return PathFileExists(path.c_str());

	}
#endif

}

#endif // FILE_UTILITY_H
