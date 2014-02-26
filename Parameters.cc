/*
 * (C) Copyright 2014 Enterome
 * 
 * This file is part of csfasta-fasta-conv.
 * 
 * csfasta-fasta-conv is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * csfasta-fasta-conv is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with csfasta-fasta-conv.  If not, see <http://www.gnu.org/licenses/>.
 */ 

#include "Parameters.hh"
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <iostream>
#include <stdexcept>

Parameters get_parameters(int argc, char* argv[])
{
	Parameters pars;
	
	// Create options decription
	po::options_description opts_desc("Convert csfasta file to fasta file and vice versa.");
		

	opts_desc.add_options()
		("help,h", "print this help message")
		("input-file,i", po::value<std::string>(&pars.input_file)->required(), "File to be converted (csfasta or fasta format)")
		("output-file,o", po::value<std::string>(&pars.output_file)->required(), "Converted file generated")
		;

	// Retrieve and parse command line parameters
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, opts_desc), vm);

	// Print help
	if (argc == 1 || vm.count("help"))
	{
		std::cout << opts_desc << std::endl;
		std::exit(0);
	}

	po::notify(vm);

	// Check input file
		if (!fs::exists(pars.input_file))
			throw (std::invalid_argument("error: " + pars.input_file +  " not found."));
			
		if (!fs::is_regular_file(pars.input_file))
			throw (std::invalid_argument("error: " + pars.input_file +  " is not a regular file."));

	return (pars);
}
