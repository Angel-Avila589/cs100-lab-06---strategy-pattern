#include "spreadsheet.hpp"
#include "select.hpp"

#include <algorithm>
#include <iostream>

Spreadsheet::~Spreadsheet()
{
    this->clear();
}

void Spreadsheet::set_selection(Select* new_select)
{
    delete select;
    select = new_select;
}

void Spreadsheet::print_selection(std::ostream& out) const
{

    if(this->select == nullptr)
    {
	for(unsigned int row = 0; row < data.size(); row++)
	{
		for(unsigned int col = 0; col < data.at(row).size(); col++)
		{
			out << cell_data(row, col) << "\t";
		}
		out << "\n";
	}
    }
    
    else
    {
	for(unsigned int row = 0; row < data.size(); row++)
	{
		for(unsigned int col = 0; col < data.at(row).size(); col++)
		{
			if(this->select->select(this, row))
			{
				out << cell_data(row, col) << "\t";
			}
		}
		if(this->select->select(this,row))
			out << "\n";
	}
    }

}

void Spreadsheet::clear()
{
    column_names.clear();
    data.clear();
    delete select;
    select = nullptr;
}

void Spreadsheet::set_column_names(const std::vector<std::string>& names)
{
    for(unsigned int i = 0; i < column_names.size(); i++){
		for (unsigned int j = 0; j < names.size(); j++){	
			if(names.at(j) == column_names.at(i)){
			std::cerr << "Error: Column Already Exists" << std::endl;
			exit(1);
		}
 	}
    }
	column_names = names;
}

void Spreadsheet::add_row(const std::vector<std::string>& row_data)
{
    data.push_back(row_data);
}

int Spreadsheet::get_column_by_name(const std::string& name) const
{
    for(int i=0; i<column_names.size(); i++)
        if(column_names.at(i) == name)
            return i;
    return -1;
}
