#pragma once
#include<map>
#include "../Object/Components/Model.h"

namespace vge {

	class ObjLoader
	{

	private:

		std::map<const char*, Model*> modelsLoaded;

	public:

		ObjLoader();
		~ObjLoader();

		static ObjLoader* get();

		static Model* loadObj(const char* path);

	};

};

#define ObjLoaderVGE (*vge::ObjLoader::get())