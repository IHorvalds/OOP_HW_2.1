#include "StrangeTypeException.h"

StrangeTypeException::StrangeTypeException(const char* m) {
	this->msg = m;
}

const char* StrangeTypeException::what() const throw() {
	return msg;
}
