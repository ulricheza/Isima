#include "BankStatement.hpp"


void BankStatement::addOperation( Operation const & op )
{
    operations_.push_back( op );
}

BankStatement::const_iterator BankStatement::begin() const
{
    return operations_.begin();
}

BankStatement::const_iterator BankStatement::end() const
{
    return operations_.end();
}
