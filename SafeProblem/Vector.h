#pragma once
#include <ostream>


//Don't try to create a vector of a type unless said type has + and += operator overloading. Thank you.
template <class E, unsigned int LENGTH>
class Vector 
{
public:
	E data[LENGTH];
	
	Vector() {};
	Vector(const E(&e)[LENGTH]) { memcpy(data, e, sizeof(E[LENGTH])); };
	Vector(const Vector<E, LENGTH> &v) { memcpy(data, v.data, sizeof(E[LENGTH])); };

	Vector operator+(const Vector &v) const;
	Vector &operator+=(const Vector &v);
	//Vector &operator=(const Vector &v){};
	Vector operator*(const int x) const;

	E &operator[] (int x) { return data[x]; };
	
	//Have to define here or linker error?
	friend std::ostream &operator<<(std::ostream &os, const Vector &v){
		
		os << "(";

		for (int i = 0; i < LENGTH; ++i) {
			os << v.data[i];
			if (i != LENGTH - 1) os << ", ";
		}
		
		return os << ")";
	};


	~Vector() {};
};	 

template <class E, unsigned int LENGTH>
inline Vector<E, LENGTH> Vector<E, LENGTH>::operator+(const Vector<E, LENGTH> &v) const {
	Vector<E,LENGTH> ret;
	for (int i = 0; i < LENGTH; ++i) 
		ret.data[i] = data[i] + v.data[i];
	return ret;
}

template <class E, unsigned int LENGTH>
inline Vector<E, LENGTH> &Vector<E, LENGTH>::operator+=(const Vector<E, LENGTH> &v) {
	for (int i = 0; i < LENGTH; ++i)
		data[i] += v.data[i];
	return *this;
}


template <class E, unsigned int LENGTH>
inline Vector<E, LENGTH> Vector<E, LENGTH>::operator*(const int x) const {
	Vector<E, LENGTH> v = data;
	for (int i = 0; i < LENGTH; ++i)
		v.data[i] *= x;
	return v;
}



