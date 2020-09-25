#pragma once
#include <iostream>
#include<vector>
class String
{
public:
	String(const char* str = "");
	String(const String& str);
	//copy constructor for copy a message
	~String();
public:

	const char* getString() const;

	bool operator ==(const char* str);
	bool operator ==(const String& str);

	bool operator !=(const char* str);
	bool operator !=(const String& str);

	//concatenate
	String& operator = (const char* str);
	String& operator = (const String& str);


	// add strings togheter
	String operator+(const char* str);
	String operator+(const String& str);

	//String& is needed everytime you gonna affect the invoking (calling) object
	String& operator+=(const char* str);
	String& operator+=(const String& str);

	bool operator<(String& rhs);
	bool operator>(String& lhs);

public:

	void setString(char* string) { m_string = string; };

	void Append(const char* str);
	void Append(const String& str);

	void Clear();

	int Find(const char* str);
	String SubStr(int s, int e);
	String Erase(int x, int e);
	std::vector<String> ParseString(String& str, std::vector<String>& sub,char* token);
	int Count(char character);

	std::string Converter();

	String To_Lower();

	char& operator[](int index);



	bool isEmply();
	size_t Length() const;

private:
	std::vector<String> parsed_str;
	char* m_string;
};

std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is,String& str);