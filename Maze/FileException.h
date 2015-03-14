#ifndef INDEXOUTOFBOUNDS_H
#define INDEXOUTOFBOUNDS_H
#include "RunTimeException.h"

class FileException : public RunTimeException
{
public:
    FileException(const string &err = "Index out of bounds.");
    ~FileException();
};

#endif // INDEXOUTOFBOUNDS_H
