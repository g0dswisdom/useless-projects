#include <iostream>
#include <string>
#include <fstream>

bool userExists(const std::string& user) {
	std::ifstream users("./users.txt");
	std::string existingUser;

	while (std::getline(users, existingUser)) {
		if (existingUser == user) {
			users.close();
			return true;
		}
	}

	users.close();
	return false;
}

bool passwordExists(const std::string& pass) {
	std::ifstream passwords("./passwords.txt");
	std::string storedPassword;

	while (std::getline(passwords, storedPassword)) {
		if (storedPassword == pass) {
			passwords.close();
			return true;
		}
	}

	passwords.close();
	return false;
}

int main()
{
	std::ifstream users;
	users.open("./users.txt");

	std::string username;
	std::string password;
	std::string check;

	std::cout << "Hello. Type 1 for login and 2 for register: ";
	std::cin >> check;

	if (check == "1") {
		std::cout << "Username: ";
		std::cin >> username;
		std::cout << "Password: ";
		std::cin >> password;
		if (userExists(username) && passwordExists(password)) {
			std::cout << "Successfully logged in!\n";
			return false;
		}
		else {
			std::cout << "Invalid username or password.\n";
			return false;
		}
	}
	else {
		std::cout << "Username: ";
		std::cin >> username;

		if (!userExists(username)) {
			std::ofstream users("./users.txt", std::ios_base::app);
			std::ofstream passwords("./passwords.txt", std::ios_base::app);

			if (users.is_open() and passwords.is_open()) {
				std::cout << "Password: ";
				std::cin >> password;
				users << username << std::endl;
				passwords << password << std::endl;
			}
		}
	};
}