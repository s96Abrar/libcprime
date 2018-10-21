#ifndef STRINGFUNC_H
#define STRINGFUNC_H

#include <QString>
#include "libcprime_global.h"

namespace CPrime {

class StringFunc
{
public:
    static QString CapitalizeEachWord(const QString &str);
};

}

#endif // STRINGFUNC_H
