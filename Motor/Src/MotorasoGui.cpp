#include "MotorasoGui.h"

MotorasoGui::MotorasoGui(Windows* window) 
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(window->GetWindowsPtr(), true);
	_window = window;
}

void MotorasoGui::UpdateMotorasoGui()
{
	ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
	ImGui::SliderFloat("X Position", &f, 0.0f, _window->GetSizeX());            // Edit 1 float using a slider from 0.0f to 1.0f    
	//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
	//ImGui::Checkbox("Another Window", &show_another_window);

	if (ImGui::Button("WIREFRAME"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
		_wireFrameActive = !_wireFrameActive;

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void MotorasoGui::CreateFrame()
{
	ImGui_ImplGlfwGL3_NewFrame();
}

void MotorasoGui::RenderGui()
{
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

MotorasoGui::~MotorasoGui()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}
