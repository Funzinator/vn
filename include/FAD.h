#ifndef FAD_H_
#define FAD_H_

#include "FloatOperation.h"

class FAD : public FloatOperation
{
public:
    FAD(RawOperation*);

    void run(Configuration*);
};

#endif /*FAD_H_*/
