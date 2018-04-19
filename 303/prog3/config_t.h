// CSE 303 Assignment #2
// Spring 2018
//
// Description: This file declares a struct for storing per-execution
// configuration information.

#include <iostream>
#include <string>

// store all of our command-line configuration parameters

struct config_t {

	int numaccounts;

  // The maximum key value
    int key_max;

    // The number of iterations for which a test should run
    int iters;

    // A string that is output with all the other information
    std::string  name;

    // simple constructor
    config_t() : key_max(256), iters(10), name("no_name") { }

    // Print the values of the seed, iters, and name fields
    void dump();
};
