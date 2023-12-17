
#ifndef IBO_CLASS_H
#define IBO_CLASS_H

#include <GL/glew.h>

class IBO
{

public:
	GLuint ID = 0;
	IBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();

};

#endif
