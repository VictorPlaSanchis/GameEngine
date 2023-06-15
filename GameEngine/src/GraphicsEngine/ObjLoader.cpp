#include "ObjLoader.h"

#include "../Log/Console.h"
#include "../GLM/glm/ext/vector_float3.hpp"

#include <set>

namespace vge {
	ObjLoader::ObjLoader()
	{
	}
	ObjLoader::~ObjLoader()
	{
	}
	ObjLoader* ObjLoader::get()
	{
		static ObjLoader objLoader;
		return &objLoader;
	}
	Model* ObjLoader::loadObj(const char* path)
	{
		std::map<const char*, Model*>::iterator it = ObjLoaderVGE.modelsLoaded.find(path);
		if (it != ObjLoaderVGE.modelsLoaded.end()) return  ObjLoaderVGE.modelsLoaded[path];
		
		ConsoleDebugS("Loading new model " + (std::string)path, GREEN, GRAPHICS_ENGINE);

		Model* modelToLoad = new Model();

		FILE* file = fopen(path, "r");

		if (!file) {
			ConsoleError((std::string)path + " couldn't be loaded.");
			return new Model();
		}
		
		std::vector<float> data;
		std::vector<float> dataColor;
		std::vector<float> dataTexCoord;
		std::vector<float> dataNormals;
		std::vector<unsigned int> dataIndexs;
		std::vector<unsigned int> dataTexCoordsIndexs;
		std::vector<unsigned int> dataNormalsIndexs;
		std::vector<unsigned int> dataColorIndexs;

		int res;
		char lineHeader[128];
		res = fscanf(file, "%s", lineHeader);
		while (res != EOF) {
			if (strcmp(lineHeader, "v") == 0) {
				float vertex[3];
				fscanf(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);
				data.push_back(vertex[0]); data.push_back(vertex[1]); data.push_back(vertex[2]);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				float uv[2];
				fscanf(file, "%f %f\n", &uv[0], &uv[1]);
				dataTexCoord.push_back(uv[0]); dataTexCoord.push_back(uv[1]);
			} 
			else if (strcmp(lineHeader, "vn") == 0) {
				float normal[3];
				fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
				dataNormals.push_back(normal[0]); dataNormals.push_back(normal[1]); dataNormals.push_back(normal[2]);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					ConsoleError((std::string)path + " couldn't be loaded.");
					break;
				}
				dataIndexs.push_back(vertexIndex[0]-1);
				dataIndexs.push_back(vertexIndex[1]-1);
				dataIndexs.push_back(vertexIndex[2]-1);
				dataTexCoordsIndexs.push_back(uvIndex[0]-1);
				dataTexCoordsIndexs.push_back(uvIndex[1]-1);
				dataTexCoordsIndexs.push_back(uvIndex[2]-1);
				dataNormalsIndexs.push_back(normalIndex[0]-1);
				dataNormalsIndexs.push_back(normalIndex[1]-1);
				dataNormalsIndexs.push_back(normalIndex[2]-1);
			}
			res = fscanf(file, "%s", lineHeader);
		}

		fclose(file);

		// Parse MultiIndex .obj format to UniIndex draw opengl format

		std::vector<float> vertexs, texCoords, normals;
		std::vector<unsigned int> vertexsIndexs;

		std::set<std::string> indexsVisited = std::set<std::string>();

		size_t numIndexs = dataIndexs.size();
		for (int i = 0; i < numIndexs; i++) 
		{
			int vI = dataIndexs[i];
			int tI = dataTexCoordsIndexs[i];
			int nI = dataNormalsIndexs[i];
			std::string id = std::to_string(vI) + '/' + std::to_string(tI) + '/' + std::to_string(nI);
			
			std::set<std::string>::iterator it = indexsVisited.find(id);
			if (it == indexsVisited.end()) 
			{
				// Afegir vertex/texcoord/normal
				vertexs.push_back(data[(vI * 3)]);
				vertexs.push_back(data[(vI * 3) + 1]);
				vertexs.push_back(data[(vI * 3) + 2]);
				texCoords.push_back(dataTexCoord[(tI * 2)]);
				texCoords.push_back(dataTexCoord[(tI * 2) + 1]);
				normals.push_back(dataNormals[(nI * 3)]);
				normals.push_back(dataNormals[(nI * 3) + 1]);
				normals.push_back(dataNormals[(nI * 3) + 2]);
				vertexsIndexs.push_back(i);
			}
			else
			{
				vertexsIndexs.push_back(i);
			}
			
		}

		modelToLoad->assignVertexs(vertexs);
		modelToLoad->assignVertexsColor({});
		modelToLoad->assignVertexsTexCoord(texCoords);
		modelToLoad->assignVertexsNormals(normals);
		modelToLoad->assignVertexsIndexs(vertexsIndexs);
		modelToLoad->assignVertexsColorIndexs({});
		modelToLoad->assignVertexsTexCoordIndexs({});
		modelToLoad->assignVertexsNormalsIndexs({});

		ObjLoaderVGE.modelsLoaded.insert(std::make_pair(path, modelToLoad));
		return modelToLoad;
	}

};