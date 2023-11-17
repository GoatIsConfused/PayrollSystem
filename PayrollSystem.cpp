#include <iostream>
#include <fstream>
#include <string>

double standardRate = 31.12;
double supervisorRate = 34.27;
double managementRate = 42.55;
double satMultiplyer = 1.2;
double sunMultiplyer = 1.4;

struct employeeInfo {
	std::string name;
	double rate; // Hourly Rate
	double hours[7]; // Create a array of size 7 (days in a week)
	double payAmount;
};

void newPayroll() {
	std::string employeeName;
	std::string payWeek;
	char confirmation;
	int amountOfEmployees;
	int employeeRate;
	double hoursWorked;
	std::string weekDays[] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"};

	std::cout << "How many people are included in this weeks payroll? ";
	std::cin >> amountOfEmployees;

	if (amountOfEmployees <= 0) { // Do error handling ont he amountOfEmployees here
		std::cout << "Not enough people to create the payroll for." << std::endl;
		return;
	}
	else if (amountOfEmployees >= 35) { // Confirm that they meant to put more than 35
		std::cout << "You entered " << amountOfEmployees << ". Did you mean to enter that many (y/n)? ";
		std::cin >> confirmation;
		if (confirmation != 'y') {
			return;
		}
	}

	std::cout << "Please enter the payweek in this format: DD_MM_YYYY" << std::endl;
	std::cin >> payWeek;

	employeeInfo* employeeListPtr; // Creates the pointer Variable
	employeeListPtr = new employeeInfo[amountOfEmployees]; // Creates amountOfEmployees amount of employeeInfo structures at employeeListPtr

	for (int x = 0; x < amountOfEmployees; x++) {
		std::cout << "Name of the employee? ";
		std::cin >> employeeName;
		(employeeListPtr + x)->name = employeeName; // (*employeeListPtr).rate = 31.12; OR employeeListPtr->rate = 31.12; | Because of precedence

		while (true) {
			std::cout << "What rate are they on?" << std::endl;
			std::cout << "1) Standard " << standardRate << std::endl;
			std::cout << "2) Supervisor " << supervisorRate << std::endl;
			std::cout << "3) Management " << managementRate << std::endl;
			std::cin >> employeeRate;
			if (employeeRate == 1) { // Error Handling
				(employeeListPtr + x)->rate = standardRate;
				break;
			}
			else if (employeeRate == 2) {
				(employeeListPtr + x)->rate = supervisorRate;
				break;
			}
			else if (employeeRate == 3) {
				(employeeListPtr + x)->rate = managementRate;
				break;
			}
		}

		(employeeListPtr + x)->payAmount = 0; // To erase any memory already there
		for (int i = 0; i < 7; i++) { // Runs 7 times for each day of the week
			while (true) {
				std::cout << "How many hours were worked on " << weekDays[i] << "?" << std::endl;
				std::cin >> hoursWorked;
				if (hoursWorked == -1) {
					// no number entered
					(employeeListPtr + x)->hours[i] = 0;
					break;
				}
				else if (hoursWorked > 12) {
					// cannot work more than 12 hours a day
					std::cout << "A casual employee cannot work more than 12 hours in a day. Re-enter the information." << std::endl;
				}
				else {
					(employeeListPtr + x)->hours[i] = hoursWorked;
					if (i == 5) { // Saturday
						(employeeListPtr + x)->payAmount += hoursWorked * ((employeeListPtr + x)->rate * satMultiplyer);
					}
					else if (i == 6) { // Sunday
						(employeeListPtr + x)->payAmount += hoursWorked * ((employeeListPtr + x)->rate * sunMultiplyer);
					}
					else { // Other days
						(employeeListPtr + x)->payAmount += hoursWorked * (employeeListPtr + x)->rate;
					}
					break;
				}
			}
		}
	}

	// Save file
	std::ofstream payrollFile("storage/" + payWeek + ".txt");
	std::string fileString;
	for (int y = 0; y < amountOfEmployees; y++) { // File format is:   NAME MON TUE WED THU FRI SAT SUN PAY
		fileString += (employeeListPtr + y)->name 
			+ " " + std::to_string((employeeListPtr + y)->hours[0])
			+ " " + std::to_string((employeeListPtr + y)->hours[1])
			+ " " + std::to_string((employeeListPtr + y)->hours[2])
			+ " " + std::to_string((employeeListPtr + y)->hours[3])
			+ " " + std::to_string((employeeListPtr + y)->hours[4])
			+ " " + std::to_string((employeeListPtr + y)->hours[5])
			+ " " + std::to_string((employeeListPtr + y)->hours[6])
			+ " " + std::to_string((employeeListPtr + y)->payAmount)
			+ "\n";
	}
	payrollFile << fileString; // Write to the file
	payrollFile.close(); // Close the file


	delete[] employeeListPtr; // Need to deallocate the dynamic memory manually as there is no longer a need for the variable anymore
}

