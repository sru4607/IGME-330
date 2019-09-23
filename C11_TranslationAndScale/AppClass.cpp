#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the meshes
	m_pMeshes = new std::vector<MyMesh*>();
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(0)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(0)->m_StartPosition = vector3(0, 0, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(1)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(1)->m_StartPosition = vector3(0, -1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(2)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(2)->m_StartPosition = vector3(0, -2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(3)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(3)->m_StartPosition = vector3(1, 0, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(4)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(4)->m_StartPosition = vector3(1, 1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(5)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(5)->m_StartPosition = vector3(2, 2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(6)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(6)->m_StartPosition = vector3(2, 1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(7)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(7)->m_StartPosition = vector3(2, 0, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(8)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(8)->m_StartPosition = vector3(2, -1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(9)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(9)->m_StartPosition = vector3(2, -2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(10)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(10)->m_StartPosition = vector3(2, 4, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(11)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(11)->m_StartPosition = vector3(3, 3, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(12)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(12)->m_StartPosition = vector3(3, 2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(13)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(13)->m_StartPosition = vector3(3, 0, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(14)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(14)->m_StartPosition = vector3(3, -1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(15)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(15)->m_StartPosition = vector3(3, -3, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(16)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(16)->m_StartPosition = vector3(4, 2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(17)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(17)->m_StartPosition = vector3(4, 1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(18)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(18)->m_StartPosition = vector3(4, 0, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(19)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(19)->m_StartPosition = vector3(4, -1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(20)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(20)->m_StartPosition = vector3(5, 2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(21)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(21)->m_StartPosition = vector3(5, 1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(22)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(22)->m_StartPosition = vector3(5, 0, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(23)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(23)->m_StartPosition = vector3(5, -1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(24)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(24)->m_StartPosition = vector3(6, 2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(25)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(25)->m_StartPosition = vector3(6, 1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(26)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(26)->m_StartPosition = vector3(6, 0, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(27)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(27)->m_StartPosition = vector3(6, -1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(28)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(28)->m_StartPosition = vector3(6, -3, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(29)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(29)->m_StartPosition = vector3(4, -3, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(30)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(30)->m_StartPosition = vector3(7, 3, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(31)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(31)->m_StartPosition = vector3(7, 2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(32)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(32)->m_StartPosition = vector3(7, 0, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(33)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(33)->m_StartPosition = vector3(7, -1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(34)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(34)->m_StartPosition = vector3(7, -3, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(35)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(35)->m_StartPosition = vector3(8, 2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(36)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(36)->m_StartPosition = vector3(8, 1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(37)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(37)->m_StartPosition = vector3(8, 0, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(38)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(38)->m_StartPosition = vector3(8, -1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(39)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(39)->m_StartPosition = vector3(8, -2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(40)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(40)->m_StartPosition = vector3(8, 4, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(41)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(41)->m_StartPosition = vector3(9, 0, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(42)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(42)->m_StartPosition = vector3(9, 1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(43)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(43)->m_StartPosition = vector3(10, -2, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(44)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(44)->m_StartPosition = vector3(10, -1, 0);
	m_pMeshes->push_back(new MyMesh());
	m_pMeshes->at(45)->GenerateCube(1.0f, C_BLACK);
	m_pMeshes->at(45)->m_StartPosition = vector3(10, 0, 0);

}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(1.0f,1.0f,1.0f));
	static float value = 0.0f;
	//Moves the mesh based on the position of the different positions and a sin wave
	for (int i = 0; i < m_pMeshes->size(); i++)
	{
		vector3 position = m_pMeshes->at(i)->m_StartPosition;
		matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(-5+position.x+value, position.y + 2.0f+sin(value), position.z + 3.0f));

		//matrix4 m4Model = m4Translate * m4Scale;
		matrix4 m4Model = m4Scale * m4Translate;

		m_pMeshes->at(i)->Render(m4Projection, m4View, m4Model);
	}
	
	
	value += 0.01f;
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pMeshes);

	//release GUI
	ShutdownGUI();
}