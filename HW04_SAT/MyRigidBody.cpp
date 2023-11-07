#include "MyRigidBody.h"
using namespace BTX;
//Allocation
uint MyRigidBody::SAT(MyRigidBody* const a_pOther)
{
	//TODO: Calculate the SAT algorithm I STRONGLY suggest you use the
	//Real Time Collision detection algorithm for OBB here but feel free to
	//implement your own solution.
	


	// For reference, I will be assigning vertex values as shown in
	// the figure below.
	/*

		   F--------G
		  /|       /|
		 / |      / |
		/  |     /  |
	   A---|----B   |
	   |   E----|---H
	   |  /     |  /
	   |/       | /
	   C--------D  
	
	*/


	// Find vertices of first shape
	// These will be stored in a vector for later
	std::vector<vector3> vertices;
	vector3 m_v3minL = GetMinLocal();
	vector3 m_v3maxL = GetMaxLocal();
	vector3 m_v3A = vector3(m_v3minL.x, m_v3maxL.y, m_v3maxL.z);
	vertices.push_back(m_v3A);
	vector3 m_v3B = vector3(m_v3maxL.x, m_v3maxL.y, m_v3maxL.z);
	vertices.push_back(m_v3B);
	vector3 m_v3C = vector3(m_v3minL.x, m_v3minL.y, m_v3maxL.z);
	vertices.push_back(m_v3C);
	vector3 m_v3D = vector3(m_v3maxL.x, m_v3minL.y, m_v3maxL.z);
	vertices.push_back(m_v3D);
	vector3 m_v3E = vector3(m_v3minL.x, m_v3minL.y, m_v3minL.z);
	vertices.push_back(m_v3E);
	vector3 m_v3F = vector3(m_v3minL.x, m_v3maxL.y, m_v3minL.z);
	vertices.push_back(m_v3F);
	vector3 m_v3G = vector3(m_v3maxL.x, m_v3maxL.y, m_v3minL.z);
	vertices.push_back(m_v3G);
	vector3 m_v3H = vector3(m_v3maxL.x, m_v3minL.y, m_v3minL.z);
	vertices.push_back(m_v3H);


	// Find vertices of second shape
	// These will be stored in a vector for later
	std::vector<vector3> otherVertices;
	vector3 m_v3otherMinL = a_pOther->GetMinLocal();
	vector3 m_v3otherMaxL = a_pOther->GetMaxLocal();
	vector3 m_v3otherA = vector3(m_v3otherMinL.x, m_v3otherMaxL.y, m_v3otherMaxL.z);
	otherVertices.push_back(m_v3otherA);
	vector3 m_v3otherB = vector3(m_v3otherMaxL.x, m_v3otherMaxL.y, m_v3otherMaxL.z);
	otherVertices.push_back(m_v3otherB);
	vector3 m_v3otherC = vector3(m_v3otherMinL.x, m_v3otherMinL.y, m_v3otherMaxL.z);
	otherVertices.push_back(m_v3otherC);
	vector3 m_v3otherD = vector3(m_v3otherMaxL.x, m_v3otherMinL.y, m_v3otherMaxL.z);
	otherVertices.push_back(m_v3otherD);
	vector3 m_v3otherE = vector3(m_v3otherMinL.x, m_v3otherMinL.y, m_v3otherMinL.z);
	otherVertices.push_back(m_v3otherE);
	vector3 m_v3otherF = vector3(m_v3otherMinL.x, m_v3otherMaxL.y, m_v3otherMinL.z);
	otherVertices.push_back(m_v3otherF);
	vector3 m_v3otherG = vector3(m_v3otherMaxL.x, m_v3otherMaxL.y, m_v3otherMinL.z);
	otherVertices.push_back(m_v3otherG);
	vector3 m_v3otherH = vector3(m_v3otherMaxL.x, m_v3otherMinL.y, m_v3otherMinL.z);
	otherVertices.push_back(m_v3otherH);



	// Find face normals

	// Ax Face Normal - AB x AF
	vector3 m_v3AB = m_v3B - m_v3A;
	vector3 m_v3AF = m_v3F - m_v3A;
	vector3 m_v3AxNorm = normalize(cross(m_v3AB, m_v3AF));

	// Ay Face Normal - AC x AF
	vector3 m_v3AC = m_v3C - m_v3A;
	vector3 m_v3AyNorm = normalize(cross(m_v3AC, m_v3AF));

	// Az Face Normal - AB x AC
	vector3 m_v3AzNorm = normalize(cross(m_v3AB, m_v3AC));

	// Bx Face Normal - AB x AF
	vector3 m_v3otherAB = m_v3otherB - m_v3otherA;
	vector3 m_v3otherAF = m_v3otherF - m_v3otherA;
	vector3 m_v3BxNorm = normalize(cross(m_v3otherAB, m_v3otherAF));

	// By Face Normal - AC x AF
	vector3 m_v3otherAC = m_v3otherC - m_v3otherA;
	vector3 m_v3ByNorm = normalize(cross(m_v3otherAB, m_v3otherAF));

	// Bz Face Normal - AB x AC
	vector3 m_v3BzNorm = normalize(cross(m_v3otherAB, m_v3otherAC));

	// Test each possible separation axis for an intersection
	// Exit early if an axis has no intersection

	// Ax
	
	// Ay

	// Az

	// Bx

	// By

	// Bz

	// AxBx

	// AxBy

	// AxBz

	// AyBx

	// AyBy

	// AyBz

	// AzBx

	// AzBy

	// AzBz


	return BTXs::eSATResults::SAT_NONE;


}

