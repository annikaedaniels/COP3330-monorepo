#ifndef STRING_CLASS_MYSTRING_H
#define STRING_CLASS_MYSTRING_H

#include <iostream>
using namespace std;

class MyString
{
    friend ostream& operator<< (ostream& s, const MyString& str);
    friend istream& operator>> (istream& s, MyString& str);
    friend istream& getline (istream& s, MyString& str);
    friend istream& getline (istream& s, MyString& str, char delim);

    friend MyString operator+ (const MyString& str1, const MyString& str2);

    friend bool operator< (const MyString& str1, const MyString& str2);
    friend bool operator> (const MyString& str1, const MyString& str2);
    friend bool operator<=(const MyString& str1, const MyString& str2);
    friend bool operator>=(const MyString& str1, const MyString& str2);
    friend bool operator==(const MyString& str1, const MyString& str2);
    friend bool operator!=(const MyString& str1, const MyString& str2);

    //change size of mystring
    friend MyString changeSize(MyString& str1, int len);

public:
    MyString();				// empty string
    MyString(const char* cstr);		// conversion from c-string
    MyString(int x);			// conversion from int
    ~MyString();				// destructor
    MyString(const MyString& str);		// copy constructor
    MyString& operator=(const MyString& str);   // assignment operator

    MyString& operator+=(const MyString& str);  // concatenation/assignment

    void changeSize(int len);                   //change size of mystring
    // bracket operators to access char positions
    char& operator[] (unsigned int index);
    const char& operator[] (unsigned int index) const;

    // insert s into the string at position "index"
    MyString& insert(unsigned int index, const MyString& str);

    // find index of the first occurrence of s inside the string
    //  return the index, or -1 if not found
    int indexOf(const MyString& str) const;

    int getLength() const;		// return string length
    const char* getCString() const;	// return c-string equiv

    MyString substring(unsigned int x, unsigned int y) const;
    MyString substring(unsigned int x) const;

private:
    //size of array
    int size;
    //pointer for dynamic array
    char * arr;

};

#endif //STRING_CLASS_MYSTRING_H
