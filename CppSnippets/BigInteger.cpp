/*************************************************
Copyright: jokerkeny
Author: jokerkeny
Date: 2019-10-03
Description: Define and Test Big Integer class(High precision)
Reference:
https://ixs.im/Algorithm/高精度总结/
https://github.com/curoky/acm/blob/master/template/%E9%AB%98%E7%B2%BE%E5%BA%A6%E6%A8%A1%E6%9D%BF%20-%20%E5%A4%A7%E6%95%B0.md
https://blog.csdn.net/code4101/article/details/38705155 小伙子根据紫书写的，我还没仔细看
**************************************************/
// choose TRACE #define to print tracking information
// #define TRACE printf("%s(%d)-<%s>\n", __FILE__, __LINE__, __FUNCTION__);
#define TRACE
#define PRINT(x) cout << "" #x ": " << (x) << endl;

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;
#define MAX_L 505 // maximum digits number
class bign {
private:
public:
  char s[MAX_L];
  int len;
  bool sign;

  // Constructor
  bign();
  bign(const char *);
  bign(const int);
  bign(const string);

  // Copy Assignment
  //我想，重载=的好处，相比于使用自动合成的copy=，隐式转换，调用构造函数bign(const
  // int)。是在于后者需要构造+拷贝，前者至少省去了拷贝的消耗。
  bign &operator=(const int);
  bign &operator=(const char *);
  bign &operator=(const string);

  // IO
  string toStr() const;
  friend istream &operator>>(istream &, const bign &);
  friend ostream &operator<<(ostream &, const bign &);

  // Comparison
  bool operator<(const bign &) const;
  bool operator>(const bign &) const;
  bool operator<=(const bign &) const;
  bool operator>=(const bign &) const;
  bool operator==(const bign &) const;
  bool operator!=(const bign &) const;

  // Arithmetic
  bign operator+() const;
  bign operator-() const;
  bign operator+(const bign &) const;
  bign operator-(const bign &) const;
  bign operator*(const bign &)const;
  bign operator/(const bign &) const;
  bign operator%(const bign &) const;

  // Compound assignment
  bign &operator+=(const bign &);
  bign &operator-=(const bign &);
  bign &operator*=(const bign &);
  bign &operator/=(const bign &);
  bign &operator%=(const bign &);

  // Increment/Decrement
  bign &operator++();
  bign operator++(int);
  bign &operator--();
  bign operator--(int);

  // Misc
  void clean();
};

// Constructor
bign::bign() {
  TRACE
  memset(s, 0, sizeof(s));
  len = 1;
  sign = 1;
};
bign::bign(const char *num) {
  TRACE
  *this = num;
};
bign::bign(const int num) {
  TRACE
  *this = num;
};
bign::bign(const string num) {
  TRACE
  *this = num;
};
// Copy Assignment
// Why overload Copy assignment?
// I think maybe for bign = int;
// overloading = (const int) could be better than implicit bign = (const bign)
// => bign(const int) => bign = (const char *) the overloaded one could save
// copy cost?
bign &bign::operator=(const int num) {
  TRACE
  char temp[MAX_L];
  sprintf(temp, "%d", num);
  *this = temp;
  return *this;
};
bign &bign::operator=(const char *num) {
  TRACE
  memset(s, 0, sizeof(s)); // very important, many operations(e.g. addition)
                           // below need 0 initialization.
  if (num[0] == '-') {
    sign = 0;
    num++;
  } else
    sign = 1;
  len = strlen(num);
  for (int i = 0; i < len; i++)
    s[i] = num[len - 1 - i] - '0';
  return *this;
};
bign &bign::operator=(const string num) {
  *this = num.c_str();
  return *this;
};

// IO
string bign::toStr() const {
  string res;
  if (!sign)
    res += '-';
  for (int i = len - 1; i >= 0; i--)
    res += s[i] + '0';
  if (res == "-" || res == "")
    res = "0";
  return res;
}
istream &operator>>(istream &in, bign &out) {
  string str;
  in >> str;
  out = str;
  return in;
}
ostream &operator<<(ostream &out, const bign &num) {
  out << num.toStr();
  return out;
}
// Comparison
bool bign::operator<(const bign &num) const { //和参考版有差异，why
  if (sign ^ num.sign)
    return num.sign;
  if (len != num.len)
    return sign ? len < num.len : num.len < len;
  for (int i = len - 1; i >= 0; i--)
    if (s[i] != num.s[i])
      return sign ? s[i] < num.s[i] : !(s[i] < num.s[i]);
  return 0;
}
bool bign::operator>(const bign &num) const { return num < *this; }
bool bign::operator<=(const bign &num) const { return !(*this > num); }
bool bign::operator>=(const bign &num) const { return !(*this < num); }
bool bign::operator!=(const bign &num) const {
  return *this < num || *this > num;
}
bool bign::operator==(const bign &num) const { return !(*this != num); }

