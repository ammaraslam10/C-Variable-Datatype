#pragma once
#ifndef VAR_H
#define VAR_H
#include<iostream>
#include<sstream>
#include<string>

class var {
	double d;
	int i;
	std::string s;
	char dtype;
	std::string convert(const double a) const {
		std::ostringstream oss; oss << a; return oss.str();
	}
	std::string convert(const int a) const {
		std::ostringstream oss; oss << a; return oss.str();
	}
	char whatType(const std::string a) const { 
		bool d = 0; 
		for (unsigned int i = 0; i < a.length(); i++) { 
			if (!(a[i] >= '0' && a[i] <= '9')) { 
				if (a[i] == '.' && d == 0) { d = 1; } 
				else { return 's'; } 
			} 
		} 
		if (d == 0) return 'i';
		return 'd';
	}
	int toInt(const std::string a, int s = 0, int e = -1) const { 
		int n = 0; 
		for (int i = s; a[i] != '\0' && i != e && a[i] != '.'; i++) { 
			if (a[i] >= '0' && a[i] <= '9') { 
				n = n * 10 + ((int)a[i] - '0'); 
			} 
		} 
		return n; 
	}
	double toDbl(const std::string a) const {
		int p = 0; while (a[p] != '.' && a[p] != '\0') { p++; }
		if (p != a[p] != '\0') {
			double n = (double) toInt(a, 0, p); double ad = (float) toInt(a, p + 1);
			while (((int)ad) > 0) { ad = ad / 10; } return n + ad;
		}
		else { return (double) toInt(a, 0); }
	}
public:
	var() { dtype = 'n'; } 
	var(const int data, bool fix = 0) { i = data; dtype = 'i'; }
	var(const double data, bool fix = 0) { d = data; dtype = 'd'; }
	var(const std::string data) { s = data; dtype = 's'; }
	var(const char* data) { s = data; dtype = 's'; } 
	var(const var& a) { 
		if (this == &a)
			return;
		d = a.d; i = a.i; s = a.s; dtype = a.dtype;
	}
	var(const std::string data, bool fix) { 
		s = data; 
		dtype = whatType(s); 
		if (dtype == 'i') i = toInt(s);
		else if (dtype == 'd') d = toDbl(s);
	}
	var(const char* data, bool fix):var((std::string) data, 1) { }

	var& operator=(const int data) { i = data; dtype = 'i'; return *this; }
	var& operator=(const double data) { d = data; dtype = 'd'; return *this; }
	var& operator=(char data) { s = data; dtype = 's'; return *this; }
	var& operator=(char* data) { s = data; dtype = 's'; return *this; }
	var& operator=(const std::string data) { s = data; dtype = 's'; return *this; }
	var& operator=(const var& data) {
		if (this == &data)
			return *this;
		d = data.d; i = data.i; s = data.s; dtype = data.dtype;
		return *this;
	}

