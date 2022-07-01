#pragma once

namespace vge {

#define GE_MOUSE_LEFT_BUTTON 0
#define GE_MOUSE_RIGHT_BUTTON 1
#define GE_MOUSE_WHEEL_BUTTON 2
#define GE_MOUSE_BACK_AUX_BUTTON 3
#define GE_MOUSE_FRONT_AUX_BUTTON 4


	class InputSystem
	{

	private:

		unsigned char lastKeyState[256] = {};
		unsigned char keyState[256] = {};
		unsigned char lastMouseState[5] = {};
		unsigned char mouseState[5] = {};

	public:

		InputSystem();
		~InputSystem();

		static InputSystem* get();

		void Update();
		void Init();

		bool isKeyPressed(int keyCode);
		bool isKeyDown(int keyCode);
		bool isKeyReleased(int keyCode);
		bool isMouseDown(int keyCode);
		bool isMousePressed(int keyCode);
		bool isMouseReleased(int keyCode);
		int getMousePosX();
		int getMousePosY();

	};

#define InputSystemVGE (*(InputSystem::get()))

}