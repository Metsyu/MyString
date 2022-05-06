#include "Mystring.h"

//Default Constructor
Mystring :: Mystring()
{
	ptr_buffer  = new char[1];
	*ptr_buffer = '\0';
	buf_size    = 1;
	len         = 0;
}

//Constructor
Mystring :: Mystring(const char* s)
{
	len        = strlen(s);
	buf_size   = len + 1;
	ptr_buffer = new char[buf_size];
	strcpy(ptr_buffer, s);
}

//Copy Constructor
Mystring :: Mystring(const Mystring& orig)
{
	len = orig.length();
	ptr_buffer = new char[len + 1];
	buf_size = len + 1;
	for (size_type i = 0; i < buf_size; i++)
	{
		ptr_buffer[i] = orig.ptr_buffer[i];
	}
}

//Destructor
Mystring :: ~Mystring()
{
	delete [] ptr_buffer;
}

//Request a change in capacity (buf_size)
void Mystring :: reserve(size_type n)
{
	//If n is greater than buf_size update ptr_buffer and buf_size
	if (n > buf_size)
	{
		char* temp = new char[n+1];
		strcpy(temp, ptr_buffer);
		ptr_buffer = new char[n+1];
		strcpy(ptr_buffer, temp);
		buf_size = n;
		delete[] temp;
	}
}

//Getter for len
Mystring :: size_type Mystring::size() const
{
	return len;
}

//Getter for len
Mystring :: size_type Mystring::length() const
{
	return len;
}

//Getter for buf_size
Mystring :: size_type Mystring::capacity() const
{
	return buf_size;
}

//Getter for maximum size of string
Mystring :: size_type Mystring::max_size() const
{
	return npos - 4;
}

//Returns whether the string is empty (if len is 0)
bool Mystring :: empty() const
{
	if (len == 0)
		return true;
	return false;
}

//Assignment Operator (string)
Mystring& Mystring :: operator=(const Mystring& orig)
{
	//If current object doesn't equal orig, update values
	if (this != &orig)
	{
		this->buf_size = this->buf_size + orig.buf_size;
		strcpy(this->ptr_buffer, orig.ptr_buffer);
		this->len = this->len + orig.len;
	}
	
	return *this;
}

//Assignment Operator (c-string)
Mystring& Mystring :: operator=(const char* orig)
{
	//If current object doesn't equal orig, update values
	if (this->c_str() != orig)
	{
		strcpy(this->ptr_buffer, orig);
		this->buf_size = strlen(orig) + 1;
		this->len = strlen(orig);
	}
	
	return *this;
}

//Array Notation (const): Returns a reference to the character at pos in the object
char Mystring ::  operator[](size_type pos) const
{
	return ptr_buffer[pos];
}

//Array Notation: Returns a reference to the character at pos in the object
char& Mystring :: operator[](size_type pos)
{
	return ptr_buffer[pos];
}

//Append Operator
Mystring& Mystring :: operator+=(const Mystring& str)
{
	//Temporary char* to hold str
	char* temp = new char[strlen(str.c_str())];
	strcpy(temp, str.c_str());
	
	//Insert temp at the end of ptr_buffer
	insert(buf_size, temp);
	
	return *this;
}

//Append Operator
Mystring& Mystring :: operator+=(const char* str)
{
	//Temporary char* to hold str
	char* temp = new char[strlen(str)];
	strcpy(temp, str);
	
	//Insert temp at the end of ptr_buffer
	for (size_type i = 0; i < strlen(str); i++)
		this->push_back(str[i]);
	
	return *this;
}

//Erases the contents of the string
void Mystring :: clear()
{
	ptr_buffer[0] = '\0';
	len = strlen(ptr_buffer);
}

//Appends a character to the end of the string and increases len by 1
void Mystring :: push_back(char c)
{
	reserve(buf_size+1);
	ptr_buffer[len] = c;
	len++;
}

//Appends a copy of a substring, str, that begins at subpos and spans sublen (substring)
Mystring& Mystring :: append(const Mystring& str, size_type subpos, size_type sublen)
{
	//Temporary char* to hold str
	char* temp = new char[sublen];
	strncpy(temp, str.c_str() + subpos, sublen);
	temp[sublen] = '\0';
	
	//Insert temp at the end of ptr_buffer
	insert(buf_size, temp);
	
	return *this;
}

//Appends a copy of the first n characters in the array of characters pointed by str (buffer)
Mystring& Mystring :: append(const char* str, size_type n)
{
	//Temporary char* to hold str
	char* temp = new char[n];
	strncpy(temp, str, n);
	temp[n] = '\0';
	
	//Insert temp at the end of ptr_buffer
	insert(buf_size, temp);
	
	return *this;
}

//Inserts a copy of str before the character indicated by pos (string)
Mystring& Mystring :: insert(size_type pos, const Mystring& str)
{
	return insert(pos, str.c_str());
}

//Inserts a copy of the string formed by str before the character indicated by pos (c-string)
Mystring& Mystring :: insert(size_type pos, const char* str)
{
	//Update len and buf_size
	len = len + strlen(str);
	reserve(len + 1);
	
	//Temporary char* to hold characters before pos
	char* temp = new char[pos];
	
	//Insert characters from ptr_buffer before pos into temp
	for (size_type i = 0; i < pos; i++)
		temp[i] = ptr_buffer[i];
	temp[pos] = '\0';
	
	//Temporary char* to hold characters after pos
	char* temp2 = new char[len - (pos + 1)];
	
	//Insert characters from ptr_buffer after pos into temp
	size_type j = 0;
	for (size_type i = pos; i < len; i++)
	{
		temp2[j] = ptr_buffer[i];
		j++;
	}
	
	//Combine all strings into ptr_buffer
	strcpy(ptr_buffer, temp);
	strcat(ptr_buffer, str);
	strcat(ptr_buffer, temp2);
	
	return *this;
}

