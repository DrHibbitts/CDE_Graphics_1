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
 * along with MSL.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#ifndef SHADER_LOADER_HPP
#define SHADER_LOADER_HPP

/***
 * Includes
 ***/
#include <GL/glew.h>

// OpenGL
// http://www.opengl.org/discussion_boards/showthread.php/172481-glGenBuffer-was-not-declared
#define GL_GLEXT_PROTOTYPES
extern "C" {
#include <GL/gl.h>
#include <GL/glext.h>
}

#include <fstream>      // File management
#include <stdexcept>    // std::runtime_error

/*!
 * \brief The ShaderLoader class - Minimalist class for compiling and linking
 * OpenGL shader programs. Just instance this class and call any of the methods
 * loadShaderProgram(). You will get the ID of a freshly OpenGL shader
 * program... or a runtime_error exception.
 *
 * NOTE: This class only loads shader programs. Once you get your program ID,
 * it's your responsability to call glUseProgram() for using the program
 * and / or glDeleteProgram() for destroying it.
 */
class ShaderLoader {
public:
	/***
	 * 1. Construction
	 ***/
	ShaderLoader() = default;
	ShaderLoader(const ShaderLoader&) = delete;
	ShaderLoader(ShaderLoader&&) = delete;

	/***
	 * 2. Destruction
	 ***/
	~ShaderLoader() = default;

	/***
	 * 3. Shader loading
	 ***/
	// Vertex + fragment shaders
	GLuint loadShaderProgram(const char* vertexShaderFilePath,
			const char* fragmentShaderFilePath);

	// Vertex + geometry + fragment shaders.
	GLuint loadShaderProgram(const char* vertexShaderFilePath,
			const char* geometryShaderFilePath,
			const char* fragmentShaderFilePath);

	/***
	 * 4. Operators
	 ***/
	ShaderLoader& operator=(const ShaderLoader&) = delete;
	ShaderLoader& operator=(ShaderLoader&&) = delete;

private:
	/***
	 * 5. Auxiliar methods
	 ***/
	void loadShaderObject(GLenum shaderType, const char* shaderFile);
	void readFile(const char* file, GLchar* buffer, const unsigned int n);
	void throwLinkingError() const;
	void throwCompilingError(GLuint shaderObject) const;

private:
	/***
	 * Attributes
	 ***/
	// Current program being built.
	GLuint shaderProgram;
};

#endif // SHADER_LOADER_HPP
