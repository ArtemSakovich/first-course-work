#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct Company {
	char companyName[30];
	char typeOfWork[30];
	char unit[15];
	double executionTime, costPerUnit;
	int minimalScopeOfWork;
};


int eneterInformationAboutStudentsFromFile(Company* companies, int& stringCounter) {
	bool f;
	int i = 0;  
	ifstream file("c:\\for_Course_Work.txt");
	f = file.is_open(); //если файл есть, то читаем первый символ, если код = -52 это значит файл пуст 
	if (f) {
		char ch;
		file.get(ch);
		if (ch == -52) i = 0;
		else {
			while (!file.eof()) {
				file.get(ch);
				if (ch == 10) i++;
			}
			i++;			//считаем кол - во символов переноса строк и увеличиваем на 1
		}
		cout << endl << "File was parsed successfully!" << endl;
	}
	else { ofstream file("c:\\for_Course_Work.txt"); 
	cout << endl << "File cannot be open!" << endl;
	}
	file.close();
	if (i > 0) {
		ifstream file("c:\\for_Course_Work.txt");
		for ( stringCounter; stringCounter < i; stringCounter++) {
			file >> companies[stringCounter].companyName;
			file >> companies[stringCounter].typeOfWork;
			file >> companies[stringCounter].unit;
			file >> companies[stringCounter].costPerUnit;
			file >> companies[stringCounter].executionTime;
			file >> companies[stringCounter].minimalScopeOfWork;
		}
		file.close();
	}
	return stringCounter;
};

void viewInformationAboutCompaniesAsATable(Company* companies, int& stringCounter) {
	cout.setf(ios::left);
	cout << endl;
	cout << setw(35) << "COMPANY";
	cout << setw(35) << "TYPE OF WORK";
	cout << setw(35) << "UNIT";
	cout << setw(35) << "COST PER UNIT";
	cout << setw(35) << "EXECUTION TIME";
	cout << setw(35) << "MINIMAL SCOPE OF WORK" << endl;
	for (int i = 0; i < stringCounter; i++) {
		{
			cout.setf(ios::left);
			cout << endl;
			cout << setw(35) << companies[i].companyName;
			cout << setw(35) << companies[i].typeOfWork;
			cout << setw(35) << companies[i].unit;
			cout << setw(35) << companies[i].costPerUnit;
			cout << setw(35) << companies[i].executionTime;
			cout << setw(35) << companies[i].minimalScopeOfWork;
		}
	}
};

void addInformationToList(Company* companies, int& stringCounter) {
	cout << "Please enter company name: ";
	cin >> companies[stringCounter].companyName;
	cout << "Please enter type of work: ";
	cin >> companies[stringCounter].typeOfWork;
	cout << "Please enter unit: ";
	cin >> companies[stringCounter].unit;
	cout << "Please enter cost per unit: ";
	cin >> companies[stringCounter].costPerUnit;
	cout << "Please enter execution time: ";
	cin >> companies[stringCounter].executionTime;
	cout << "Please enter scope of work: ";
	cin >> companies[stringCounter].minimalScopeOfWork;
	stringCounter++;
	cout << "\nInformation was added successfully!\n";
};

void deleteInformationFromList(Company* companies, int& stringCounter) {
	char companyNameHelper[30];
	int indexForDelete = -1;
	int lastCompanyIndex;
	lastCompanyIndex = stringCounter - 1;
	cout << "Please enter company name to find what company will be deleted: ";
	cin >> companyNameHelper;
	for (int i = 0; i < stringCounter; i++) {
		if (strcmp(companyNameHelper, companies[i].companyName) == 0) {
			indexForDelete = i;
			break;
		}
	}
	if (indexForDelete != -1) {
		Company temp = companies[indexForDelete];
		companies[indexForDelete] = companies[lastCompanyIndex];
		companies[lastCompanyIndex] = temp;
		stringCounter--;
	}
};

