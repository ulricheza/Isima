
#include "Line.hpp"
#include "Operation.hpp"
#include "BankStatement.hpp"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/regex.hpp>
#include <boost/spirit/home/phoenix/core.hpp>
#include <boost/spirit/home/phoenix/operator.hpp>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>


/**
 * Creates an operation from a matched line in the format
 *   date [>>] label montant
 */
Operation createOperation( boost::smatch const & matches )
{
    using boost::phoenix::arg_names::arg1;

    // Date: dd/mm
    std::string const dateString( matches[ "date" ] );
    std::vector< std::string > tokens;

    boost::algorithm::split( tokens, dateString, arg1 == '/' );

    Operation::Date const date( 
        2011, // hard-coded year --> wrong! Should be read in the file
        boost::lexical_cast< int >( tokens[1] ),
        boost::lexical_cast< int >( tokens[0] ) );


    // Optional fee indicator: >>
    bool const isFee = matches[ "optionalFeeIndicator" ] != "";

    
    // Label: bla bla bla
    std::string const label( matches[ "label" ] );


    // Amount: +- xxx,xx
    std::string amountString( matches[ "plusOrMinus" ] );
    amountString += matches[ "amount" ];
    boost::algorithm::replace_first( amountString, ",", "." );

    float const amount = boost::lexical_cast< float >( amountString );


    return Operation( date, label, amount, isFee );
}

/**
 * Adds capture to a regular expression (as string).
 */
std::string capture( std::string const & exp )
{
    return '(' + exp + ')';
}

/**
 * Adds named capture to a regular expression (as string).
 */
std::string capture( std::string const & exp, std::string const & name )
{
    return "(?'" + name + '\'' + exp + ')';
}

/**
 * Create a bank statement from a range of strings. Strings that do not
 * represent an operation are ignored, the others trigger the creation
 * of an Operation instance that is added to the resulting BankStatement.
 */
template < typename InputIterator >
BankStatement importStatement( InputIterator first, InputIterator last )
{
    static std::string const date                 = "\\d{2}/\\d{2}";
    static std::string const optionalFeeIndicator = "(?:>>)?";
    static std::string const label                = ".*?";
    static std::string const plusOrMinus          = "(?:\\+|-)";
    static std::string const amount               = "\\d*,\\d{2}";

    static std::string const spaces               = "\\s*";

    static boost::regex const operationRegex(
        spaces +
        capture( date, "date" ) +
        spaces +
        capture( optionalFeeIndicator, "optionalFeeIndicator" ) +
        spaces +
        capture( label, "label" ) +
        spaces +
        capture( plusOrMinus, "plusOrMinus" ) +
        spaces +
        capture( amount, "amount" ) +
        spaces );

    BankStatement statement;

    for ( InputIterator it = first ; it != last ; ++it )
    {
        std::string const str( *it );

        boost::smatch matches;

        if ( boost::regex_match( str, matches, operationRegex ) )
        {
            statement.addOperation( createOperation( matches ) );
        }
    }

    return statement;
}


/**
 * Prints all the operations of a BankStatement to the destination range denoted by "out". Operations
 * are formatted using fmt.
 *
 * @throw boost::io::bad_format_string when the format is ill-formed
 * @throw boost::io::too_few_args when the format contains too many placeholders
 */
template < typename OutputIterator >
void exportStatement( BankStatement const & statement, boost::format const & fmt, OutputIterator out )
{
    boost::transform( statement, out, boost::bind( & Operation::format, _1, fmt ) ); 
}


int main( int argc, char ** argv )
{
    namespace po = boost::program_options;

    static std::string const usage = "Usage: convert [options] inputFile";


    // Define options

    static unsigned int const lineLength = 120;

    po::options_description options( "Options", lineLength );
    options.add_options()
        ( "help,h", "produce help message" )
        ( "output-file,o", po::value< std::string >(), "output file" )
        ( "format,f", po::value< std::string >()->default_value( "%1%,%2%,%3%,%4%" ), "format to be used for output" );

    po::options_description hidden( "Hidden options" );
    hidden.add_options()
        ( "input-file", po::value< std::string >(), "input file" );

    po::positional_options_description positionalOptions;
    positionalOptions.add( "input-file", 1 );


    // Store options from the command line

    po::variables_map optionValues;

    try
    {
        po::store( 
            po::command_line_parser( argc, argv).
                options( po::options_description().add( options ).add( hidden ) ).
                positional( positionalOptions ).
                run(),
            optionValues );
        po::notify( optionValues );
    }
    catch( po::error const & ex )
    {
        std::cerr << "An error occured while parsing the command line: " << ex.what() << '\n';
        std::cerr << usage << '\n' << options << std::endl;
        return EXIT_FAILURE;
    }
    

    // Check if options are valid

    if ( optionValues.count( "help" ) )
    {
        std::cout << usage << '\n' << options << std::endl;
        return EXIT_SUCCESS;
    }

    if ( ! optionValues.count( "input-file" ) )
    {
        std::cerr << "No input file." << std::endl;
        return EXIT_FAILURE;
    }


    // Open input file

    std::ifstream input( optionValues[ "input-file" ].as< std::string >().c_str(), std::ifstream::in );

    if ( ! input )
    {
        std::cerr << "A problem occured while opening the input file." << std::endl;
        return EXIT_FAILURE;
    }


    // Open output stream

    std::ostream  * output = & std::cout; // by default, output to console
    std::ofstream   outputFile;

    if ( optionValues.count( "output-file" ) )
    {
        outputFile.open( optionValues[ "output-file" ].as< std::string >().c_str() );

        if ( ! outputFile )
        {
            std::cerr << "A problem occured while opening the output file." << std::endl;
            return EXIT_FAILURE;
        }

        output = &outputFile;
    }
    

    // Convert input file to output stream

    BankStatement const statement = importStatement( std::istream_iterator< Line >( input ), std::istream_iterator< Line >() );

    try
    {
        exportStatement( 
            statement, 
            boost::format( optionValues[ "format" ].as< std::string >() ), 
            std::ostream_iterator< std::string >( *output, "\n" ) );
    }
    catch( boost::io::bad_format_string const & )
    {
        std::cerr << "The format specified is ill-formed." << std::endl;
        return EXIT_FAILURE;
    }
    catch( boost::io::too_few_args const & ex )
    {
        boost::format error( "The format specified contains too many placeholders. "
                             "There are only %1% elements in an operation while the format string contains %2% placeholders." );
        error % ex.get_cur() % ex.get_expected();

        std::cerr << error << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}