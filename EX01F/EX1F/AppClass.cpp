#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	m_pMesh = new MyMesh();
	m_pMesh->GenerateWave(0.5f, 3, 6.0f, 0, C_GREEN);
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

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//make a new clock and time it
	static uint uClock = m_pSystem->GenClock();
	static float fTime = 0.0f;
	float fDelta = m_pSystem->GetDeltaTime(uClock);
	fTime += fDelta;
	
	//make something happen every one second
	static int iSeconds = 0.0f;
	if ((fTime - iSeconds) > 0.0f)
	{
		iSeconds++;
		m_pMesh->GenerateWave(0.5f, 3 + iSeconds, 6.0f, iSeconds, C_GREEN);
	}
	
	// get the matrices
	matrix4 m4Model = ToMatrix4(m_qArcBall);
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	// draw the list
	m_pMesh->Render(m4Projection, m4View, m4Model);

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
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}