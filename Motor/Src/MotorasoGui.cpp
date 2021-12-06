#include "MotorasoGui.h"
#include "Entity.h"
#include "Light.h"
#include <glm/glm.hpp>
#include "GameBase.h"

#include <glew.h>
#include <GLFW/glfw3.h>
#include "Gui/imgui.h"
#include "Gui/imgui_impl_glfw_gl3.h"
#include "AxisAlignedBoundingBox.h"	 

Entity* MotorasoGui::lastEntitySelected;
Entity* MotorasoGui::currentEntitySelected;

float MotorasoGui::speedPosition = 40.0f;
float MotorasoGui::speedRotation = 1.0f;
float MotorasoGui::speedScalated = 50.0f;
int MotorasoGui::countObjectInScreen = 0;
bool MotorasoGui::_wireFrameActive = false;

MotorasoGui::MotorasoGui(Windows* window)
{
	CreateContext(window);
	_window = window;
}

void MotorasoGui::TreeEntitys(Entity * entityNode)
{
	_TreeEntitys(entityNode);
	if (currentEntitySelected) {
		currentEntitySelected->ShowUI();
		End();
	}
	if (lastEntitySelected) { 
		if (lastEntitySelected != currentEntitySelected) {
			//lastEntitySelected->HideUI();
			lastEntitySelected = currentEntitySelected;
		}
	}
}

void MotorasoGui::_TreeEntitys(Entity * entity)
{
	if (entity->GetIsUILocked()) { return; }
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
	if (entity == currentEntitySelected) {
		flags |= ImGuiTreeNodeFlags_Selected;
	}
	if (entity->GetChildrens().empty()) {
		flags |= ImGuiTreeNodeFlags_Leaf;
	}
	bool isOpened = ImGui::TreeNodeEx(entity->GetName().c_str(), flags);
	bool isSelected = ImGui::IsItemClicked();
	if (isOpened) {
		if (isSelected) {
			if (!lastEntitySelected) {
				lastEntitySelected = entity;
			}
			else {
				lastEntitySelected = currentEntitySelected;
			}
			currentEntitySelected = entity;
		}
		for (Entity* child : entity->GetChildrens()) {
			_TreeEntitys(child);
		}
		ImGui::TreePop();
	}
	else {
		if (isSelected) {
			currentEntitySelected = entity;
		}
	}
}

void MotorasoGui::CheckCountObjectsInScreen(Entity* entityRoot)
{
	if (entityRoot->GetIsAlive())
		countObjectInScreen++;

	for (Entity* child : entityRoot->GetChildrens()) 
	{
		CheckCountObjectsInScreen(child);
	}
}

void MotorasoGui::ShowTransform(Entity* entityNode)
{
	glm::vec3 pos = entityNode->transform.position;
	glm::vec3 rot = entityNode->transform.rotation;
	glm::vec3 scl = entityNode->transform.scale;
	float newPos[3] = { pos.x, pos.y, pos.z };
	float newRot[3] = { rot.x, rot.y, rot.z };
	float newScl[3] = { scl.x, scl.y, scl.z };
	ImGui::Text("Transform");
	ImGui::InputFloat3("Position", newPos, -1, ImGuiInputTextFlags_CharsDecimal);
	ImGui::InputFloat3("Rotation", newRot, -1, ImGuiInputTextFlags_CharsDecimal);
	ImGui::InputFloat3("Scale", newScl, -1, ImGuiInputTextFlags_CharsDecimal);
	
	ImGui::Separator();
	ImGui::Text("Position Object");
	ImGui::SliderFloat("Position X", &newPos[0], newPos[0] - speedPosition, newPos[0] + speedPosition);
	ImGui::SliderFloat("Position Y", &newPos[1], newPos[1] - speedPosition, newPos[1] + speedPosition);
	ImGui::SliderFloat("Position Z", &newPos[2], newPos[2] - speedPosition, newPos[2] + speedPosition);
	
	ImGui::Separator();
	ImGui::Text("Rotation Object");
	ImGui::SliderFloat("Rotation X", &newRot[0], newRot[0] - speedRotation, newRot[0] + speedRotation);
	ImGui::SliderFloat("Rotation Y", &newRot[1], newRot[1] - speedRotation, newRot[1] + speedRotation);
	ImGui::SliderFloat("Rotation Z", &newRot[2], newRot[2] - speedRotation, newRot[2] + speedRotation);

	ImGui::Separator();
	ImGui::Text("Scale Object");
	ImGui::SliderFloat("Scale X", &newScl[0], newScl[0] - speedScalated, newScl[0] + speedScalated);
	ImGui::SliderFloat("Scale Y", &newScl[1], newScl[1] - speedScalated, newScl[1] + speedScalated);
	ImGui::SliderFloat("Scale Z", &newScl[2], newScl[2] - speedScalated, newScl[2] + speedScalated);

	entityNode->SetPosition(glm::vec3(newPos[0], newPos[1], newPos[2]));
	entityNode->SetRotationX(newRot[0]);
	entityNode->SetRotationY(newRot[1]);
	entityNode->SetRotationZ(newRot[2]);
	entityNode->SetScale(glm::vec3(newScl[0], newScl[1], newScl[2]));
	ImGui::Separator();
}

