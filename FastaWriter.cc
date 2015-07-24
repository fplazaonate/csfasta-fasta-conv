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

#include "FastaWriter.hh"
#include <fstream>

FastaWriter::FastaWriter(const std::string& file_path)
: file_path_(file_path), fasta_blocks_queue_(2)
{};

void FastaWriter::add_fasta_block(std::vector<FastaRecord>* fasta_block)
{
	fasta_blocks_queue_.enqueue(fasta_block);
};


void FastaWriter::write_file()
{
	std::ofstream ofs;
	ofs.open(file_path_);

	std::vector<FastaRecord>* new_fasta_block = fasta_blocks_queue_.dequeue();
	while(new_fasta_block != nullptr)
	{
		for (const FastaRecord& fr: *new_fasta_block)
			ofs << fr;

		delete new_fasta_block;
		new_fasta_block = fasta_blocks_queue_.dequeue();
	}

	ofs.close();
}


