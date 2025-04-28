#include "LoginChecker.h"
#include <iostream>

bool IsEmailValid(std::string address) {
	std::regex pattern("^[a-zA-Z0-9_.±]+@[a-zA-Z0-9-]+.[a-zA-Z0-9-.]+$");
	return std::regex_match(address, pattern);
}

bool IsPasswordValid(std::string p1, std::string p2) {
	bool isMatching = p1 == p2;
	std::string password = p1;
	bool hasLowerCase = false;
	for (char c : password) {
		hasLowerCase |= islower(c);
		std::cout << c;
	}
	bool hasUpperCase = false;
	for (char c : password) {
		hasUpperCase |= isupper(c);
	}
	bool hasNumber = false;
	for (char c : password) {
		hasNumber |= isdigit(c);
	}
	bool isLongEnough = password.size() >= 8;
	return hasLowerCase && hasUpperCase && hasNumber && isLongEnough && isMatching;
}