//
//  ILogger.hpp
//  logger_
//
//  Created by Francesco Ferrara on 20.11.11.
//  Copyright 2011 ETH Zürich. All rights reserved.
//

#ifndef logger_ILogger_hpp
#define logger_ILogger_hpp


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <vector>
#include <string>


using namespace std;


#define debug__read_log 0


// Define a data type for the size of a list
typedef struct
{
    int rows, cols;
}size_l;

class ILogger
{    
	// Input stream
	ifstream ifile;
    
    // File name
    string iname;
    
    // List
	list< vector< double > > ilist;
    
    // Number of columns
	int icols;
    
    // Size of the list
    size_l isize;
    
	// Get data line
	vector< double > get_line( int line );
    
	// Open a file
	bool open_file();
    
	// Close a file
	void close_file();
    
	// Get the number of data columns
	int get_cols();
    
	// Fill the list
	void fill_list();
    
public:    
	// Standard constructor
	ILogger();
    
	// Copy constructor
	ILogger( const ILogger & ilogger );
    
	// Constructor with file name
	ILogger( const char * ifile_name );
    
	// Standard destructor
	~ILogger();
    
	// Operator =
	ILogger & operator=( const ILogger & ilogger );
    
	// Operator ()
	double operator()( int i, \
                       int j );
    
    // Get the size of a list
    size_l get_isize();
    
	// Read a log file
	bool read_log();
    
	// Get the list
	int get_ilist( list< vector< double > > & ilist );
};


#endif
