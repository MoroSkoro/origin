#include <iostream>

class Fraction
{
private:
	int numerator_;
	int denominator_;

	friend std::ostream& operator<<(std::ostream& strm, Fraction& out);
	friend Fraction operator+(const Fraction& f1, const Fraction& f2);
	friend Fraction operator-(const Fraction& f1, const Fraction& f2);
	friend Fraction operator*(const Fraction& f1, const Fraction& f2);
	friend Fraction operator/(const Fraction& f1, const Fraction& f2);

public:
	Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}
	~Fraction(){}

	Fraction& operator-()
	{
		numerator_ = -numerator_;
		return *this;
	}
	Fraction& operator++()
	{
		numerator_ = numerator_ + denominator_;
		return *this;
	}
	Fraction& operator++(int)
	{
		Fraction prev = *this;
		++* this;
		return prev;
	}
	Fraction& operator--()
	{
		numerator_ = numerator_ - denominator_;
		return *this;
	}
	Fraction& operator--(int)
	{
		Fraction prev = *this;
		--* this;
		return prev;
	}

	bool operator==(Fraction other) { return ((numerator_ * other.denominator_) == (other.numerator_ * denominator_)); }
	bool operator!=(Fraction other) { return !(*this == other); }
	bool operator>(Fraction other) { return ((numerator_ * other.denominator_) > (other.numerator_ * denominator_)); }
	bool operator<(Fraction other) { return other > *this; }
	bool operator>=(Fraction other) { return !(*this < other); }
	bool operator<=(Fraction other) { return !(*this > other); }
};

std::ostream& operator<<(std::ostream& strm, Fraction& out) {
	strm << out.numerator_ << "/" << out.denominator_;
	return strm;
}

int NOD(int a, int b) {
	a = abs(a), b = abs(b);
	if (b == 0)return a;
	else return NOD(b, a % b);
}

Fraction operator+(const Fraction& f1, const Fraction& f2) {
	int sum1 = (f1.numerator_ * f2.denominator_ + f2.numerator_ * f1.denominator_);
	int sum2 = (f1.denominator_ * f2.denominator_);
	int n = NOD(sum1, sum2);
	sum1 = sum1 / n;
	sum2 = sum2 / n;
	return Fraction(sum1, sum2);
}

Fraction operator-(const Fraction& f1, const Fraction& f2) {
	int sub1 = (f1.numerator_ * f2.denominator_ - f2.numerator_ * f1.denominator_);
	int sub2 = (f1.denominator_ * f2.denominator_);
	int n = NOD(sub1, sub2);
	sub1 = sub1 / n;
	sub2 = sub2 / n;
	return Fraction(sub1, sub2);
}

Fraction operator*(const Fraction& f1, const Fraction& f2) {
	int mul1 = (f1.numerator_ * f2.numerator_);
	int mul2 = (f1.denominator_ * f2.denominator_);
	int n = NOD(mul1, mul2);
	mul1 = mul1 / n;
	mul2 = mul2 / n;
	return Fraction(mul1, mul2);
}

Fraction operator/(const Fraction& f1, const Fraction& f2) {
	int div1 = (f1.numerator_ * f2.denominator_);
	int div2 = (f1.denominator_ * f2.numerator_);
	int n = NOD(div1, div2);
	div1 = div1 / n;
	div2 = div2 / n;
	return Fraction(div1, div2);
}

int main()
{
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	
	int a, b, c, d;
	
	std::cout << "Введите числитель дроби 1: ";
	std::cin >> a;
	std::cout << "Введите знаменатель дроби 1: ";
	std::cin >> b;
	std::cout << "Введите числитель дроби 2: ";
	std::cin >> c;
	std::cout << "Введите знаменатель дроби 2: ";
	std::cin >> d;

	Fraction f1(a, b);
	Fraction f2(c, d);
	Fraction f3(c, d);

	std::cout << f1 << " + " << f2 << " = " << (f3 = (f1+f2)) << '\n';
	std::cout << f1 << " - " << f2 << " = " << (f3 = (f1 - f2)) << '\n';
	std::cout << f1 << " * " << f2 << " = " << (f3 = (f1 * f2)) << '\n';
	std::cout << f1 << " / " << f2 << " = " << (f3 = (f1 / f2)) << '\n';

	std::cout << "++" << f1;
	std::cout << " * " << f2 << " = " << (f3 = (++f1 * f2)) << '\n';
	std::cout << "Значени дроби 1 = " << f1 << '\n';
	
	std::cout << f1 << "--";
	std::cout << " * " << f2 << " = " << (f3 = (f1-- * f2)) << '\n';
	std::cout << "Значени дроби 1 = " << f1 << '\n';
	
}