#include "MyEntityManager.h"
using namespace Simplex;
//  MyEntityManager
MyEntityManager* MyEntityManager::m_pInstance = nullptr;
void MyEntityManager::Init(void)
{
	ReleaseInstance();
	m_entityList = std::vector<MyEntity*>();
	m_pInstance = this;
}
void MyEntityManager::Release(void)
{
	m_entityList.clear();
}
MyEntityManager* MyEntityManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}
void MyEntityManager::ReleaseInstance()
{
	m_pInstance = nullptr;
}
int Simplex::MyEntityManager::GetEntityIndex(String a_sUniqueID)
{
	for (int i = 0; i < m_entityList.size(); i++) {
		if (m_entityList[i]->GetUniqueID() == a_sUniqueID) {
			return i;
		}
	}
}
//Accessors
Model* Simplex::MyEntityManager::GetModel(uint a_uIndex)
{
	return m_entityList[a_uIndex]->GetModel();
}
Model* Simplex::MyEntityManager::GetModel(String a_sUniqueID)
{
	return m_entityList[this->GetEntityIndex(a_sUniqueID)]->GetModel();
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(uint a_uIndex)
{
	return m_entityList[a_uIndex]->GetRigidBody();
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(String a_sUniqueID)
{
	return m_entityList[this->GetEntityIndex(a_sUniqueID)]->GetRigidBody();
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(uint a_uIndex)
{
	return m_entityList[a_uIndex]->GetModelMatrix();
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(String a_sUniqueID)
{
	return m_entityList[this->GetEntityIndex(a_sUniqueID)]->GetModelMatrix();
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, String a_sUniqueID)
{
	return m_entityList[this->GetEntityIndex(a_sUniqueID)]->SetModelMatrix(a_m4ToWorld);
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, uint a_uIndex)
{
	return m_entityList[a_uIndex]->SetModelMatrix(a_m4ToWorld);
}
//The big 3
MyEntityManager::MyEntityManager(){Init();}
MyEntityManager::MyEntityManager(MyEntityManager const& other){}
MyEntityManager& MyEntityManager::operator=(MyEntityManager const& other) { return *this; }
MyEntityManager::~MyEntityManager(){Release();};
// other methods
void Simplex::MyEntityManager::Update(void)
{

}
void Simplex::MyEntityManager::AddEntity(String a_sFileName, String a_sUniqueID)
{
	m_entityList.push_back(new MyEntity(a_sFileName, a_sUniqueID));
}
void Simplex::MyEntityManager::RemoveEntity(uint a_uIndex)
{
	m_entityList.erase(m_entityList.begin() + a_uIndex-1);
}
void Simplex::MyEntityManager::RemoveEntity(String a_sUniqueID)
{
	m_entityList.erase(m_entityList.begin() + this->GetEntityIndex(a_sUniqueID) - 1);
}
String Simplex::MyEntityManager::GetUniqueID(uint a_uIndex)
{
	return m_entityList[a_uIndex]->GetUniqueID();
}
MyEntity* Simplex::MyEntityManager::GetEntity(uint a_uIndex)
{
	return m_entityList[a_uIndex];
}
void Simplex::MyEntityManager::AddEntityToRenderList(uint a_uIndex, bool a_bRigidBody)
{
	m_entityList[a_uIndex]->AddToRenderList(a_bRigidBody);
}
void Simplex::MyEntityManager::AddEntityToRenderList(String a_sUniqueID, bool a_bRigidBody)
{
	m_entityList[this->GetEntityIndex(a_sUniqueID)]->AddToRenderList(a_bRigidBody);
}