#include "spreadsheet.hpp"
#include "select_contains.hpp"
#include "gtest/gtest.h"
#include <sstream>
#include "select_and.hpp"
#include "select_not.hpp"
#include "select_or.hpp"
#include "select.hpp"


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
//Select Contains Tests

TEST(selectContainsTests, multipleNameTests){
	Spreadsheet sheet;
	std::stringstream ss;
	std::stringstream ss1;
	std::stringstream ss2;

	sheet.set_column_names({"First", "Last", "Age", "Major"});
	sheet.add_row({"Amanda", "Andrews", "22", "Business"});
	sheet.add_row({"Brian", "Jackson", "21", "Mathematics"});
	sheet.add_row({"Angel","Avila","20","Computer Science"});
	sheet.add_row({"Henry", "Lopez", "19", "Economics"});
	sheet.add_row({"Maria", "Martinez", "22", "Political Science"});
	sheet.add_row({"Angela", "Chu", "23", "Biochemistry"});

	sheet.set_selection(new Select_Contains(&sheet, "First", "Angel"));
	sheet.print_selection(ss);

	EXPECT_EQ("Angel\tAvila\t20\tComputer Science\t\nAngela\tChu\t23\tBiochemistry\t\n", ss.str());
	
	sheet.set_selection(new Select_Contains(&sheet, "Last", "ez"));
	sheet.print_selection(ss1);

	EXPECT_EQ("Henry\tLopez\t19\tEconomics\t\nMaria\tMartinez\t22\tPolitical Science\t\n", ss1.str());

	sheet.set_selection(new Select_Contains(&sheet, "Major", "Science"));
	sheet.print_selection(ss2);

	EXPECT_EQ("Angel\tAvila\t20\tComputer Science\t\nMaria\tMartinez\t22\tPolitical Science\t\n", ss2.str());
}

TEST(selectContainsTests, emptyString){
	Spreadsheet sheet;
	std::stringstream ss;
	
	sheet.set_column_names({"First", "Last", "Company", "Salary"});
	sheet.add_row({"Michael", "Scott", "Dunder Mifflin", "40k"});
	sheet.add_row({"Wendy", "Harrison", "Apple", "180k"});

	sheet.set_selection(new Select_Contains(&sheet, "Salary", ""));
	sheet.print_selection(ss);

	EXPECT_EQ("Michael\tScott\tDunder Mifflin\t40k\t\nWendy\tHarrison\tApple\t180k\t\n", ss.str());	
} 

TEST(selectContainsTests, wrongString){
	Spreadsheet sheet;
	std::stringstream ss;

	sheet.set_column_names({"Name", "Animal Type"});
	sheet.add_row({"Luna", "cat"});
	sheet.add_row({"Georgia", "German Shepherd Dog"});
	sheet.add_row({"Puggy", "French Bulldog"});
	
	sheet.set_selection(new Select_Contains(&sheet, "Animal Type", "dog"));
	sheet.print_selection(ss);
	
	EXPECT_EQ("Puggy\tFrench Bulldog\t\n", ss.str());

	std::stringstream ss1;
	sheet.set_selection(new Select_Contains(&sheet, "Animal Type", "Dog"));
	sheet.print_selection(ss1);

	EXPECT_EQ("Georgia\tGerman Shepherd Dog\t\n", ss1.str());
}

TEST(selectContainsTests, sameColumnName){
	Spreadsheet sheet;
	sheet.set_column_names({"Name", "Major", "Age"});

	ASSERT_EXIT(sheet.set_column_names({"Age"}), ::testing::ExitedWithCode(1), "Error: Column Already Exists");
}

TEST(selectContainsTests, selectNull){
	Spreadsheet sheet;
	std::stringstream ss;

	sheet.set_column_names({"Username", "Password"});
	sheet.add_row({"jroti55", "7771"});
	sheet.add_row({"mfarah25", "6963"});

	sheet.print_selection(ss);
	EXPECT_EQ("jroti55\t7771\t\nmfarah25\t6963\t\n", ss.str());
}

TEST(selectContainsTests, allCapsColumn){
	Spreadsheet sheet;
	std::stringstream ss;

	sheet.set_column_names({"Item", "Price"});
	sheet.add_row({"Apples", "$3.50"});

	EXPECT_EQ(sheet.get_column_by_name("ITEM"), -1);
}

