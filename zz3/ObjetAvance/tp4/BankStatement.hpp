#ifndef BOOST_BANKSTATEMENT_HPP
#define BOOST_BANKSTATEMENT_HPP

#include "Operation.hpp"

#include <vector>

/**
 * Represents a bank statement, i.e. a set of operations (credit, debit).
 * Can be iterated over (read-only).
 */
class BankStatement
{
  public:

    typedef std::vector< Operation >::const_iterator const_iterator;
    
    void addOperation( Operation const & op );

    const_iterator begin() const;
    const_iterator end() const;

  private:

    std::vector< Operation > operations_;
};

#endif //BANKSTATEMENT_HPP
