#ifndef ENTIER_H_
#define ENTIER_H_

#include "ConvertOperation.h"

class ENTIER : public ConvertOperation
{
public:
    ENTIER(RawOperation*);

    void run(Configuration*);
};

#endif /*ENTIER_H_*/
