#ifndef TYPE_UTILITY_H
#define TYPE_UTILITY_H

#include <typeinfo>
#include <string>
#include <cstdlib> // for free? lol

#ifdef __GNUC__
#include <cxxabi.h>
#endif

using namespace std;

namespace TypeUtility 
{

    //------------------------------------------------------------------------
    // Name: TypeName
    // Desc: return the demangled type name of given type_info
    //------------------------------------------------------------------------
    template<typename T>
    string TypeName() 
    {
        auto& typeInfo = typeid(T);

#ifdef __GNUC__
        int status; 
        auto demangled = abi::__cxa_demangle(typeInfo.name(), nullptr, nullptr, &status);
        auto demangledString = string(demangled);

        free(demangled);

        return demangledString;   
#endif

        // Apparently this is ok for clang and msvc
        return typeInfo.name();
    }
}

#endif // TYPE_UTILITY_H