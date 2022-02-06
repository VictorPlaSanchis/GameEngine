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

	};


}


