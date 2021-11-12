#ifndef __SELECT_OR_HPP__
#define __SELECT_OR_HPP__

#include "select.hpp"

class Select_Or : public Select
{
private:
	Select* val1;
	Select* val2;
public:
	Select_Or(Select* v1, Select* v2)
	{
		this->val1 = v1;
		this->val2 = v2;
	}

	~Select_Or()
	{
		delete this->val1;
		delete this->val2;
	}

	bool select(const Spreadsheet* sheet, int row) const
	{
		return this->val1->select(sheet, row) || this->val2->select(sheet, row);
	}
};

#endif //__SELECT_OR_HPP__
