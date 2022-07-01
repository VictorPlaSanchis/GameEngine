#pragma once
#include <map>
#include <string>

namespace vge {

	class Console
	{

	public:

		Console();
		~Console();

		enum COLOR {
			RED,
			MAGENTA,
			CYAN,
			BLUE,
			GREEN,
			YELLOW,
			WHITE,
		};

		enum SENDER {
			APPLICATION,
			GRAPHICS_ENGINE,
			INPUT_SYSTEM,
			AUXILIAR,
			GUI
		};

		static std::map<Console::COLOR, std::string> COLOR_VALUE;
		static std::map<Console::SENDER, std::string> SENDER_VALUE;

		static void debug(std::string message, COLOR color, SENDER sender);
		static void testConsole();

	};

#define ConsoleLogS(x,s) vge::Console::debug(x, Console::COLOR::WHITE, Console::SENDER::s);
#define ConsoleLog(x) vge::Console::debug(x, Console::COLOR::WHITE, Console::SENDER::APPLICATION);
#define ConsoleWarningS(x,s) vge::Console::debug(x, Console::COLOR::YELLOW, Console::SENDER::s);
#define ConsoleWarning(x) vge::Console::debug(x, Console::COLOR::YELLOW, Console::SENDER::APPLICATION);
#define ConsoleErrorS(x,s) vge::Console::debug(x, Console::COLOR::RED, Console::SENDER::s);
#define ConsoleError(x) vge::Console::debug(x, Console::COLOR::RED, Console::SENDER::APPLICATION);
#define ConsoleDebugS(x,c,s) vge::Console::debug(x, Console::COLOR::c, Console::SENDER::s);
#define ConsoleDebug(x,c) vge::Console::debug(x, Console::COLOR::c, Console::SENDER::APPLICATION);

}


