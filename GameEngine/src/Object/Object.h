#pragma once
#include "Component.h"
#include "Transform.h"
#include <list>

#include "../Log/Console.h"

namespace vge {

    class Object {

    public:

        Object();
        ~Object();

        Transform* transform;
        std::list<Object*> childs;
        std::list<Component*> components;

        template <class C, typename Args>
        C* addComponent(Args& args...) {
            if (std::is_base_of<Component, C>::value) {
                C* newComponent = new C(args);
                this->components.push_back(newComponent);
                return newComponent;
            }
            else Console::debug("Cant add this component...", Console::COLOR::RED, Console::SENDER::APPLICATION);
        }
        template <class C>
        C* addComponent() {
            if (std::is_base_of<Component, C>::value) {
                C* newComponent = new C();
                this->components.push_back(newComponent);
                return newComponent;
            }
            else Console::debug("Cant add this component...", Console::COLOR::RED, Console::SENDER::APPLICATION);
        }
        void removeComponent(Component* component);
        void addChild(Object* child);
        void removeChild(Object* child);

        virtual void Update() = 0;

    };

}

#define LEFT Vector<float, 3> ({ -1.0f,  0.0f, 0.0f })
#define RIGHT Vector<float, 3>({  1.0f,  0.0f, 0.0f })
#define UP Vector<float, 3>   ({  0.0f,  1.0f, 0.0f })
#define DOWN Vector<float, 3> ({  0.0f, -1.0f, 0.0f })
