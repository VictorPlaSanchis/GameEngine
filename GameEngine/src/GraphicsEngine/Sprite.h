#pragma once

namespace vge {

	class Sprite
	{

	private:

		unsigned int sizeX, sizeY;
		unsigned int scaleX, scaleY;


	public:

		Sprite();
		~Sprite();
		
		Sprite(unsigned int sizeX, unsigned int sizeY, unsigned int scaleX, unsigned int scaleY);

	};

}

