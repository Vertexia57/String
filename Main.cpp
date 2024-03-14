#include <iostream>
#include "String.h"

bool runTest(String FunctionDefinition, size_t ExpectedSize, String PreString, String PostString)
{
	std::cout << "\n >--TEST----------------< \n";
	std::cout << "  - Function Ran    : " << FunctionDefinition.CStr() << "\n";
	std::cout << "  - Expected Size   : " << ExpectedSize << "\n\n";
	std::cout << "  + Starting String : " << PreString.CStr() << " \n";
	std::cout << "  | + Start Size    : " << sizeof(char) * PreString.Length() << " \n";
	std::cout << "  + Ending String   : " << PostString.CStr() << " \n";
	std::cout << "  | + End Size      : " << sizeof(char) * PostString.Length() << " \n";
	std::cout << " >--" << ((sizeof(char) * PostString.Length() == ExpectedSize) ? "PASSED" : "FAILED") << "--------------< \n\n";
	system("pause");
	return (sizeof(char) * PostString.Length() == ExpectedSize);
}

int main()
{
	bool AllTests = true;

	String PreString = "Hello World!";
	String PostString = String(PreString);
	PostString.Append(" Goodbye World.");
	if (!runTest("Append", sizeof(char) * PreString.Length() + 15, PreString, PostString))
		AllTests = false;

	PreString = "Hello World!";
	PostString = String(PreString);
	PostString.Prepend("*crawls out of sewer* ");
	if (!runTest("Prepend", sizeof(char) * PreString.Length() + 22, PreString, PostString))
		AllTests = false;

	PreString = "Hello World!";
	PostString = String(PreString);
	PostString.Insert(6, "Cruel ");
	if (!runTest("Insert", sizeof(char) * PreString.Length() + 6, PreString, PostString))
		AllTests = false;

	PreString = "Hello World!";
	PostString = String(PreString);
	PostString.Remove(5, 6);
	if (!runTest("Remove", sizeof(char) * PreString.Length() - 6, PreString, PostString))
		AllTests = false;

	PreString = "Hello World!";
	PostString = String(PreString);
	PostString.Replace("Hello", "Goodbye");
	if (!runTest("Replace", sizeof(char) * PreString.Length() + 2, PreString, PostString))
		AllTests = false;

	PreString = "Hello World! Hello You! Hello ALL!!";
	PostString = String(PreString);
	PostString.ReplaceAll("Hello", "Goodbye");
	if (!runTest("Replace All", sizeof(char) * PreString.Length() + 6, PreString, PostString))
		AllTests = false;

	PreString = "Hello World! Frogs am I right?";
	PostString = PreString.Substring(13, 8);
	if (!runTest("Substring", 8, PreString, PostString))
		AllTests = false;

	PreString = "Hello World! Hello You! Hello ALL!!";
	PostString = String(PreString);
	PostString.ToLower();
	if (!runTest("ToLower", sizeof(char) * PreString.Length(), PreString, PostString))
		AllTests = false;

	PreString = "Hello World! Hello You! Hello ALL!!";
	PostString = String(PreString);
	PostString.ToUpper();
	if (!runTest("ToUpper", sizeof(char) * PreString.Length(), PreString, PostString))
		AllTests = false;

	if (AllTests)
		std::cout << "\n --------> Passed All Tests! <--------\n";
	else
		std::cout << "\n --------> Failed A Test. <--------\n";

	return 0;
}