	#define OPRFUNC(X) bool operator X (const var& data) const { \
		if (dtype == 'i' && data.dtype == 'i') \
			return i X data.i; \
		else if (dtype == 'd' && data.dtype == 'd') \
			return d X data.d; \
		else if (dtype == 's' && data.dtype == 's') \
			return s X data.s; \
		else if (dtype == 'i' && data.dtype == 'd') \
			return i X data.d; \
		else if (dtype == 'd' && data.dtype == 'i') \
			return d X data.i; \
		else if (dtype == 'i' && data.dtype == 's') \
			return convert(i) X data.s; \
		else if (dtype == 'd' && data.dtype == 's') \
			return convert(d) X data.s; \
		else if (data.dtype == 'i' && dtype == 's') \
			return convert(data.i) X s; \
		else if (data.dtype == 'd' && dtype == 's') \
			return convert(data.d) X s; \
		else if (data.dtype == 'n' && dtype == 'n') \
			return true; \
		return false; \
	}
	OPRFUNC(==);
	OPRFUNC(>);
	OPRFUNC(<);
	OPRFUNC(>=);
	OPRFUNC(<=);
	OPRFUNC(!=);
	#undef OPRFUNC
	bool equals(const var& data) const {
		if (dtype != data.dtype)
			return false;
		else if (dtype == 'i')
			return i == data.i;
		else if (dtype == 'd')
			return d == data.d;
		else if (dtype == 's')
			return s == data.s;
		else if (dtype == 'n')
			return true;
		return false;
	}
	// +
	var operator+(const var& data) const {
		if (dtype == 'i' && data.dtype == 'i')
			return i + data.i;
		else if (dtype == 'd' && data.dtype == 'd')
			return d + data.d;
		else if (dtype == 's' && data.dtype == 's')
			return s + data.s;
		else if (dtype == 'i' && data.dtype == 'd')
			return i + data.d;
		else if (dtype == 'd' && data.dtype == 'i')
			return d + data.i;
		else if (dtype == 'i' && data.dtype == 's')
			return convert(i) + data.s;
		else if (dtype == 'd' && data.dtype == 's')
			return convert(d) + data.s;
		else if (data.dtype == 'i' && dtype == 's')
			return convert(data.i) + s;
		else if (data.dtype == 'd' && dtype == 's')
			return convert(data.d) + s;
		return var();
	}
	// +=
	var operator+=(const var& data) {
		if (dtype == 'i' && data.dtype == 'i')
			i += data.i;
		else if (dtype == 'd' && data.dtype == 'd')
			d += data.d;
		else if (dtype == 's' && data.dtype == 's')
			s += data.s;
		else if (dtype == 'i' && data.dtype == 'd') {
			d = i + data.d;
			dtype = 'd';
		} else if (dtype == 'd' && data.dtype == 'i')
			d += data.i;
		else if (dtype == 'i' && data.dtype == 's') {
			s = convert(i) + data.s;
			dtype = 's';
		} else if (dtype == 'd' && data.dtype == 's') {
			s = convert(d) + data.s;
			dtype = 's';
		} else if (data.dtype == 'i' && dtype == 's') {
			s = convert(data.i) + s;
			dtype = 's';
		} else if (data.dtype == 'd' && dtype == 's') {
			s = convert(data.d) + s;
			dtype = 's';
		}
		return var();
	}
	#define OPRFUNC(X) var operator X (const var& data) const { \
		if (dtype == 'i' && data.dtype == 'i') \
			return i X data.i; \
		else if (dtype == 'd' && data.dtype == 'd') \
			return d X data.d; \
		else if (dtype == 'i' && data.dtype == 'd') \
			return i X data.d; \
		else if (dtype == 'd' && data.dtype == 'i') \
			return d X data.i; \
		return var(); \
	}
	OPRFUNC(-);
	OPRFUNC(*);
	#undef OPRFUNC
	var operator/(const var& data) const {
		if (dtype == 'i' && data.dtype == 'i')
			return i / (double) data.i;
		else if (dtype == 'd' && data.dtype == 'd') 
			return d / data.d;
		else if (dtype == 'i' && data.dtype == 'd') 
			return i / data.d;
		else if (dtype == 'd' && data.dtype == 'i') 
			return d / data.i;
		return (*this);
	}
	var operator%(const var& data) const {
		if (dtype == 'i' && data.dtype == 'i')
			return i % data.i;
		else if (dtype == 'd' && data.dtype == 'd')
			return (int)d % (int)data.d;
		else if (dtype == 'i' && data.dtype == 'd')
			return i % (int)data.d;
		else if (dtype == 'd' && data.dtype == 'i')
			return (int)d % data.i;
		return var();
	}
	#define OPRFUNC(X) var& operator X (const var& data) { \
		if (dtype == 'i' && data.dtype == 'i') \
			i X data.i; \
		else if (dtype == 'd' && data.dtype == 'd') \
			d X data.d; \
		else if (dtype == 'i' && data.dtype == 'd') { \
			d = i; \
			d X data.d; \
			dtype = 'd'; \
		} else if (dtype == 'd' && data.dtype == 'i') \
			d X data.i; \
		return (*this); \
	}
	OPRFUNC(-=);
	OPRFUNC(*=);
	#undef OPRFUNC
	var& operator/=(const var& data) {
		if (dtype == 'i' && data.dtype == 'i')
			if(i % data.i == 0) i = data.i;
			else { d = i / data.i; dtype = 'd'; }
		else if (dtype == 'd' && data.dtype == 'd') {
			d /= data.d;
		} else if (dtype == 'i' && data.dtype == 'd') {
			d = i / data.d;
			dtype = 'd';
		} else if (dtype == 'd' && data.dtype == 'i') {
			d /= data.i;
		}
		return (*this);
	}
	var& operator%=(const var& data) {
		if (dtype == 'i' && data.dtype == 'i')
			i %= data.i;
		else if (dtype == 'd' && data.dtype == 'd') {
			i = (int)d % (int)data.d;
			dtype = 'i';
		} else if (dtype == 'i' && data.dtype == 'd')
			i %= (int) data.d;
		else if (dtype == 'd' && data.dtype == 'i') {
			i = (int)d % data.i;
			dtype = 'i';
		}
		return (*this);
	}
	char& operator[](const int a) {
		if (dtype == 's')
			return s[a];
		else if (dtype == 'i')
			return convert(i)[a];
		else if(dtype == 'd')
			return convert(i)[a];
		// 0 of null? lets consider it invalid operation, but avoid exit(0)
		else {
			i = 0; return convert(i)[0];
		}
	}
	var& operator++() { 
		if(dtype == 's')
			++s[s.length() - 1];
		else if (dtype == 'd')
			++d;
		else if (dtype == 'i')
			++i;
		return *this;
	}
	var operator++(int) { var temp = *this; ++*this; return temp; }
	var& operator--() { 
		if (dtype == 's')
			--s[s.length() - 1];
		else if (dtype == 'd')
			--d;
		else if (dtype == 'i')
			--i;
		return *this; 
	}
	var operator--(int) { var temp = *this; --*this; return temp; }

	char type() const {
		return dtype;
	}
	std::string toString() const {
		if (dtype == 'i')
			return convert(i);
		else if (dtype == 'd')
			return convert(d);
		else if (dtype == 's')
			return s;
		else
			return "null";
	}
	int parseInt() const {
		return (int) parseDouble();
	}
	double parseDouble() const {
		if (dtype == 'i') return i;
		else if (dtype == 'd') return d;
		else if (dtype == 'n') return 0;
		char type = whatType(s);
		if (type == 'i')
			return toInt(s);
		else if (type == 'd')
			return toDbl(s);
		return 0;
	}
	std::string parseString() const { return toString(); }
	bool isNull() {
		return dtype == 'n';
	}
	bool isInt() const {
		if (dtype == 'i' || (dtype == 's' && whatType(s) == 'i'))
			return true;
		return false;
	}
	bool isNumeric() const {
		if (dtype == 'i' || dtype == 'd' || (dtype == 's' && whatType(s) != 's'))
			return true;
		return false;
	}
	void convertInt() {
		if (dtype == 'i')
			return;
		else if (dtype == 'd') 
			i = (int) d;
		else if (dtype == 'n') 
			i = 0;
		else if (dtype == 's')
			i = toInt(s);
		dtype = 'i';
	}
	void convertDouble() {
		if (dtype == 'd')
			return;
		else if (dtype == 'i') 
			d = (double) i;
		else if (dtype == 'n') 
			d = 0;
		else if (dtype == 's')
			d = toDbl(s);
		dtype = 'd';
	}
	void convertString() {
		if (dtype == 's')
			return;
		else if (dtype == 'i') 
			s = convert(i);
		else if (dtype == 'd') 
			s = convert(d);
		else if (dtype == 'n') 
			s = "null";
		dtype = 's';
	}
	void clear() {
		this->~var();
	}
	~var() {
		dtype = 'n';
	}
	#define FRIENDEXP(X, T) \
	friend T operator X (const var, const int); friend T operator X (const int, const var); \
	friend T operator X (const var, const double); friend T operator X (const double, const var); \
	friend T operator X (const var, const char*); friend T operator X (const char*, const var); \
	friend T operator X (const var, const std::string); friend T operator X (const std::string, const var); 
	FRIENDEXP(== ,bool); FRIENDEXP(> ,bool); FRIENDEXP(< ,bool); FRIENDEXP(>= ,bool); FRIENDEXP(<= ,bool); FRIENDEXP(!= ,bool);
	FRIENDEXP(+, var); FRIENDEXP(-, var); FRIENDEXP(/ , var); FRIENDEXP(*, var); FRIENDEXP(%, var);
	#undef FRIENDEXP
	#define FRIENDEXP(X) \
	friend var& operator X (var&, const int); friend int& operator X (int&, const var); \
	friend var& operator X (var&, const double); friend double& operator X (double&, const var); \
	friend var& operator X (var&, const char*); \
	friend var& operator X (var&, const std::string); friend std::string& operator X (std::string&, const var); 
	FRIENDEXP(+=); FRIENDEXP(-=); FRIENDEXP(/=); FRIENDEXP(*=); FRIENDEXP(%=);
	#undef FRIENDEXP
};
std::ostream& operator<<(std::ostream& s, const var& a) {
	s << a.toString();
	return s;
}
std::istream& operator>>(std::istream& s, var& a) { 
	std::string temp; s >> temp;
	a = temp;
	if (a.isInt())
		a.convertInt();
	else if (a.isNumeric())
		a.convertDouble();
	return s; 
}
#define OPRFUNC(X, T1, RET) RET operator X (const var data, const T1 val) { \
	return data X var(val, 1); \
}
#define OPRFUNC2(X, T1, RET) RET operator X (const T1 val, const var data) { \
	return var(val, 1) X data; \
}
#define OPRFUNCMAC(X, T) \
OPRFUNC(X , int, T); OPRFUNC2(X , int, T); \
OPRFUNC(X , double, T); OPRFUNC2(X , double, T); \
OPRFUNC(X , char*, T); OPRFUNC2(X , char*, T); \
OPRFUNC(X , std::string, T); OPRFUNC2(X , std::string, T);

