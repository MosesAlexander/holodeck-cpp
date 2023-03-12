#ifndef EXCEPTION_HEADERFILE_H
#define EXCEPTION_HEADERFILE_H

class holodeck_exception: public std::runtime_error {
public:
	holodeck_exception(std::string const &msg): std::runtime_error(msg) {}
};

#endif