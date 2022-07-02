#pragma once

namespace vge {

	class Component
	{

	private:

	public:

		Component();
		~Component();

		virtual void Behaviour() = 0;

	};


}
