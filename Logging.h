#pragma once
#include "String.h"

// Log Level Enum: [Info, Warning, Error]
enum
{
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR
};

class Logger
{
public:
	Logger();

	// Adds the text to the log, and outputs the text to the console, with a prepended level
	void addLog(String text, int level);

	// Outputs the log to the console
	void outputLog();

	// Saves the log to a file
	void saveLog(String location);

	// Clears the log, removing all text in it
	void clearLog();

	// Returns a the log as a const reference
	inline const String& getLog() { return m_Log; };

private:
	String m_Log;
};

extern Logger logger; // Logger Singleton

