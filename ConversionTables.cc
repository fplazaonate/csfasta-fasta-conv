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

#include "ConversionTables.hh"

const std::uint8_t ConversionTables::ascii_to_cs[128] =
{
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,0,1,
	2,3,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4
};

const std::uint8_t ConversionTables::ascii_to_dna[128] =
{
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,0,4,1,4,4,
	4,2,4,4,4,4,4,4,4,4,
	4,4,4,4,3,4,4,4,4,4,
	4,4,4,4,4,4,4,0,4,1,
	4,4,4,2,4,4,4,4,4,4,
	4,4,4,4,4,4,3,4,4,4,
	4,4,4,4,4,4,4,4
};


const char ConversionTables::cs_to_ascii[5] =
{
	'0','1','2','3','.'
};

const char ConversionTables::dna_to_ascii[5] =
{
	'A','C','G','T','N'
};

const std::uint8_t ConversionTables::cs_to_dna[5][5] =
{
	{0,1,2,3,4},
	{1,0,3,2,4},
	{2,3,0,1,4},
	{3,2,1,0,4},
	{4,4,4,4,4}
};

