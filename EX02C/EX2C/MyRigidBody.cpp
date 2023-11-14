#pragma region DO NOT CHANGE
#include "MyRigidBody.h"
using namespace BTX;
//Helper function, feel free to use it, it will take one vector from local to global space
vector3 MyRigidBody::Globalize(vector3 a_v3Input)
{
	return m_m4ToWorld * vector4(a_v3Input, 1.0f);
}
#pragma endregion

vector3 MyRigidBody::FindMax(std::vector<vector3> a_pointList)
{
	float f_xMax = a_pointList[0].x;
	float f_yMax = a_pointList[0].y;
	float f_zMax = a_pointList[0].z;
	int i_verts = a_pointList.size();

	for (int i = 0; i < i_verts; i++)
	{
		if (a_pointList[i].x > f_xMax)
		{
			f_xMax = a_pointList[i].x;
		}
		if (a_pointList[i].y > f_yMax)
		{
			f_yMax = a_pointList[i].y;
		}
		if (a_pointList[i].z > f_zMax)
		{
			f_zMax = a_pointList[i].z;
		}
	}
	return vector3(f_xMax, f_yMax, f_zMax);
}

vector3 MyRigidBody::FindMin(std::vector<vector3> a_pointList)
{
	float f_xMin = a_pointList[0].x;
	float f_yMin = a_pointList[0].y;
	float f_zMin = a_pointList[0].z;
	int i_verts = a_pointList.size();

	for (int i = 0; i < i_verts; i++)
	{
		if (a_pointList[i].x < f_xMin)
		{
			f_xMin = a_pointList[i].x;
		}
		if (a_pointList[i].y < f_yMin)
		{
			f_yMin = a_pointList[i].y;
		}
		if (a_pointList[i].z < f_zMin)
		{
			f_zMin = a_pointList[i].z;
		}
	}
	return vector3(f_xMin, f_yMin, f_zMin);
}

// Didn't end up using this function
vector3 MyRigidBody::FindCenter(std::vector<vector3> a_pointList)
{
	float sum_x = 0.0f;
	float sum_y = 0.0f;
	float sum_z = 0.0f;
	int i_verts = a_pointList.size();

	for (int i = 0; i < i_verts; i++)
	{
		sum_x += a_pointList[i].x;
		sum_y += a_pointList[i].y;
		sum_z += a_pointList[i].z;
	}

	return vector3(sum_x / i_verts,
		sum_y / i_verts,
		sum_z / i_verts);
}

void MyRigidBody::Update(void)
{
#pragma region DO NOT CHANGE
	static quaternion qDirection;
	qDirection = qDirection * glm::angleAxis(glm::radians(1.0f), AXIS_Z);
#pragma endregion

	//Update the m_v3Direction of the arrow, this is the global Y axis oriented by qDirection (as you did Forward in camera assigment)
	m_v3Direction = glm::normalize(glm::rotate(qDirection,AXIS_Y));
}
//Allocation
MyRigidBody::MyRigidBody(std::vector<vector3> a_pointList)
{
#pragma region DO NOT CHANGE
	Init();
	//Count the points of the incoming list
	uint uVertexCount = a_pointList.size();

	//If there are none just return, we have no information to create the BS from
	if (uVertexCount == 0)
		return;
#pragma endregion

	//replace the following with your code
	m_v3MaxG = m_v3MaxL = FindMax(a_pointList);
	m_v3MaxG = Globalize(m_v3MaxL);
	m_v3MinG = m_v3MinL = FindMin(a_pointList);
	m_v3MinG = Globalize(m_v3MinL);
	m_v3Center = (m_v3MaxL + m_v3MinL) / 2.0f;
	m_v3HalfWidth = (m_v3MaxL - m_v3MinL) / 2.0f;
	m_fRadius = glm::distance(m_v3Center, m_v3MaxL);
}
void MyRigidBody::SetModelMatrix(matrix4 a_m4ModelMatrix)
{
#pragma region DO NOT CHANGE
	//to save some calculations if the model matrix is the same there is nothing to do here
	if (a_m4ModelMatrix == m_m4ToWorld)
		return;

	//replace the following with your code
	m_m4ToWorld = a_m4ModelMatrix;
#pragma endregion

	//Add your code
	
	// Find corners of the cube
	vector3 vertices[8];
	vertices[0] = vector3(m_v3MinL.x, m_v3MinL.y, m_v3MinL.z); // left bottom back
	vertices[1] = vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MinL.z); // right bottom back
	vertices[2] = vector3(m_v3MinL.x, m_v3MaxL.y, m_v3MinL.z); // left top back
	vertices[3] = vector3(m_v3MaxL.x, m_v3MaxL.y, m_v3MinL.z); // right top back
	vertices[4] = vector3(m_v3MinL.x, m_v3MinL.y, m_v3MaxL.z); // left bottom front
	vertices[5] = vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MaxL.z); // right bottom front
	vertices[6] = vector3(m_v3MinL.x, m_v3MaxL.y, m_v3MaxL.z); // left top front
	vertices[7] = vector3(m_v3MaxL.x, m_v3MaxL.y, m_v3MaxL.z); // right top front

	// Convert to global space
	for (int i = 0; i < 8; i++)
	{
		vertices[i] = Globalize(vertices[i]);
	}

	// Set the first corner to max and min
	m_v3MaxG = m_v3MinG = vertices[0];

	// Find new global max and min
	for (int i = 1; i < 8; ++i)
	{
		if (m_v3MaxG.x < vertices[i].x)
		{
			m_v3MaxG.x = vertices[i].x;
		}
		else if (m_v3MinG.x > vertices[i].x)
		{
			m_v3MinG.x = vertices[i].x;
		}

		if (m_v3MaxG.y < vertices[i].y)
		{
			m_v3MaxG.y = vertices[i].y;
		}
		else if (m_v3MinG.y > vertices[i].y) 
		{ 
			m_v3MinG.y = vertices[i].y; 
		}

		if (m_v3MaxG.z < vertices[i].z)
		{
			m_v3MaxG.z = vertices[i].z;
		}
		else if (m_v3MinG.z > vertices[i].z)
		{
			m_v3MinG.z = vertices[i].z;
		}
	}

	m_v3ARBBSize = m_v3MaxG - m_v3MinG; 
}
bool MyRigidBody::TestARBB(MyRigidBody* const other)
{
	// Check for separating axis on x
	if (m_v3MaxG.x < other->GetMinGlobal().x || m_v3MinG.x > other->GetMaxGlobal().x)
	{
		return false;
	}
	// Check for separating axis on y
	if (m_v3MaxG.y < other->GetMinGlobal().y || m_v3MinG.y > other->GetMaxGlobal().y)
	{
		return false;
	}
	// Check for separating axis on z
	if (m_v3MaxG.z < other->GetMinGlobal().z || m_v3MinG.z > other->GetMaxGlobal().z)
	{
		return false;
	}
	// No separating axis found, must be colliding
	return true;
}

