#include <cstring>
#include "ZRBString.h"
#include "Exception.h"
#include <sys/file.h>

namespace ZRBLib
{

void String::init(const char *s)
{
    m_str = strdup(s);
    if(m_str)
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create string..");
    }
}

String::String()
{
    init("");
}

String::String(char c)
{
    char str[] = {c, '\0'};

    init(str);
}

String::String(const String& s)
{
    init(s.m_str);
}

String::String(const char* s)
{
    init(s ? s : "");
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

String::~String()
{
    free(m_str);
}

bool String::operator ==(const String& s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}

bool String::operator ==(const char* s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool String::operator !=(const String& s) const
{
    return (strcmp(m_str, s.m_str) != 0);
}

bool String::operator !=(const char* s) const
{
    return (strcmp(m_str, s ? s : "") != 0);
}

bool String::operator >=(const String& s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}

bool String::operator >=(const char* s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool String::operator <=(const String& s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}

bool String::operator <=(const char* s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

bool String::operator >(const String& s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}

bool String::operator >(const char* s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool String::operator <(const String& s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}

bool String::operator <(const char* s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

String String::operator +(const String& s) const
{
    return (*this + s.m_str);
}

String String::operator +(const char* s) const
{
    String ret;
    int len = m_length + strlen(s ? s : "");
    char* str = reinterpret_cast<char*>(malloc(len + 1));

    if(str)
    {
        strcpy(str, m_str);
        strcat(str, s ? s : "");

        free(ret.m_str);

        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create string..");
    }

    return ret;
}

String& String::operator +=(const String& s)
{
    return (*this = *this + s);
}

String& String::operator +=(const char* s)
{
    return (*this = *this + s);
}

String String::operator -(const String& s) const
{
    return String(*this).remove(s);
}

String String::operator -(const char* s) const
{
    return String(*this).remove(s);
}

String& String::operator -=(const String& s)
{
    return remove(s);
}

String& String::operator -=(const char* s)
{
    return remove(s);
}

String& String::operator =(const String& s)
{
    return (*this = s.m_str);
}
String& String::operator =(const char* s)
{
    char* str = strdup(s);

    if(str)
    {
        free(m_str);

        m_str = str;
        m_length = strlen(s ? s : "");
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create string..");
    }

    return *this;
}

String& String::operator =(char c)
{
    char str[] = {c, '\0'};
    return (*this = str);
}

char& String::operator [](int i)
{
    if((i >= 0) && (i < m_length))
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "paramter is invaild..");
    }
}

char String::operator [](int i) const
{
    return const_cast<String&>(*this)[i];
}

bool String::equal(const char* l, const char* r, int len) const
{
    bool ret = true;

    for(int i = 0; (i < len) && ret; i++)
    {
        ret = ret && (l[i] == r[i]);
    }

    return ret;
}

bool String::startWith(const char* s) const
{
    bool ret = (s != NULL);

    if(ret)
    {
        int len = strlen(s);
        ret = (len < m_length) && equal(m_str, s, len);
    }

    return ret;
}

bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}

bool String::endWith(const char* s) const
{
    bool ret = (s != NULL);

    if(ret)
    {
        int len = strlen(s);
        char* str = m_str + (m_length - len);
        ret = (len < m_length) && equal(str, s, len);
    }

    return ret;
}

bool String::endWith(const String& s) const
{
    return endWith(s.m_str);
}

String& String::insert(int i, const char* s)
{
    if((i <= m_length) && (i >= 0))
    {
        if((s != NULL) && (s[0] != '\0'))
        {
            int len = strlen(s);
            char* str = reinterpret_cast<char*>(malloc(m_length + len + 1));
            if(str != NULL)
            {
                strncpy(str, m_str, i);
                strncpy(str + i, s, len);
                strncpy(str + len + i, m_str + i, m_length - i);
                str[m_length + len] = '\0';

                free(m_str);
                m_str = str;
                m_length += len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert string value..");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "paramter is invaild..");
    }

    return *this;
}

String& String::insert(int i, const String& s)
{
    return insert(i, s.str());
}

String& String::trim()
{
    int b = 0;
    int e = m_length - 1;

    while(m_str[b] == ' ')
        b++;
    while(m_str[e] == ' ')
        e--;

    if(b == 0)
    {
        m_str[m_length] = '\0';
    }
    else
    {
        for(int i = 0, j = b; j <= e; i++, j++)
        {
            m_str[i] = m_str[j];
        }
        m_str[e - b + 1] = '\0';
        m_length = e - b +1;
    }

    return *this;
}

int* String::get_pmt(const char* p) const
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int) * len));

    if(ret != NULL)
    {
        int ll = 0;              //这里ll值是前后缀交集的最大长度
        ret[0] = 0;

        for(int i = 1; i < len; i++)
        {
            while((ll > 0) && (p[ll] != p[i]))
            {
                ll = ret[ll-1];         //这里匹配不上就找 当前匹配时的重叠部分
            }

            if(p[ll] == p[i])
            {
                ll++;
            }
            ret[i] = ll;
        }
    }
    return ret;
}

int String::kmp(const char* s, const char* p) const
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int* pmt = get_pmt(p);


    if((pmt != NULL) && (pl > 0) && (pl <= sl))
    {
        for(int i = 0, j = 0; i < sl; i++)
        {
            while((j > 0) && (p[j] != s[i]))
            {
                j = j - (j - pmt[j-1]);//pmt[j-1];
            }
            if(p[j] == s[i])
            {
                j++;
            }
            if(j == pl)
            {
                ret = i + 1 - pl;
                break;
            }

        }

    }

    free(pmt);

    return ret;
}