void editInformationAboutCompany(Company* companies, int& stringCounter) {
	char companyNameHelper[30];
	char typeOfWorkHelper[30];
	char unitHelper[15];
	double executionTimeHelper, costPerUnitHelper;
	int minimalScopeOfWorkHelper;
	int howManyUnitsIsCoincided = 0;
	int indexToEdit = -1;
	cout << "Please enter company name to find wat company will be edited: ";
	cin >> companyNameHelper;
	for (int i = 0; i < stringCounter; i++) {
		if (!strcmp(companyNameHelper, companies[i].companyName)) {
			howManyUnitsIsCoincided++;
		}
		if (howManyUnitsIsCoincided == 1) {
			indexToEdit = i;
		}
		howManyUnitsIsCoincided = 0;
	}
	if (indexToEdit != -1) {
		cout << "Please enter new information or enter 0 to leave unchanged." << endl;
		cout << "Please enter new company name: ";
		cin >> companyNameHelper;
		cout << "Please enter new type of work: ";
		cin >> typeOfWorkHelper;
		cout << "Please enter new unit: ";
		cin >> unitHelper;
		cout << "Please enter new execution time: ";
		cin >> costPerUnitHelper;
		cout << "Please enter new cost per unit: ";
		cin >> executionTimeHelper;
		cout << "Please enter new scope of work: ";
		cin >> minimalScopeOfWorkHelper;

		if (companyNameHelper[0] != '0') {
			strcpy_s(companies[indexToEdit].companyName, companyNameHelper);
		}
		if (typeOfWorkHelper[0] != '0') {
			strcpy_s(companies[indexToEdit].typeOfWork, typeOfWorkHelper);
		}
		if (unitHelper[0] != '0') {
			strcpy_s(companies[indexToEdit].unit, unitHelper);
		}
		if (costPerUnitHelper != 0) {
			companies[indexToEdit].executionTime = costPerUnitHelper;
		}
		if (executionTimeHelper != 0) {
			companies[indexToEdit].costPerUnit = executionTimeHelper;
		}
		if (minimalScopeOfWorkHelper != 0) {
			companies[indexToEdit].minimalScopeOfWork = minimalScopeOfWorkHelper;
		}

		cout << "Done!" << endl;
	}
	else {
		cout << "Company was not found!" << endl;
	}
};

void sortByCompanyNameInAlphabeticalOrder(Company* companies, int& stringCounter) {
	int smaller_index;
	for (int i = 0; i < stringCounter; i++) {
		smaller_index = i;
		for (int j = i + 1; j < stringCounter; j++) {
			bool is_smaller = false;
			int k = 0;
			while (!is_smaller && (k < strlen(companies[j].companyName) || k < strlen(companies[smaller_index].companyName))) {
				if (companies[j].companyName[k] < companies[smaller_index].companyName[k]) {
					smaller_index = j;
					is_smaller = true;
				}
				else {
					if (companies[j].companyName[k] == companies[smaller_index].companyName[k]) {
						k++;
					}
					else {
						is_smaller = true;
					}
				}
			}
		}

		Company temp = companies[i];
		companies[i] = companies[smaller_index];
		companies[smaller_index] = temp;
	}
	cout << endl << "Sorted!" << endl;
}; 

void sortByTypeOfWorkInAlphabeticalOrder(Company* companies, int& stringCounter) {
	int smaller_index;
	for (int i = 0; i < stringCounter; i++) {
		smaller_index = i;
		for (int j = i + 1; j < stringCounter; j++) {
			bool is_smaller = false;
			int k = 0;
			while (!is_smaller && (k < strlen(companies[j].typeOfWork) || k < strlen(companies[smaller_index].typeOfWork))) {
				if (companies[j].typeOfWork[k] < companies[smaller_index].typeOfWork[k]) {
					smaller_index = j;
					is_smaller = true;
				}
				else {
					if (companies[j].typeOfWork[k] == companies[smaller_index].typeOfWork[k]) {
						k++;
					}
					else {
						is_smaller = true;
					}
				}
			}
		}

		Company temp = companies[i];
		companies[i] = companies[smaller_index];
		companies[smaller_index] = temp;
	}
	cout << endl << "Sorted!" << endl;
};

