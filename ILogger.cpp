//
//  ILogger.cpp
//  logger
//
//  Created by Francesco Ferrara on 20.11.11.
//  Copyright 2011 ETH Zürich. All rights reserved.
//

#include "ILogger.hpp"


// Standard constructor
ILogger::ILogger(){}

// Copy constructor
ILogger::ILogger( const ILogger & ilogger )
{
    // File name
	iname = ilogger.iname;
    
    // List
	ilist = ilogger.ilist;
    
    // Number of columns
	icols = ilogger.icols;
}

// Constructor with file name ( for either input or output )
ILogger::ILogger( const char * ifile_name )
{
    // Set the file name
    iname = string( ifile_name );
    
    cout << "\niname: " << iname << endl;
}

// Standard destructor
ILogger::~ILogger(){}

// Get data line
vector< double > ILogger::get_line( int line )
{
	// List iterator
    list< vector< double > >::iterator line_it = ilist.begin();
    
    // Advance the iterator
    for ( int i = 0; i < line; i++ )
    {
        line_it++;
    }
    
    return *line_it;
}

// Operator =
ILogger & ILogger::operator=( const ILogger & ilogger )
{    
    // File name
	iname = ilogger.iname;
    
    // List
	ilist = ilogger.ilist;
    
    // Number of columns
	icols = ilogger.icols;
    
	return *this;
}

// Operator ()
double ILogger::operator()( int i, \
                            int j )
{
	// Check if the indices are negative
	if ( ( i < 0 ) || ( j < 0 ) )
	{
		cout << "\nNeither i nor j are allowed to be negative!\n";
		abort();
	}
    
	// Line vector
	vector< double > line;
    
	if ( i < ( int )ilist.size() )
    {
        if ( j < icols )
        {
            // Get the line
            line = get_line( i );
        }
        else
        {
            cout << "\nj > num_data_cols - 1!\n";
            abort();
        }
    }
    else
    {
        cout << "\ni > num_data_rows - 1!\n";
        abort();
    }
    
    return line.at( j );
}

// Get the size of a list
size_l ILogger::get_isize()
{
    // Temporary variable
    size_l size;
    
    // Get the rows
    size.rows = ( int )ilist.size();
    
    // Get the columns
    list< vector< double > >::iterator i = ilist.begin();
    size.cols = ( int )i->size();
    
    return size;
}

// Open a file
bool ILogger::open_file()
{
	// Close the file
    close_file();
    
    // Open the file
    ifile.open( iname.c_str(), ios_base::in );
    
    // Return the value of the check if it is open
    return ifile.is_open();
}

// Close a file
void ILogger::close_file()
{
	// If the file is already open
    if ( ifile.is_open() )
    {
        // Clear the error flags
        ifile.clear( ios_base::goodbit );
        
        // Close the file
        ifile.close();
    }
}

// Get the number of data columns
int ILogger::get_cols()
{
	// Initialize columns
	int cols = 0;
    
	// Initialize temporary variable
	char character;
    
	// Read the first character
	ifile.get( character );
    
#if debug__read_log
	cout << "\nhead_line:\n" << character;
#endif
    
	while ( character != '\n' )
	{
		// Get the character
		ifile.get( character );
        
#if debug__read_log
		cout << character;
#endif
        
		// Compare the character with a space character
		if ( character == ' ' )
		{
			cols = cols + 1;
		}
	}
    
	return cols + 1;
}

// Fill the list
void ILogger::fill_list()
{
	// Temporary variables
	double value;
	vector< double > line;
    
	// While the end of file is not reached
	while ( !ifile.eof() )
	{
		// Fill a line
		for ( int i = 0; i < icols; i++ )
		{
			ifile >> value;
			line.push_back( value );
		}
		// Push the line into the list
		ilist.push_back( line );
        
		// Clear the line
		line.clear();
	}
}

// Read a log file
bool ILogger::read_log()
{
	// Open the file
	bool check = open_file();
    
	// Clear the input list
	ilist.clear();
    
	// Check if the file is open
	if ( check == true )
	{
		// Get the number of columns and discard the title line
		icols = get_cols();
        
#if debug__read_log
		cout << "\ncols = " << icols << endl;
#endif
        
		// Fill the list
		fill_list();
	}
	else
	{
		cout << "\ninput_file is not open!\n";
		abort();
	}
	// Close the file
	close_file();
    
	return check;
}

// Get the input list
int ILogger::get_ilist( list< vector< double > > & ilist )
{
	ilist = this->ilist;
    
	return icols;
}
