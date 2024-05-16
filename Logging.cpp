#include "Logging.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>

Logger::Logger()
{
	m_Log = String();
}

void Logger::addLog(String text, int level)
{
	String line = String();

	// Get the current date and time
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	// Add the warning to the beginning
	switch (level)
	{
	case LOG_LEVEL_INFO:
		line.Append("[INFO");
		break;
	case LOG_LEVEL_WARNING:
		line.Append("[WARNING");
		break;
	case LOG_LEVEL_ERROR:
		line.Append("[ERROR!");
		break;
	}
	
	// Turn the time into a string
	String time = String(std::ctime(&now));
	time.Remove(time.Length() - 1, 1); // Remove the random \n at the end of std::ctime

	// Add the time and the actual text
	line.Append(" @ " + time + "] " + text);

	// Output to console
	std::cout << line << "\n";

	// Add it to the combined log
	m_Log.Append(line + "\n");
}

void Logger::outputLog()
{
	// Output the combined log to the console
	std::cout << m_Log << "\n";
}

void Logger::saveLog(String location)
{
	std::ofstream out(location.CStr());
	out << m_Log;
	out.close();
}

void Logger::clearLog()
{
	// Clear the combined log
	m_Log = String();
}

Logger logger = Logger(); // Initialise the Singleton, might not be necesary