// Arithmetic
bign bign::operator+() const { return *this; }
bign bign::operator-() const {
  bign res = *this;
  res.sign ^= 1;
  return res;
}
bign bign::operator+(const bign &num) const {
  if (sign ^ num.sign) {
    bign subtrahend = sign ? num : *this;
    subtrahend.sign = 1;
    return sign ? (*this - subtrahend) : (num - subtrahend);
  }
  bign res;
  res.sign = sign;
  int up = 0;
  int i = 0;
  for (; i < max(len, num.len) || up; i++) {
    up = s[i] + num.s[i] + up;
    res.s[i] = up % 10;
    up /= 10;
  }
  res.len = i;
  return res;
}
bign bign::operator-(const bign &num) const {
  bign a = *this, b = num;
  if (!a.sign && !b.sign) {
    a.sign = b.sign = 1;
    return b - a;
  }
  if (!b.sign) {
    b.sign = 1;
    return a + b;
  }
  if (!a.sign) {
    b.sign = 0;
    return a + b;
  }
  if (a < b)
    return -(b - a);
  int i = 0, up = 0;
  bign res;
  res.len = a.len;
  res.sign = 1;
  for (; i < a.len; i++) {
    int x = a.s[i] - up;
    if (i < b.len)
      x -= b.s[i];
    if (x >= 0)
      up = 0;
    else {
      up = 1;
      x += 10;
    }
    res.s[i] = x;
  }
  res.clean();
  return res;
}
bign bign::operator*(const bign &num) const {
  bign res;
  res.len = len + num.len;
  res.sign = !(sign ^ num.sign);
  for (int i = 0; i < len; i++) {
    int up = 0;
    for (int j = 0; j < num.len; j++) {
      res.s[i + j] += s[i] * num.s[j] + up;
      up = res.s[i + j] / 10;
      res.s[i + j] %= 10;
    }
    res.s[i + num.len] += up;
  }
  res.clean();
  return res;
}
bign bign::operator/(const bign &num) const {
  // improved version combined two reference.
  if (!sign)
    return -((-*this) / num);
  if (!num.sign)
    return -(*this / (-num));
  bign down = 0;
  bign res;
  res.len = len;
  for (int i = len - 1; i >= 0; i--) {
    down *= 10;
    down = down + s[i];
    if (num > down)
      continue;
    int quotient;
    for (quotient = 1; num * quotient <= down && quotient < 10; quotient++)
      ;
    quotient--;
    res.s[i] = quotient;
    down -= num * quotient;
  }
  res.clean();
  return res;
}
bign bign::operator%(const bign &num) const {
  if (!sign)
    return -(-*this % num);
  if (!num.sign)
    return *this % (-num);
  bign quotient = *this / num;
  return *this - quotient * num;
}

// Compound assignment
bign &bign::operator+=(const bign &num) {
  *this = *this + num;
  return *this;
}
bign &bign::operator-=(const bign &num) {
  *this = *this - num;
  return *this;
}
bign &bign::operator*=(const bign &num) {
  *this = *this * num;
  return *this;
}
bign &bign::operator/=(const bign &num) {
  *this = *this / num;
  return *this;
}
bign &bign::operator%=(const bign &num) {
  *this = *this % num;
  return *this;
}

// Increment/Decrement
bign &bign::operator++() {
  *this = *this + 1;
  return *this;
}
bign bign::operator++(int) {
  bign old = *this;
  *this = *this + 1;
  return old;
}
bign &bign::operator--() {
  *this = *this - 1;
  return *this;
}
bign bign::operator--(int) {
  bign old = *this;
  *this = *this - 1;
  return old;
}

// Misc
void bign::clean() {
  if (len == 0)
    len++;
  int i = len - 1;
  while (!s[i] && i)
    i--;
  len = i + 1;
}

