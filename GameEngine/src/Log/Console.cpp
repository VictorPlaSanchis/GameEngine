#include "Console.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace vge {

	std::map<Console::COLOR, std::string> Console::COLOR_VALUE = {
		{Console::RED, "\033[31m"},
		{Console::MAGENTA, "\033[35m"},
		{Console::BLUE, "\033[34m"},
		{Console::GREEN, "\033[32m"},
		{Console::WHITE, "\033[37m"},
		{Console::CYAN, "\033[36m"},
		{Console::YELLOW, "\033[33m"}
	};
	std::map<Console::SENDER, std::string> Console::SENDER_VALUE = {
		{Console::APPLICATION, "APP"},
		{Console::GRAPHICS_ENGINE, "GEL"},
		{Console::INPUT_SYSTEM, "ISL"},
		{Console::AUXILIAR, "AUX"},
		{Console::GUI, "GUI"}
	};

	Console::Console()
	{
	}

	Console::~Console()
	{
	}

	void Console::debug(std::string message, COLOR color, SENDER sender = Console::SENDER::AUXILIAR)
	{	
		double currentTime = glfwGetTime();
		std::cout << COLOR_VALUE[color] << "[" + std::to_string(currentTime) + "s] " << SENDER_VALUE[sender] + ": " + message + COLOR_VALUE[Console::WHITE] << std::endl;
	}



}
