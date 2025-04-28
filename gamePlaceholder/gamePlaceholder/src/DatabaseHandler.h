#pragma once
#include <firebase/app.h>
#include <firebase/firestore.h>

struct UserInfo {
	std::string UserName = "";
	int ratingScore = 0;
};

class DatabaseHandler {
private:
	firebase::firestore::Firestore* database;
	firebase::firestore::CollectionReference userdataReference;
public:
	DatabaseHandler(firebase::App*);
	~DatabaseHandler();

	void CreateNewUserData(std::string, UserInfo);
	int UpdateUserRanking(std::string, int, bool);

	UserInfo GetUserInfo(std::string);
};