#include <array>
#include <math.h>

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

		Vector<T, D> operator/(T divisor)
		{
			Vector<T, D> result;
			for (int i = 0; i < D; i++)
			{
				result[i] = this->get(i) / divisor;
			}
			return result;
		}

		void operator*=(T scalar)
		{
			(*this) = (*this) * scalar;
		}

		static Vector<T, D> normalize(Vector<T, D> vector) 
		{
			const Vector<T, D> auxiliar = vector;
			T modul = T();
			for (int i = 0; i < D; i++) {
				T powNi = static_cast<T>(pow(static_cast<double>(vector[i]), D));
				modul += powNi;
			}
			Vector<T, D> result = vector / static_cast<T>(pow(static_cast<double>(modul), 1.0f / D));
			for (int i = 0; i < D; i++) {
				if (isnan(static_cast<double>(result[i]))) return auxiliar;
			}
			return result;
		}

	};

#define Vector3F Vector<float, 3>
#define Vector2F Vector<float, 2>
#define Vector3D Vector<double, 3>
#define Vector2D Vector<double, 2>
#define Vector3I Vector<int, 3>
#define Vector2I Vector<int, 2>
#define Vector3UI Vector<unsigned int, 3>
#define Vector2UI Vector<unsigned int, 2>

}