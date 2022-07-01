#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace vge {

	class ImGuiController
	{

	private:

		unsigned short IM_GUI_WINDOWS;
		void VersionWindow();
		void ProjectDirectoryWindow();

	public:

		ImGuiController();
		~ImGuiController();

		static ImGuiController* get();

		void Init();
		void Run();

	};

#define ImGuiControllerVGE (*(ImGuiController::get()))

}