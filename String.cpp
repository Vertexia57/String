#include "String.h"
#include <cstring>
#include <cctype>
#include <iostream>

// Base initialiser
String::String()
{
	m_Length = 0;
	m_Capacity = 1;
	m_Str = new char[1];
	m_Str[0] = '\0';
}

// Const Char initialiser
String::String(const char* _str)
{
	m_Length = strlen(_str);
	m_Capacity = m_Length + 1;
	m_Str = new char[m_Capacity];
	strcpy_s(m_Str, m_Capacity * sizeof(char), _str);
}

// String initialiser
String::String(const String& _other)
{
	m_Length = _other.m_Length;
	m_Capacity = _other.m_Capacity;
	m_Str = new char[m_Capacity];
	strcpy_s(m_Str, m_Capacity * sizeof(char), _other.m_Str);
}

// Deconstructor
String::~String()
{
	// Clear the CString from the heap
	delete[] m_Str;
}

// Returns the length of the current string (Not including terminator)
size_t String::Length() const
{
	return m_Length;
}

// Returns the character at _index in the string
char& String::CharacterAt(size_t _index)
{
	return m_Str[_index];
}

// Returns a const character at _index in the string
const char& String::CharacterAt(size_t _index) const
{
	return m_Str[_index];
}

// Returns if two strings are exactly equal or not
bool String::EqualTo(const String& _other) const
{
	return strcmp(m_Str, _other.m_Str) == 0;
}

// Appends _str to the current string (Add _str to end)
String& String::Append(const String& _str)
{
	// Set the new length and capacity of the string to hold the appended string as well
	m_Length = m_Length + _str.m_Length;
	m_Capacity = m_Length + 1;

	// Create a new CString with enough capacity to hold the appended string and the current string
	char* newString = new char[m_Capacity];

	// Copy m_Str to the start of newString
	strcpy_s(newString, m_Capacity * sizeof(char), m_Str);
	delete[] m_Str; // Clear m_Str from the heap

	// Concatonate _str onto the end of newString 
	strcat_s(newString, m_Capacity * sizeof(char), _str.m_Str);
	m_Str = newString; //Change the pointer of m_Str to newString

	//Returns the current string object
	return *this;
}

// Prepends _str to the current string (Add _str to beginning)
String& String::Prepend(const String& _str)
{
	// Create a new string with the same contents as _str
	String prependString = String(_str);
	prependString.Append(m_Str); // Append current string to the end of the new string

	delete[] m_Str; // Clear m_Str from the heap

	// Set string data to hold prependString
	m_Length = prependString.m_Length;
	m_Capacity = prependString.m_Capacity;
	m_Str = new char[m_Capacity];
	strcpy_s(m_Str, m_Capacity * sizeof(char), prependString.m_Str); // Replace all current data with the data in prependString

	//Returns the current string object
	return *this;
}

// Return the const char version of the string object
const char* String::CStr() const
{
	return m_Str;
}

// Set all alphabetic characters in the string to their lowercase variant
String& String::ToLower()
{
	for (size_t i = 0; i < m_Capacity; i++)
		m_Str[i] = tolower(m_Str[i]);

	//Returns the current string object
	return *this;
}

// Set all alphabetic characters in the string to their uppercase variant
String& String::ToUpper()
{
	for (size_t i = 0; i < m_Capacity; i++)
		m_Str[i] = toupper(m_Str[i]);

	//Returns the current string object
	return *this;
}

// Find the location of a string within a string
size_t String::Find(const String& _str)
{
	// Find pointer to string within m_Str
	char* loc = strstr(m_Str, _str.m_Str);

	if (loc == nullptr) // If nullptr return SIZE_T_MAX
		return SIZE_T_MAX;

	int index = (loc - m_Str) / sizeof(char); // Get the difference between m_Str and loc in memory, counting the amount of chars between them
	return index;
}

// Find the location of a string within a string after a certain point
size_t String::Find(size_t _startIndex, const String& _str)
{
	// Get a substring which only contains the chars after _startIndex and find the string within that string
	// After that, offset the location by the amount taken away from the substring (Being _startIndex)
	return Substring(_startIndex - 1, m_Length - _startIndex + 1).Find(_str) + _startIndex - 1;
}

// Replace the first occurance of a string with a new string
String& String::Replace(const String& _find, const String& _replace)
{
	// Finds the first occurance of a string withing the current string
	size_t locReturn = Find(_find);
	if (locReturn == SIZE_T_MAX) // If not found, break out of this function
		return *this;

	Remove(locReturn, _find.Length()); // Remove the string found
	Insert(locReturn, _replace); // Insert _replace into that location

	//Returns the current string object
	return *this;
}

// Replace ALL occurances of a string with a new string
String& String::ReplaceAll(const String& _find, const String& _replace)
{
	// Initialise starting variables
	size_t locReturn = 0;
	size_t findLength = _find.Length();

	for (int loops = 0; loops < m_Length; loops++) // Cap the amount of times it will check for a string to the length of the string (safety)
	{
		// Finds the first occurance of a string withing the current string
		size_t locReturn = Find(_find);
		if (locReturn == SIZE_T_MAX) // Check if the string contains _find, otherwise, break out of the loop
			break;

		Remove(locReturn, findLength); // Remove the string found
		Insert(locReturn, _replace); // Insert _replace into that location
	}

	//Returns the current string object
	return *this;
}

