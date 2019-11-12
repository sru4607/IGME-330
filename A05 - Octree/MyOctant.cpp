#include "MyOctant.h"
namespace Simplex {

#pragma region Constructors/Deconstructor
	int MyOctant::m_maxLevels;
	int MyOctant::m_IdealEntityCount;
	int MyOctant::m_OctantCreated;
	/*
		USAGE: Constructor, will create an MyOctant containing all MagnaEntities Instances in the Mesh
		manager	currently contains (Sets up root)
		ARGUMENTS:
		- uint a_nMaxLevel = 2 -> Sets the maximum level of subdivision
		- uint nIdealEntityCount = 5 -> Sets the ideal level of objects per MyOctant
		OUTPUT: class object
		*/
	MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount) {
		Init();
		MyOctant::m_OctantCreated = 0;
		MyOctant::m_maxLevels = a_nMaxLevel;
		MyOctant::m_IdealEntityCount = a_nIdealEntityCount;

		m_ID = 0;
		m_Level = 1;
		m_Root = this;
		m_LeafsWithObjects.clear();

		//Find Min and Max
		//For each entity find max distance along axis from 0
		float maxDist = 0;
		for (int i = 0; i < MyEntityManager::GetInstance()->GetEntityCount(); i++)
		{
			MyRigidBody* rb = MyEntityManager::GetInstance()->GetEntity(i)->GetRigidBody();
			vector3 max = rb->GetMaxGlobal();
			vector3 min = rb->GetMinGlobal();
			if (max.x > maxDist)
			{
				maxDist = max.x;
			}
			if (max.y > maxDist)
			{
				maxDist = max.x;
			}
			if (max.z > maxDist)
			{
				maxDist = max.x;
			}
			if (-min.x > maxDist)
			{
				maxDist = min.x;
			}
			if (-min.y > maxDist)
			{
				maxDist = min.y;
			}
			if (-min.z > maxDist)
			{
				maxDist = min.z;
			}
			
		}
		m_OctantSize = 2 * maxDist;
		m_Max = vector3(maxDist);
		m_Min = vector3(-1 * maxDist);
		MyOctant::m_OctantCreated++;
		//Construct Tree
		ConstructTree(MyOctant::m_maxLevels);
		OrganizeEntities();

		int total = 0;
		for each (MyOctant* c in m_LeafsWithObjects)
		{
			for each (int i in c->m_EntityList) {
				total++;
			}
		}
		std::cout << total << std::endl;
		
	}
	/*
	USAGE: Constructor
	ARGUMENTS:
	- vector3 a_v3Center -> Center of the MyOctant in global space
	- float a_fSize -> size of each side of the MyOctant volume
	OUTPUT: class object
	*/
	MyOctant::MyOctant(vector3 a_v3Center, float a_fSize) {
		Init();
		//Set center and size and ID
		m_Center = a_v3Center;
		m_OctantSize = a_fSize;
		m_Max = m_Center + vector3(m_OctantSize / 2);
		m_Min = m_Center - vector3(m_OctantSize / 2);
		m_ID = MyOctant::m_OctantCreated;
		MyOctant::m_OctantCreated++;
	}
	/*
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	MyOctant::MyOctant(MyOctant const& other) {
		
	}
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	MyOctant& MyOctant::operator=(MyOctant const& other) {
		if (this != &other)
		{
			Release();
			Init();
			MyOctant temp(other);
			Swap(temp);
		}
		return *this;
	}
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	MyOctant::~MyOctant(void)
	{
		Release();
	}
#pragma endregion

#pragma region Accessors



	/*
	USAGE: Gets this MyOctant's size
	ARGUMENTS: ---
	OUTPUT: size of MyOctant
	*/
	float MyOctant::GetSize(void) {
		return m_OctantSize;
	}
	/*
	USAGE: Gets the center of the MyOctant in global scape
	ARGUMENTS: ---
	OUTPUT: Center of the MyOctant in global space
	*/
	vector3 MyOctant::GetCenterGlobal(void) {
		return m_Center;
	}
	/*
	USAGE: Gets the min corner of the MyOctant in global space
	ARGUMENTS: ---
	OUTPUT: Minimum in global space
	*/
	vector3 MyOctant::GetMinGlobal(void) {
		return m_Min;
	}
	/*
	USAGE: Gets the max corner of the MyOctant in global space
	ARGUMENTS: ---
	OUTPUT: Maximum in global space
	*/
	vector3 MyOctant::GetMaxGlobal(void) {
		return m_Max;
	}
	/*
	USAGE: returns the child specified in the index
	ARGUMENTS: uint a_nChild -> index of the child (from 0 to 7)
	OUTPUT: MyOctant object (child in index)
	*/
	MyOctant* MyOctant::GetChild(uint a_nChild) {
		return m_Children[a_nChild];
	}
	/*
	USAGE: returns the parent of the MyOctant
	ARGUMENTS: ---
	OUTPUT: MyOctant object (parent)
	*/
	MyOctant* MyOctant::GetParent(void) {
		return m_Parent;
	}
	/*
	USAGE: Asks the MyOctant if it does not contain any children (its a leaf)
	ARGUMENTS: ---
	OUTPUT: It contains no children
	*/
	bool MyOctant::IsLeaf(void) {
		return (m_childrenCount == 8);
	}
	/*
	USAGE: Asks the MyOctant if it contains more than this many Bounding Objects
	ARGUMENTS:
	- uint a_nEntities -> Number of Entities to query
	OUTPUT: It contains at least this many Entities
	*/
	bool MyOctant::ContainsMoreThan(uint a_nEntities) {
		return (a_nEntities <= m_EntityList.size());
	}

	/*
	USAGE: Gets the total number of MyOctants in the world
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	uint MyOctant::GetMyOctantCount(void) {
		//return m_OctantsCreated;
		return MyOctant::m_OctantCreated;
	}
#pragma endregion
	/*
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	- MyOctant& other -> object to swap content from
	OUTPUT: ---
	*/
	void MyOctant::Swap(MyOctant& other) {
		//Store other information
		int temporaryID = other.m_ID;
		int tempLevel = other.m_Level;
		int tempChildCount = other.m_childrenCount;
		float tempSize = other.m_OctantSize;
		vector3 tempCenter = other.m_Center;
		vector3 tempMin = other.m_Min;
		vector3 tempMax = other.m_Max;
		MyOctant* tempParent = other.m_Parent;
		std::vector<int> tempEntityList = other.m_EntityList;
		//Set other information to this information
		other.m_ID = m_ID;
		other.m_Level = m_Level;
		other.m_childrenCount = m_childrenCount;
		other.m_OctantSize = m_OctantSize;
		other.m_Center = m_Center;
		other.m_Min = m_Min;
		other.m_Max = m_Max;
		other.m_Parent = m_Parent;
		other.m_EntityList = m_EntityList;
		//Set this information to the saved information
		m_ID = temporaryID;
		m_Level = tempLevel;
		m_childrenCount = tempChildCount;
		m_OctantSize = tempSize;
		m_Center = tempCenter;
		m_Min = tempMin;
		m_Max = tempMax;
		m_Parent = tempParent;
		m_EntityList = tempEntityList;
	}

	/*
	USAGE: Asks if there is a collision with the Entity specified by index from
	the Bounding Object Manager
	ARGUMENTS:
	- int a_uRBIndex -> Index of the Entity in the Entity Manager
	OUTPUT: check of the collision
	*/
	bool MyOctant::IsColliding(uint a_uRBIndex) {

		//Get entity
		MyEntity* entity = MyEntityManager::GetInstance()->GetEntity(a_uRBIndex);
		//Get rigidbody
		MyRigidBody* rigidBody = entity->GetRigidBody();
		//get max and min of rigidbody
		vector3 entityMax = rigidBody->GetMaxGlobal();
		vector3 entityMin = rigidBody->GetMinGlobal();
		//Check each dimension to see if collision occurs
		//If min is less than max and max is greater than min then collision occurs
		if (m_Max.x < entityMin.x) //this to the right of other
			return false;
		if (m_Min.x > entityMax.x) //this to the left of other
			return false;

		if (m_Max.y < entityMin.y) //this below of other
			return false;
		if (m_Min.y > entityMax.y) //this above of other
			return false;

		if (m_Max.z < entityMin.z) //this behind of other
			return false;
		if (m_Min.z > entityMax.z) //this in front of other
			return false;

		return true;
	}
