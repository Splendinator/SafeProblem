#pragma once
#include <ostream>


//Don't try to create a vector of a type unless said type has + and += operator overloading. Thank you.
template <class E, unsigned int LENGTH>
class Vector 
{
public:
	E data[LENGTH];
	
	Vector() {};
	Vector(E e[LENGTH]) : data(e) {};

	Vector operator+(const Vector &v);
	Vector &operator+=(const Vector &v);

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
inline Vector<E, LENGTH> Vector<E, LENGTH>::operator+(const Vector<E, LENGTH> &v) {
	Vector<E,LENGTH> v;
	for (int = 0; i < LENGTH; ++i) 
		v.data[i] = data[i] + v.data[i];
	return v;
}

template <class E, unsigned int LENGTH>
inline Vector<E, LENGTH> &Vector<E, LENGTH>::operator+=(const Vector<E, LENGTH> &v) {
	for (int = 0; i < LENGTH; ++i)
		data[i] += v.data[i];
	return *this;
}



