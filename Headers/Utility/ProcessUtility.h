//
// Created by Julian  on 17/07/2016.
//

#ifndef PROCESS_UTILITY_H
#define PROCESS_UTILITY_H

#include <string>

#ifdef __APPLE__
    #include <sys/param.h>
    #include <unistd.h>
#endif // __APPLE__

#ifdef _WIN32
	#include <Windows.h>
	#include <direct.h>
	#define GetCurrentDir _getcwd
#endif

using namespace std;

namespace ProcessUtility
{
    static string CurrentApplicationDirectory()
    {
#ifdef __APPLE__

        char* buffer;
        buffer = new char[MAXPATHLEN];
        getcwd(buffer, MAXPATHLEN);

        if (buffer != nullptr) {
            string path(buffer);
            delete[] buffer;
            return path;
        } else {
            return "";
        }

#endif // __APPLE__

#ifdef _WIN32
		char currentPath[FILENAME_MAX];
		if (!GetCurrentDir(currentPath, sizeof(currentPath))) {
			
			// error
			return string("");
		}

		string workingDir(currentPath);
        return workingDir;
#endif
    }

};

#endif // PROCESS_UTILITY_H
