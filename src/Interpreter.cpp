#include "Interpreter.h"

Interpreter::Interpreter(QMap<unsigned int, Operation *> ops, Configuration *config)
{
    this->config = config;
    this->ops = ops;
}

void Interpreter::next()
{
    unsigned int PC = this->config->getPC();
    
    if (this->ops[PC])
    {
        this->ops[PC]->run(this->config);
    }
}

Configuration *Interpreter::getConfiguration()
{
    return this->config;
}