//
// Created by Julian  on 27/02/16.
//

#ifndef LOG_UTILITY_H
#define LOG_UTILITY_H

#include <string>
#include <iostream>
#include <time.h>

using namespace std; 

namespace LogUtility
{
	static void Log(string message)
	{
		string currentTime; 
		cout << currentTime << ": " << message << endl; 
	}
};

#endif // LOG_UTILITY_H