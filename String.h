#pragma once
#include <iostream>

// Set a max size, necessary as size_t is unsigned
#define SIZE_T_MAX (size_t)(-1)

class String
{
public:
	String();
	String(const char* _str);

	String(const String& _other);

	~String();

public:
	size_t Length() const;
	char& CharacterAt(size_t _index);
	const char& CharacterAt(size_t _index) const;

	bool EqualTo(const String& _other) const;

	String& Append(const String& _str);
	String& Prepend(const String& _str);

	const char* CStr() const;

	String& ToLower();
	String& ToUpper();

	size_t Find(const String& _str);
	size_t Find(size_t _startIndex, const String& _str);

	String& Replace(const String& _find, const String& _replace);

	// [!] Added Functionality
	String Substring(const size_t _startIndex, const size_t _length);
	String& Insert(const size_t _loc, const String& _str);
	String& Remove(const size_t _loc, const size_t _length);
	String& ReplaceAll(const String& _find, const String& _replace);

	String& ReadFromConsole();
	String& WriteToConsole();

public:
	bool operator==(const String& _other);
	bool operator!=(const String& _other);

	String& operator=(const String& _str);

	char& operator[](size_t _index);
	const char& operator[](size_t _index) const;

	// [!] Added Functionality
	
	// Appends the second string to the first one, concatonating them and return a new temporaty value
	String operator+(const String& _other); // String + String
	// Appends the second string to the first one, concatonating them and return a new temporaty value
	String operator+(const char* _other); // String + Char*
	// Appends the second string to the first one, concatonating them and return a new temporaty value
	friend String operator+(const char* _first, const String& _second); // Char* + String

	// Appends the second string to the first one, concatonating them
	String& operator+=(const String& _other); // String + String
	// Appends the second string to the first one, concatonating them
	String& operator+=(const char* _other); // String + Char*
	// Appends the second string to the first one, concatonating them
	friend String operator+=(const char* _first, const String& _second); // Char* + String

	friend std::ostream& operator<<(std::ostream& console, const String& _string); // Allows for std::cout << String
private:
	char* m_Str;
	size_t m_Length;
	size_t m_Capacity;
};