void searchPayroll() {
	try {
		std::string fileName;
		std::cout << "Enter the payweek followed by .txt to open the correct file (format: DD_MM_YYYY.txt)." << std::endl;
		std::cin >> fileName;

		std::ifstream payrollFile("storage/" + fileName);
		std::string fileContent;
		if (!payrollFile.is_open()) {
			throw 505;
		}
		std::string word;
		payrollFile >> word;
		while (payrollFile.good()) {
			fileContent += word + " ";
			payrollFile >> word;
		}
		std::cout << fileContent << std::endl;
		std::cin.ignore();
		payrollFile.close();
	}
	catch (...) {
		std::cout << "An error occured while opening the file likely an incorrect file name was given." << std::endl;
		return;
	}
}

void settings() {
	int option;
	std::cout << "Please select and option:" << std::endl;
	std::cout << "1. Write settings" << std::endl;
	std::cout << "2. View settings" << std::endl;
	std::cin >> option;

	if (option == 1) {
		std::string fileContent;
		std::string userInput;
		std::cout << "Standard rate: ";
		std::cin >> userInput;
		standardRate = stod(userInput);
		std::cout << "Supervisor rate: ";
		std::cin >> userInput;
		supervisorRate = stod(userInput);
		std::cout << "Management rate: ";
		std::cin >> userInput;
		managementRate = stod(userInput);
		std::cout << "Saturday Multiplier: ";
		std::cin >> userInput;
		satMultiplyer = stod(userInput);
		std::cout << "Sunday Multiplier: ";
		std::cin >> userInput;
		sunMultiplyer = stod(userInput);

		// Save file
		std::ofstream settingsFile("storage/settings.txt");
		std::string fileString;
		fileString = std::to_string(standardRate) 
			+ " " + std::to_string(supervisorRate) 
			+ " " + std::to_string(managementRate) 
			+ " " + std::to_string(satMultiplyer) 
			+ " " + std::to_string(sunMultiplyer);
		settingsFile << fileString; // Write to the file
		settingsFile.close(); // Close the file
	}
	else if (option == 2) {
		std::cout << "Standard Rate: " << standardRate << std::endl;
		std::cout << "Supervisor Rate: " << supervisorRate << std::endl;
		std::cout << "Management Rate: " << managementRate << std::endl;
		std::cout << "Saturday Multiplier: " << satMultiplyer << std::endl;
		std::cout << "Sunday Multiplier: " << sunMultiplyer << std::endl;
	}
	else {
		std::cout << "No option declared." << std::endl;
		return;
	}
}

int main()
{
	// Load settings
	try {
		std::ifstream settingsFile("storage/settings.txt");
		std::string fileContent;
		if (!settingsFile.is_open()) {
			throw 505;
		}
		std::string word;
		settingsFile >> word;
		standardRate = stod(word);
		settingsFile >> word;
		supervisorRate = stod(word);
		settingsFile >> word;
		managementRate = stod(word);
		settingsFile >> word;
		satMultiplyer = stod(word);
		settingsFile >> word;
		sunMultiplyer = stod(word);
		settingsFile.close();
	}
	catch (...) {
		std::cout << "An error occured while loading the settings." << std::endl;
	}


	int userInput;
	while (true) {
		std::cout << "Payroll Creator" << std::endl;
		std::cout << "1. New Payroll" << std::endl;
		std::cout << "2. Search Payrolls" << std::endl;
		std::cout << "3. Settings" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cin >> userInput;

		if (userInput == 1) {
			newPayroll();
		}
		else if (userInput == 2) {
			searchPayroll();
		}
		else if (userInput == 3) {
			settings();
		}
		else if (userInput == 4) {
			break;
		}
	}
	return 0;
}
