#include "ImGuiController.h"
#include "../GameEngine.h"
#include <string>

vge::ImGuiController::ImGuiController()
{
}

vge::ImGuiController::~ImGuiController()
{
}

vge::ImGuiController* vge::ImGuiController::get()
{
	static ImGuiController instance;
	return &instance;
}

void vge::ImGuiController::Init()
{

	// Setup Dear ImGui context
	ImGui::CreateContext();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(GameEngine::get()->getWindowGame(), true);
	ImGui_ImplOpenGL3_Init(std::stod((std::string)GameEngine::get()->getOpenGLversion()));

	// Setup Dear ImGui style
	ImGui::StyleColorsLight();

	IM_GUI_WINDOWS = 0b0000000000000011;

}

void vge::ImGuiController::VersionWindow() 
{

	ImGui::Begin("Version window");
	ImGui::Text("OpenGL version that is running:");
	ImGui::Text((const char*)glGetString(GL_VERSION));
	ImGui::End();

}

void vge::ImGuiController::ProjectDirectoryWindow()
{

	ImGui::Begin("Project directory");
	ImGui::Text("OpenGL running:");
	ImGui::Text((const char*)glGetString(GL_VERSION));
	ImGui::End();
	
}

void vge::ImGuiController::Run()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Window render selector
	if (IM_GUI_WINDOWS & 0b0000000000000001) VersionWindow();
	if (IM_GUI_WINDOWS & 0b0000000000000010) ProjectDirectoryWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
}
