#ifndef __SELECT_NOT_HPP__
#define __SELECT_NOT_HPP__

class Select_Not : public Select
{
private:
	Select* val;
public:
	Select_Not(Select* v)
	{
		this->val = v;
	}
	
	~Select_Not()
	{
		delete this->val;
	}

	bool select(const Spreadsheet* sheet, int row) const
	{
		if (this->val->select(sheet, row))
		{
			return false;
		}
		else 
			return true;
	}
};

#endif