#pragma region DisplayMethods



	/*
	USAGE: Displays the MyOctant volume specified by index including the objects underneath
	ARGUMENTS:
	- uint a_nIndex -> MyOctant to be displayed.
	- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
	OUTPUT: ---
	*/
	void MyOctant::Display(int a_nIndex, vector3 a_v3Color) {
		//If matching index display all children
		if (this == nullptr) {
			//Do Something
		}
		if(m_ID == a_nIndex) {
		for each (MyOctant* child in m_Children)
		{
			child->Display(a_v3Color);
		}
		MeshManager::GetInstance()->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_Center) * glm::scale(vector3(m_OctantSize)), a_v3Color, RENDER_WIRE);
		}
		//Check each child
		else 
		{
			if (m_Children[0] != nullptr) {
				for each (MyOctant * child in m_Children)
				{
					child->Display(a_nIndex, a_v3Color);
				}
			}
		}
	}
	/*
	USAGE: Displays the MyOctant volume in the color specified
	ARGUMENTS:
	- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
	OUTPUT: ---
	*/
	void MyOctant::Display(vector3 a_v3Color) {
		//This is here as I was having a bug without it
		if (this == nullptr) {
			//do something
		}
		if (this != nullptr) {
			MeshManager::GetInstance()->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_Center) * glm::scale(vector3(m_OctantSize)), a_v3Color, RENDER_WIRE);
			if (m_Children[0] != nullptr) {
				for each (MyOctant * child in m_Children)
				{
					child->Display(a_v3Color);
				}
			}
		}
	}
	/*
	USAGE: Displays the non empty leafs in the octree
	ARGUMENTS:
	- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
	OUTPUT: ---
	*/
	void MyOctant::DisplayLeafs(vector3 a_v3Color) {
		//Display all leafs with stuff in it
		if (m_childrenCount == 0 && m_EntityList.size() > 0) {
			MeshManager::GetInstance()->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_Center) * glm::scale(vector3(m_OctantSize)), a_v3Color, RENDER_WIRE);
		}
	}
