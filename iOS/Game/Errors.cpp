#include "headers\Errors.h"

// suggested error naming scheme:
// error xy, where x is category, and y is error number
// analogous to errors xyy in HTML (for example, 404, where x = 4 and yy == 04). See https://www.w3.org/Protocols/HTTP/HTRESP.html

// more errors to be added as needed

// usage in program: to throw an error, write
// complain(ErrNo::<errortype>);
// this makes the window invisible
// the error will be caught on next game_loop, and execution halted

int error::trace_error(int code) {
	switch (code)
	{
	case 10:
		error::corrupt_profile();
		break;
	case 42:
		error::file_access();
		break;
	case 404:
		error::profile_not_found();
		break;
	case 101:
		error::capture_screen_error();
		break;
	default:
		break;
	}
	std::cin.get(); // get user's attention
	return code;
}

void error::corrupt_profile()
{
	std::cerr << "The user profile is corrupt!";
}

void error::file_access()
{
	std::cerr << "File access error!";
}

void error::profile_not_found()
{
	std::cerr << "Profile not found!";
}

void error::too_many_iterations()
{
	std::cerr << "Either that loop is too long, or you're REALLY unlucky!";
}

void error::capture_screen_error()
{
	std::cerr << "Error with print screen!";
}


logger_file::logger_file()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	file_name = "logs/log_";
	file_name += (st.wDay >= 10) ? std::to_string(st.wDay) : "0" + std::to_string(st.wDay);
	file_name += "-";
	file_name += (st.wMonth >= 10) ? std::to_string(st.wMonth) : "0" + std::to_string(st.wMonth);
	file_name += "-";
	file_name += std::to_string(st.wYear);
	file_name += ".txt";
	
	file.open(file_name, std::ios::in);

	if (file.is_open()) {
		file.close();
		file.open(file_name, std::ios::app | std::ios::out);
		file << "\n";
		
		// ASCII art:
		file << "                                              __\n";
		file << "     ,                                      ,\" e`- - o\n";
		file << "    ((                                     (  | __,'\n";
		file << "     \\~----------------------------------' \\_;/\n";
		file << "     (     Elvis Borges & Jo�o Ferreira       /\n";
		file << "     /) ._________________________________.  )\n";
		file << "    (( (                                  (( (\n";
		file << "     ``-'                                  ``-'\n";

		
		file << "\n\n";
	}
	else {
		file.close();
		file.open(file_name, std::ios::app | std::ios::out);
	}
}

logger_file::logger_file(std::string filename)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	file_name = "logs/" + filename + "_";
	file_name += (st.wDay >= 10) ? std::to_string(st.wDay) : "0" + std::to_string(st.wDay);
	file_name += "-";
	file_name += (st.wMonth >= 10) ? std::to_string(st.wMonth) : "0" + std::to_string(st.wMonth);
	file_name += "-";
	file_name += std::to_string(st.wYear);
	file_name += ".txt";

	file.open(file_name, std::ios::in);

	if (file.is_open()) {
		file.close();
		file.open(file_name, std::ios::app | std::ios::out);
		file << "\n-------------------------------------\n";
	}
	else {
		file.close();
		file.open(file_name, std::ios::app | std::ios::out);
	}
}

logger_file::~logger_file()
{
	file.close();
}

void logger_file::log(std::string str)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	std::string partial;

	partial = (st.wHour >= 10) ? std::to_string(st.wHour) : ("0" + std::to_string(st.wHour));
	file << partial;
	file << ":";
	
	partial = (st.wMinute >= 10) ? std::to_string(st.wMinute) : ("0" + std::to_string(st.wMinute));
	file << partial;
	file << ":";
	
	partial = (st.wSecond >= 10) ? std::to_string(st.wSecond) : ("0" + std::to_string(st.wSecond));
	file << partial;
	file << " - ";
	file << str.c_str() << "." << std::endl;
}

namespace LOGGER {
	logger_file * l = new logger_file;

	void log(std::string str) {
		return l->log(str);
	}
};
