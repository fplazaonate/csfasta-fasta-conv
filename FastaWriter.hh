#ifndef FASTA_WRITER_HH
#define FASTA_WRITER_HH
 
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
#include "FastaRecord.hh"
#include "BlockingQueue.hh"

class FastaWriter
{
	private:
		std::string file_path_;
		BlockingQueue<std::vector<FastaRecord>*> fasta_blocks_queue_;

	public:
		FastaWriter(const std::string& file_path);
		void add_fasta_block(std::vector<FastaRecord>* fasta_block);
		void write_file();
};



#endif // FASTA_WRITER_HH
