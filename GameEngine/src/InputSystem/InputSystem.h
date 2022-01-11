#pragma once
#include "InputListener.h"
#include <map>

class InputSystem
{

protected:


private:

	std::map<InputListener*, InputListener*> m_listener_collection;

	unsigned char m_posible_keys[256] = {};
	unsigned char m_last_keys_state[256] = {};

public:

	InputSystem();
	~InputSystem();

	static InputSystem* get();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

};