OPRFUNCMAC(== ,bool); OPRFUNCMAC(> ,bool); OPRFUNCMAC(< ,bool); OPRFUNCMAC(>= ,bool); OPRFUNCMAC(<= ,bool); OPRFUNCMAC(!= ,bool);
OPRFUNCMAC(+, var); OPRFUNCMAC(-, var); OPRFUNCMAC(/ , var); OPRFUNCMAC(*, var); OPRFUNCMAC(% , var);
#undef OPRFUNC
#undef OPRFUNC2
#undef OPRFUNCMAC
#define OPRFUNCMAC(W, X, T, F) \
T& operator W (T& val, const var data) { \
	val = (var(val, 1) X data).parse##F(); \
	return val; \
} \
var& operator W(var& data, const T val){ \
	data = (data X var(val, 1)).parse##F(); \
	return data; \
}
OPRFUNCMAC(+=, +, int, Int); OPRFUNCMAC(+=, +, double, Double); OPRFUNCMAC(+=, +, std::string, String);
OPRFUNCMAC(-=, -, int, Int); OPRFUNCMAC(-=, -, double, Double); OPRFUNCMAC(-=, -, std::string, String);
OPRFUNCMAC(*=, *, int, Int); OPRFUNCMAC(*=, *, double, Double); OPRFUNCMAC(*=, *, std::string, String);
OPRFUNCMAC(/=, /, int, Int); OPRFUNCMAC(/=, /, double, Double); OPRFUNCMAC(/=, /, std::string, String);
OPRFUNCMAC(%=, %, int, Int); OPRFUNCMAC(%=, %, double, Double); OPRFUNCMAC(%=, %, std::string, String);
var& operator+=(var& data, const char* val) {
	data = (data += var(val, 1)).parseString();
	return data;
}
#undef OPRFUNCMAC
#endif