//Copies str and replaces the portion of the string that begins at start
//and spans, span, characters (string)
Mystring& Mystring :: replace(size_type start, size_type span, const Mystring& str)
{
	return replace(start, span, str.c_str());
}

//Copies the c-string, str, and replaces the portion of the string that begins at start
//and spans, span, characters (c-string)
Mystring& Mystring :: replace(size_type start, size_type span, const char* str)
{
	//Create a temporary char * to hold characters from str and ptr_buffer
	char* temp = new char[buf_size + strlen(str)];
	
	//If start > 0 copy the elements from ptr_buffer at before start to the beginning of temp
	if (start > 0)
	{
		for (size_type i = 0; i < start; i++)
			temp[i] = ptr_buffer[i];
	}

	//Copy all elements from str to temp starting at start
	size_type j = 0;
	for (size_type i = start; j <= strlen(str); i++)
	{
		temp[i] = str[j];
		j++;
	}

	//Copy elements from ptr_buffer starting at span + start to temp starting at the end of temp
	size_type k = strlen(temp);
	for (size_type i = span + start; i <= len + strlen(str); i++)
	{
		temp[k] = ptr_buffer[i];
		k++;
	}
	
	//Update buf_size, len, and ptr_buffer
	reserve(strlen(temp) + 1);
	len = strlen(temp);
	ptr_buffer = temp;
	
	return *this;
}

//Get the c-string equivalent of the current string object
const char* Mystring :: c_str() const
{
	return ptr_buffer;
}

//Searches the string for the first character that matches any of the characters specified in s.
//Only searches after pos and ignores occurrences before pos.
Mystring :: size_type Mystring :: find_first_of (const char* s, size_type pos, size_type n) const
{
	//Iterate through ptr_buffer
	for (size_type i = 0; i < s[i] != '\0'; i++)
	{
		//Iterate through s
		for (size_type j = 0; j < n; j++)
		{
			//Check if the characters match and return
			if (s[i + pos] == s[j])
				return i + pos;
		}
	}
	
	//Return npos if no matching character is found
	return npos;
}

//Searches the string for the last character that does not match any of the characters specified in s.
//Searches the entire string since pos = npos.
Mystring :: size_type Mystring :: find_last_not_of (const char* s, size_type pos) const
{
	//If pos is specified
	if (pos < len)
	{
		//Iterate backwards through ptr_buffer, starting at pos
		for (size_type i = pos; i >= 0; i--)
		{
			bool found = false;
			
			//Set c equal to current element
			char c = ptr_buffer[i];
			
			//Iterate through s
			for (size_type j = 0; j < strlen(s); j++)
			{
				//If the current element in s matches c, set found equal to true
				if (s[j] == c)
					found = true;
			}
			
			//If found is false, return current index
			if (!found)
				return i;
			
			//If no character can be found that isn't in s, return npos
			if (i == 0)
				return npos;
		}
	}
	
	//Else if pos isn't specified
	else
	{
		//Iterate backwards through the entirety of ptr_buffer
		for (size_type i = len-1; i >= 0; i--)
		{
			bool found = false;
			
			//Set c equal to current element
			char c = ptr_buffer[i];
			
			//Iterate through s
			for (size_type j = 0; j < strlen(s); j++)
			{
				//If the current element in s doesn't match c, set found equal to true
				if (s[j] == c)
					found = true;
			}
			
			//If found is false, return current index
			if (!found)
				return i;
			
			//If no character can be found that isn't in s, return npos
			if (i == 0)
				return npos;
		}
	}
	
	//Default return npos
	return npos;
}

//Does equal overload operator
bool operator==(const Mystring& first, const Mystring& second)
{
	for (int i = 0; first[i] != '\0' && second[i] != '\0'; i++)
	{
		if (first[i] != second[i])
			return false;
	}
	
	return true;
}

//Does equal overload operator
bool operator==(const char* first, const Mystring& second)
{
	for (int i = 0; first[i] != '\0' && second[i] != '\0'; i++)
	{
		if (first[i] != second[i])
			return false;
	}
	
	return true;
}

//Does equal overload operator
bool operator==(const Mystring& first, const char* second)
{
	for (int i = 0; first[i] != '\0' && second[i] != '\0'; i++)
	{
		if (first[i] != second[i])
			return false;
	}
	
	return true;
}

//Does not equals overload operator
bool operator!=(const Mystring& first, const Mystring& second)
{
	for (int i = 0; first[i] != '\0' && second[i] != '\0'; i++)
	{
		if (first[i] != second[i])
			return true;
	}
	
	return false;
}

//Does not equals overload operator
bool operator!=(const char* first, const Mystring& second)
{
	for (int i = 0; first[i] != '\0' && second[i] != '\0'; i++)
	{
		if (first[i] != second[i])
			return true;
	}
	
	return false;
}

//Does not equals overload operator
bool operator!=(const Mystring& first, const char* second)
{
	for (int i = 0; first[i] != '\0' && second[i] != '\0'; i++)
	{
		if (first[i] != second[i])
			return true;
	}
	
	return false;
}

//Concatenate string
Mystring operator+(const Mystring& first, const Mystring& second)
{
	//Temporary char* to hold the characters of first and second
	char* temp = new char[strlen(first.c_str() + strlen(second.c_str()))];
	
	//Add characters of first to temp
	strcpy(temp, first.c_str());
	
	//Concatenate temp with second
	strcat(temp, second.c_str());
	
	return temp;
}

//Output
ostream& operator<<(ostream& out, const Mystring& str)
{
	out << str.c_str();
	return out;
}