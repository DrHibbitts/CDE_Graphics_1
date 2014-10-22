/***
 * Copyright 2013, 2014 Moises J. Bonilla Caraballo (Neodivert)
 *
 * This file is part of MSL.
 *
 * MSL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License v3 as published by
 * the Free Software Foundation.
 *
 * MSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with COMO.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#include "ShaderLoader.h"

/***
 * 3. Shader loading
 ***/

ShaderLoader::ShaderLoader()
{
	shaderProgram = 0;
}

ShaderLoader::~ShaderLoader()
{
}

GLuint ShaderLoader::loadShaderProgram(const char* vertexShaderFilePath,
		const char* fragmentShaderFilePath)
{
	GLint linkingResult;

	shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
	{
		throw std::runtime_error(
				"Error at ShaderLoader::loadShaderProgram() - glCreateProgram() returned 0");
	}

	// Load both vertex and fragment shaders.
	loadShaderObject( GL_VERTEX_SHADER, vertexShaderFilePath);
	loadShaderObject( GL_FRAGMENT_SHADER, fragmentShaderFilePath);

	// Link the shader program and check the result.
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkingResult);

	if (linkingResult == GL_FALSE)
	{
		throwLinkingError();
	}

	return shaderProgram;
}

GLuint ShaderLoader::loadShaderProgram(const char* vertexShaderFilePath,
		const char* geometryShaderFilePath, const char* fragmentShaderFilePath)
{
	GLint linkingResult;

	shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
	{
		throw std::runtime_error(
				"Error at ShaderLoader::loadShaderProgram() - glCreateProgram() returned 0");
	}

	// Load both vertex and fragment shaders.
	loadShaderObject( GL_VERTEX_SHADER, vertexShaderFilePath);
	loadShaderObject( GL_GEOMETRY_SHADER, geometryShaderFilePath);
	loadShaderObject( GL_FRAGMENT_SHADER, fragmentShaderFilePath);

	// Link the shader program and check the result.
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkingResult);

	if (linkingResult == GL_FALSE)
	{
		throwLinkingError();
	}

	return shaderProgram;
}

/***
 * 5. Auxiliar methods
 ***/

void ShaderLoader::loadShaderObject(GLenum shaderType, const char* shaderFile)
{
	const GLint STR_SIZE = 5112;
	GLchar* shaderCode = new GLchar[STR_SIZE]();
	GLuint shaderObject;
	GLint compilationResult;

	// Create shader object.
	shaderObject = glCreateShader(shaderType);

	// Read shader source from file.
	readFile(shaderFile, shaderCode, STR_SIZE);
	glShaderSource(shaderObject, 1, (const GLchar**) (&shaderCode), &STR_SIZE);

	// Compile shader and check compilation result.
	glCompileShader(shaderObject);
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compilationResult);

	if (compilationResult == GL_FALSE)
	{
		throwCompilingError(shaderObject);
	}

	// Attach shader object to shader program.
	glAttachShader(shaderProgram, shaderObject);

	delete[] shaderCode;
}

void ShaderLoader::readFile(const char* filePath, GLchar* buffer,
		const unsigned int n)
{
	// Open given file.
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		return;
	}

	// Copy file content to buffer and append a null character.
	file.read(buffer, n - 1);
	buffer[file.gcount()] = 0;

	// Close file.
	file.close();
}

void ShaderLoader::throwLinkingError() const
{
	const GLint MAX_LOG_SIZE = 1024;
	GLchar log[MAX_LOG_SIZE];

	glGetProgramInfoLog(shaderProgram, MAX_LOG_SIZE, NULL, log);
	const std::string errorMessage = std::string(
			"Error linking shader program - log:\n");
	throw std::runtime_error(errorMessage);
}

void ShaderLoader::throwCompilingError(GLuint shaderObject) const
{
	const GLint MAX_LOG_SIZE = 1024;
	GLchar log[MAX_LOG_SIZE];

	glGetShaderInfoLog(shaderObject, MAX_LOG_SIZE, NULL, log);
	const std::string errorMessage = std::string(
			"Error compiling shader object - log:\n");
	throw std::runtime_error(errorMessage);
}

ShaderLoader& ShaderLoader::operator =(const ShaderLoader& otherShaderLoader)
{
	shaderProgram = otherShaderLoader.shaderProgram;
	return *this;
}

ShaderLoader& ShaderLoader::operator =(ShaderLoader& otherShaderLoader)
{
	shaderProgram = otherShaderLoader.shaderProgram;
	return *this;
}
