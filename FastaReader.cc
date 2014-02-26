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

#include "FastaReader.hh"
#include <fstream>
#include <iterator>

const unsigned FastaReader::DEFAULT_FASTA_BLOCK_SIZE = 100000;

FastaReader::FastaReader(const std::string& file_path, unsigned fasta_block_size)
: file_path_(file_path), fasta_blocks_queue_(1), fasta_block_size_(fasta_block_size)
{};


void FastaReader::add_fasta_block(std::vector<FastaRecord>* block)
{
	fasta_blocks_queue_.enqueue(block);
}

std::vector<FastaRecord>* FastaReader::get_fasta_block()
{
	return fasta_blocks_queue_.dequeue();
}

void FastaReader::read_file()
{
	std::ifstream ifs;
	ifs.open(file_path_);

	std::istream_iterator<FastaRecord> eos;
	std::istream_iterator<FastaRecord> iit (ifs); 


	while(iit != eos)
	{
		std::vector<FastaRecord>* new_fasta_block = new std::vector<FastaRecord>();

		do
		{
			(*new_fasta_block).push_back(*iit);
			iit++;
		} while(iit != eos && new_fasta_block->size() < fasta_block_size_);

		// fasta block is added to the queue because it is full or eof is reached
		add_fasta_block(new_fasta_block);
	}


	add_fasta_block(nullptr);
}
