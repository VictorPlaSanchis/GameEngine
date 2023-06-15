#include <typeinfo>
#include <cmath>
#include <array>

#include "../GLM/glm/ext/vector_float3.hpp"

#define PI 3.14159265359

namespace vge {

	template<typename T, int D>
	class Vector;

	template<typename T>
	class Quaternion;

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
			: values({ params... })
		{
		}

		glm::vec3 ToGLM() 
		{ 
			return glm::vec3(
				this->values[0],
				this->values[1],
				this->values[2]
			); 
		}

		void operator+=(Vector<T, D> direction)
		{
			static_assert(sizeof(direction) == sizeof(values), "Incompatible sum between two vectors of different dimensions.");
			static_assert(sizeof(direction) == sizeof(values), "Incompatible sum between two vectors of different dimensions.");
			for (int i = 0; i < D; i++) {
				this->operator[](i) += direction.operator[](i);
			}
		}

		void operator-=(Vector<T, D> direction)
		{
			static_assert(sizeof(direction) == sizeof(values), "Incompatible sum between two vectors of different dimensions.");
			static_assert(sizeof(direction) == sizeof(values), "Incompatible sum between two vectors of different dimensions.");
			for (int i = 0; i < D; i++) {
				this->operator[](i) -= direction.operator[](i);
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

		Vector<T, D> operator-(Vector<T, D> vector)
		{
			Vector<T, D> result;
			static_assert(sizeof(vector) == sizeof(values), "Incompatible sum between two vectors of different dimensions.");
			int i = 0;
			for (T value : vector.values) {
				result.values[i] -= this->operator[](i);
				result.values[i] -= vector.operator[](i);
				i++;
			}
			return result;
		}

		void operator=(Vector<T, D> vector)
		{
			static_assert(sizeof(vector) == sizeof(values), "Incompatible assignation between two vectors of different dimensions.");
			int i = 0;
			for (T value : vector.values) {
				this->values[i] = value;
				i++;
			}
		}
		T operator*(Vector<T, D> vector)
		{
			T sum = T();
			for (int i = 0; i < D; i++)
			{
				sum += (*this)[i] * vector[i];
			}
			return sum;
		}
		Vector<T, D> operator*(T scalar)
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
		void operator/=(T scalar)
		{
			(*this) = (*this) / scalar;
		}

		Vector<T, D> normalize()
		{
			T modul = T();
			for (int i = 0; i < D; i++) {
				T powNi = static_cast<T>(pow(static_cast<double>((*this)[i]), D));
				modul += powNi;
			}
			Vector<T, D> result = (*this) / static_cast<T>(pow(static_cast<double>(modul), 1.0f / D));
			for (int i = 0; i < D; i++) {
				if (isnan(static_cast<double>(result[i]))) return (*this);
			}
			(*this) = result;
			return (*this);
		}

		T magnitude()
		{
			T sum = T();
			for (int i = 0; i < D; i++) {
				sum += static_cast<T>(pow(this->values[i], D - 1));
			}
			return pow(sum, (T)1 / ((T)(D - 1)));
		}
		T dot(Vector<T, D> a)
		{
			static_assert(sizeof(a.values) == sizeof(values), "Incompatible assignation between two vectors of different dimensions.");
			T sum = T();
			for (int i = 0; i < D; i++) {
				sum += a.values[i] * this->values[i];
			}
			return sum;
		}
		Vector<T, 3> cross(Vector<T, 3> vector)
		{
			std::array<T, 3> valuesB = this->values;
			std::array<T, 3> valuesA = vector.values;
			T x = ((valuesA[1] * valuesB[2]) - (valuesA[2] * valuesB[1]));
			T y = ((valuesA[0] * valuesB[2]) - (valuesA[2] * valuesB[0]));
			T z = ((valuesA[0] * valuesB[1]) - (valuesA[1] * valuesB[0]));
			return Vector<T, 3>({
				-x , y , -z
				});
		}

		Vector<T, 3> rotate(T angle, Vector<T, 3> axis)
		{
			Quaternion<T> pure = Quaternion<T>(T(), (*this));

			axis.normalize();
			Quaternion<T> rotationQuatNormalized = Quaternion<T>(angle, axis);
			rotationQuatNormalized.convertToUnitNormQuaternion();
			Quaternion<T> rotationQuatNormalizedInverse = rotationQuatNormalized.inverse();
			Quaternion<T> rotationResult = (rotationQuatNormalizedInverse * pure * rotationQuatNormalized);
			(*this) = rotationResult.getImaginari();
			return (*this);

		}

		T angleOnEulerDegrees(Vector<T, D> vector)
		{
			T anglesRad = this->angleOnRadiants(vector);
			return anglesRad * ((T)180 / PI);
		}

		T angleOnRadiants(Vector<T, D> vector)
		{
			T product = (*this) * vector;
			T magnitudA = vector.magnitude();
			T magnitudB = this->magnitude();
			if (magnitudA == T() || magnitudB == T()) return (T)0;
			else return acos(product / (magnitudA * magnitudB));
		}


	};

#define Vector3F vge::Vector<float, 3>
#define Vector2F vge::Vector<float, 2>
#define Vector3D vge::Vector<double, 3>
#define Vector2D vge::Vector<double, 2>
#define Vector3I vge::Vector<int, 3>
#define Vector2I vge::Vector<int, 2>
#define Vector3UI vge::Vector<unsigned int, 3>
#define Vector2UI vge::Vector<unsigned int, 2>

	template<typename T>
	class Quaternion {

	private:

		T real;
		Vector<T, 3> imaginari;

	public:

		Quaternion<T>()
		{
			//static_assert((typeid(float) == typeid(T)) || (typeid(double) == typeid(T)), "Invalid template typename, should be float or double.");
			this->real = T();
			this->imaginari = Vector<T, 3>({T(), T(), T()});
		}

		Quaternion<T>(T real, Vector<T, 3> imaginari)
		{
			//static_assert((typeid(float) == typeid(T)) || (typeid(double) == typeid(T)), "Invalid template typename, should be float or double.");
			this->real = real;
			this->imaginari = imaginari;
		}

		~Quaternion<T>() {}

		Vector<T, 3> getImaginari() { return this->imaginari;  }
		T getReal() { return this->real; }

		void operator +=(const Quaternion<T>& a)
		{
			real += a->real();
			imaginari += a->imaginari();
		}

		Quaternion<T> operator+(const Quaternion<T>& a)
		{
			T realSum = real + a.real;
			Vector<T, 3> imaginariSum = imaginari + a.imaginari;
			
			return Quaternion<T>(realSum, imaginariSum);
		}

		void operator -=(const Quaternion<T>& a)
		{
			this->real -= a.real();
			this->imaginari -= a.imaginari();
		}

		Quaternion<T> operator-(const Quaternion<T>& a)
		{
			T realSum = this->real - a.real;
			Vector<T, 3> imaginariSum = this->imaginari - a.imaginari;

			return Quaternion<T>(realSum, imaginariSum);
		}

		void operator *=(Quaternion<T>& a)
		{
			this->real = (this->real * a.real) - this->imaginari.dot(a.imaginari);
			this->imaginari = (this->imaginari * a.real) + (a.imaginari * this->real) + this->imaginari.cross(a.imaginari);
		}

		Quaternion<T> operator*(Quaternion<T>& a)
		{
			Quaternion<T> result;
			result.real = (this->real * a.real) - this->imaginari.dot(a.imaginari);
			result.imaginari = (this->imaginari * a.real) + (a.imaginari * this->real) + this->imaginari.cross(a.imaginari);
			return result;
		}

		void operator /=(T scalar)
		{
			this->real /= scalar;
			this->imaginari /= scalar;
		}

		Quaternion<T> operator/(T scalar)
		{
			Quaternion<T> result;
			result.real = this->real / scalar;
			result.imaginari = this->imaginari / scalar;
			return result;
		}

		void operator *=(const T a)
		{
			this->real *= a;
			this->imaginari *= a;
		}

		Quaternion<T> operator*(const T a)
		{
			return Quaternion<T>(this->real*a, this->imaginari*a);
		}

		T magnitude()
		{
			return pow(
				pow(this->real,(T)2) +
				pow(this->imaginari[0], (T)2) +
				pow(this->imaginari[1], (T)2) +
				pow(this->imaginari[2], (T)2)
				,(T)1/(T)2
			);
		}

		Quaternion<T> normalize()
		{
			T magnitude = (this->magnitude());
			if (magnitude != (T)0) {
				return (*this) / (this->magnitude());
			}
			else return (*this);
		}

		Quaternion<T> conjugate()
		{
			return Quaternion<T>(this->real, (this->imaginari)*((T)(-1)));
		}

		Quaternion<T> inverse()
		{
			T absoluteValue = (T)1 / pow(this->magnitude(),(T)2);
			Quaternion<T> conjugate = this->conjugate();

			return Quaternion<T>(
				conjugate.real * absoluteValue,
				conjugate.imaginari * absoluteValue
			);

		}

		T degree2radiants(T degrees)
		{
			return degrees * ((T)PI / (T)180);
		}

		void convertToUnitNormQuaternion() 
		{
			T angle = degree2radiants(this->real);
			(this->imaginari).normalize();
			this->real = cos(angle * (T)0.5);
			this->imaginari = this->imaginari * sin(angle * (T)0.5);

		}

	};


};