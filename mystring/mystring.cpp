#include <iostream>
#include <cstring>

#include "mystring.h"

using namespace std;

//constructors

//default constructor
MyString::MyString() {
    size= 1;
    arr= new char[size];
    arr[0]= '\0';
}

MyString::MyString(const char * cstr) {
    //get length of cstring
    size= strlen(cstr);
    arr= new char[size];
    //copy each value of the cstr to the MyString dynamic array
    for(int i=0; i<size; i++)
        arr[i]= cstr[i];
}

MyString::MyString(int x) {
    int temp= x;
    int counter= 0;
    //count how many digits the number has
    while(temp>0){
        counter++;
        temp=temp/10;
    }
    //add an extra spot for null char
    size= counter+1;
    arr= new char[size];

    //set last value of array to null character
    arr[counter]= '\0';
    //add each digit of the int, starting from the end to the dynamic array
    for(int i=size-2; i>=0; i--){
        //convert from ascii value to int value
        arr[i]= x%10 + '0';
        //remove last digit of int
        x= x/10;
    }
}

//automatics

//destructor
MyString::~MyString(){
    delete [] arr;
}

//copy constructor
MyString::MyString(const MyString& str) {
    size= str.size;
    //create new dynamic array
    arr= new char[size];
    //copy dynamic data
    for(int i=0; i<size; i++)
        arr[i]= str[i];
}

//assignment operator
MyString& MyString::operator=(const MyString &str) {
    //if object passed is not already in this object
    if(this != &str){
        //delete data we already have bc not a new object
        delete [] arr;

        size= str.size;

        //copy dynamic data
        arr= new char[size];
        for(int i=0; i<size; i++)
            arr[i]= str[i];
    }
    return *this;
}

//io functions
ostream& operator<< (ostream& s, const MyString& str){
    //loop through MyString object, print every value but the last one
    for(int i=0; i<str.size; i++){
        s<<str[i];
    }
    return s;
}

istream& operator>> (istream& s, MyString& str){
    //make string empty
    str= MyString();

    int start= -1;
    //get a single char from the input and add to the string, if possible
    //ignore white space and new lines
    while(start<0){
        if(s.get()!= '\n' || s.get()!= ' ')
            //operate on original string
            str= str+ s.get();
        else
            start= 1;
    }
    return s;
}

//deliminator of '\n'
istream& getline (istream& s, MyString& str){
    //call other getline function
    getline(s, str, '\n');
    return s;
}

istream& getline (istream& s, MyString& str, char delim){
    //make string empty
    str= MyString();

    //get a single char from the input and add to string until reaching deliminator
    while(s.get()!=delim)
        str= str+ s.get();

    return s;
}

//comparison operators

bool operator< (const MyString& str1, const MyString& str2){
    //if not equal to
    if(str1==str2)
        return false;
    //if the first size is larger, false
    if(str1.size>str2.size)
        return false;
    //if the first value is smaller, true
    if(str1.size<str2.size)
        return true;

    //compare each value manually
    for(int i=0; i<str1.size; i++){
        //convert values to ascii values
        int val1= int(str1[i]);
        int val2= int(str2[i]);

        if(val1>val2)
            return false;
    }
    return true;
}

//greater than
bool operator> (const MyString& str1, const MyString& str2){
    //if not equal to and not less than
    if(str1==str2)
        return false;
    if(str1<str2)
        return false;
    return true;
}

//less than or equal to
bool operator<=(const MyString& str1, const MyString& str2){
    //if equal to
    if(str1==str2)
        return true;
    //if less than
    if(str1<str2)
        return true;
    return false;
}

//greater than or equal to
bool operator>=(const MyString& str1, const MyString& str2){
    //if equal to
    if(str1==str2)
        return true;
    //if greater than
    if(str1>str2)
        return true;
    return false;
}

//equals
bool operator==(const MyString& str1, const MyString& str2){
    //if not the same size, not equal
    if(str1.size!=str2.size)
        return false;
    for(int i=0; i<str1.size; i++){
        //if not the same char in same spot, not equal
        if(str1[i]!=str2[i])
            return false;
    }
    return true;
}