//Select_And Tests
TEST(selectAndTest, test){
	Spreadsheet sheet;
	sheet.set_column_names({"First", "Last", "Age", "Major"});
	sheet.add_row({"Amanda", "Andrews","22","business"});
	sheet.add_row({"Brian", "Jackson", "21", "computer science"});
	sheet.add_row({"Carol", "Conners", "21", "computer science"});
	sheet.add_row({"Andrew", "Jackson", "20", "economics"});

	sheet.set_selection(new Select_And(new Select_Contains(&sheet, "Last", "Jackson"),new Select_Not(new Select_Contains(&sheet, "First", "d"))));

	std::stringstream ss;
	sheet.print_selection(ss);
	
	EXPECT_EQ("Brian\tJackson\t21\tcomputer science\t\n", ss.str());
}

TEST(SelectAndTest, TestingSelectAnd){
	Spreadsheet sheet;
	sheet.set_column_names({"First", "Last", "Age", "Major"});
	sheet.add_row({"Amanda", "Andrews", "22", "business"});
	sheet.add_row({"Brian", "Becker", "21", "computer science"});
	sheet.add_row({"Carol", "Conners", "23", "computer science"});

	Select* tst = new Select_And(new Select_Contains(&sheet, "Last", "er"), new Select_Contains(&sheet, "Age", "23"));;
	bool retVal = tst->select(&sheet, 2);
	EXPECT_EQ(retVal, true);
	delete tst;

	tst = new Select_And(new Select_Contains(&sheet, "Last", "m"), new Select_Contains(&sheet, "Major", "science"));
	retVal = tst->select(&sheet, 1);
	EXPECT_EQ(retVal, false);

	delete tst;
}

//Select_Not Tests
TEST(selectNotTest, notTest){
	Spreadsheet sheet;
	sheet.set_column_names({"Name", "Birthday"});
	sheet.add_row({"Raidah", "March 13, 2001"});
	sheet.add_row({"Ryan", "May 7, 2002"});
	sheet.add_row({"Amy", "March 13, 1998"});

	std::stringstream ss;
	sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "Birthday", "19")));
	sheet.print_selection(ss);

	EXPECT_EQ("Raidah\tMarch 13, 2001\t\nRyan\tMay 7, 2002\t\n", ss.str());
}

TEST(SelectNotTest, TestingSelectNot){
	Spreadsheet sheet;
	sheet.set_column_names({"First", "Last", "Age", "Major"});
	sheet.add_row({"Amanda", "Andrews", "22", "business"});
	sheet.add_row({"Brian", "Beckers", "21", "computer science"});
	sheet.add_row({"Carol", "Conners", "21", "computer science"});

	Select* tst = new Select_Not(new Select_Contains(&sheet, "Last", "m"));
	bool retVal = tst->select(&sheet, 0);
	EXPECT_EQ(retVal, true);

	delete tst;

	tst = new Select_Not(new Select_Contains(&sheet, "First", "Brian"));
	retVal = tst->select(&sheet, 1);
	EXPECT_EQ(retVal, false);

	delete tst;
}


//Select_Or Tests
TEST(selectOrTest, orTest){
	Spreadsheet sheet;
	std::stringstream ss;

	sheet.set_column_names({"Username", "PIN"});
	sheet.add_row({"rgere11", "9988"});
	sheet.add_row({"mgerald12", "4467"});
	sheet.add_row({"bjane", "5126"});
	sheet.add_row({"zkavv","9991"});
	sheet.add_row({"ghade", "1342"});

	sheet.set_selection(new Select_Or(
				new Select_Contains(&sheet, "Username", "ger"),
				new Select_Or(new Select_Contains(&sheet, "Username", "v"), new Select_Contains(&sheet, "PIN", "3"))));

	sheet.print_selection(ss);
	
	EXPECT_EQ("rgere11\t9988\t\nmgerald12\t4467\t\nzkavv\t9991\t\nghade\t1342\t\n", ss.str());
}

TEST(selectOrTest, TestingSelectOr){
	Spreadsheet sheet;
	sheet.set_column_names({"Username", "PIN"});
	sheet.add_row({"rgere11", "9988"});
	sheet.add_row({"aavil053", "4477"});
	sheet.add_row({"zkavv", "9991"});
	sheet.add_row({"ghade", "1342"});

	Select* tst = new Select_Or(new Select_Contains(&sheet, "Username", "vil"), new Select_Contains(&sheet, "PIN", "7"));
	bool retVal = tst->select(&sheet, 1);
	EXPECT_EQ(retVal, true);

	delete tst;

	tst = new Select_Or(new Select_Contains(&sheet, "Username", "x"), new Select_Contains(&sheet, "PIN", "6"));
	retVal = tst->select(&sheet, 1);
	EXPECT_EQ(retVal, false);

	delete tst;
}
