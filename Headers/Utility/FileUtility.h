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
	static list<string> DirectoryContents(const string& directory)
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

#endif
		return files; 
	}


}

#endif // FILE_UTILITY_H