#pragma endregion
	/*
	USAGE: Clears the Entity list for each node
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void MyOctant::ClearEntityList(void) {
		//Clear all entities from nodes
		if (m_childrenCount == 0) return;
		for each (MyOctant * child in m_Children)
		{
			child->ClearEntityList();
		}
		m_EntityList.clear();
	}
	/*
	USAGE: allocates 8 smaller MyOctants in the child pointers
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void MyOctant::Subdivide(void) {
		
		//Min min min
		vector3 newCenter = m_Center + vector3(-m_OctantSize / 4, -m_OctantSize / 4, -m_OctantSize / 4);
		m_Children[0] = new MyOctant(newCenter, m_OctantSize / 2);
		//Min min max
		newCenter = m_Center + vector3(-m_OctantSize / 4, -m_OctantSize / 4, m_OctantSize / 4);
		m_Children[1] = new MyOctant(newCenter, m_OctantSize / 2);
		//Min max min
		newCenter = m_Center + vector3(-m_OctantSize / 4, m_OctantSize / 4, -m_OctantSize / 4);
		m_Children[2] = new MyOctant(newCenter, m_OctantSize / 2);
		//Min max max
		newCenter = m_Center + vector3(-m_OctantSize / 4, m_OctantSize / 4, m_OctantSize / 4);
		m_Children[3] = new MyOctant(newCenter, m_OctantSize / 2);
		//Max min min
		newCenter = m_Center + vector3(m_OctantSize / 4, -m_OctantSize / 4, -m_OctantSize / 4);
		m_Children[4] = new MyOctant(newCenter, m_OctantSize / 2);
		//Max min max
		newCenter = m_Center + vector3(m_OctantSize / 4, -m_OctantSize / 4, m_OctantSize / 4);
		m_Children[5] = new MyOctant(newCenter, m_OctantSize / 2);
		//Max max min
		newCenter = m_Center + vector3(m_OctantSize / 4, m_OctantSize / 4, -m_OctantSize / 4);
		m_Children[6] = new MyOctant(newCenter, m_OctantSize / 2);
		//Max max max
		newCenter = m_Center + vector3(m_OctantSize / 4, m_OctantSize / 4, m_OctantSize / 4);
		m_Children[7] = new MyOctant(newCenter, m_OctantSize / 2);
		for each (MyOctant * child in m_Children) {
			child->m_Parent = this;
			child->m_Root = m_Root;
			child->m_Level = m_Level + 1;

		}
	}
	/*
	USAGE: Deletes all children and the children of their children (almost sounds apocalyptic)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void MyOctant::KillBranches(void) {
		//If there are no children then just return
		if (m_childrenCount == 0) return;
		//Kill Children
		for each (MyOctant* child in m_Children)
		{
			child->KillBranches();
			child->~MyOctant();
		}
		m_childrenCount = 0;
	}
	/*
	USAGE: Creates a tree using subdivisions, the max number of objects and levels
	ARGUMENTS:
	- uint a_nMaxLevel = 3 -> Sets the maximum level of the tree while constructing it
	OUTPUT: ---
	*/
	void MyOctant::ConstructTree(uint a_nMaxLevel) {
		//if not max level subdivide
		if (m_Level < a_nMaxLevel) {
			Subdivide();
			//For each child then call this method
			for each (MyOctant * child in m_Children) {
				child->ConstructTree(a_nMaxLevel);
			}
		}
	}

	/*
	USAGE: Goes through each of the leaves and adds the entities in it to a list
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void MyOctant::OrganizeEntities(void) {
		//For Every Child Call this method until yyou are in the leaves
		if (m_Level < MyOctant::m_maxLevels) {
			for each (MyOctant* child in m_Children)
			{
				child->OrganizeEntities();
			}
		}
		//If it is a leaf
		else if (m_Level == MyOctant::m_maxLevels) {
			//Check each entity and check if it is colliding with current octant
			MyEntityManager* instance = MyEntityManager::GetInstance();
			for (int i = 0; i < instance->GetEntityCount(); i++) {
				if (IsColliding(i)) {
					m_EntityList.push_back(i);
				}
			}
			if (m_EntityList.size() > 0) {
				m_Root->m_LeafsWithObjects.push_back(this);
			}
		}
	}
#pragma region otherMethods



	/*
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void MyOctant::Release(void) {

		KillBranches();
		m_Level = 0;
		m_childrenCount = 0;
		m_ID = 0;
	}
	/*
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void MyOctant::Init(void) {
		m_Level = 0;
		m_childrenCount = 0;
		m_ID = 0;
	}
#pragma endregion
}