void Constructor_IO_test() {
  //其实说实话下面这些都是优先调用move_constructor吧
  cout << "Constructor_IO_test" << endl;
  bign Default;
  PRINT(Default)
  bign char0 = "0";
  PRINT(char0)
  bign charnull = "";
  PRINT(charnull)
  bign charn0 = "-0";
  PRINT(charn0)
  bign Int = -0;
  PRINT(Int)
  bign String = (string("-123"));
  PRINT(String)
  bign Uniform{"123"};
  PRINT(Uniform)
  bign functional("123");
  PRINT(functional)
  bign POD = {"-123"};
  PRINT(POD)

  bign Input1, Input2;
  cout << "Test Input1 & Input2:";
  cin >> Input1 >> Input2;
  PRINT(Input1)
  PRINT(Input2)

  cout << endl;
}
void Assignment_test() {
  cout << "Assignment_test" << endl;
  int x = -10;
  bign Int;
  PRINT(Int = x)
  char charx[] = "-10";
  bign Char;
  PRINT(Char = charx)
  string stringx("-10");
  bign String;
  PRINT(String = stringx)
  PRINT(String = Char = Int = 66666)
  cout << endl;
}
void Comparison_test() {
  cout << "Comparison_test" << endl;
  cout << boolalpha;

  PRINT(bign(123) < bign(123))
  PRINT(bign(122) < bign(123))
  PRINT(bign(123) < bign(122))
  cout << endl;
  PRINT(bign(-123) < bign(-123))
  PRINT(bign(-122) < bign(-123))
  PRINT(bign(-123) < bign(-122))
  cout << endl;
  PRINT(bign(123) < bign(-123))
  PRINT(bign(122) < bign(-123))
  PRINT(bign(123) < bign(-122))
  cout << endl;

  PRINT(bign(123) > bign(122))
  cout << endl;
  PRINT(bign(123) <= bign(123))
  PRINT(bign(122) <= bign(123))
  PRINT(bign(123) <= bign(122))
  cout << endl;
  PRINT(bign(123) >= bign(122))
  cout << endl;
  PRINT(bign(123) != bign(123))
  PRINT(bign(122) != bign(123))
  PRINT(bign(123) != bign(122))
  cout << endl;
  PRINT(bign(123) == bign(123))
  PRINT(bign(122) == bign(123))
  PRINT(bign(123) == bign(122))

  cout << noboolalpha;
  cout << endl;
}
void Arithmetic_test() {
  cout << "Arithmetic_test" << endl;
  PRINT(+bign(123))
  PRINT(+bign(0))
  PRINT(+bign("-0"))
  PRINT(+bign(-123))
  cout << endl;
  PRINT(-bign(123))
  PRINT(-bign(0))
  PRINT(-bign("-0"))
  PRINT(-bign(-123))
  cout << endl;
  PRINT(bign(11111) + 1111)
  PRINT(bign(11111) + bign(1111))
  PRINT(bign(11111) + bign(-11112))
  PRINT(bign(-11111) + bign(11112))
  PRINT(bign(-11111) + bign(-11112))
  cout << endl;
  PRINT(bign(11111) - 1111)
  PRINT(bign(11111) - bign(1111))
  PRINT(bign(11111) - bign(-11112))
  PRINT(bign(-11111) - bign(11112))
  PRINT(bign(-11111) - bign(-11112))
  cout << endl;

  PRINT((long long)99999 * 9999)
  PRINT(bign(99999) * 9999)
  PRINT(bign(99999) * bign(9999))
  PRINT(bign(99999) * bign(-9999))
  PRINT(bign(-99999) * bign(9999))
  PRINT(bign(-99999) * bign(-9999))
  cout << endl;
  PRINT((long long)1234567890 / 99999)
  PRINT((long long)1234567890 / -99999)
  PRINT((long long)-1234567890 / 99999)
  PRINT((long long)-1234567890 / -99999)
  PRINT(bign(1234567890) / 99999)
  PRINT(bign(1234567890) / bign(99999))
  PRINT(bign(1234567890) / bign(-99999))
  PRINT(bign(-1234567890) / bign(99999))
  PRINT(bign(-1234567890) / bign(-99999))
  cout << endl;
  PRINT(bign(1234567890) % 99999)
  PRINT(bign(1234567890) % bign(99999))
  PRINT(bign(1234567890) % bign(-99999))
  PRINT(bign(-1234567890) % bign(99999))
  PRINT(bign(-1234567890) % bign(-99999))
  PRINT(1234567890 % 99999)
  PRINT(1234567890 % -99999)
  PRINT(-1234567890 % 99999)
  PRINT(-1234567890 % -99999)
  cout << endl;
}
void Compound_Assignment_test() {
  cout << "Compound_Assignment_test" << endl;
  PRINT(bign(11111) += 111)
  PRINT(bign(11111) += bign(111) += 111)
  PRINT(bign(11111) -= -11112)
  PRINT(bign(11111) *= 111)
  PRINT(bign(1234567890) /= -99999)
  PRINT(bign(1234567890) %= -99999)
  cout << endl;
}
void IncDec_test() {
  cout << "IncDec_test" << endl;
  bign x(111);
  PRINT(x)
  PRINT(x++)
  PRINT(x--)
  PRINT(x)
  PRINT(++x)
  PRINT(++x = 666)
  PRINT(--x)
  PRINT(--x = -666)
  PRINT(x)
  cout << endl;
  bign y = 0;
  PRINT(y)
  PRINT(--y)
  PRINT(++y)
  cout << endl;
}
void unit_test() {
  Constructor_IO_test();
  Assignment_test();
  Comparison_test();
  Arithmetic_test();
  Compound_Assignment_test();
  IncDec_test();
}

int main() {
  unit_test();
  return 0;
}