#include <array>

namespace vge {

	template<typename T, int D>
	class Vector {

	private:

		std::array<T, D> values;

	public:

		Vector()
		{
			for (int i = 0; i < D; i++) {
				this->values[i] = T();
			}
		}

		~Vector()
		{
		}

		template<typename... Ps>
		Vector(Ps... params)
			: values({params...})
		{
		}

		void operator+=(Vector<T, D> direction)
		{
			static_assert(sizeof(direction) == sizeof(values), "Incompatible sum between two vectors of different dimensions.");
			for (int i = 0; i < D; i++) {
				this->operator[](i) += direction.operator[](i);
			}
		}

		T& get(int index)
		{
			if (sizeof(values) <= index) throw("Index out of bounds.");
			return this->values[index];
		}

		T& operator[](int index)
		{
			return get(index);
		}

		const T& operator[](int index) const
		{
			return get(index);
		}

		Vector<T, D> operator+(Vector<T, D> vector)
		{ 
			Vector<T, D> result;
			static_assert(sizeof(vector) == sizeof(values), "Incompatible sum between two vectors of different dimensions.");
			int i = 0;
			for (T value : vector.values) {
				result.values[i] += this->operator[](i);
				result.values[i] += vector.operator[](i);
				i++;
			}
			return result;
		}

		void operator=(Vector<T,D> vector) 
		{
			static_assert(sizeof(vector) == sizeof(values), "Incompatible assignation between two vectors of different dimensions.");
			int i = 0;
			for (T value : vector.values) {
				this->values[i] = value;
				i++;
			}
		}

		Vector<T,D> operator*(T scalar)
		{
			Vector<T, D> result;
			for (int i = 0; i < D; i++)
			{
				result[i] = this->get(i) * scalar;
			}
			return result;
		}

		void operator*=(T scalar)
		{
			(*this) = (*this) * scalar;
		}

		T getX() { return values[0]; }
		T getY() { return values[1]; }
		T getZ() { return values[2]; }

	};


#define x getX()
#define y getY()
#define z getZ();

}