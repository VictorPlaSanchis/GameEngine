#pragma once
#include "Component.h"

class ExampleComponent : public Component
{

private:

	int value;

public:

	ExampleComponent();
	~ExampleComponent();

	virtual void Behaviour() override;

};

