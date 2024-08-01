#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class RenderableObject {
private:
	RenderableObject(float vertexes[], int vertexSize, unsigned int indices[], int indicesSize, Shader& sh);
public:
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
	VertexBufferLayout vertexBufferLayout;
	IndexBuffer indexBuffer;
	Shader& relatedShader;

	~RenderableObject();

	static RenderableObject* MakeObject2D(float vertexes[], int vertexSize, unsigned int indices[], int indicesSize, Shader& sh);
	static RenderableObject* MakeObject3D(float vertexes[], int vertexSize, unsigned int indices[], int indicesSize, Shader& sh);
};