#pragma once
#include "Component.h"
#include "Transform.h"
#include <list>

namespace vge {

    class Object {

    public:

        Object();
        ~Object();

        Transform* transform;
        std::list<Object*> childs;
        std::list<Component*> components;

        void addComponent(Component* component);
        void removeComponent(Component* component);
        void addChild(Object* child);
        void removeChild(Object* child);

        void Update();



    };

}

