#include "stdafx.h"
#include <fstream>
#include <vector>

const string Material::folder = "Shaders/";
GLuint Material::vertLibId = 0;
GLuint Material::fragLibId = 0;

Material::Material() {}

Material::Material(string shaderName)
{
	string vertName("Vert");
	vertName += shaderName;
	string fragmentName("Frag");
	fragmentName += shaderName;

	if (vertLibId == 0) 
	{
		vertLibId = loadShader("VertLibrary.glsl", GL_VERTEX_SHADER);
		fragLibId = loadShader("FragLibrary.glsl", GL_FRAGMENT_SHADER);
	}

	GLuint vertexShaderID = loadShader(vertName.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShaderID = loadShader(fragmentName.c_str(), GL_FRAGMENT_SHADER);
	linkProgram(vertexShaderID, fragmentShaderID);
}

GLuint Material::getID()
{
	return id;
}

GLuint Material::loadShader(const char* name, GLenum type)
{

	GLuint shaderID = glCreateShader(type);

	// Read the Shader code from the file
	string shaderCode;
	
	ifstream shaderStream(folder + name, ios::in);
	if(shaderStream.is_open())
	{
		string Line = "";
		while(getline(shaderStream, Line))
			shaderCode += "\n" + Line;
		shaderStream.close();
	}
	else
	{
		printf("Impossible to open %s.", name);
		getchar();
		return shaderID;
	}

	GLint result = GL_FALSE;
	int infoLogLength;


	// Compile Shader
	printf("Compiling shader : %s\n", name);
	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer , NULL);
	glCompileShader(shaderID);

	// Check Shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 )
	{
		vector<char> shaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
	}	

	return shaderID;
}

void Material::linkProgram(GLuint vert, GLuint frag) 
{
	GLint result = GL_FALSE;
	int infoLogLength;

	printf("Linking program\n");
	id = glCreateProgram();
	glAttachShader(id, vertLibId);
	glAttachShader(id, vert);
	glAttachShader(id, fragLibId);
	glAttachShader(id, frag);
	glLinkProgram(id);

	// Check the program
	glGetProgramiv(id, GL_LINK_STATUS, &result);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		vector<char> ProgramErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(id, infoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	/*glDeleteShader(vert);
	glDeleteShader(frag);*/
}