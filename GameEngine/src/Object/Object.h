#pragma once
#include "Component.h"
#include <list>

class Object {

private:

    std::list<Component*> components;

public:

    Object();
    ~Object();

    void addComponent(Component* component);
    void removeComponent(Component* component);
    void Update();

};

