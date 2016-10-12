#include <iostream>

template <class T>
class Vector2D {
public:
	T x_, y_;
	
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
		os << vec.x_ << " " << vec.y_;
		return os;
	}
};


template <class T>
void print(const T& i) {
	std::cout << i << std::endl;
}

int main(void) {
	Vector2D<int> a;
	Vector2D<float> b;
	Vector2D<double> c;
	a.x_ = 3;
	a.y_ = 4.5;
	b.x_ = 3.4;
	b.y_ = 4.5;
	c.x_ = 3.4;
	c.y_ = 4.5;
	print(a);
	print(b);
	print(c);
}