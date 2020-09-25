#include "String.h"




std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.getString();
	return os;
}

std::istream& operator>>(std::istream& is, String& str)
{
	str.Clear();

	char* temp = new char[10'000];

	is.getline(temp, 10'000);

	str = temp;

	delete[] temp;

	return is;
}

//========================================================================
String::String(const char* str)
{
	m_string = nullptr;
	*this = str;
}

String::String(const String& str)
{

	////============ DO NOT DO THIS=============
	////example of shallow copy
	////m_string = str.m_string;
	////========================================

	////example of deep copy
	////str.m_string is because the m_string is below str
	//size_t SIZE = strlen(str.m_string) + 1;
	//// plus on is for the terminatind null
	//m_string = new char[SIZE];
	//strcpy_s(m_string, SIZE, str.m_string);

	m_string = nullptr;
	*this = str;
}

String::~String()
{
	//delete got the "[]" because otherwise would just cancel the first element
	delete[] m_string;
}

bool String::operator==(const char* str)
{
	//strcmp returns 0 as true, but our "return" gets zeros as false! So by doing this we translate it for the return
	return (!strcmp(m_string, str));
}

bool String::operator==(const String& str)
{
	return (!strcmp(m_string, str.m_string));
}

bool String::operator!=(const char* str)
{
	return (strcmp(m_string, str));
}

bool String::operator!=(const String& str)
{
	return (strcmp(m_string, str.m_string));
}

const char* String::getString() const
{
	return m_string;
}

String& String::operator=(const char* str)
{
	delete[] m_string;
	const size_t SIZE = strlen(str) + 1;
	// plus on is for the terminatind null
	m_string = new char[SIZE];
	strcpy_s(m_string, SIZE, str);


	// This is the left of the operator
	return *this;
}

String& String::operator=(const String& str)
{
	if (this == &str)
	{
		return *this;
	}
	delete[] m_string;
	const size_t SIZE = strlen(str.m_string) + 1;
	// plus on is for the terminatoind null
	m_string = new char[SIZE];
	strcpy_s(m_string, SIZE, str.m_string);


	// This is the left of the operator
	return *this;

}

String String::operator+(const char* str)
{
	//const size_t SIZE = strlen(m_string) + strlen(str) + 1;
	//char* sum_str = new char[SIZE];

	//strcpy_s(sum_str, SIZE,m_string);
	//strcat_s(sum_str, SIZE,str );

	//// this is because sum_str IS A POINTER! So we wrap it in our constructor and next time you don't have to use Getstring() for visualise it
	//String temp(sum_str);
	//return temp;

	String temp(*this);
	// because when we use the "+" it "calls" the operator "function"
	return (temp += str);
}

String String::operator+(const String& str)
{
	//const size_t SIZE = strlen(m_string) + strlen(str.m_string) + 1;
	//char* sum_str = new char[SIZE];

	//strcpy_s(sum_str, SIZE, m_string);
	//strcat_s(sum_str, SIZE, str.m_string);
	//// this is because sum_str IS A POINTER! So we wrap it in our constructor and next time you don't have to use Getstring() for visualise it
	//String temp(sum_str);
	//return temp;
	String temp(*this);
	// because when we use the "+" it "calls" the operator "function"
	return (temp += str);
}

String& String::operator+=(const char* str)
{
	char* sum_str = nullptr;
	const size_t SIZE = strlen(m_string) + strlen(str) + 1;
	sum_str = new char[SIZE];

	strcpy_s(sum_str, SIZE, m_string);
	strcat_s(sum_str, SIZE, str);

	delete[] m_string;
	m_string = sum_str;

	return *this;
}

String& String::operator+=(const String& str)
{
	*this += str.m_string;
	return *this;
}

bool String::operator<(String& rhs)
{
	String str = getString();
	char c = str[0];
	char c1 = rhs[0];
	return tolower(c) < tolower(c1);
}

bool String::operator>(String& lhs)
{
	String str = getString();
	char c = str[0];
	char c1 = lhs[0];
	return tolower(c) > tolower(c1);
}

void String::Append(const char* str)
{
	size_t SIZE1 = strlen(m_string) + 1;
	size_t SIZE2 = strlen(str) + 1;

	const size_t SIZE = SIZE2 + SIZE1;
	char* sum_str = new char[SIZE];

	strcpy_s(sum_str, SIZE, m_string);
	strcat_s(sum_str, SIZE, str);

	m_string = sum_str;
}

void String::Append(const String& str)
{
	size_t SIZE1 = (size_t)strlen(m_string) + 1;
	size_t SIZE2 = strlen(str.m_string) + 1;

	const size_t SIZE = SIZE2 + SIZE1;
	char* sum_str = new char[SIZE];

	strcpy_s(sum_str, SIZE, m_string);
	strcat_s(sum_str, SIZE, str.m_string);

	m_string = sum_str;
}

char& String::operator[](int index)
{
	size_t SIZE = strlen(m_string) + 1;

	//For suggest to the user that he should put a lower number
	if (index >= SIZE)
	{
		std::cout << "Index of of bound, please enter a lower number." << std::endl;
		//exit(0);
	}
	return m_string[index];
}

void String::Clear()
{
	delete[] m_string;
	//making an empty string otherwise you gonna get or a crash or garbage
	m_string = new char;
	strcpy_s(m_string, 1, "");
}

int String::Find(const char* str)
{
	size_t SIZE1 = strlen(m_string);
	size_t SIZE2 = strlen(str);
	//int i;
	//int j;
	for (int i = 0; i <= SIZE1; i++)
	{
		if (m_string[i] == str[0])
		{
			return i;
		}
	}

	std::cout << "Character not found" << std::endl;
	return -1;
}

String String::SubStr(int s, int e)
{
	int i, j;
	int size = (e - s);

	char* c = new char[size + 1];

	for (i = 0, j = s; j < e && m_string[j] != '\0'; i++, j++)
	{
		c[i] = m_string[j];
	}
	c[i] = '\0';
	String str = c;
	//std::cout << str << std::endl;
	return str;
}

String String::Erase(int s, int e)
{
	int i, j;
	size_t SIZE1 = strlen(m_string);

	//char* cOriginal = new char[SIZE1 + 1];
	String str1 = m_string;
	String str2 = m_string;

	String str = str1.SubStr(0, s) + str2.SubStr(e, SIZE1 + 1);
	return str;
}

std::vector<String> String::ParseString(String & str, std::vector<String> & sub, char* token)
{
	char* tag_list = new char[str.Length() + 1];
	for (size_t i = 0; i < (str.Length() + 1); i++)
	{
		tag_list[i] = str[i];
	}
	String tag_list_copy = tag_list;
	//char* result = 0;
	char* context = NULL;
	char* s = strtok_s(tag_list, token, &context);
	if (s != NULL)
	{
		sub.push_back(s);
	}
	while (s != NULL)
	{
		s = strtok_s(NULL, token, &context);
		//std::cout << s << std::endl;
		if (s != NULL)
		{
			sub.push_back(s);
		}

	}
	//sub.push_back(str);

	return sub;
}

int String::Count(char character)
{
	int count = 0;
	size_t SIZE1 = strlen(m_string);
	for (int i = 0; i <= (int)SIZE1; i++) 
	{
		if (m_string[i] == character) 
		{
			count++;
		}

	}
	return count;
}

bool String::isEmply()
{
	return (*this=="");
}

size_t String::Length() const
{
	//The +1 is missing cause otherwise would count also the null element at the end.
	return strlen(m_string);
}