void sortByUnitInAlphabeticalOrder(Company* companies, int& stringCounter) {
	int smaller_index;
	for (int i = 0; i < stringCounter; i++) {
		smaller_index = i;
		for (int j = i + 1; j < stringCounter; j++) {
			bool is_smaller = false;
			int k = 0;
			while (!is_smaller && (k < strlen(companies[j].unit) || k < strlen(companies[smaller_index].unit))) {
				if (companies[j].unit[k] < companies[smaller_index].unit[k]) {
					smaller_index = j;
					is_smaller = true;
				}
				else {
					if (companies[j].unit[k] == companies[smaller_index].unit[k]) {
						k++;
					}
					else {
						is_smaller = true;
					}
				}
			}
		}

		Company temp = companies[i];
		companies[i] = companies[smaller_index];
		companies[smaller_index] = temp;
	}
	cout << endl << "Sorted!" << endl;
};

void sortByMinimalScopeOfWork(Company* companies, int& stringCounter) {
	for (int i = 0; i < stringCounter - 1; i++) {
		for (int j = 0; j < stringCounter - i - 1; j++) {
			if (companies[j].minimalScopeOfWork > companies[j + 1].minimalScopeOfWork) {
				swap(companies[j].minimalScopeOfWork, companies[j + 1].minimalScopeOfWork);
			}
		}
	}
	cout << endl << "Sorted!" << endl;
};

void sortByExecutionTime(Company* companies, int& stringCounter) {
	for (int i = 0; i < stringCounter - 1; i++) {
		for (int j = 0; j < stringCounter - i - 1; j++) {
			if (companies[j].executionTime > companies[j + 1].executionTime) {
				swap(companies[j].executionTime, companies[j + 1].executionTime);
			}
		}
	}
	cout << endl << "Sorted!" << endl;
};

void sortByCostPerUnit(Company* companies, int& stringCounter) {
	for (int i = 0; i < stringCounter - 1; i++) {
		for (int j = 0; j < stringCounter - i - 1; j++) {
			if (companies[j].costPerUnit > companies[j + 1].costPerUnit) {
				swap(companies[j].costPerUnit, companies[j + 1].costPerUnit);
			}
		}
	}
	cout << endl << "Sorted!" << endl;
};

void searchByCompanyName(Company* companies, int& stringCounter, char* companyNameHelper) {
	int sum = 0;
	for (int i = 0; i < stringCounter; i++) {
		if (strcmp(companyNameHelper, companies[i].companyName) == 0) {
			sum = sum + 1;
			cout.setf(ios::left);
			cout << endl;
			cout << setw(22) << "COMPANY";
			cout << setw(32) << "TYPE OF WORK";
			cout << setw(13) << "UNIT";
			cout << setw(17) << "COST PER UNIT";
			cout << setw(19) << "EXECUTION TIME";
			cout << setw(10) << "MINIMAL SCOPE OF WORK";
			cout << endl;
			cout << setw(22) << companies[i].companyName << setw(32) << companies[i].typeOfWork << setw(13) << companies[i].unit << setw(17) << companies[i].costPerUnit << setw(19) << companies[i].executionTime << setw(10) << companies[i].minimalScopeOfWork << endl;
		}
	}
	if (sum == 0) {
		cout << "I'm sorry, but there are no suitable options. ";
	}
};

void searchByTypeOfWork(Company* companies, int& stringCounter, char* typeOfWorkHelper) {
	int sum = 0;
	for (int i = 0; i < stringCounter; i++) {
		if (strcmp(typeOfWorkHelper, companies[i].typeOfWork) == 0) {
			sum = sum + 1;
			cout.setf(ios::left);
			cout << endl;
			cout << setw(22) << "COMPANY";
			cout << setw(32) << "TYPE OF WORK";
			cout << setw(13) << "UNIT";
			cout << setw(17) << "COST PER UNIT";
			cout << setw(19) << "EXECUTION TIME";
			cout << setw(10) << "SCOPE OF WORK";
			cout << endl;
			cout << setw(22) << companies[i].companyName << setw(32) << companies[i].typeOfWork << setw(13) << companies[i].unit << setw(17) << companies[i].costPerUnit << setw(19) << companies[i].executionTime << setw(10) << companies[i].minimalScopeOfWork << endl;
		}
	}
	if (sum == 0) {
		cout << "I'm sorry, but there are no suitable options. ";
	}
};

