#include "MotorasoGui.h"
#include "Entity.h"
#include <glm/glm.hpp>
#include "GameBase.h"
MotorasoGui::MotorasoGui(Windows* window) 
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(window->GetWindowsPtr(), true);
	_window = window;

	speedPosition = 15.0f;
	speedRotation = 1.0f;
	speedScalated = 50.0f;
}

void MotorasoGui::UpdateMotorasoGui()
{
	ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
	ImGui::SliderFloat("X Position", &xPosition, 0.0f, _window->GetSizeX());            // Edit 1 float using a slider from 0.0f to 1.0f    
	//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
	//ImGui::Checkbox("Another Window", &show_another_window);

	if (ImGui::Button("WIREFRAME"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
		_wireFrameActive = !_wireFrameActive;

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void MotorasoGui::UpdateMotorasoGui(vector<Entity*> entitysData)
{
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f),"Inspector");
	float p = 0;
	ImVec4 color;
	for(int i = 0; i < entitysData.size(); i++)
	{
		if (entitysData[i] != NULL) 
		{
			if (entitysData[i]->GetIsAlive()) 
				color = ImVec4(0.0,1.0f,0.0f,1.0f);
			else
				color = ImVec4(1.0, 0.0f, 0.0f, 1.0f);


			ImGui::TextColored(ImVec4(1.0f, 1.0f , 1.0f, 1.0f),entitysData[i]->GetName().c_str());

			if (ImGui::ColorButton(entitysData[i]->GetName().c_str(), color))
			{
				entitysData[i]->SetShowInDebug(!entitysData[i]->GetShowInDebug());
				for (int j = 0; j < entitysData.size(); j++)
				{
					if (j != i)
					{
						entitysData[j]->SetShowInDebug(false);
					}
				}
			}
			if (entitysData[i]->GetShowInDebug())
			{
				ImGui::Text("Position");
				ImGui::SliderFloat("Position X", &entitysData[i]->transform.position.x, entitysData[i]->transform.position.x - speedPosition, entitysData[i]->transform.position.x + speedPosition);
				ImGui::SliderFloat("Position Y", &entitysData[i]->transform.position.y, entitysData[i]->transform.position.y - speedPosition, entitysData[i]->transform.position.y + speedPosition);
				ImGui::SliderFloat("Position Z", &entitysData[i]->transform.position.z, entitysData[i]->transform.position.z - speedPosition, entitysData[i]->transform.position.z + speedPosition);
				ImGui::Text("Rotation");
				ImGui::SliderFloat("Rotation X", &entitysData[i]->transform.rotation.x, entitysData[i]->transform.rotation.x - speedRotation, entitysData[i]->transform.rotation.x + speedRotation);
				ImGui::SliderFloat("Rotation Y", &entitysData[i]->transform.rotation.y, entitysData[i]->transform.rotation.y - speedRotation, entitysData[i]->transform.rotation.y + speedRotation);
				ImGui::SliderFloat("Rotation Z", &entitysData[i]->transform.rotation.z, entitysData[i]->transform.rotation.z - speedRotation, entitysData[i]->transform.rotation.z + speedRotation);
				ImGui::Text("Scaled");
				ImGui::SliderFloat("Scaled", &entitysData[i]->transform.scale.x, entitysData[i]->transform.scale.x - speedScalated, entitysData[i]->transform.scale.x + speedScalated);
				entitysData[i]->SetPosition(entitysData[i]->transform.position.x, entitysData[i]->transform.position.y, entitysData[i]->transform.position.z);
				entitysData[i]->SetRotationX(entitysData[i]->transform.rotation.x);
				entitysData[i]->SetRotationY(entitysData[i]->transform.rotation.y);
				entitysData[i]->SetRotationZ(entitysData[i]->transform.rotation.z);
				entitysData[i]->SetScale(entitysData[i]->transform.scale.x, entitysData[i]->transform.scale.x, entitysData[i]->transform.scale.x);
				
				if (!entitysData[i]->GetIsInmortal()) 
				{
					if (entitysData[i]->GetIsAlive()) {
						if (ImGui::Button("Disable object")) {
							GameBase::DisableObjectInGame(entitysData[i]);
						}
					}

					if (!entitysData[i]->GetIsAlive()) {
						if (ImGui::Button("Enable object")) {
							GameBase::EnableObjectInGame(entitysData[i]);
						}
					}
				}
			}
		}
	}

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
