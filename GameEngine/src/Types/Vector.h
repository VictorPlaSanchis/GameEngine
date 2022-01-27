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

		Vector<T, D> Vector<T, D>::operator+=(const Vector<T, D>& direction)
		{
			static_assert(sizeof(direction) == sizeof(values), "Incompatible sum beetwen two vectors of different dimensions.");
			Vector<T, D> result = Vector<T, D>();
			for (int i = 0; i < D; i++) {
				//result += this->values[i] + direction[i];
			}
			return result;
		}

		T getX() { return values[0]; }
		T getY() { return values[1]; }
		T getZ() { return values[2]; }

	};


#define x getX()
#define y getY()
#define z getZ();

}