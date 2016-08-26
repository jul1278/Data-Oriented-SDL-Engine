// CComponentCollectionFwd.h
#ifndef C_COMPONENT_COLLECTION_FWD_H
#define C_COMPONENT_COLLECTION_FWD_H

#include "Components/BaseComponent.h"

#include <type_traits>  

namespace Repository 
{
    template<typename T, typename U = typename std::enable_if<std::is_base_of<BaseComponent, T>::value>::type>
    class ComponentCollection;
}

#endif // C_COMPONENT_COLLECTION_FWD_H