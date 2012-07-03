#ifndef BOOST_OPERATION_H
#define BOOST_OPERATION_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format/format_fwd.hpp>

#include <iostream>
#include <string>

/**
 * Represents an operation. An operation occurs at a given date, is described by a label
 * and amounts to a given sum. Operations concerning bank fees are tagged as such.
 */
class Operation
{
  public:
    typedef boost::gregorian::date Date;

    Operation( Date const & date, std::string const & label, float amount, bool isFee = false );

    /**
     * Creates a string representing the operation using the given format.
     *
     * @param fmt a format with 4 or less placeholders:
     *   - %1% will be replaced by the date;
     *   - %2% will be replaced by the label;
     *   - %3% will be replaced by the amount;
     *   - %4% will be replaced by 0 if the operation does not represent a bank
     *     fee, 1 if it represents a bank fee;
     * Not all placeholders have to be present.
     *
     * @throw boost::io::bad_format_string when the format is ill-formed
     * @throw boost::io::too_few_args when the format contains too many placeholders
     */
    std::string format( boost::format fmt ) const;

  private:

    Date        date_;
    std::string label_;
    float       amount_;
    bool        isFee_;
};

#endif //BOOST_OPERATION_H
