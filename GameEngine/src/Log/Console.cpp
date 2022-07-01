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

	void Console::testConsole() 
	{
		ConsoleDebug("ConsoleDebug",WHITE);
		ConsoleDebugS("ConsoleDebugS",WHITE,AUXILIAR);
		ConsoleLog("ConsoleLog");
		ConsoleLogS("ConsoleLogS",AUXILIAR);
		ConsoleWarning("ConsoleWarning");
		ConsoleWarningS("ConsoleWarningS", AUXILIAR);
		ConsoleError("ConsoleError");
		ConsoleErrorS("ConsoleErrorS", AUXILIAR);
		ConsoleDebug("ConsoleDebugWhite", WHITE);
		ConsoleDebugS("ConsoleDebugSWhite", WHITE, AUXILIAR);
		ConsoleDebug("ConsoleDebugYellow", YELLOW);
		ConsoleDebugS("ConsoleDebugSYellow", YELLOW, AUXILIAR);
		ConsoleDebug("ConsoleDebugBlue", BLUE);
		ConsoleDebugS("ConsoleDebugSBlue", BLUE, AUXILIAR);
		ConsoleDebug("ConsoleDebugCyan", CYAN);
		ConsoleDebugS("ConsoleDebugSCyan", CYAN, AUXILIAR);
		ConsoleDebug("ConsoleDebugGreen", GREEN);
		ConsoleDebugS("ConsoleDebugSGreen", GREEN, AUXILIAR);
		ConsoleDebug("ConsoleDebugMagenta", MAGENTA);
		ConsoleDebugS("ConsoleDebugSMagenta", MAGENTA, AUXILIAR);
		ConsoleDebug("ConsoleDebugRed", RED);
		ConsoleDebugS("ConsoleDebugSRed", RED, AUXILIAR);
	}

	void Console::debug(std::string message, COLOR color, SENDER sender = Console::SENDER::AUXILIAR)
	{	
		double currentTime = glfwGetTime();
		std::cout << COLOR_VALUE[color] << "[" + std::to_string(currentTime) + "s] " << SENDER_VALUE[sender] + ": " + message + COLOR_VALUE[Console::WHITE] << std::endl;
	}

}
