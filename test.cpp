#include "spreadsheet.hpp"

#include "gtest/gtest.h"
#include "select.hpp"
#include "select_and.hpp"
#include "select_or.hpp"
#include "select_contains.hpp"
#include "select_not.hpp"
#include <iostream>

TEST(SeletctNotTest, TestingSelectNot)
{
	Spreadsheet sheet;
	sheet.set_column_names({"First","Last","Age", "Major"});
	sheet.add_row({"Amanda","Andrews","22","business" });
	sheet.add_row({ "Brian","Becker","21","computer science" });
	sheet.add_row({ "Carol","Conners","21","computer science" });
	Select* tst = new Select_Not(new Select_Contains(&sheet, "Last", "m"));
	bool retVal = tst->select(&sheet, 0);
	EXPECT_EQ(retVal, true);

	delete tst;

	tst = new Select_Not(new Select_Contains(&sheet, "First", "Brian"));
	retVal = tst->select(&sheet, 1);
	EXPECT_EQ(retVal, false);

	delete tst;
}

TEST(SelectAndTest, TestingSelectAnd)
{
	
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
