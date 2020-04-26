#pragma once
#include <exception>


class StrangeTypeException : public std::exception
{
	const char* msg;
public:
	StrangeTypeException(const char* m);
	
	virtual const char* what() const throw ();
};

