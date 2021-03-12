#pragma once

#include <glm.hpp>
#include "Model.h"
#include <list>
#include <stdlib.h>
#include <noise/noise.h>
#include "noiseutils.h"

using namespace noise;

class Chunk
{
private:
	const int ySize = 3;
	const int xSize = 16;
	const int zSize = 16;

	std::list<Model*> blocks;

	std::vector<glm::vec3> vec = 
	{	
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.f, 0.f, -1.f),
	};

	bool testBlock(glm::vec3 pos);

	void GenerateChunkMesh();

public:
	Chunk(glm::vec3 pos);

	void renderChunk(Shader* shader);
};

