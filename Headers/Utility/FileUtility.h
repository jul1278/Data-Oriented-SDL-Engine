#ifndef FILE_UTILITY_H
#define FILE_UTILITY_H

#include <string>
#include <list>

#ifdef __APPLE__
    #include <sys/param.h>
    #include <unistd.h>
	#include <dirent.h>
#endif // __APPLE__

#ifdef _WIN32
	#include <Windows.h>
#endif

using namespace std;

namespace FileUtility
{
	//--------------------------------------------------------------------- 
	// Name: StringEndsWith
	// Desc: 
	//---------------------------------------------------------------------
	static bool StringEndsWith(const string& str, const string& end)
	{
		if (str.length() < end.length()) {
			return false; 
		}

		return std::equal(str.end() - end.length(), str.end(), end.begin());
	}

	//-------------------------------------------------------------------------------------------
	// Name: StringEndsWith
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


}

#endif // FILE_UTILITY_H
