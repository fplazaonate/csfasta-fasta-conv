/*
 * (C) Copyright 2014-2015 Enterome
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
#include "FileConverter.hh"
#include "FastaReader.hh"
#include "FastaWriter.hh"
#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
	try
	{
		const Parameters& pars = get_parameters(argc, argv);

		std::unique_ptr<FileConverter> file_converter = FileConverterFactory::create_converter(pars.input_file);
		FastaReader fasta_reader(pars.input_file);
		FastaWriter fasta_writer(pars.output_file);

		std::thread producer(&FastaReader::read_file, std::ref(fasta_reader));
		std::thread consumer(&FastaWriter::write_file, std::ref(fasta_writer));

		std::vector<FastaRecord>* fasta_block;
		// Read next block from input file until eof
		do
		{
			fasta_block = fasta_reader.get_fasta_block();
			// Convert block to desired format
			file_converter->convert(fasta_block);
			// Write it to the output file
			fasta_writer.add_fasta_block(fasta_block);

		} while(fasta_block != nullptr);

		producer.join();
		consumer.join();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}


	return 0;
}
