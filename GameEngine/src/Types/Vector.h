#include <array>

namespace vge {

	template<typename T, int D>
	class Vector {

	private:

		std::array<T, D> values;

	public:

		Vector()
		{
		}

		~Vector()
		{
		}

		template<typename... Ps>
		Vector(Ps... params)
			: values({ params... })
		{
		}

		T getX() { return values[0]; }
		T getY() { return values[1]; }
		T getZ() { return values[2]; }

	};


#define x getX()
#define y getY()
#define z getZ();

}