#ifndef C_COMPONENT_COLLECTION_H
#define C_COMPONENT_COLLECTION_H

#include "Components/Repository/ComponentCollectionIterator.h"
#include "Components/Repository/IComponentContainer.h"
#include "Components/BaseComponent.h"

#include <list>
#include <memory>
#include <type_traits>
#include <vector>
#include <cassert>

using namespace std; 

namespace Repository 
{
    class IComponentCollection 
    {
    public:

        virtual unsigned int Size() = 0; 
        virtual ~IComponentCollection() {}
    };

    template<typename T, typename U>
    class ComponentCollection : public IComponentCollection
    {
        list<weak_ptr<vector<T>>> components; 
        
        weak_ptr<vector<T>> lastAccessed; 
        unsigned int lastOffset; 
        unsigned int lastOffsetMax; 
 
    public:

        ComponentCollection() 
            : lastOffset(0), lastOffsetMax(0)
        {}

        ComponentCollection(list<weak_ptr<vector<T>>> addComponents) 
            : components(addComponents), lastOffset(0), lastOffsetMax(0)
        {}

        ComponentCollection(const ComponentContainer<T>& componentContainer)
            : ComponentCollection()
        {
            this->Append(componentContainer.components);
        }       
        //-------------------------------------------------------------------------------
        // Name: Constructor 
        // Desc:
        //-------------------------------------------------------------------------------
        ComponentCollection(const weak_ptr<vector<T>>& addComponents) 
            : lastOffset(0), lastOffsetMax(0)
        {
            if (auto a = addComponents.lock()) {
                this->components.push_back(addComponents);         
            }
        }       
        //-------------------------------------------------------------------------------
        // Name: Append
        // Desc: append a vector of components
        //-------------------------------------------------------------------------------
        void Append(const shared_ptr<vector<T>>& appendComponents) 
        {
            this->components.push_back(appendComponents); 
        }
        //-------------------------------------------------------------------------------
        // Name: Append
        // Desc: append a container
        //-------------------------------------------------------------------------------
        void Append(ComponentContainer<T> componentContainer)
        {
            this->Append(componentContainer.components); 
        }
        //-------------------------------------------------------------------------------
        // Name: Append
        // Desc: append another collection
        //-------------------------------------------------------------------------------
        void Append(Repository::ComponentCollection<T>& componentCollection)
        {
            for(auto collection : componentCollection.components) {
                
                // We can assume they're not empty
                this->components.push_back(collection);     
            }
        }
        //-------------------------------------------------------------------------------
        // Name: Size 
        // Desc:
        //-------------------------------------------------------------------------------
        unsigned int Size() override final
        {
            unsigned int counter = 0; 

            for (auto vec : this->components) {
                if (auto v = vec.lock()) {
                    counter += v->size();
                    
                } else {

                    // drop from components
                    this->components.remove_if(
                    [vec] (const weak_ptr<vector<T>>& v) {
                        
                        if (auto a = vec.lock()) { 
                            if (auto b = v.lock()) {
                                return a == b;
                            } 
                        } 

                        return false; 
                    }); 

                    // if the one we removed is the cached
                }
            }

            return counter; 
        }
        //-------------------------------------------------------------------------------
        // Name: operator[] 
        // Desc:
        //-------------------------------------------------------------------------------
        T& operator[](unsigned int index)
        {
            assert(index < this->Size());
            auto offset = 0; 

            // Try access the last cached one. 
            if (index > this->lastOffset && index < this->lastOffsetMax) {
                if (auto v = this->lastAccessed.lock()) {
                    return (*v)[index - this->lastOffset]; 
                }    
            }
            
            // Linear but I think this is ok since I wouldn't expect the list to be very large
            for(auto vec : this->components) {
                if (auto v = vec.lock()) {
                    if (index >= v->size()) {
                        index -= v->size();
                        offset += v->size(); 

                    } else {

                        this->lastOffset = offset;
                        this->lastOffsetMax = offset + v->size();  
                        this->lastAccessed = vec; 
                        return (*v)[index];
                    }
                }
            }
        }
        //---------------------------------------------------------------------------------
        // Name: empty
        // Desc:
        //---------------------------------------------------------------------------------
        bool empty()
        {
            if (!this->components.empty()) {
                for (auto container : this->components) {
                    if (auto c = container.lock()) {
                        // As soon as we find one that isn't empty we can return true. 
                        if (!(*c).empty()) {
                            return false;
                        }
                    }
                }
            }

            return true; 
        }
        //---------------------------------------------------------------------------------
        // Name: front
        // Desc:
        //---------------------------------------------------------------------------------
        T& front()
        {
            auto firstContainer = components.front(); 
            auto front = firstContainer.lock();
        
            return (*front).front();
        }
        //---------------------------------------------------------------------------------
        // Name: back
        // Desc:
        //---------------------------------------------------------------------------------
        T& back()
        {
            auto backContainer = components.back();
            auto back = backContainer.lock();

            return (*back).back(); 
        }
        //---------------------------------------------------------------------------------
        // Name: begin
        // Desc:
        //---------------------------------------------------------------------------------
        ComponentCollectionIterator<T> begin()
        {
            if (this->empty()) {
                return this->end();
            }

            return ComponentCollectionIterator<T>(this); 
        }
        //---------------------------------------------------------------------------------
        // Name: end
        // Desc:
        //---------------------------------------------------------------------------------
        ComponentCollectionIterator<T> end()
        {
            return ComponentCollectionIterator<T>(nullptr); 
        }
        //---------------------------------------------------------------------------------
        // Name: 
        // Desc:
        //---------------------------------------------------------------------------------
        virtual ~ComponentCollection() {} 
    };
}


#endif // C_COMPONENT_COLLECTION_H