//not equals
bool operator!=(const MyString& str1, const MyString& str2){
    //if they're equal, its false
    if(str1==str2)
        return false;
    return true;
}

//concatenation operators
MyString operator+ (const MyString& str1, const MyString& str2){
    MyString s= str1;
    int len= str1.size+str2.size;
    s.changeSize(len);
    int counter= 0;
    for(int i= str1.size; i<len; i++){
        s[i]= str2[counter];
        counter++;
    }
    return s;
}

MyString& MyString::operator+=(const MyString& str){
    int len= size+str.size;
    int temp= size;
    //change size of self to length
    changeSize(len);
    int counter= 0;
    //add str to end of original
    for(int i=temp; i<len; i++) {
        arr[i] = str[counter];
        counter++;
    }
    //change size
    size= len;
    return *this;
}

//change the size of a MyString given new length
MyString changeSize(MyString& str1, int len){
    //make new dynamic array with the intended size
    char * newarr = new char[len];
    //copy over the data
    for(int i=0; i<str1.size; i++)
        newarr[i]= str1.arr[i];
    //delete old array
    delete [] str1.arr;
    //define the old array as the new array
    str1.arr= newarr;
    str1.size= len;

    return str1;
}

//member function change size
void MyString::changeSize(int len){
    //make new dynamic array with the intended size
    char * newarr= new char[len];
    //copy over data
    for(int i=0; i<size; i++)
        newarr[i]= arr[i];
    //delete old array
    delete [] arr;
    //define old array as new array

    size= len;
    arr= newarr;
}

//bracket operators
char& MyString::operator[] (unsigned int index){
    if(index>=size){
        int len= index-size;
        changeSize(size+len);
    }
    return arr[index];
}

const char& MyString::operator[] (unsigned int index) const{
    //if size is too big
    if(index>=size)
        return '\0';
    return arr[index];
}

//accessors
int MyString::getLength() const{
    return size;
}
const char* MyString::getCString() const{
    return arr;
}

//substring functions
MyString MyString::substring(unsigned int x, unsigned int y) const{
    //if length given for substring is too big, default to rest of string
    if(y>=size-1)
        y= size-x;
    //string to return
    MyString s= MyString();
    //change size to length asked for
    s.changeSize(y);
    int counter= 0;
    //copy substring
    for(int i=x; i<x+y; i++){
        s.arr[counter]=arr[i];
        counter++;
    }
    return s;
}

MyString MyString::substring(unsigned int x) const{
    MyString s= MyString();
    //size should be from x to end of string
    s.changeSize(size-x);
    int counter= x;
    //copy substring
    for(int i=0; i<s.size; i++){
        s.arr[i]= arr[counter];
        counter++;
    }
    return s;
}

//insert() function
MyString& MyString::insert(unsigned int index, const MyString& str){
    //create a substring for second half of word
    MyString temp= substring(index);
    cout<<temp<<endl;
    //if index is out of bounds, adjust it to bounds
    if(index>size){
        index= size;
    }
    //add size to array to accommodate str
    changeSize(size+str.size);
    int counter= 0;
    //add str to arr
    for(int i=index; i<size-1; i++){
        arr[i]= str[counter];
        counter++;
    }
    counter= 0;
    //add temp to arr
    for(int i=index+str.size; i<size; i++){
        arr[i]= temp[counter];
        counter++;
    }

    return *this;
}

//indexOf function
int MyString::indexOf(const MyString& str) const{
    int len= str.size;
    //locate substring
    for(int i=0; i<=size-len; i++){
        //reset found to true
        bool found= true;
        for(int j=0; j<str.size; j++){
            if(arr[i+j]!=str[j])
                found= false;
            //return index of str where substring starts
            if(j==str.size-1 && found)
                return i;
        }
    }
    //if no index was found, return -1
    return -1;
}