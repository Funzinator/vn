#ifndef OR_H_
#define OR_H_

#include "RawOperation.h"
#include "LogicOperation.h"

class OR : public LogicOperation
{
public:
    OR(RawOperation*);

    void run(Configuration*);
};

#endif /*OR_H_*/