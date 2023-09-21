#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Will Jerum - wrj2313@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Allocate the memory for the Meshes
	for (int i = 0; i < 46; i++)
	{
		MyMesh* mesh = new MyMesh();
		meshList.push_back(mesh);
		mesh->GenerateCube(1.0f, C_BLACK);
	}
		
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Calculate the model, view and projection matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	// track time - for use in transformations
	static float currentTime = 0;
	static uint newClock = m_pSystem->GenClock();
	currentTime += m_pSystem->GetDeltaTime(newClock);

	// set up translations
	float xPos = 0.0f;
	vector3 position(xPos, 0.0f, 0.0f);
	position.x = xPos + currentTime;
	

	// draw meshes to screen
	matrix4 m4Position = glm::translate(vector3(2.0f, 0.0f, 0.0f)) * glm::translate(position);
	int i = 0;

	// row 1
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, 0.0f, 0.0f)));
	i++;

	// row 2
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(1.0f, -1.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f, -1.0f, 0.0f)));
	i++;

	// row 3
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f, -2.0f, 0.0f)));
	i++;																				
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(1.0f, -2.0f, 0.0f)));
	i++;																				
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, -2.0f, 0.0f)));
	i++;																				
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f, -2.0f, 0.0f)));
	i++;																				
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, -2.0f, 0.0f)));
	i++;																				
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f, -2.0f, 0.0f)));
	i++;																				
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, -2.0f, 0.0f)));
	i++;

	// row 4
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-1.0f, -3.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f, -3.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, -3.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f, -3.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, -3.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, -3.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(7.0f, -3.0f, 0.0f)));
	i++;

	// row 5
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-2.0f, -4.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-1.0f, -4.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f, -4.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(1.0f, -4.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, -4.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f, -4.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, -4.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f, -4.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, -4.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(7.0f, -4.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f, -4.0f, 0.0f)));
	i++;

	// row 6
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-2.0f, -5.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f, -5.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(1.0f, -5.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, -5.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f, -5.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, -5.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f, -5.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, -5.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f, -5.0f, 0.0f)));
	i++;

	// row 7
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(-2.0f, -6.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f, -6.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f, -6.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f, -6.0f, 0.0f)));
	i++;

	// row 8
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(1.0f, -7.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f, -7.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f, -7.0f, 0.0f)));
	i++;
	meshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f, -7.0f, 0.0f)));
	i++;

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release meshes
	for (int i = 0; i < 46; i++)
	{
		if (meshList[i] != nullptr)
		{
			SafeDelete(meshList[i]);
		}
	}

	//release GUI
	ShutdownGUI();
}