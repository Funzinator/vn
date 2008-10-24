#include "NGA.h"

NGA::NGA(RawOperation *rawOp) : NegateOperation(rawOp)
{
    /* nichts zu tun */
}

void NGA::run(Configuration *c)
{
    c->getAC()->setInt(-(c->getAC()->getInt()));
    c->setPC(c->getPC() + 1);
}
