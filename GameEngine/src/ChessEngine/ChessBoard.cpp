#include "ChessBoard.h"
#include "whiteSquare.h"
#include "blackSquare.h"

vge::ChessBoard::ChessBoard()
{

	Vector2F leftUpCorner = Vector2F(boardCenter[0] - ((boardSize / 8) * 4), boardCenter[1] - ((boardSize / 8) * 4));

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			float positionX = leftUpCorner[0] + ((boardSize / 8) * i);
			float positionY = leftUpCorner[1] + ((boardSize / 8) * j);
			if ((i + j) % 2 != 0) {
				WhiteSquare* object = new WhiteSquare();
				object->transform->move(Vector3F(positionX, positionY, 0.0f));
				object->transform->scale(Vector3F(boardSize / 16, boardSize / 16, 1.0f));
				this->addChild(object);
			}
			else {
				BlackSquare* object = new BlackSquare();
				object->transform->move(Vector3F(positionX, positionY, 0.0f));
				object->transform->scale(Vector3F(boardSize / 16, boardSize / 16, 1.0f));
				this->addChild(object);
			}
		}
	}

	this->transform->move(Vector3F(boardSize / 16, boardSize / 16, 0.0f)); // center the board
}

vge::ChessBoard::ChessBoard(Vector2F center, float boardSize)
{
	this->boardCenter = center;
	this->boardSize = boardSize;

	Vector2F leftUpCorner = Vector2F(boardCenter[0] - ((boardSize / 8) * 4), boardCenter[1] - ((boardSize / 8) * 4));

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			float positionX = leftUpCorner[0] + ((boardSize / 8) * i);
			float positionY = leftUpCorner[1] + ((boardSize / 8) * j);
			if ((i + j) % 2 != 0) {
				WhiteSquare* object = new WhiteSquare();
				object->transform->move(Vector3F(positionX, positionY, 0.0f));
				object->transform->scale(Vector3F(boardSize / 16, boardSize / 16, 1.0f));
				this->addChild(object);
			}
			else {
				BlackSquare* object = new BlackSquare();
				object->transform->move(Vector3F(positionX, positionY, 0.0f));
				object->transform->scale(Vector3F(boardSize / 16, boardSize / 16, 1.0f));
				this->addChild(object);
			}
		}
	}

	this->transform->move(Vector3F(boardSize / 16, boardSize / 16, 0.0f)); // center the board
}

vge::ChessBoard::~ChessBoard()
{
}

void vge::ChessBoard::Update()
{

}
