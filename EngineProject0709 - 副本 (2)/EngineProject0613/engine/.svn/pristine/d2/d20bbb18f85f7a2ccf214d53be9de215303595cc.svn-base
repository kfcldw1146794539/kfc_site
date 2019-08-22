
#include <glad/glad.h>

class UserData_A {
	GLuint programObject;

	// Attribute locations
	GLint  positionLoc;
	GLint  normalLoc;

	// Sampler location
	GLint samplerLoc;

	// Texture handle
	GLuint textureId;

	// Vertex data
	int      numIndices;
	GLfloat *vertices;
	GLfloat *normals;
	GLuint  *indices;

	unsigned int VBO, vao, EBO;
	void setupPoinShuXing()
	{
		glGenBuffers(1, &VBO);
		

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		// Load the normal
		glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, normals);

		
		
		glEnableVertexAttribArray(positionLoc);
		glEnableVertexAttribArray(normalLoc);
	}
};
class UserData_B {
	GLuint programObject;

	// Attribute locations
	GLint  positionLoc;
	GLint  normalLoc;

	// Sampler location
	GLint samplerLoc;

	// Texture handle
	GLuint textureId;

	// Vertex data
	int      numIndices;
	GLfloat *vertices;
	GLfloat *normals;
	GLuint  *indices;

	unsigned int VBO, vao;
	void setupPoinShuXing()
	{
		glVertexAttribPointer(positionLoc, 3, GL_FLOAT,
			GL_FALSE, 0, vertices);
		// Load the normal
		glVertexAttribPointer(normalLoc, 3, GL_FLOAT,
			GL_FALSE, 0, normals);

		glEnableVertexAttribArray(positionLoc);
		glEnableVertexAttribArray(normalLoc);
	}
};