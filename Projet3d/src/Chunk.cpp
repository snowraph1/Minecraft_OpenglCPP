#include "Chunk.h"

Chunk::Chunk(glm::vec3 pos) {

	module::Perlin myModule;

	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(256, 256);
	heightMapBuilder.SetBounds(1, 8, 1, 8);
	heightMapBuilder.Build();

	for (int x = 0; x < this->zSize; x++) {
		for (int z = 0; z < this->zSize; z++) {
			int test = rand() % 3 + 1;

			//cout << glm::roundEven(heightMap.GetValue(x, z) * 10) << "\n";

			int height = glm::abs(glm::roundEven(heightMap.GetValue(x, z) * 10.f));

			cout << height << "\n";

			for (int y = 0; y < height; y++) {
				glm::vec3 chunkPos(x - xSize / 2 + pos.x, y + pos.y, z - zSize / 2 + pos.z);

				Model* block = new Model(Grass, chunkPos);

				blocks.push_back(block);
			}
		}
	}

	GenerateChunkMesh();
}

void Chunk::GenerateChunkMesh() {
	for (Model* var : blocks)
	{
		vector<bool> size = { true, true, true, true, true, true };

		for (int i = 0; i < 6; i ++) {
			if (!testBlock(var->GetWorldPos() + vec[i])) {
				size[i] = false;
			}
		}

		if (size != vector<bool>{false, false, false, false, false, false}) {
			var->GenerateMesh(size);
		}
	}
}

bool Chunk::testBlock(glm::vec3 pos) {

	for (Model* var : blocks)
	{
		//std::cout << var->GetWorldPos().x <<"\n";
		if (var->GetWorldPos() == pos) {
			return false;
		}
	}

	return true;
}

void Chunk::renderChunk(Shader* shader) {
	for (Model* var : blocks)
	{
		//std::cout << "allo : " << var->getGenerated() << "   " << var->GetWorldPos().x << ", " << var->GetWorldPos().z << "\n";
		//var->mesh->Render(shader);

		if (var->getGenerated()) {
			var->mesh->Render(shader);
		}
	}
}

