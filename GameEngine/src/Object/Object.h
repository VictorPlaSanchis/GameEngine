#pragma once
#include "Component.h"
#include "Transform.h"
#include "./Components/Model.h"
#include <typeinfo>
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
            else ConsoleError("Cant add this component...");
        }
        template <class C>
        C* addComponent() {
            if (std::is_base_of<Component, C>::value) {
                C* newComponent = new C();
                this->components.push_back(newComponent);
                if (std::is_base_of<Model, C>::value) {
                    Model* newModel = newComponent;
                    newModel->setTransform(this->transform);
                    return newModel;
                } else return newComponent;
            }
            else Console::debug("Cant add this component...", Console::COLOR::RED, Console::SENDER::APPLICATION);
        }
        template <class C>
        C* getComponent() {
            for (Component* component : this->components) {
                if (typeid(C) == typeid(*component)) {
                    // static_cast used to avoid compilation type error, it is safe for the programmer but not for the compiler, needed
                    return static_cast<C*>(component);
                }
            }
            return nullptr;
        }
        template <class C>
        std::vector<C*> getComponents() {
            std::vector<C*> components;
            for (Component* component : this->components) {
                if (typeid(C) == typeid(*component)) {
                    // static_cast used to avoid compilation type error, it is safe for the programmer but not for the compiler, needed
                    components.push_back(static_cast<C*>(component));
                }
            }
            return components;
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