void MotorasoGui::UpdateIsStaticEntity(Entity * entityNode)
{
	ImGui::Separator();

	if (ImGui::Button("IsStatic"))
		entityNode->SetIsStatic(!entityNode->GetIsStatic());
}

void MotorasoGui::UpdateWireFrameGui()
{
	ImGui::Separator();

	if (ImGui::Button("WIREFRAME"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
		_wireFrameActive = !_wireFrameActive;
}

void MotorasoGui::UpdateAABB(Entity* entityNode)
{
	ImGui::Separator();
	ModelNode* modelNode = nullptr;
	modelNode = (ModelNode*)(entityNode);
	if (entityNode->GetAABB() != NULL && (modelNode == nullptr || modelNode == NULL))
	{
		if (ImGui::Button("AABB"))
		{
			entityNode->SetEnableDrawAABB(!entityNode->GetAABB()->GetEnableDraw());
		}
	}
	else if(entityNode->GetAABB() != NULL)
	{
		if (modelNode->_meshList.size() > 0) 
		{
			if (ImGui::Button("AABB"))
			{
				entityNode->SetEnableDrawAABB(!entityNode->GetAABB()->GetEnableDraw());
			}
		}
	}
}

void MotorasoGui::ShowEntityNodeInfo(Entity * entity)
{
	ImGui::Begin("Properties");
	ImGui::Separator();
	ImGui::Text(string("Type:" + entity->GetClassName()).c_str());
	static char buf[254];
	memcpy(buf, (void*)&entity->GetName()[0], entity->GetName().size());
	if (ImGui::InputText("Name", buf, 254, ImGuiInputTextFlags_EnterReturnsTrue)) {
		entity->SetName(string(buf));
	}
	memset(buf, 0, 254);

	ImVec4 color;

	if (entity->GetIsAlive())
		color = ImVec4(0.0,1.0f,0.0f,1.0f);
	else
		color = ImVec4(1.0, 0.0f, 0.0f, 1.0f);

	//if (!entity->GetIsInmortal())
	//{
		if (entity->GetIsAlive()) {
			if (ImGui::Button("Disable object")) {
				GameBase::DisableObjectInGame(entity);
			}
		}

		if (!entity->GetIsAlive()) {
			if (ImGui::Button("Enable object")) {
				GameBase::EnableObjectInGame(entity);
			}
		}
		ImGui::ColorButton(entity->GetName().c_str(), color);
	//}

	ImGui::Separator();

	ShowEntityInfo(entity);

	ImGui::Separator();
	if (entity->GetClassName() == "Light")
		ShowLightInfo((Light*)entity);

	UpdateIsStaticEntity(entity);

	if (entity->GetIsStatic())
		color = ImVec4(0.0, 1.0f, 0.0f, 1.0f);
	else
		color = ImVec4(1.0, 0.0f, 0.0f, 1.0f);
	ImGui::ColorButton("Is Static", color);

	UpdateWireFrameGui();

	UpdateAABB(entity);

	ImGui::Separator();

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::Separator();
}

void MotorasoGui::ShowEntityInfo(Entity * entityNode)
{
	if (entityNode->GetClassName() != "EmptyObject")
		ShowTransform(entityNode);
}

void MotorasoGui::ShowLightInfo(Light * light)
{
	if (light != NULL) 
	{
		string nameLight = "Light - " + light->GetTypeLightString();
		ImGui::Text(nameLight.c_str());
		glm::vec3 lColor = glm::vec3(light->GetColorLight());
		float newColor[3] = { lColor.x, lColor.y, lColor.z };
		ImGui::ColorEdit3("Color", newColor, ImGuiColorEditFlags_NoAlpha);
		light->SetColorLight(newColor[0], newColor[1], newColor[2]);

		glm::vec3 ambient = light->GetAmbient();
		float newAmbient[3] = { ambient.x, ambient.y, ambient.z };
		glm::vec3 diffuse = light->GetDiffuse();
		float newDiffuse[3] = { diffuse.x, diffuse.y, diffuse.z };
		glm::vec3 specular = light->GetSpecular();
		float newSpecular[3] = { specular.x, specular.y, specular.z };

		ImGui::InputFloat3("Ambient", newAmbient);
		ImGui::InputFloat3("Diffuse", newDiffuse);
		ImGui::InputFloat3("Specular", newSpecular);

		light->SetAmbient(newAmbient[0], newAmbient[1], newAmbient[2]);
		light->SetDiffuse(newDiffuse[0], newDiffuse[1], newDiffuse[2]);
		light->SetSpecular(newSpecular[0], newSpecular[1], newSpecular[2]);

		ImGui::Separator();
	}
}

void MotorasoGui::Text(const string& text) {
	ImGui::Text(text.c_str());
}

void MotorasoGui::Begin(const string & windowName, bool opened, size_t flags)
{
	ImGui::Begin(windowName.c_str(), &opened, flags);
}



void MotorasoGui::CreateContext(Windows * window)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(window->GetWindowsPtr(), true);
}

void MotorasoGui::Destroy()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void MotorasoGui::NewFrame()
{
	ImGui_ImplGlfwGL3_NewFrame();
}

void MotorasoGui::Render()
{
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}


void MotorasoGui::End()
{
	ImGui::End();
}

MotorasoGui::~MotorasoGui()
{
	Destroy();
}

//void MotorasoGui::UpdateMotorasoGui(vector<Entity*> entitysData)
//{
//	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f),"Inspector");
//	float p = 0;
//	ImVec4 color;
//	for(int i = 0; i < entitysData.size(); i++)
//	{
//		if (entitysData[i] != NULL) 
//		{
//			if (entitysData[i]->GetIsAlive()) 
//				color = ImVec4(0.0,1.0f,0.0f,1.0f);
//			else
//				color = ImVec4(1.0, 0.0f, 0.0f, 1.0f);
//
//
//			ImGui::TextColored(ImVec4(1.0f, 1.0f , 1.0f, 1.0f),entitysData[i]->GetName().c_str());
//
//			if (ImGui::ColorButton(entitysData[i]->GetName().c_str(), color))
//			{
//				entitysData[i]->SetShowInDebug(!entitysData[i]->GetShowInDebug());
//				for (int j = 0; j < entitysData.size(); j++)
//				{
//					if (j != i)
//					{
//						entitysData[j]->SetShowInDebug(false);
//					}
//				}
//			}
//			if (entitysData[i]->GetShowInDebug())
//			{
//				ImGui::Text("Position");
//				ImGui::SliderFloat("Position X", &entitysData[i]->transform.position.x, entitysData[i]->transform.position.x - speedPosition, entitysData[i]->transform.position.x + speedPosition);
//				ImGui::SliderFloat("Position Y", &entitysData[i]->transform.position.y, entitysData[i]->transform.position.y - speedPosition, entitysData[i]->transform.position.y + speedPosition);
//				ImGui::SliderFloat("Position Z", &entitysData[i]->transform.position.z, entitysData[i]->transform.position.z - speedPosition, entitysData[i]->transform.position.z + speedPosition);
//				ImGui::Text("Rotation");
//				ImGui::SliderFloat("Rotation X", &entitysData[i]->transform.rotation.x, entitysData[i]->transform.rotation.x - speedRotation, entitysData[i]->transform.rotation.x + speedRotation);
//				ImGui::SliderFloat("Rotation Y", &entitysData[i]->transform.rotation.y, entitysData[i]->transform.rotation.y - speedRotation, entitysData[i]->transform.rotation.y + speedRotation);
//				ImGui::SliderFloat("Rotation Z", &entitysData[i]->transform.rotation.z, entitysData[i]->transform.rotation.z - speedRotation, entitysData[i]->transform.rotation.z + speedRotation);
//				ImGui::Text("Scaled");
//				ImGui::SliderFloat("Scaled", &entitysData[i]->transform.scale.x, entitysData[i]->transform.scale.x - speedScalated, entitysData[i]->transform.scale.x + speedScalated);
//				entitysData[i]->SetPosition(entitysData[i]->transform.position.x, entitysData[i]->transform.position.y, entitysData[i]->transform.position.z);
//				entitysData[i]->SetRotationX(entitysData[i]->transform.rotation.x);
//				entitysData[i]->SetRotationY(entitysData[i]->transform.rotation.y);
//				entitysData[i]->SetRotationZ(entitysData[i]->transform.rotation.z);
//				entitysData[i]->SetScale(entitysData[i]->transform.scale.x, entitysData[i]->transform.scale.x, entitysData[i]->transform.scale.x);
//				
//				if (!entitysData[i]->GetIsInmortal()) 
//				{
//					if (entitysData[i]->GetIsAlive()) {
//						if (ImGui::Button("Disable object")) {
//							GameBase::DisableObjectInGame(entitysData[i]);
//						}
//					}
//
//					if (!entitysData[i]->GetIsAlive()) {
//						if (ImGui::Button("Enable object")) {
//							GameBase::EnableObjectInGame(entitysData[i]);
//						}
//					}
//				}
//			}
//		}
//	}
//
//	
//}
