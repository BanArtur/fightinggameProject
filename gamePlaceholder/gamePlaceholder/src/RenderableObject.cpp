#include "RenderableObject.h"

RenderableObject::RenderableObject(float vertexes[], int vertexSize, unsigned int indices[], int indicesSize, Shader& sh) :
	vertexBuffer(vertexes, vertexSize), indexBuffer(indices, indicesSize), relatedShader(sh) {
	
}

RenderableObject::~RenderableObject() {
}

RenderableObject* RenderableObject::MakeObject2D(float vertexes[], int vertexSize, unsigned int indices[], int indicesSize, Shader& sh) {
	RenderableObject* tmp = new RenderableObject(vertexes, vertexSize, indices, indicesSize, sh);
	tmp->vertexBufferLayout.Push<float>(2);
	tmp->vertexBufferLayout.Push<float>(2);
	tmp->vertexArray.AddBuffer(tmp->vertexBuffer, tmp->vertexBufferLayout);
	return tmp;
}

RenderableObject* RenderableObject::MakeObject3D(float vertexes[], int vertexSize, unsigned int indices[], int indicesSize, Shader& sh) {
	RenderableObject* tmp = new RenderableObject(vertexes, vertexSize, indices, indicesSize, sh);
	tmp->vertexBufferLayout.Push<float>(3);
	tmp->vertexBufferLayout.Push<float>(2);
	tmp->vertexArray.AddBuffer(tmp->vertexBuffer, tmp->vertexBufferLayout);
	return tmp;
}