void searchByUnit(Company* companies, int& stringCounter, char* unitHelper) {
	int sum = 0;
	for (int i = 0; i < stringCounter; i++) {
		if (strcmp(unitHelper, companies[i].unit) == 0) {
			sum = sum + 1;
			cout.setf(ios::left);
			cout << endl;
			cout << setw(22) << "COMPANY";
			cout << setw(32) << "TYPE OF WORK";
			cout << setw(13) << "UNIT";
			cout << setw(17) << "COST PER UNIT";
			cout << setw(19) << "EXECUTION TIME";
			cout << setw(10) << "MINIMAL SCOPE OF WORK";
			cout << endl;
			cout << setw(22) << companies[i].companyName << setw(32) << companies[i].typeOfWork << setw(13) << companies[i].unit << setw(17) << companies[i].costPerUnit << setw(19) << companies[i].executionTime << setw(10) << companies[i].minimalScopeOfWork << endl;
		}
	}
	if (sum == 0) {
		cout << "I'm sorry, but there are no suitable options. ";
	}
};

void searchByCostPerUnit(Company* companies, int& stringCounter, double costPerUnitHelper) {
	int sum = 0;
	for (int i = 0; i < stringCounter; i++) {
		if (costPerUnitHelper == companies[i].costPerUnit) {
			sum = sum + 1;
			cout.setf(ios::left);
			cout << endl;
			cout << setw(22) << "COMPANY";
			cout << setw(32) << "TYPE OF WORK";
			cout << setw(13) << "UNIT";
			cout << setw(17) << "COST PER UNIT";
			cout << setw(19) << "EXECUTION TIME";
			cout << setw(10) << "MINIMAL SCOPE OF WORK";
			cout << endl;
			cout << setw(22) << companies[i].companyName << setw(32) << companies[i].typeOfWork << setw(13) << companies[i].unit << setw(17) << companies[i].costPerUnit << setw(19) << companies[i].executionTime << setw(10) << companies[i].minimalScopeOfWork << endl;
		}
	}
	if (sum == 0) {
		cout << "I'm sorry, but there are no suitable options. ";
	}
};

void searchByExecutionTime(Company* companies, int& stringCounter, double executionTimeHelper) {
	int sum = 0;
	for (int i = 0; i < stringCounter; i++) {
		if (executionTimeHelper == companies[i].executionTime) {
			sum = sum + 1;
			cout.setf(ios::left);
			cout << endl;
			cout << setw(22) << "COMPANY";
			cout << setw(32) << "TYPE OF WORK";
			cout << setw(13) << "UNIT";
			cout << setw(17) << "COST PER UNIT";
			cout << setw(19) << "EXECUTION TIME";
			cout << setw(10) << "MINIMAL SCOPE OF WORK";
			cout << endl;
			cout << setw(22) << companies[i].companyName << setw(32) << companies[i].typeOfWork << setw(13) << companies[i].unit << setw(17) << companies[i].costPerUnit << setw(19) << companies[i].executionTime << setw(10) << companies[i].minimalScopeOfWork << endl;
		}
	}
	if (sum == 0) {
		cout << "I'm sorry, but there are no suitable options. ";
	}
};

void searchByMinimalScopeOfWork(Company* companies, int& stringCounter, int minimalScopeOfWork) {
	int sum = 0;
	for (int i = 0; i < stringCounter; i++) {
		if (minimalScopeOfWork == companies[i].minimalScopeOfWork) {
			sum = sum + 1;
			cout.setf(ios::left);
			cout << endl;
			cout << setw(22) << "COMPANY";
			cout << setw(32) << "TYPE OF WORK";
			cout << setw(13) << "UNIT";
			cout << setw(17) << "COST PER UNIT";
			cout << setw(19) << "EXECUTION TIME";
			cout << setw(10) << "MINIMAL SCOPE OF WORK";
			cout << endl;
			cout << setw(22) << companies[i].companyName << setw(32) << companies[i].typeOfWork << setw(13) << companies[i].unit << setw(17) << companies[i].costPerUnit << setw(19) << companies[i].executionTime << setw(10) << companies[i].minimalScopeOfWork << endl;
		}
	}
	if (sum == 0) {
		cout << "I'm sorry, but there are no suitable options. ";
	}
};

