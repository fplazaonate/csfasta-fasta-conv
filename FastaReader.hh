#ifndef FASTA_READER_HH
#define FASTA_READER_HH
 
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

#include <string>
#include <vector>
#include "BlockingQueue.hh"
#include "FastaRecord.hh"

class FastaReader
{
	private:
		static const unsigned DEFAULT_FASTA_BLOCK_SIZE;
		const std::string file_path_;
		BlockingQueue<std::vector<FastaRecord>*> fasta_blocks_queue_;
		const unsigned fasta_block_size_;
		void add_fasta_block(std::vector<FastaRecord>* block);
	public:
		FastaReader(const std::string& file_path, unsigned fasta_block_size = DEFAULT_FASTA_BLOCK_SIZE);
		void read_file();
		std::vector<FastaRecord>* get_fasta_block();
};

#endif // FASTA_READER_HH