int String::indexof(const char* s) const
{
/*    int ret = -1;
    int len = strlen(s);
    if((s != NULL) && (len <= m_length) && (len > 0))
    {
        char* str = m_str;
        int i = 0;
        while(i <= len)
        {
            if(s[i] == str[i])
            {
                i++;
            }
            else
            {
                str++;
                if(str[0] == '\0')
                    break;
                i = 0;
            }

            if(i == len)
            {
                ret = str - m_str;
                break;
            }

        }
    }
*/

    return kmp(m_str, s ? s : "");
}

int String::indexof(const String& s) const
{
    return kmp(m_str, s.str());
}

String& String::remove(int i, int len)
{
    if((i > 0) && (i < m_length))
    {
        int n = i;
        int m = i + len;

        while((n < m) && (m < m_length))
        {
            m_str[n++] = m_str[m++];
        }

        m_str[n] = '\0';
        m_length = m_length - len;
    }

    return *this;
}

String& String::remove(const char* s)
{
    return remove(indexof(s), s ? strlen(s) : 0);
}

String& String::remove(const String& s)
{
    return remove(indexof(s), s.length());
}

String& String::replace(const char* s, const char* p)
{
    if((s != NULL) && (p != NULL))
    {
        int index = indexof(s);

        if(index >= 0)
        {
            remove(s);
            insert(index, p);
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Invaild paramter ..");
    }
    return *this;

}

String& String::replace(const String& s, const String& p)
{
    return replace(s.str(), p.str());
}

String& String::replace(const String& s, const char*  p)
{
    return replace(s.str(), p);
}

String& String::replace(const char* s, const String& p)
{
    return replace(s, p.str());
}

String String::sub(int i, int len) const
{
    String ret;

    if((i >= 0) && (len <= m_length))
    {
       if(len < 0)
           len = 0;
       if(len + i > m_length)
           len = m_length - i;
       char* str = static_cast<char*>(malloc(len + 1));
       if(str != NULL)
       {
            strncpy(str, m_str + i, len);
            str[len] = '\0';
            ret = str;
       }
       else
       {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create String");
       }
    }
    return ret;
}

}
