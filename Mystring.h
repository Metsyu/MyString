#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Mystring
{
	public:
		typedef unsigned int size_type;
		static const unsigned int npos = 0xFFFFFFFF;
		
		//Default constructor
		Mystring();
		
		//Constructor
		Mystring(const char* s);
		
		//Copy constructor
		Mystring(const Mystring& orig);
		
		//Destructor
		~Mystring();
		
		//Memory related methods
		void reserve(size_type n);
		size_type size() const;
		size_type length() const;
		size_type capacity() const;
		size_type max_size() const;
		bool empty() const;
		
		//Assignment operator
		Mystring& operator=(const Mystring& orig);
		Mystring& operator=(const char* orig);
		
		// Array notation
		char operator[](size_type pos) const;
		char& operator[](size_type pos);
		
		//Append
		Mystring& operator+=(const Mystring& str);
		Mystring& operator+=(const char* str);
		
		//Methods that modify the string
		void clear();
		void push_back(char c);
		Mystring& append(const Mystring& str, size_type subpos, size_type sublen);
		Mystring& append(const char* str, size_type n);
		Mystring& insert(size_type pos, const Mystring& str);
		Mystring& insert(size_type pos, const char* str);
		Mystring& replace(size_type start, size_type span, const Mystring& str);
		Mystring& replace(size_type start, size_type span, const char* str);
		const char* c_str() const;
		size_type find_first_of (const char* s, size_type pos, size_type n) const;
		size_type find_last_not_of (const char* s, size_type pos = npos) const;
		
	private:
		//Pointer to the memory location where string is stored as a c-style
		char * ptr_buffer;
		
		//The size of the memory in terms of bytes or characters
		size_type buf_size;
		
		//Number of characters currently in the memory not including the terminating null character
		size_type len;
};

//Overloading global operators for Mystring
bool operator==(const Mystring& first, const Mystring& second);
bool operator==(const char* first, const Mystring& second);
bool operator==(const Mystring& first, const char* second);
bool operator!=(const Mystring& first, const Mystring& second);
bool operator!=(const char* first, const Mystring& second);
bool operator!=(const Mystring& first, const char* second);
Mystring operator+(const Mystring& first, const Mystring& second);
ostream& operator<<(ostream& out, const Mystring& str);

#endif /* MYSTRING_H */