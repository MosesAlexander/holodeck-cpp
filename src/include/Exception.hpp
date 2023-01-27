#ifndef EXCEPTION_HEADERFILE_H
#define EXCEPTION_HEADERFILE_H

class application_exception: public std::runtime_error {
public:
	application_exception(std::string const &msg): std::runtime_error(msg) {}
};

#endif