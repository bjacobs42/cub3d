#pragma once

template <typename T = double>
class Vec2
{
	public:
		T	x, y;

		Vec2(const T init_x = 0, const T init_y = 0) : x(init_x), y(init_y) {}
		Vec2(const Vec2& source) { *this = source; }
		~Vec2(void) {}

		Vec2&	operator=(const Vec2& source)
		{
			if (this != &source)
			{
				this->y = source.y;
				this->x = source.x;
			}
			return (*this);
		}

		Vec2&	operator+=(const Vec2& source)
		{
			this->y += source.y;
			this->x += source.x;
			return (*this);
		}

		Vec2&	operator+=(const int num)
		{
			this->y += num;
			this->x += num;
			return (*this);
		}

		Vec2	operator+(const	int num) const
		{
			return (Vec2(this->x + num, this->y + num));
		}

		Vec2	operator+(const	Vec2& source) const
		{
			return (Vec2(this->x + source.x, this->y + source.y));
		}

		Vec2&	operator-=(const Vec2& source)
		{
			this->y -= source.y;
			this->x -= source.x;
			return (*this);
		}

		Vec2&	operator-=(const int num)
		{
			this->y -= num;
			this->x -= num;
			return (*this);
		}

		Vec2	operator-(const	int num) const
		{
			return (Vec2(this->x - num, this->y - num));
		}

		Vec2	operator-(const	Vec2& source) const
		{
			return (Vec2(this->x - source.x, this->y - source.y));
		}
		
		Vec2&	operator*=(const Vec2& source)
		{
			this->y *= source.y;
			this->x *= source.x;
			return (*this);
		}

		Vec2&	operator*=(const int num)
		{
			this->y *= num;
			this->x *= num;
			return (*this);
		}

		Vec2	operator*(const	int num) const
		{
			return (Vec2(this->x * num, this->y * num));
		}

		Vec2	operator*(const	Vec2& source) const
		{
			return (Vec2(this->x * source.x, this->y * source.y));
		} 
};
