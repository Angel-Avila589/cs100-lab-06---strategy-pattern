#ifndef __SELECT_CONTAINS_HPP__
#define __SELECT_CONTAINS_HPP__

#include "select.hpp"

class Select_Contains : public Select_Column
{
private:
	std::string val;

public:
	Select_Contains(Spreadsheet* sheet, std::string col, std::string name) : Select_Column(sheet, col)
	{
		this->val = name;
	}

	~Select_Contains()
	{
	}

	bool select(const Spreadsheet* sheet, int row) const
	{
		return select(sheet->cell_data(row, this->column));
	}

	bool select(const std::string& s) const
	{
		if (s.find(this->val) != std::string::npos)
			return true;
		else
			return false;
	}
};

#endif //__SELECT_CONTAINS_HPP__
