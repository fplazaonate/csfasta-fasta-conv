#ifndef CONVERSION_TABLES_HH
#define CONVERSION_TABLES_HH
 
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

#include <cstdint>

class ConversionTables
{
	public:
		static const std::uint8_t ascii_to_cs[128];
		static const char cs_to_ascii[5];
		static const std::uint8_t ascii_to_dna[128];
		static const char dna_to_ascii[5];
		static const std::uint8_t cs_to_dna[5][5];
};

#endif // CONVERSION_TABLES_HH
