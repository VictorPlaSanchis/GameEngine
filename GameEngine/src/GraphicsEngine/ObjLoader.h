#pragma once

#include "../Object/Components/Model.h"

namespace vge {
	
	class ObjLoader
	{

	private:



	public:

		ObjLoader();
		~ObjLoader();
		static Model* loadObj(const char* path);

	};

};