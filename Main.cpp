#include <iostream>
#include "Logging.h"
#include "String.h"
#include <string> // shhhhh, Only used for std::to_string, I don't want to figure out converting between int and string

bool runTest(String FunctionDefinition, size_t ExpectedSize, String PreString, String PostString)
{
	// Create the log output
	String test = String();
	test += FunctionDefinition + ", Expected: " + std::to_string(ExpectedSize).c_str()
		+ ", Recieved: " + std::to_string(sizeof(char) * PostString.Length()).c_str()
		+ ", Test " + ((sizeof(char) * PostString.Length() == ExpectedSize) ? "passed" : "failed");
	
	// Check if it's passed and push it to the logger singleton
	bool passed = (sizeof(char) * PostString.Length() == ExpectedSize);
	if (passed)
		logger.addLog(test, LOG_LEVEL_INFO);
	else
		logger.addLog(test, LOG_LEVEL_ERROR);

	return passed; // Return if the test passed or not
}

int main()
{
	bool AllTests = true;

	// Test Append
	String PreString = "Hello World!";
	String PostString = String(PreString);
	PostString.Append(" Goodbye World.");
	if (!runTest("Append", sizeof(char) * PreString.Length() + 15, PreString, PostString))
		AllTests = false;

	// Test Preppend
	PreString = "Hello World!";
	PostString = String(PreString);
	PostString.Prepend("*crawls out of sewer* ");
	if (!runTest("Prepend", sizeof(char) * PreString.Length() + 22, PreString, PostString))
		AllTests = false;

	// Test Insert
	PreString = "Hello World!";
	PostString = String(PreString);
	PostString.Insert(6, "Cruel ");
	if (!runTest("Insert", sizeof(char) * PreString.Length() + 6, PreString, PostString))
		AllTests = false;

	// Test Remove
	PreString = "Hello World!";
	PostString = String(PreString);
	PostString.Remove(5, 6);
	if (!runTest("Remove", sizeof(char) * PreString.Length() - 6, PreString, PostString))
		AllTests = false;

	// Test Replace
	PreString = "Hello World!";
	PostString = String(PreString);
	PostString.Replace("Hello", "Goodbye");
	if (!runTest("Replace", sizeof(char) * PreString.Length() + 2, PreString, PostString))
		AllTests = false;

	// Test Replace All
	PreString = "Hello World! Hello You! Hello ALL!!";
	PostString = String(PreString);
	PostString.ReplaceAll("Hello", "Goodbye");
	if (!runTest("Replace All", sizeof(char) * PreString.Length() + 6, PreString, PostString))
		AllTests = false;

	// Test Substring
	PreString = "Hello World! Frogs am I right?";
	PostString = PreString.Substring(13, 8);
	if (!runTest("Substring", 8, PreString, PostString))
		AllTests = false;

	// Test To Lower
	PreString = "Hello World! Hello You! Hello ALL!!";
	PostString = String(PreString);
	PostString.ToLower();
	if (!runTest("ToLower", sizeof(char) * PreString.Length(), PreString, PostString))
		AllTests = false;

	// Test To Upper
	PreString = "Hello World! Hello You! Hello ALL!!";
	PostString = String(PreString);
	PostString.ToUpper();
	if (!runTest("ToUpper", sizeof(char) * PreString.Length(), PreString, PostString))
		AllTests = false;

	// Output test status
	if (AllTests)
		logger.addLog("\n --------> Passed All Tests! <--------\n", LOG_LEVEL_INFO);
	else
		logger.addLog("\n --------> Failed A Test. <--------\n", LOG_LEVEL_ERROR);

	logger.saveLog("TestLog.txt");

	return 0;
}