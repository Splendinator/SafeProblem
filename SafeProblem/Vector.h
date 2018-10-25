#pragma once
#include <ostream>



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
	Vector operator-(const Vector &v) const;

	E &operator[] (int x) { return data[x]; };
	E operator[] (int x) const { return data[x]; };
	
	friend std::ostream &operator<<(std::ostream &os, const Vector &v){
		

		for (int i = 0; i < LENGTH; ++i) {
			if (v.data[i] > 0) os << "+";
			os << v.data[i];
			if (i != LENGTH - 1) os << ", ";
		}
		
		return os;
	};

	static bool hasDupes(Vector<E, LENGTH> v);

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

template<class E, unsigned int LENGTH>
inline Vector<E, LENGTH> Vector<E, LENGTH>::operator-(const Vector & v) const
{
	Vector<E, LENGTH> ret = data;
	for (int i = 0; i < LENGTH; ++i)
		ret.data[i] -= v.data[i];
	return ret;
}

template<class E, unsigned int LENGTH>
inline bool Vector<E, LENGTH>::hasDupes(Vector<E, LENGTH> v)
{
	for (int i = 0; i < LENGTH - 1; ++i) {
		for (int j = i + 1; j < LENGTH; ++j) {
			if (v[i] == v[j]) return true;
		}
	}
	return false;
}

