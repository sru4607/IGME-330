#ifndef __MYOCTANT_H_
#define __MYOCTANT_H_


#include "MyEntityManager.h";

namespace Simplex {
	class MyOctant
	{


		int m_ID = 0;//Id of MyOctant
		int m_Level = 0;//Current level of MyOctant
		int m_childrenCount = 0; //Either 0 - No children, 8 - children exist
		//Size of MyOctant
		float m_OctantSize = 0.0f;
		//Managers
		MeshManager* m_MeshManager = nullptr;
		//Center of MyOctant
		vector3 m_Center = vector3(0.0f);
		//Minimum Point
		vector3 m_Min = vector3(0.0f);
		//Maximum Point
		vector3 m_Max = vector3(0.0f);
		//Parent MyOctant
		MyOctant* m_Parent = nullptr;
		//Children MyOctants (If Children Exist)
		MyOctant* m_Children[8];

		//Root of MyOctant
		MyOctant* m_Root = nullptr;



	public:
		static int m_maxLevels; //Maximum Level of MyOctants
		static int m_OctantCreated; //Number of octants created
		static int m_IdealEntityCount; //Tells the number of entities this will ideally contain
		//List of entities in MyOctant
		std::vector<int> m_EntityList;
		//List of nodes containing objects
		std::vector<MyOctant*> m_LeafsWithObjects;
		/*
		USAGE: Constructor, will create an MyOctant containing all MagnaEntities Instances in the Mesh
		manager	currently contains
		ARGUMENTS:
		- uint a_nMaxLevel = 2 -> Sets the maximum level of subdivision
		- uint nIdealEntityCount = 5 -> Sets the ideal level of objects per MyOctant
		OUTPUT: class object
		*/
		MyOctant(uint a_nMaxLevel = 2, uint a_nIdealEntityCount = 5);
		/*
		USAGE: Constructor
		ARGUMENTS:
		- vector3 a_v3Center -> Center of the MyOctant in global space
		- float a_fSize -> size of each side of the MyOctant volume
		OUTPUT: class object
		*/
		MyOctant(vector3 a_v3Center, float a_fSize);
		/*
		USAGE: Copy Constructor
		ARGUMENTS: class object to copy
		OUTPUT: class object instance
		*/
		MyOctant(MyOctant const& other);
		/*
		USAGE: Copy Assignment Operator
		ARGUMENTS: class object to copy
		OUTPUT: ---
		*/
		MyOctant& operator=(MyOctant const& other);
		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~MyOctant(void);
		/*
		USAGE: Changes object contents for other object's
		ARGUMENTS:
		- MyOctant& other -> object to swap content from
		OUTPUT: ---
		*/
		void Swap(MyOctant& other);
		/*
		USAGE: Gets this MyOctant's size
		ARGUMENTS: ---
		OUTPUT: size of MyOctant
		*/
		float GetSize(void);
		/*
		USAGE: Gets the center of the MyOctant in global scape
		ARGUMENTS: ---
		OUTPUT: Center of the MyOctant in global space
		*/
		vector3 GetCenterGlobal(void);
		/*
		USAGE: Gets the min corner of the MyOctant in global space
		ARGUMENTS: ---
		OUTPUT: Minimum in global space
		*/
		vector3 GetMinGlobal(void);
		/*
		USAGE: Gets the max corner of the MyOctant in global space
		ARGUMENTS: ---
		OUTPUT: Maximum in global space
		*/
		vector3 GetMaxGlobal(void);
		/*
		USAGE: Asks if there is a collision with the Entity specified by index from
		the Bounding Object Manager
		ARGUMENTS:
		- int a_uRBIndex -> Index of the Entity in the Entity Manager
		OUTPUT: check of the collision
		*/
		bool IsColliding(uint a_uRBIndex);
		/*
		USAGE: Displays the MyOctant volume specified by index including the objects underneath
		ARGUMENTS:
		- uint a_nIndex -> MyOctant to be displayed.
		- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
		OUTPUT: ---
		*/
		void Display(int a_nIndex, vector3 a_v3Color = C_YELLOW);
		/*
		USAGE: Displays the MyOctant volume in the color specified
		ARGUMENTS:
		- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
		OUTPUT: ---
		*/
		void Display(vector3 a_v3Color = C_YELLOW);
		/*
		USAGE: Displays the non empty leafs in the octree
		ARGUMENTS:
		- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
		OUTPUT: ---
		*/
		void DisplayLeafs(vector3 a_v3Color = C_YELLOW);
		/*
		USAGE: Clears the Entity list for each node
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void ClearEntityList(void);
		/*
		USAGE: allocates 8 smaller MyOctants in the child pointers
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Subdivide(void);
		/*
		USAGE: returns the child specified in the index
		ARGUMENTS: uint a_nChild -> index of the child (from 0 to 7)
		OUTPUT: MyOctant object (child in index)
		*/
		MyOctant* GetChild(uint a_nChild);
		/*
		USAGE: returns the parent of the MyOctant
		ARGUMENTS: ---
		OUTPUT: MyOctant object (parent)
		*/
		MyOctant* GetParent(void);
		/*
		USAGE: Asks the MyOctant if it does not contain any children (its a leaf)
		ARGUMENTS: ---
		OUTPUT: It contains no children
		*/
		bool IsLeaf(void);
		/*
		USAGE: Asks the MyOctant if it contains more than this many Bounding Objects
		ARGUMENTS:
		- uint a_nEntities -> Number of Entities to query
		OUTPUT: It contains at least this many Entities
		*/
		bool ContainsMoreThan(uint a_nEntities);
		/*
		USAGE: Deletes all children and the children of their children (almost sounds apocalyptic)
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void KillBranches(void);
		/*
		USAGE: Creates a tree using subdivisions, the max number of objects and levels
		ARGUMENTS:
		- uint a_nMaxLevel = 3 -> Sets the maximum level of the tree while constructing it
		OUTPUT: ---
		*/
		void ConstructTree(uint a_nMaxLevel = 3);
		/*
		USAGE: Traverse the tree up to the leafs and sets the objects in them to the index
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void AssignIDtoEntity(void);

		/*
		USAGE: Gets the total number of MyOctants in the world
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		uint GetMyOctantCount(void);

	private:
		/*
		USAGE: Deallocates member fields
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Release(void);
		/*
		USAGE: Allocates member fields
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Init(void);
		/*
		USAGE: Goes through each of the leaves and adds the entities in it to a list
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void OrganizeEntities(void);


	};

}

#endif // !__MYOCTANT_H_