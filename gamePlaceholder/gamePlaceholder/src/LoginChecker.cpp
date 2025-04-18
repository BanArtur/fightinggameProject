#include "LoginChecker.h"

bool IsEmailValid(std::string address) {
	std::regex pattern("^[a-zA-Z0-9_.±]+@[a-zA-Z0-9-]+.[a-zA-Z0-9-.]+$");
	return std::regex_match(address, pattern);
}

bool IsPasswordValid(std::string password, std::string passwordAgain) {
	bool isMatching = password == passwordAgain;
	std::regex pattern("^(?=.*\d)(?=.*[A-Z])(?=.*[a-zA-Z]).{8,}$");
	return isMatching && std::regex_match(password, pattern);
}