// Creates a NEW string object containing a substring of the current string
String String::Substring(const size_t _startIndex, const size_t _length)
{
	// Create a new string, which is the size of the substring
	char* subString = new char[_length + 1];

	// Loop through the string, setting subString to the values between _startIndex and _length
	for (size_t i = 0; i < _length; i++)
		subString[i] = m_Str[i + _startIndex];
	subString[_length] = '\0'; // Set the terminator for subString

	// Create the new string object
	String returnString = String(subString);
	delete[] subString; // Remove subString from the heap
	return returnString; // Return the new string object
}

// Inserts a string into the location specified
String& String::Insert(const size_t _loc, const String& _str)
{
	// Create a new string, the length of which is the current strings plus _str's
	int newLength = m_Length + _str.Length();
	char* newString = new char[newLength + 1];
	newString[newLength] = '\0'; // Set the terminator for newString

	// Loop through setting the values up to _loc
	for (size_t i = 0; i < _loc; i++)
		newString[i] = m_Str[i];

	// Once reached _loc start writing the values from _str instead of m_Str
	for (size_t i = _loc; i < _loc + _str.Length(); i++)
		newString[i] = _str[i - _loc]; // Ignore this, I have no idea why it's green

	// After that's finished, continue writing the values from m_Str until complete
	for (size_t i = _loc + _str.Length(); i < newLength; i++)
		newString[i] = m_Str[i - _str.Length()];

	// Remove m_Str from the heap
	delete[] m_Str;
	m_Str = newString; // Assign m_Str to the newString
	m_Length = strlen(m_Str); // Set length and capacity
	m_Capacity = m_Length + 1;

	//Returns the current string object
	return *this;
}

String& String::Remove(const size_t _loc, const size_t _length)
{
	// Create a new string, the length of which is the current string's length minus _length's value
	int newLength = m_Length - _length;
	char* newString = new char[newLength + 1];
	newString[newLength] = '\0'; // Set the terminator for newString

	// Loop through setting the values up to _loc
	for (size_t i = 0; i < _loc; i++)
		newString[i] = m_Str[i];
	// After that's finished, skip over _length and continue until complete
	for (size_t i = _loc; i < newLength; i++)
		newString[i] = m_Str[i + _length];

	// Remove m_Str from the heap
	delete[] m_Str;
	m_Str = newString; // Assign m_Str to the newString
	m_Length = strlen(m_Str); // Set length and capacity
	m_Capacity = m_Length + 1;

	//Returns the current string object
	return *this;
}

// Take a string input from the console
String& String::ReadFromConsole()
{
	// Create an input buffer of 256 chars
	char* in = new char[256];
	std::cin >> in; // Take the input

	// Remove m_Str from the heap
	delete[] m_Str;
	m_Length = strlen(in); // Set length and capacity
	m_Capacity = m_Length + 1;
	m_Str = new char[m_Capacity]; // Create a new CString with in's capacity
	strcpy_s(m_Str, m_Capacity * sizeof(char), in);  // Assign m_Str to the in

	//Returns the current string object
	return *this;
}

// Write string to the console
String& String::WriteToConsole()
{
	// outputs m_Str to the console 
	std::cout << m_Str;

	//Returns the current string object
	return *this;
}

// Check if String A is equal to String B
bool String::operator==(const String& _other)
{
	return EqualTo(_other);
}

// Check if String A is not equal to String B
bool String::operator!=(const String& _other)
{
	return !EqualTo(_other);
}

// Copy String B to this
String& String::operator=(const String& _str)
{
	delete[] m_Str;
	m_Length = _str.m_Length;
	m_Capacity = _str.m_Capacity;
	m_Str = new char[m_Capacity];
	strcpy_s(m_Str, m_Capacity * sizeof(char), _str.m_Str);

	return *this;
}

// Get character at _index
char& String::operator[](size_t _index)
{
	return CharacterAt(_index);
}

// Get character at _index
const char& String::operator[](size_t _index) const
{
	return CharacterAt(_index);
}

// Appends the second string to the first one, concatonating them and return a new temporaty value
String String::operator+(const String& _other)
{
	String temp = *this;
	temp.Append(_other);
	return temp;
}

// Appends the second string to the first one, concatonating them and return a new temporaty value
String String::operator+(const char* _other)
{
	String temp = *this;
	temp.Append(_other);
	return temp;
}

// Appends the second string to the first one, concatonating them and return a new temporaty value
String operator+(const char* _first, const String& _second)
{
	return String(_first).Append(_second);
}

// Appends the second string to the first one, concatonating them
String& String::operator+=(const String& _other)
{
	Append(_other);
	return *this;
}

// Appends the second string to the first one, concatonating them
String& String::operator+=(const char* _other)
{
	Append(_other);
	return *this;
}

// Appends the second string to the first one, concatonating them
String operator+=(const char* _first, const String& _second)
{
	String(_first).Append(_second);
	return String();
}

std::ostream& operator<<(std::ostream& console, const String& _string)
{
	console << _string.CStr();
	return console;
}
