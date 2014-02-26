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

#include "FastaRecord.hh"

std::ostream& operator<<(std::ostream& os, const FastaRecord& fr)
{
	os << fr.header << '\n';
	os << fr.sequence << '\n';

	return os;
}

std::istream& operator>>(std::istream& is, FastaRecord& fr )
{
	std::getline(is, fr.header);
	std::getline(is, fr.sequence);

	return is;
}
