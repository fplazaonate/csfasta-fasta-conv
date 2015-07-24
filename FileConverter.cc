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

#include "FileConverter.hh"
#include "ConversionTables.hh"
#include <stdexcept>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

void CsFastaToFasta::convert(std::vector<FastaRecord>* records)
{
	// Nothing to do
	if (records == nullptr)
		return;

	// Analysis of each fasta record
	for (FastaRecord& record: *records)
	{
		// Convert sequence to a list of numbers representing nucleotides
		std::string& sequence = record.sequence;

		std::uint8_t previous_base = 
			ConversionTables::ascii_to_dna[(unsigned)sequence[0]];

		for (unsigned j = 1; j < sequence.size() ; j++)
		{
			std::uint8_t current_color = 
				ConversionTables::ascii_to_cs[(unsigned)sequence[j]];
			std::uint8_t current_base = 
				ConversionTables::cs_to_dna[previous_base][current_color];
			sequence[j-1] =  
				ConversionTables::dna_to_ascii[current_base];
			previous_base = current_base;
		}
		sequence.resize(sequence.size()-1);
	}
}

void FastaToCsFasta::convert(std::vector<FastaRecord>* records)
{
	// Nothing to do
	if (records == nullptr)
		return;

	// Analysis of each fasta record
	for (FastaRecord& record: *records)
	{
		// Convert sequence to a list of colors
		std::string& sequence = record.sequence;

		std::uint8_t previous_base = 
			ConversionTables::ascii_to_dna[(unsigned)sequence[0]];

		for (unsigned j = 1; j < sequence.size() ; j++)
		{
			std::uint8_t current_base = 
				ConversionTables::ascii_to_dna[(unsigned)sequence[j]];
			const std::uint8_t current_color = 
				ConversionTables::cs_to_dna[previous_base][current_base];
			sequence[j] =  
				ConversionTables::cs_to_ascii[current_color];
			previous_base = current_base;
		}
	}
}

std::unique_ptr<FileConverter> FileConverterFactory::create_converter(const std::string& file_path)
{
	std::string file_extension = 
		fs::extension(file_path);
	std::transform(file_extension.begin(), file_extension.end(), file_extension.begin(), ::tolower);

	if (std::find(FASTA_EXTENSIONS.begin(), FASTA_EXTENSIONS.end(), file_extension) != 
			FASTA_EXTENSIONS.end())
	{
		return std::unique_ptr<FileConverter>(new FastaToCsFasta());
	}
	else if (std::find(CSFASTA_EXTENSIONS.begin(), CSFASTA_EXTENSIONS.end(), file_extension) !=
			CSFASTA_EXTENSIONS.end())
	{
		return std::unique_ptr<FileConverter>(new CsFastaToFasta());
	}
	else
	{
		throw (std::invalid_argument("error: " +  file_extension+  " is a unknown file extension."));
	}

}

const std::vector<std::string> FileConverterFactory::FASTA_EXTENSIONS =
{".fasta", ".fa", "fna"};

const std::vector<std::string> FileConverterFactory::CSFASTA_EXTENSIONS = 
{".csfasta"};
