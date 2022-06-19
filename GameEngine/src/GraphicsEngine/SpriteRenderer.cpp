#include "SpriteRenderer.h"

#include "GraphicsEngine.h"

#include <GL/glew.h>

namespace vge {

    SpriteRenderer::SpriteRenderer()
    {
    }

    SpriteRenderer::SpriteRenderer(const char* filename)
	{
        return;
        // Data read from the header of the BMP file
        unsigned char header[54]; // Each BMP file begins by a 54-bytes header
        unsigned int dataPos;     // Position in the file where the actual data begins
        unsigned int imageSize;   // = width*height*3

        // Open the file
        FILE* file = fopen(filename, "rb");
        if (!file) { printf("Image could not be opened\n"); return; }

        if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
            printf("Not a correct BMP file\n");
            return;
        }

        if (header[0] != 'B' || header[1] != 'M') {
            printf("Not a correct BMP file\n");
            return;
        }

        // Read ints from the byte array
        dataPos = *(int*)&(header[0x0A]);
        imageSize = *(int*)&(header[0x22]);
        this->width = *(int*)&(header[0x12]);
        this->height = *(int*)&(header[0x16]);

        // Some BMP files are misformatted, guess missing information
        if (imageSize == 0)    imageSize = this->width * this->height * 3; // 3 : one byte for each Red, Green and Blue component
        if (dataPos == 0)      dataPos = 54; // The BMP header is 

        // Create a buffer
        this->textureData = new unsigned char[imageSize];

        // Read the actual data from the file into the buffer
        fread(this->textureData, 1, imageSize, file);

        //Everything is in memory now, the file can be closed
        fclose(file);

	}

	void SpriteRenderer::Behaviour()
	{
	}

}
