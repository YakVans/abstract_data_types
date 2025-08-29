#pragma once

#include <iostream>
#include <cmath>

#include "exceptions.h"

class Complex {
private:
    double Re;
    double Im;
public:
    Complex() :
        Re(0),
        Im(0)
    {}
    Complex(double value) :
        Re(value),
        Im(0)
    {}
    Complex(double Re_val, double Im_val) :
        Re(Re_val),
        Im(Im_val)
    {}
    Complex(const Complex &other) :
        Re(other.Re),
        Im(other.Im)
    {}

    ~Complex() = default;

    double GetRe() const {
        return Re;
    }
    double GetIm() const {
        return Im;
    }
    double GetMod() const {
        return sqrt(Re * Re + Im * Im);
    }

    void SetRe(double value) {
        Re = value;
    }
    void SetIm(double value) {
        Im = value;
    }

    Complex operator-() const {
        return Complex(-Re, -Im);
    }
    Complex &operator=(const Complex& other) {
        Re = other.Re;
        Im = other.Im;
        return *this;
    }
    Complex &operator+=(const Complex& other) {
        Re += other.Re;
        Im += other.Im;
        return *this;
    }
    Complex &operator-=(const Complex& other) {
        Re -= other.Re;
        Im -= other.Im;
        return *this;
    }
    Complex &operator*=(const Complex& other) {
        double new_Re = Re * other.Re - Im * other.Im;
        double new_Im = Re * other.Im + Im * other.Re;
        Re = new_Re;
        Im = new_Im;
        return *this;
    }
    Complex &operator/=(const Complex& other) {
        double up_Re = Re * other.Re + Im * other.Im;
        double up_Im = -Re * other.Im + Im * other.Re;
        double down = other.Re * other.Re + other.Im * other.Im;
        Re = up_Re / down;
        Im = up_Im / down;
        return *this;
    }

    Complex operator+(const Complex& other) const {
        return Complex(*this) += other;
    }
    Complex operator-(const Complex& other) const {
        return Complex(*this) -= other;
    }
    Complex operator*(const Complex& other) const {
        return Complex(*this) *= other;
    }
    Complex operator/(const Complex& other) const {
        return Complex(*this) /= other;
    }

    bool operator==(const Complex& other) const {
        return Re == other.Re && Im == other.Im;
    }
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    bool operator>=(const Complex& other) const {
        return GetMod() >= other.GetMod();
    }
    bool operator<=(const Complex& other) const {
        return GetMod() <= other.GetMod();
    }
    bool operator>(const Complex& other) const {
        return GetMod() > other.GetMod();
    }
    bool operator<(const Complex& other) const {
        return GetMod() < other.GetMod();
    }


    Complex &operator=(double other) {
        Re = other;
        Im = 0;
        return *this;
    }
    Complex &operator+=(double other) {
        Re += other;
        return *this;
    }
    Complex &operator-=(double other) {
        Re -= other;
        return *this;
    }
    Complex &operator*=(double other) {
        Re *= other;
        Im *= other;
        return *this;
    }
    Complex &operator/=(double other) {
        Re /= other;
        Im /= other;
        return *this;
    }

    Complex operator+(double other) const {
        return Complex(*this) += other;
    }
    Complex operator-(double other) const {
        return Complex(*this) -= other;
    }
    Complex operator*(double other) const {
        return Complex(*this) *= other;
    }
    Complex operator/(double other) const {
        return Complex(*this) /= other;
    }

    bool operator==(double other) const {
        return Re == other && Im == 0;
    }
    bool operator!=(double other) const {
        return !(*this == other);
    }
    bool operator>=(double other) const {
        return GetMod() >= other;
    }
    bool operator<=(double other) const {
        return GetMod() <= other;
    }
    bool operator>(double other) const {
        return GetMod() > other;
    }
    bool operator<(double other) const {
        return GetMod() < other;
    }
};

Complex operator+(double first, const Complex &second) {
    return Complex(second.GetRe() + first, second.GetIm());
}
Complex operator-(double first, const Complex &second) {
    return Complex(second.GetRe() - first, second.GetIm());
}
Complex operator*(double first, const Complex &second) {
    return Complex(second.GetRe() * first, second.GetIm() * first);
}
Complex operator/(double first, const Complex &second) {
    return Complex(second.GetRe() / first, second.GetIm() / first);
}

bool operator==(double first, const Complex &second) {
    return second.GetRe() == first && second.GetIm() == 0;
}
bool operator!=(double first, const Complex &second) {
    return !(second == first);
}
bool operator>=(double first, const Complex &second) {
    return first >= second.GetMod();
}
bool operator<=(double first, const Complex &second) {
    return first <= second.GetMod();
}
bool operator>(double first, const Complex &second) {
    return first > second.GetMod();
}
bool operator<(double first, const Complex &second) {
    return first < second.GetMod();
}


std::istream& operator>>(std::istream& is, Complex& c) {
    char open, comma, close;
    double real = 0.0, imag = 0.0;

    if (!(is >> std::ws >> open) || open != '(') {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (!(is >> real)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (!(is >> std::ws >> comma) || comma != ',') {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (!(is >> imag)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (!(is >> std::ws >> close) || close != ')') {
        is.setstate(std::ios::failbit);
        return is;
    }

    c.SetRe(real);
    c.SetIm(imag);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    if (c.GetIm() == 0) os << c.GetRe();
    else {
        if (c.GetRe() == 0) {
            if (c.GetIm() == -1) os << "-";
            else if (c.GetIm() != 1) os << c.GetIm();
            os << "i";
        }
        else if (c.GetIm() > 0) {
            os << c.GetRe() << " + ";
            if (c.GetIm() != 1) os << c.GetIm();
            os << "i";
        }
        else {
            os << c.GetRe() << " - ";
            if (c.GetIm() != -1) os << -c.GetIm();
            os << "i";
        }
    }
    return os;
}