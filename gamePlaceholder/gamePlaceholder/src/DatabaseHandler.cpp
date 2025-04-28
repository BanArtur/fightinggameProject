#include "DatabaseHandler.h"
#include <iostream>

DatabaseHandler::DatabaseHandler(firebase::App* app_p) {
	database = firebase::firestore::Firestore::GetInstance(app_p);
	userdataReference = database->Collection("/UserData");
}

DatabaseHandler::~DatabaseHandler() {
	delete database;
}

void DatabaseHandler::CreateNewUserData(std::string id, UserInfo info) {
	firebase::firestore::DocumentReference userDocument = userdataReference.Document("/" + id);
	userDocument.Set(firebase::firestore::MapFieldValue{
		{"UserName", firebase::firestore::FieldValue::String(info.UserName)},
		{"RatingScore", firebase::firestore::FieldValue::Integer(info.ratingScore)}
	});
}

int DatabaseHandler::UpdateUserRanking(std::string id, int guestRating, bool userWon) {
	firebase::firestore::DocumentReference userDocument = userdataReference.Document("/" + id);
	firebase::Future<firebase::firestore::DocumentSnapshot> documentSnapshot = userDocument.Get();
	while (documentSnapshot.status() == firebase::kFutureStatusPending) {
		std::cout << "Retrieving user info..\n";
	}
	firebase::firestore::Error error = static_cast<firebase::firestore::Error>(documentSnapshot.error());
	if (error != firebase::firestore::kErrorNone) {
		std::cout << "Error while retrieving user info!\n";
		return 0;
	}
	else {
		std::cout << "Successfully retrieved user info!\n";
		UserInfo userInfo = UserInfo{ documentSnapshot.result()->Get("UserName").ToString(), stoi(documentSnapshot.result()->Get("RatingScore").ToString()) };
		int ratingChange = abs(userInfo.ratingScore - guestRating)*0.2;
		if (userWon) {
			userInfo.ratingScore += ratingChange;
		}
		else {
			userInfo.ratingScore -= ratingChange;
		}
		CreateNewUserData(id,userInfo);
		return ratingChange;
	}
}

UserInfo DatabaseHandler::GetUserInfo(std::string id) {
	firebase::firestore::DocumentReference userDocument = userdataReference.Document("/" + id);
	firebase::Future<firebase::firestore::DocumentSnapshot> documentSnapshot = userDocument.Get();
	while (documentSnapshot.status() == firebase::kFutureStatusPending) {
		std::cout << "Retrieving user info..\n";
	}
	firebase::firestore::Error error = static_cast<firebase::firestore::Error>(documentSnapshot.error());
	if (error != firebase::firestore::kErrorNone) {
		std::cout << "Error while retrieving user info!\n";
		return UserInfo();
	}
	else {
		std::cout << "Successfully retrieved user info!\n";
		return UserInfo{ documentSnapshot.result()->Get("UserName").ToString(), stoi(documentSnapshot.result()->Get("RatingScore").ToString())};
	}
}
