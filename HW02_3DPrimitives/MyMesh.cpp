#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code

	std::vector<vector3 > vertex;
	GLfloat theta = 0;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));
	vector3 apex = vector3(0.0f, (a_fHeight/2), 0.0f);
	vector3 baseCenter = vector3(0.0f, (-a_fHeight / 2), 0.0f);

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(theta) * a_fRadius,  (-a_fHeight/2), sin(theta)* a_fRadius);
		theta += delta;
		vertex.push_back(temp);
	}

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// Generate base
		AddTri(baseCenter, vertex[i], vertex[(i + 1) % a_nSubdivisions]);
		// Connect base to apex
		AddTri(vertex[i], apex, vertex[(i + 1) % a_nSubdivisions]);
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	std::vector<vector3> vertexTop;    // Store vertices for the top circle
	std::vector<vector3> vertexBottom; // Store vertices for the bottom circle
	GLfloat theta = 0;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));

	// Generate vertices for the top and bottom circles
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 tempTop = vector3(cos(theta) * a_fRadius, a_fHeight * 0.5f, sin(theta) * a_fRadius);
		vector3 tempBottom = vector3(cos(theta) * a_fRadius, -a_fHeight * 0.5f, sin(theta) * a_fRadius);
		theta += delta;
		vertexTop.push_back(tempTop);
		vertexBottom.push_back(tempBottom);
	}

	// Generate triangles for the top and bottom circles
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// Top circle
		AddTri(vector3(0.0f, a_fHeight * 0.5f, 0.0f), vertexTop[(i + 1) % a_nSubdivisions], vertexTop[i]);

		// Bottom circle
		AddTri(vector3(0.0f, -a_fHeight * 0.5f, 0.0f), vertexBottom[i], vertexBottom[(i + 1) % a_nSubdivisions]);
	}

	// Generate side walls
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		int nextIndex = (i + 1) % a_nSubdivisions;

		// Side wall triangles
		AddQuad(vertexTop[i], vertexTop[nextIndex], vertexBottom[i], vertexBottom[nextIndex]);
	}


	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	std::vector<vector3> vertexTopOuter;    // Store vertices for the top outer circle
	std::vector<vector3> vertexBottomOuter; // Store vertices for the bottom outer circle
	std::vector<vector3> vertexTopInner;    // Store vertices for the top inner circle
	std::vector<vector3> vertexBottomInner; // Store vertices for the bottom inner circle

	GLfloat theta = 0;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));

	// Generate vertices for the top and bottom outer circles and inner circles
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 tempTopOuter = vector3(cos(theta) * a_fOuterRadius, a_fHeight * 0.5f, sin(theta) * a_fOuterRadius);
		vector3 tempBottomOuter = vector3(cos(theta) * a_fOuterRadius, -a_fHeight * 0.5f, sin(theta) * a_fOuterRadius);
		vector3 tempTopInner = vector3(cos(theta) * a_fInnerRadius, a_fHeight * 0.5f, sin(theta) * a_fInnerRadius);
		vector3 tempBottomInner = vector3(cos(theta) * a_fInnerRadius, -a_fHeight * 0.5f, sin(theta) * a_fInnerRadius);

		theta += delta;

		vertexTopOuter.push_back(tempTopOuter);
		vertexBottomOuter.push_back(tempBottomOuter);
		vertexTopInner.push_back(tempTopInner);
		vertexBottomInner.push_back(tempBottomInner);
	}

	// Generate triangles for the top and bottom outer circles
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// Top outer circle
		AddQuad(vertexTopInner[i], vertexTopInner[(i + 1) % a_nSubdivisions], vertexTopOuter[i], vertexTopOuter[(i + 1) % a_nSubdivisions]);

		// Bottom outer circle
		AddQuad(vertexBottomOuter[i], vertexBottomOuter[(i + 1) % a_nSubdivisions], vertexBottomInner[i], vertexBottomInner[(i + 1) % a_nSubdivisions]);
	}

	// Generate side walls
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(vertexTopOuter[i], vertexTopOuter[(i + 1) % a_nSubdivisions], vertexBottomOuter[i], vertexBottomOuter[(i + 1) % a_nSubdivisions]);
		AddQuad(vertexTopInner[(i + 1) % a_nSubdivisions], vertexTopInner[i], vertexBottomInner[(i + 1) % a_nSubdivisions], vertexBottomInner[i]);
	}
	// -------------------------------



	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	


	// Replace this with your code

	float deltaTheta = 2.0f * PI / static_cast<float>(a_nSubdivisionsA);
    float deltaPhi = 2.0f * PI / static_cast<float>(a_nSubdivisionsB);

    // Generate the torus vertices
    std::vector<std::vector<vector3>> circles;

    for (int i = 0; i < a_nSubdivisionsA; i++)
	{
        std::vector<vector3> vertices;
        for (int j = 0; j < a_nSubdivisionsB; j++) 
		{
            float theta = static_cast<float>(i) * deltaTheta;
            float phi = static_cast<float>(j) * deltaPhi;

            float cosTheta = cos(theta);
            float sinTheta = sin(theta);
            float cosPhi = cos(phi);
            float sinPhi = sin(phi);

            float x = (a_fOuterRadius + a_fInnerRadius * cosPhi) * cosTheta;
            float y = (a_fOuterRadius + a_fInnerRadius * cosPhi) * sinTheta;
            float z = a_fInnerRadius * sinPhi;

            vector3 vertex = vector3(x, y, z);
            vertices.push_back(vertex);
        }
        circles.push_back(vertices);
    }

    // Generate the torus faces (quads)
    for (int i = 0; i < a_nSubdivisionsA; i++) 
	{
        int nextI = (i + 1) % a_nSubdivisionsA;
        for (int j = 0; j < a_nSubdivisionsB; j++) 
		{
            int nextJ = (j + 1) % a_nSubdivisionsB;
            int current = i * a_nSubdivisionsB + j;
            int nextA = nextI * a_nSubdivisionsB + j;
            int nextB = i * a_nSubdivisionsB + nextJ;
            int nextAB = nextI * a_nSubdivisionsB + nextJ;

            // Add quad using AddQuad method
            AddQuad
			(
                circles[i][j],       
                circles[nextI][j],   
                circles[i][nextJ],   
                circles[nextI][nextJ]
            );
        }
    }

	// -------------------------------
	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// Replace this with your code
	float deltaTheta = static_cast<float>(2.0 * PI) / a_nSubdivisions;
	float deltaPhi = static_cast<float>(PI) / a_nSubdivisions;

	std::vector<vector3> vertices;
	for (int i = 0; i <= a_nSubdivisions; i++)
	{
		
		for (int j = 0; j <= a_nSubdivisions; j++)
		{
			// Calculate the spherical coordinates
			float theta = i * deltaTheta;
			float phi = j * deltaPhi;

			// Calculate the x, y, and z coordinates of the vertex on the sphere
			float x = a_fRadius * sin(phi) * cos(theta);
			float y = a_fRadius * sin(phi) * sin(theta);
			float z = a_fRadius * cos(phi);

			// Add the vertex to the list
			vertices.push_back(vector3(x, y, z));
		}
	}

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		for (int j = 0; j < a_nSubdivisions; j++)
		{
			// Calculate the indices of the vertices in the current quad
			int index0 = i * (a_nSubdivisions + 1) + j;
			int index1 = index0 + 1;
			int index2 = (i + 1) * (a_nSubdivisions + 1) + j;
			int index3 = index2 + 1;

			// Create quads
			AddQuad(
				vector3(vertices[index0]),
				vector3(vertices[index1]),
				vector3(vertices[index2]),
				vector3(vertices[index3])
			);
		}
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}