#pragma region DO NOT CHANGE
bool MyRigidBody::IsColliding(MyRigidBody* const other)
{
	//check if spheres are colliding
	bool bColliding = TestARBB(other);
	
	//if they are check the Axis Aligned Bounding Box
	if (bColliding) //they are colliding with bounding sphere
	{
		if (bColliding) //they are colliding with bounding box also
		{
			this->AddCollisionWith(other);
			other->AddCollisionWith(this);
		}
		else //they are not colliding with bounding box
		{
			this->RemoveCollisionWith(other);
			other->RemoveCollisionWith(this);
		}
	}
	else //they are not colliding with bounding sphere
	{
		this->RemoveCollisionWith(other);
		other->RemoveCollisionWith(this);
	}
	return bColliding;
}
void MyRigidBody::Init(void)
{
	m_pModelMngr = ModelManager::GetInstance();
	m_bVisibleBS = false;
	m_bVisibleOBB = true;
	m_bVisibleARBB = true;

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
void MyRigidBody::Swap(MyRigidBody& other)
{
	std::swap(m_pModelMngr, other.m_pModelMngr);
	std::swap(m_bVisibleBS, other.m_bVisibleBS);
	std::swap(m_bVisibleOBB, other.m_bVisibleOBB);
	std::swap(m_bVisibleARBB, other.m_bVisibleARBB);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_v3ColorColliding, other.m_v3ColorColliding);
	std::swap(m_v3ColorNotColliding, other.m_v3ColorNotColliding);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3MinL, other.m_v3MinL);
	std::swap(m_v3MaxL, other.m_v3MaxL);

	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3ARBBSize, other.m_v3ARBBSize);

	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_CollidingRBSet, other.m_CollidingRBSet);
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
vector3 MyRigidBody::GetCenterGlobal(void) { return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
vector3 MyRigidBody::GetMinGlobal(void) { return m_v3MinG; }
vector3 MyRigidBody::GetMaxGlobal(void) { return m_v3MaxG; }
vector3 MyRigidBody::GetHalfWidth(void) { return m_v3HalfWidth; }
matrix4 MyRigidBody::GetModelMatrix(void) { return m_m4ToWorld; }



//The big 3

MyRigidBody::MyRigidBody(MyRigidBody const& other)
{
	m_pModelMngr = other.m_pModelMngr;

	m_bVisibleBS = other.m_bVisibleBS;
	m_bVisibleOBB = other.m_bVisibleOBB;
	m_bVisibleARBB = other.m_bVisibleARBB;

	m_fRadius = other.m_fRadius;

	m_v3ColorColliding = other.m_v3ColorColliding;
	m_v3ColorNotColliding = other.m_v3ColorNotColliding;

	m_v3Center = other.m_v3Center;
	m_v3MinL = other.m_v3MinL;
	m_v3MaxL = other.m_v3MaxL;

	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3ARBBSize = other.m_v3ARBBSize;

	m_m4ToWorld = other.m_m4ToWorld;

	m_CollidingRBSet = other.m_CollidingRBSet;
}
MyRigidBody& MyRigidBody::operator=(MyRigidBody const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyRigidBody temp(other);
		Swap(temp);
	}
	return *this;
}
MyRigidBody::~MyRigidBody() { Release(); };

//--- other Methods
void MyRigidBody::AddCollisionWith(MyRigidBody* other)
{
	/*
		check if the object is already in the colliding set, if
		the object is already there return with no changes
	*/
	auto element = m_CollidingRBSet.find(other);
	if (element != m_CollidingRBSet.end())
		return;
	// we couldn't find the object so add it
	m_CollidingRBSet.insert(other);
}
void MyRigidBody::RemoveCollisionWith(MyRigidBody* other)
{
	m_CollidingRBSet.erase(other);
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
	m_pModelMngr->AddLineToRenderList(m_m4ToWorld * glm::translate(m_v3Center), vector3(0.0, 0.0, 0.0), m_v3Direction * 10.0f, C_BLUE, C_RED);
}
#pragma endregion