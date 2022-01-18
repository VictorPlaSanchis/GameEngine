#include <iostream>
#include <vector>

class Component {

public:

    Component() {}
	
	void foo() { std::cout << "ComponentBehaviour" << std::endl; }
	
	virtual void behaviour() {}

};

class PhysicsBehaviour : public Component {
  
public:

    PhysicsBehaviour() { }
    
    void behaviour() override {
        std::cout << "PhysicsBehaviour" << std::endl;
    }
    
};

class RenderBehaviour : public Component {
    
public:

    RenderBehaviour() {}
    
    void behaviour() override {
        std::cout << "RenderBehaviour" << std::endl;
    }
    
};

class Object {
    
public:

    Object() { }
    
    std::vector<Component*> components;
    
    void addComponent(Component* c) {
        components.push_back(c);
    }
    
    void update() {
        
        std::cout << "Updating object..." << std::endl;
        
        for(auto component : components) {
            component->behaviour();
        }
    }
    
};

int main() {
    
    PhysicsBehaviour a = PhysicsBehaviour();
    RenderBehaviour r = RenderBehaviour();
    
    Object myObj = Object();
    myObj.addComponent(&a);
    myObj.addComponent(&r);
    myObj.update();
    
    return 0;
}
