#include "InputSystem.h"
#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

InputSystem* InputSystem::get()
{
	static InputSystem inputSystem;
	return &inputSystem;
}

void InputSystem::update()
{

	// SAVE THE ACTUAL STATE
	::memcpy(m_last_keys_state, m_posible_keys, sizeof(unsigned char) * 256);

	if (GetKeyboardState(m_posible_keys)) {

		for (int i = 0; i < 256; i++) {

			// ON KEY DOWN
			if (m_posible_keys[i] & 0x80) {

				std::map<InputListener*, InputListener*>::iterator it = m_listener_collection.begin();

				while (it != m_listener_collection.end()) {
					it->second->onKeyDown(i);
					++it;
				}

			}
			// ON KEY UP
			else {

				if (m_last_keys_state[i] != m_posible_keys[i]) {

					std::map<InputListener*, InputListener*>::iterator it = m_listener_collection.begin();

					while (it != m_listener_collection.end()) {
						it->second->onKeyUp(i);
						++it;
					}

				}

			}

		}

	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_listener_collection.insert(std::make_pair<InputListener*, InputListener*>(
		std::forward<InputListener*>(listener),
		std::forward<InputListener*>(listener)
	));
}

void InputSystem::removeListener(InputListener* listener)
{
	std::map<InputListener*, InputListener*>::iterator it = m_listener_collection.find(listener);
	if (it != m_listener_collection.end()) m_listener_collection.erase(it);

}