// Helper method for SAT, returns vector2 representing min and
// max projections respectively

vector2 MyRigidBody::ProjectToAxis(std::vector<vector3> vertices, vector3 axis)
{
	float maxDot = -INFINITY;
	float minDot = INFINITY;
	for (int i = 0; i < vertices.size(); i++)
	{
		float projection = dot(vertices[i], axis);

		if (projection < minDot)
		{
			minDot = projection;
		}
		if (projection > maxDot)
		{
			maxDot = projection;
		}
	}
	return vector2(minDot, maxDot);
}

bool MyRigidBody::CheckProjectionOverlap(vector2 objectA, vector2 objectB)
{
	if (objectA[1] < objectB[0])
	{
		return false;
	}
	if (objectB[1] < objectA[0])
	{
		return false;
	}
	return true;
}

bool MyRigidBody::IsColliding(MyRigidBody* const a_pOther)
{
	//check if spheres are colliding
	bool bColliding = true;
	/*
	* We use Bounding Spheres or ARBB as a pre-test to avoid expensive calculations (SAT)
	* we default bColliding to true here to always fall in the need of calculating
	* SAT for the sake of the assignment.
	*/
	if (bColliding) //they are colliding with bounding sphere
	{
		uint nResult = SAT(a_pOther);

		if (bColliding) //The SAT shown they are colliding
		{
			this->AddCollisionWith(a_pOther);
			a_pOther->AddCollisionWith(this);
		}
		else //they are not colliding
		{
			this->RemoveCollisionWith(a_pOther);
			a_pOther->RemoveCollisionWith(this);
		}
	}
	else //they are not colliding with bounding sphere
	{
		this->RemoveCollisionWith(a_pOther);
		a_pOther->RemoveCollisionWith(this);
	}
	return bColliding;
}
void MyRigidBody::Init(void)
{
	m_pModelMngr = ModelManager::GetInstance();
	m_bVisibleBS = false;
	m_bVisibleOBB = true;
	m_bVisibleARBB = false;

	m_fRadius = 0.0f;

	m_v3ColorColliding = C_RED;
	m_v3ColorNotColliding = C_WHITE;

	m_v3Center = ZERO_V3;
	m_v3MinL = ZERO_V3;
	m_v3MaxL = ZERO_V3;

	m_v3MinG = ZERO_V3;
	m_v3MaxG = ZERO_V3;

	m_v3HalfWidth = ZERO_V3;
	m_v3ARBBSize = ZERO_V3;

	m_m4ToWorld = IDENTITY_M4;
}
void MyRigidBody::Swap(MyRigidBody& a_pOther)
{
	std::swap(m_pModelMngr, a_pOther.m_pModelMngr);
	std::swap(m_bVisibleBS, a_pOther.m_bVisibleBS);
	std::swap(m_bVisibleOBB, a_pOther.m_bVisibleOBB);
	std::swap(m_bVisibleARBB, a_pOther.m_bVisibleARBB);

	std::swap(m_fRadius, a_pOther.m_fRadius);

	std::swap(m_v3ColorColliding, a_pOther.m_v3ColorColliding);
	std::swap(m_v3ColorNotColliding, a_pOther.m_v3ColorNotColliding);

	std::swap(m_v3Center, a_pOther.m_v3Center);
	std::swap(m_v3MinL, a_pOther.m_v3MinL);
	std::swap(m_v3MaxL, a_pOther.m_v3MaxL);

	std::swap(m_v3MinG, a_pOther.m_v3MinG);
	std::swap(m_v3MaxG, a_pOther.m_v3MaxG);

	std::swap(m_v3HalfWidth, a_pOther.m_v3HalfWidth);
	std::swap(m_v3ARBBSize, a_pOther.m_v3ARBBSize);

	std::swap(m_m4ToWorld, a_pOther.m_m4ToWorld);

	std::swap(m_CollidingRBSet, a_pOther.m_CollidingRBSet);
}
void MyRigidBody::Release(void)
{
	m_pModelMngr = nullptr;
	ClearCollidingList();
}
//Accessors
bool MyRigidBody::GetVisibleBS(void) { return m_bVisibleBS; }
void MyRigidBody::SetVisibleBS(bool a_bVisible) { m_bVisibleBS = a_bVisible; }
bool MyRigidBody::GetVisibleOBB(void) { return m_bVisibleOBB; }
void MyRigidBody::SetVisibleOBB(bool a_bVisible) { m_bVisibleOBB = a_bVisible; }
bool MyRigidBody::GetVisibleARBB(void) { return m_bVisibleARBB; }
void MyRigidBody::SetVisibleARBB(bool a_bVisible) { m_bVisibleARBB = a_bVisible; }
float MyRigidBody::GetRadius(void) { return m_fRadius; }
vector3 MyRigidBody::GetColorColliding(void) { return m_v3ColorColliding; }
vector3 MyRigidBody::GetColorNotColliding(void) { return m_v3ColorNotColliding; }
void MyRigidBody::SetColorColliding(vector3 a_v3Color) { m_v3ColorColliding = a_v3Color; }
void MyRigidBody::SetColorNotColliding(vector3 a_v3Color) { m_v3ColorNotColliding = a_v3Color; }
vector3 MyRigidBody::GetCenterLocal(void) { return m_v3Center; }
vector3 MyRigidBody::GetMinLocal(void) { return m_v3MinL; }
vector3 MyRigidBody::GetMaxLocal(void) { return m_v3MaxL; }
vector3 MyRigidBody::GetCenterGlobal(void){	return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
vector3 MyRigidBody::GetMinGlobal(void) { return m_v3MinG; }
vector3 MyRigidBody::GetMaxGlobal(void) { return m_v3MaxG; }
vector3 MyRigidBody::GetHalfWidth(void) { return m_v3HalfWidth; }
matrix4 MyRigidBody::GetModelMatrix(void) { return m_m4ToWorld; }
void MyRigidBody::SetModelMatrix(matrix4 a_m4ModelMatrix)
{
	//to save some calculations if the model matrix is the same there is nothing to do here
	if (a_m4ModelMatrix == m_m4ToWorld)
		return;

	//Assign the model matrix
	m_m4ToWorld = a_m4ModelMatrix;

	//Calculate the 8 corners of the cube
	vector3 v3Corner[8];
	//Back square
	v3Corner[0] = m_v3MinL;
	v3Corner[1] = vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MinL.z);
	v3Corner[2] = vector3(m_v3MinL.x, m_v3MaxL.y, m_v3MinL.z);
	v3Corner[3] = vector3(m_v3MaxL.x, m_v3MaxL.y, m_v3MinL.z);

	//Front square
	v3Corner[4] = vector3(m_v3MinL.x, m_v3MinL.y, m_v3MaxL.z);
	v3Corner[5] = vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MaxL.z);
	v3Corner[6] = vector3(m_v3MinL.x, m_v3MaxL.y, m_v3MaxL.z);
	v3Corner[7] = m_v3MaxL;

	//Place them in world space
	for (uint uIndex = 0; uIndex < 8; ++uIndex)
	{
		v3Corner[uIndex] = vector3(m_m4ToWorld * vector4(v3Corner[uIndex], 1.0f));
	}

	//Identify the max and min as the first corner
	m_v3MaxG = m_v3MinG = v3Corner[0];

	//get the new max and min for the global box
	for (uint i = 1; i < 8; ++i)
	{
		if (m_v3MaxG.x < v3Corner[i].x) m_v3MaxG.x = v3Corner[i].x;
		else if (m_v3MinG.x > v3Corner[i].x) m_v3MinG.x = v3Corner[i].x;

		if (m_v3MaxG.y < v3Corner[i].y) m_v3MaxG.y = v3Corner[i].y;
		else if (m_v3MinG.y > v3Corner[i].y) m_v3MinG.y = v3Corner[i].y;

		if (m_v3MaxG.z < v3Corner[i].z) m_v3MaxG.z = v3Corner[i].z;
		else if (m_v3MinG.z > v3Corner[i].z) m_v3MinG.z = v3Corner[i].z;
	}

	//we calculate the distance between min and max vectors
	m_v3ARBBSize = m_v3MaxG - m_v3MinG;
}
//The big 3
MyRigidBody::MyRigidBody(std::vector<vector3> a_pointList)
{
	Init();
	//Count the points of the incoming list
	uint uVertexCount = a_pointList.size();

	//If there are none just return, we have no information to create the BS from
	if (uVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3MaxL = m_v3MinL = a_pointList[0];

	//Get the max and min out of the list
	for (uint i = 1; i < uVertexCount; ++i)
	{
		if (m_v3MaxL.x < a_pointList[i].x) m_v3MaxL.x = a_pointList[i].x;
		else if (m_v3MinL.x > a_pointList[i].x) m_v3MinL.x = a_pointList[i].x;

		if (m_v3MaxL.y < a_pointList[i].y) m_v3MaxL.y = a_pointList[i].y;
		else if (m_v3MinL.y > a_pointList[i].y) m_v3MinL.y = a_pointList[i].y;

		if (m_v3MaxL.z < a_pointList[i].z) m_v3MaxL.z = a_pointList[i].z;
		else if (m_v3MinL.z > a_pointList[i].z) m_v3MinL.z = a_pointList[i].z;
	}

	//with model matrix being the identity, local and global are the same
	m_v3MinG = m_v3MinL;
	m_v3MaxG = m_v3MaxL;

	//with the max and the min we calculate the center
	m_v3Center = (m_v3MaxL + m_v3MinL) / 2.0f;

	//we calculate the distance between min and max vectors
	m_v3HalfWidth = (m_v3MaxL - m_v3MinL) / 2.0f;

	//Get the distance between the center and either the min or the max
	m_fRadius = glm::distance(m_v3Center, m_v3MinL);
}
MyRigidBody::MyRigidBody(MyRigidBody const& a_pOther)
{
	m_pModelMngr = a_pOther.m_pModelMngr;

	m_bVisibleBS = a_pOther.m_bVisibleBS;
	m_bVisibleOBB = a_pOther.m_bVisibleOBB;
	m_bVisibleARBB = a_pOther.m_bVisibleARBB;

	m_fRadius = a_pOther.m_fRadius;

	m_v3ColorColliding = a_pOther.m_v3ColorColliding;
	m_v3ColorNotColliding = a_pOther.m_v3ColorNotColliding;

	m_v3Center = a_pOther.m_v3Center;
	m_v3MinL = a_pOther.m_v3MinL;
	m_v3MaxL = a_pOther.m_v3MaxL;

	m_v3MinG = a_pOther.m_v3MinG;
	m_v3MaxG = a_pOther.m_v3MaxG;

	m_v3HalfWidth = a_pOther.m_v3HalfWidth;
	m_v3ARBBSize = a_pOther.m_v3ARBBSize;

	m_m4ToWorld = a_pOther.m_m4ToWorld;

	m_CollidingRBSet = a_pOther.m_CollidingRBSet;
}
MyRigidBody& MyRigidBody::operator=(MyRigidBody const& a_pOther)
{
	if (this != &a_pOther)
	{
		Release();
		Init();
		MyRigidBody temp(a_pOther);
		Swap(temp);
	}
	return *this;
}
MyRigidBody::~MyRigidBody() { Release(); };

//--- a_pOther Methods
void MyRigidBody::AddCollisionWith(MyRigidBody* a_pOther)
{
	/*
		check if the object is already in the colliding set, if
		the object is already there return with no changes
	*/
	auto element = m_CollidingRBSet.find(a_pOther);
	if (element != m_CollidingRBSet.end())
		return;
	// we couldn't find the object so add it
	m_CollidingRBSet.insert(a_pOther);
}
void MyRigidBody::RemoveCollisionWith(MyRigidBody* a_pOther)
{
	m_CollidingRBSet.erase(a_pOther);
}
void MyRigidBody::ClearCollidingList(void)
{
	m_CollidingRBSet.clear();
}

void MyRigidBody::AddToRenderList(void)
{
	if (m_bVisibleBS)
	{
		if (m_CollidingRBSet.size() > 0)
			m_pModelMngr->AddWireSphereToRenderList(glm::translate(m_m4ToWorld, m_v3Center) * glm::scale(vector3(m_fRadius)), C_BLUE_CORNFLOWER);
		else
			m_pModelMngr->AddWireSphereToRenderList(glm::translate(m_m4ToWorld, m_v3Center) * glm::scale(vector3(m_fRadius)), C_BLUE_CORNFLOWER);
	}
	if (m_bVisibleOBB)
	{
		if (m_CollidingRBSet.size() > 0)
			m_pModelMngr->AddWireCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) * glm::scale(m_v3HalfWidth * 2.0f), m_v3ColorColliding);
		else
			m_pModelMngr->AddWireCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) * glm::scale(m_v3HalfWidth * 2.0f), m_v3ColorNotColliding);
	}
	if (m_bVisibleARBB)
	{
		if (m_CollidingRBSet.size() > 0)
			m_pModelMngr->AddWireCubeToRenderList(glm::translate(GetCenterGlobal()) * glm::scale(m_v3ARBBSize), C_YELLOW);
		else
			m_pModelMngr->AddWireCubeToRenderList(glm::translate(GetCenterGlobal()) * glm::scale(m_v3ARBBSize), C_YELLOW);
	}
}