void search(Company* companies, int& stringCounter) {
	int switchHelper;
	string countinueHelper;
	cout << "Available actions: " << endl << "Search by company name - 1 " << endl << "Search by type of work - 2" << endl << "Search by unit - 3" << endl << "Search by cost per unit - 4" << endl << "Search by execution time - 5" << endl << "Search by minimal scope of work - 6" << endl;
	cout << "Please select the search you need: "; cin >> switchHelper;
	switch (switchHelper)
	{
	case 1:
	{
		char companyNameHelper[30];
		cout << "Please enter company name to search: "; cin >> companyNameHelper;
		searchByCompanyName(companies, stringCounter, companyNameHelper);
	}
	break;
	case 2:
	{
		char typeOfWorkHelper[30];
		cout << "Please enter type of work to search: "; cin >> typeOfWorkHelper;
		searchByTypeOfWork(companies, stringCounter, typeOfWorkHelper);
	}
	break;
	case 3:
	{
		char unitHelper[15];
		cout << "Please enter unit to search: "; cin >> unitHelper;
		searchByUnit(companies, stringCounter, unitHelper);
	}
	break; 
	case 4:
	{
		double costPerUnitHelper;
		cout << "Please enter cost per unit to search: "; cin >> costPerUnitHelper;
		searchByCostPerUnit(companies, stringCounter, costPerUnitHelper);
	}
	break;
	case 5:
	{
		double executionTimeHelper;
		cout << "Please enter execution time to search: "; cin >> executionTimeHelper;
		searchByExecutionTime(companies, stringCounter, executionTimeHelper);
	}
	break;
	case 6:
	{
		int minimalScopeOfWorkHelper;;
		cout << "Please enter minimal scope of work to search: "; cin >> minimalScopeOfWorkHelper;
		searchByMinimalScopeOfWork(companies, stringCounter, minimalScopeOfWorkHelper);
	}
	break;
	}
};

void saveInformationToFile(Company* companies, int& stringCounter) {
	ofstream file("c:\\for_Course_Work.txt");
	file.clear();
	for (int j = 0; j < stringCounter; j++) {
		file << companies[j].companyName << " ";
		file << companies[j].typeOfWork << " ";
		file << companies[j].unit << " ";
		file << companies[j].executionTime << " ";
		file << companies[j].costPerUnit << " ";
		file << companies[j].minimalScopeOfWork << " ";
		if (j != stringCounter - 1) file << endl;
	}
	file.close();
	cout << endl << "Information was saved!" << endl;
};

int menu(Company* companies, int& stringCounter) {
	int switchHelper;
	string countinueHelper;
	cout << "Available actions: " << endl << "Enter information from a file - 1 " << endl << "View companies information as a table - 2" << endl << "Add item to the list - 3" << endl << "Delete item from the list - 4" << endl << "Edit item from the list - 5" << endl <<  "Sort by company name in alphabetical order- 6" << endl << "Sort by type of work in alphabetical order - 7" << endl << "Sort by unit in alphabetical order - 8" << endl << "Sort by execution time - 9" << endl << "Sort by cost per unit - 10" << endl << "Sort by minimal scope of work - 11" << endl << "Save information to a file - 12" << endl << "Search - 13" << endl;
	cout << "Plese choose the action you need: "; cin >> switchHelper;
	switch (switchHelper)
	{
	case 1:
	{
		eneterInformationAboutStudentsFromFile(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 2:
	{
		viewInformationAboutCompaniesAsATable(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 3:
	{
		addInformationToList(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 4:
	{
		deleteInformationFromList(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 5:
	{
		editInformationAboutCompany(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 6:
	{
		sortByCompanyNameInAlphabeticalOrder(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 7:
	{
		sortByTypeOfWorkInAlphabeticalOrder(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 8:
	{
		sortByUnitInAlphabeticalOrder(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 9:
	{
		sortByExecutionTime(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 10:
	{
		sortByCostPerUnit(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 11:
	{
		sortByMinimalScopeOfWork(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 12:
	{
		saveInformationToFile(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 13:
	{
		search(companies, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		cout << endl;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 0: return 0;
	}
	return menu(companies, stringCounter);
};



int main() {
	Company* companies = new Company[100];
	int stringCounter = 0;
	menu(companies, stringCounter);
	return 0;
};
