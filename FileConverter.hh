#ifndef FILE_CONVERTER_HH
#define FILE_CONVERTER_HH
 
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

#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include "FastaRecord.hh"

class FileConverter
{
	public:
		virtual void convert(std::vector<FastaRecord>* records) = 0;
		virtual ~FileConverter(){};
};

class CsFastaToFasta : public FileConverter
{
	public:
		virtual void convert(std::vector<FastaRecord>* records);
};

class FastaToCsFasta : public FileConverter
{
	public:
		virtual void convert(std::vector<FastaRecord>* records);
};

class FileConverterFactory
{
	public:
	   	static std::unique_ptr<FileConverter> create_converter(const std::string& file_path);
	private:
		static const std::vector<std::string> FASTA_EXTENSIONS;
		static const std::vector<std::string> CSFASTA_EXTENSIONS;
};

#endif // FILE_CONVERTER_HH
