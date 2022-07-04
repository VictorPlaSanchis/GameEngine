#ifndef _VECTOR_H_
#include "Vector.h"
#endif

#include <typeinfo>
#include <cmath>

#define _QUATERNION_H_

namespace vge {

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

		void operator *=(const T a)
		{
			this->real *= a;
			this->imaginari *= a;
		}

		Quaternion<T> operator*(const T a)
		{
			return Quaternion<T>(this->real*a, this->imaginari*a);
		}

	};

};