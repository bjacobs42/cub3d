#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <functional>
#include <initializer_list>

template <typename T, size_t N>
class Vector
{
	protected:
		std::array<T, N>	_data;

	private:
		template<typename Func>
		void	_apply(const Vector<T, N>& other, Func func)
		{
			for (size_t i = 0; i < N; ++i)
				func(_data[i], other[i]);
		}

		template<typename Func>
		void	_apply(const T& scalar, Func func)
		{
			for (size_t i = 0; i < N; ++i)
				func(_data[i], scalar);
		}

		template<typename Func>
		Vector<T, N>	_apply(const T& scalar, Func func) const
		{
			Vector<T, N>	result;

			for (size_t i = 0; i < N; ++i)
				result[i] = func(_data[i], scalar);
			return (result);
		}

		template<typename Func>
		Vector<T, N>	_apply(const Vector<T, N>& other, Func func) const
		{
			Vector<T, N>	result;

			for (size_t i = 0; i < N; ++i)
				result[i] = func(_data[i], other[i]);
			return (result);
		}

	public:
		Vector(void) : _data{} {};
		Vector(std::initializer_list<T> list) : _data{}
		{
			assert(list.size() <= N);
			std::copy(list.begin(), list.end(), _data.begin());
		}
		Vector(const Vector<T, N>& src) : _data(src._data) {};
		~Vector(void) {};

		size_t	size(void) const { return (N); }

		T	sum(void) const
		{
			T	sum;
			for (const T& num : _data)
				sum += num;
			return (sum);
		}

		T&	operator[](size_t i) { return (_data[i]); }
		const T&	operator[](size_t i) const { return (_data[i]); }

		Vector<T, N>&	operator=(const Vector<T, N>& source)
		{
			if (this != &source)
				_apply(source, [](T& a, const T& b) { a = b; });
			return (*this);
		}

		Vector<T, N>&	operator+=(const Vector<T, N>& source)
		{
			_apply(source, [](T& a, const T& b) { a += b; });
			return (*this);
		}
		Vector<T, N>&	operator+=(T num)
		{
			_apply(num, [](T& a, const T& b) { a += b; });
			return (*this);
		}

		Vector<T, N>	operator+(const	T num) const
		{
			return (_apply(num, [](const T& a, const T& b) { return (a + b); }));
		}
		Vector<T, N>	operator+(const	Vector<T, N>& rhs) const
		{
			return (_apply(rhs, [](const T& a, const T& b) { return (a + b); }));
		}

		Vector<T, N>&	operator-=(const Vector<T, N>& rhs)
		{
			_apply(rhs, [](T& a, const T& b) { a -= b; });
			return (*this);
		}
		Vector<T, N>&	operator-=(const T num)
		{
			_apply(num, [](T& a, const T& b) { a -= b; });
			return (*this);
		}

		Vector<T, N>	operator-(const	T num) const
		{
			return (_apply(num, [](const T& a, const T& b) { return(a - b); }));
		}
		Vector<T, N>	operator-(const	Vector<T, N>& rhs) const
		{
			return (_apply(rhs, [](const T& a, const T& b) { return(a - b); }));
		}
		
		Vector<T, N>&	operator*=(const Vector<T, N>& rhs)
		{
			_apply(rhs, [](T& a, const T& b) { a *= b; });
			return (*this);
		}
		Vector<T, N>&	operator*=(const T num)
		{
			_apply(num, [](T& a, const T& b) { a *= b; });
			return (*this);
		}

		Vector<T, N>	operator*(const Vector<T, N>& rhs)
		{
			return (_apply(rhs, [](const T& a, const T& b) { return (a * b); }));
		}
		Vector<T, N>	operator*(const	T num) const
		{
			return (_apply(num, [](const T& a, const T& b) { return (a * b); }));
		}

		bool	operator<(const Vector<T, N>& rhs) const
		{
			return (this->sum() < rhs.sum());
		}

		bool operator==(const Vector<T, N>& rhs) const {
			for (size_t i = 0; i < N; ++i) {
				if (_data[i] != rhs[i])
					return false;
			}
			return true;
		}
};

namespace std {
	template <typename T, size_t N>
	struct hash<Vector<T, N>> {
		std::size_t operator()(const Vector<T, N>& vec) const {
			std::size_t h = 0;
			for (size_t i = 0; i < N; ++i) {
				h ^= std::hash<T>{}(vec[i]) + 0x9e3779b9 + (h << 6) + (h >> 2); // hash combine
			}
			return h;
		}
	};
}


template <typename T = double>
struct Vec2 : public Vector<T, 2>
{
	Vec2(void) : Vector<T, 2>() {}
	Vec2(std::initializer_list<T> list) : Vector<T, 2>(list) {}
	Vec2(const Vector<T, 2>& vec) : Vector<T, 2>(vec) {}
	Vec2(T x, T y) : Vector<T, 2>({x, y}) {}

	T& x() { return (this->_data[0]); }
	const T& x() const { return (this->_data[0]); }
	T& y() { return (this->_data[1]); }
	const T& y() const { return (this->_data[1]); }
};

template <typename T = double>
struct Vec3 : public Vector<T, 3>
{
	Vec3(void) : Vector<T, 3>() {}
	Vec3(std::initializer_list<T> list) : Vector<T, 3>(list) {}
	Vec3(const Vector<T, 3>& vec) : Vector<T, 3>(vec) {}
	Vec3(T x, T y, T z) : Vector<T, 3>({x, y, z}) {}

	T& x() { return (this->_data[0]); }
	const T& x() const { return (this->_data[0]); }
	T& y() { return (this->_data[1]); }
	const T& y() const { return (this->_data[1]); }
	T& z() { return (this->_data[2]); }
	const T& z() const { return (this->_data[2]); }
};
