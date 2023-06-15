#pragma once

#include "../Object/Object.h"
#include "../Object/Components/SpriteRenderer.h"
#include "../Object/Components/Model.h"

namespace vge {

	class ChessBoard : public Object
	{

	private:

		Vector2F boardCenter = Vector2F(0.0f, 0.0f);
		float boardSize = 3.0f;

	public:

		ChessBoard();
		ChessBoard(Vector2F center, float boardSize = 3.0f);
		~ChessBoard();

		virtual void Update() override;

	};

}


