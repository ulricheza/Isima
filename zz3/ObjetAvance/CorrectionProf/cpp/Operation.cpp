#include "Operation.hpp"

#include <boost/format.hpp>


Operation::Operation( Date const & date, std::string const & label, float const amount, bool const isFee )
    : date_( date ), label_( label ), amount_( amount ), isFee_( isFee )
{
}

std::string Operation::format( boost::format fmt ) const
{
    fmt.exceptions( boost::io::all_error_bits ^ boost::io::too_many_args_bit );
    fmt % date_ % label_ % amount_ % isFee_;
    
    return fmt.str();
}
