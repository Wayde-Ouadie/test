#pragma once
#include <iostream>

class vect2 {
	private:
		int x;
		int y;
	public:
		vect2() : x(0), y(0) {};
		vect2(int x, int y) : x(x), y(y) {};
		vect2(const vect2& other) : x(other.x), y(other.y) {};

		vect2& operator=(const vect2& other) {
			if (*this != other) {
				x = other.x;
				y = other.y;
			}
			return *this;
		}

		int& operator[](int i) {
			return (i == 0 ? x : y);
		}

		int operator[](int i) const {
			return (i == 0 ? x : y);
		}

		friend std::ostream& operator<<(std::ostream& os, const vect2& vec) {
			os << "{" << vec[0] << ", " << vec[1] << "}";
			return os;
		}

		vect2 operator++(int) {
			vect2 tmp = *this;
			x++;
			y++;
			return tmp;
		}

		vect2& operator++() {
			x++;
			y++;
			return *this;
		}

		vect2 operator--(int) {
			vect2 tmp = *this;
			x--;
			y--;
			return tmp;
		}

		vect2& operator--() {
			x--;
			y--;
			return *this;
		}

		vect2& operator+=(const vect2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		vect2& operator-=(const vect2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		vect2 operator+(const vect2& other) const {
			return vect2(x + other.x, y + other.y);
		}

		vect2 operator-(const vect2& other) const {
			return vect2(x - other.x, y - other.y);
		}

		vect2 operator*(int num) const{
			return vect2(x * num, y * num);
		}

		friend vect2 operator*(int num, const vect2& other) {
			return vect2(other.x * num, other.y * num);
		}

		vect2& operator*=(int num) {
			x *= num;
			y *= num;
			return *this;
		}

		vect2 operator-() const {
			return vect2(-x, -y);
		}

		bool operator==(const vect2& other) const {
			return (x == other.x && y == other.y);
		}

		bool operator!=(const vect2& other) const {
			return (!(x == other.x && y == other.y));
		}
};
