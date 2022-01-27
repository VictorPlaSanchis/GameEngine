#pragma once
#include "Component.h"
#include <list>

namespace vge {

    class Object {

    private:

        std::list<Object*> childs;
        std::list<Component*> components;

    public:

        Object();
        ~Object();

        void addComponent(Component* component);
        void removeComponent(Component* component);
        void addChild(Object* child);
        void removeChild(Object* child);

        void Update();

    };

}

