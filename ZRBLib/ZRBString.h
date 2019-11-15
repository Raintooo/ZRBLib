#ifndef ZRBSTRING_H
#define ZRBSTRING_H

#include "Object.h"

namespace ZRBLib
{

class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    bool equal(const char* l, const char* r, int len) const;
    int* get_pmt(const char* p) const;
    int kmp(const char* s, const char* p) const;
public:
    String();
    String(char c);
    String(const String& s);
    String(const char* s);
    ~String();

    int length() const;
    const char* str() const;

    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endWith(const char* s) const;
    bool endWith(const String& s) const;

    String& insert(int i, const char* s);
    String& insert(int i, const String& s);

    String& trim();
    int indexof(const char* s) const;
    int indexof(const String& s) const;
    String& remove(int i, int len);
    String& remove(const char* s);
    String& remove(const String& s);

    String& replace(const char* s, const char* p);
    String& replace(const String& s, const String& p);
    String& replace(const String& s, const char*  p);
    String& replace(const char* s, const String& p);

    String sub(int i, int len) const;

    bool operator ==(const String& s) const;
    bool operator ==(const char* s) const;
    bool operator !=(const String& s) const;
    bool operator !=(const char* s) const;
    bool operator >=(const String& s) const;
    bool operator >=(const char* s) const;
    bool operator <=(const String& s) const;
    bool operator <=(const char* s) const;
    bool operator >(const String& s) const;
    bool operator >(const char* s) const;
    bool operator <(const String& s) const;
    bool operator <(const char* s) const;

    String operator +(const String& s) const;
    String operator +(const char* s) const;
    String& operator +=(const String& s);
    String& operator +=(const char* s);
    String operator -(const String& s) const;
    String operator -(const char* s) const;
    String& operator -=(const String& s);
    String& operator -=(const char* s);
    String& operator =(const String& s);
    String& operator =(const char* s);
    String& operator =(char c);

    char& operator [](int i);   //这里使用引用是为了能够成为左值
    char operator [](int i) const;

};


}



#endif // ZRBSTRING_H
