#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct Student {
	const int id;
	string surname;
	string course;
	float average;
	Student(int ID, string Surname, string Course, float Average) :id(ID) {
		this->surname = Surname;
		surname[0] = toupper(surname[0]);
		this->course = Course;
		course[0] = toupper(course[0]);
		this->average = Average;
	}
};

#pragma region [basic]

void addStudent(vector<shared_ptr<Student>>& v) {
	int ID;
	string surname, specialization;
	float average;
	ifstream nr_id;
	nr_id.open("baza.txt");
	if (!nr_id)
		cerr << "Nie mozna otworzyc pliku!\n";
	nr_id >> ID;
	cout << "Podaj nazwisko: ";
	cin >> surname;
	cout << "Podaj specjalizacje: ";
	cin >> specialization;
	do {
		cout << "Podaj srednia: ";
		if (!(cin >> average)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (average > 5.0 || average < 2.0);
	v.push_back(make_shared<Student>(ID, surname, specialization, average));
	ID++;
	ofstream nr_ID("baza.txt",ios::trunc);
	nr_ID << ID;
	nr_id.close();
}

void saveDatabase(vector<shared_ptr<Student>> v) {
	int id;
	ifstream ID;
	ID.open("baza.txt");
	if (!ID)
		cerr << "Nie udalo sie otworzyc pliku!\n";
	ID >> id;
	ID.close();
	ofstream base;
	base.open("baza.txt",ios::trunc);
	base << id;
	if (!base)
		cerr << "Nie udalo sie otworzyc pliku!\n";
	for (unsigned int i = 0; i < v.size(); i++)
		base<< '\n' << v[i]->id << ' ' << v[i]->surname << ' ' << v[i]->course << ' ' << fixed << setprecision(2) << v[i]->average;
	base.close();
}

void displayDatabase(vector<shared_ptr<Student>> v) {
	cout << setw(2) << "Id" << setw(15) << "Nazwisko" << setw(20) << "Specjalizacja" << setw(10) << "Srednia\n";
	for (auto e : v)
		cout << setw(2) << e->id << setw(15) << e->surname << setw(20) << e->course << setw(9) << fixed << setprecision(2) << e->average << '\n';
	cout << "Obecna ilosc uczniow: " << v.size() << '\n';
}

void loadDatabese(vector<shared_ptr<Student>>& v) {
	int ID,a;
	string surname, specialization;
	float average;
	ifstream base_w;
	base_w.open("baza.txt");
	if (!base_w)
		cerr << "Nie udalo sie otworzyc pliku!\n";
	base_w >> a;
	for(int i=0; !base_w.eof(); i++) {
		base_w >> ID >> surname >> specialization >> average;
		v.push_back(make_shared<Student>(ID, surname, specialization, average));
	}
	base_w.close();
}

void deleteStudent(vector<shared_ptr<Student>>& v) {
	int ID=-1,a=0;
	do {
		do {
			cout << "Podaj ID: ";
			if (!(cin >> ID)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (ID == -1);
		for (unsigned int i = 0; i < v.size(); i++)
			if (v[i]->id == ID) {
				a = i;
			}
	} while (a == 0);
	v.erase(v.begin() + a);
}

#pragma endregion

#pragma region [menu]

void menu() {
	cout << "MENU GLOWNE\n";
	cout << "1.Dodaj ucznia.\n";
	cout << "2.Zapisz baze.\n";
	cout << "3.Wyswietl baze.\n";
	cout << "4.Usun ucznia.\n";
	cout << "5.Sortuj.\n";
	cout << "6.Edytuj.\n";
	cout << "7.Wyszukiwanie.\n";
	cout << "8.Wyjscie.\n";
}

void sortingMenu() {
	cout << "Wedlug:\n";
	cout << "1.ID.\n";
	cout << "2.Nazwisko.\n";
	cout << "3.Specjalizacja.\n";
	cout << "4.Srednia.\n";
}

void sortingMR() {
	cout << "1.Rosnaco.\n";
	cout << "2.Malejaco.\n";
	cout << "Wybierz: ";
}

#pragma endregion

#pragma region [sorting]

void sortIDr(vector<shared_ptr<Student>>& v) {
	sort(v.begin(), v.end(), [](const shared_ptr<Student> left, const shared_ptr<Student> right) {return left->id < right->id; });
}

void sortIDm(vector<shared_ptr<Student>>& v){
	sort(v.rbegin(), v.rend(), [](const shared_ptr<Student> left, const shared_ptr<Student> right) {return left->id < right->id; });
}

void sortNazwiskoR(vector<shared_ptr<Student>>& v) {
	sort(v.begin(), v.end(), [](const shared_ptr<Student> left, const shared_ptr<Student> right) {return left->surname < right->surname; });
}

void sortNazwiskoM(vector<shared_ptr<Student>>& v) {
	sort(v.rbegin(), v.rend(), [](const shared_ptr<Student> left, const shared_ptr<Student> right) {return left->surname < right->surname; });
}

void sortSpecjalizacjaR(vector<shared_ptr<Student>>& v) {
	sort(v.begin(), v.end(), [](const shared_ptr<Student> left, const shared_ptr<Student> right) {return left->course < right->course; });
}

void sortSpecjalizacjaM(vector<shared_ptr<Student>>& v) {
	sort(v.rbegin(), v.rend(), [](const shared_ptr<Student> left, const shared_ptr<Student> right) {return left->course < right->course; });
}

void sortSredniaR(vector<shared_ptr<Student>>& v) {
	sort(v.begin(), v.end(), [](const shared_ptr<Student> left, const shared_ptr<Student> right) {return left->average < right->average; });
}

void sortSredniaM(vector<shared_ptr<Student>>& v) {
	sort(v.rbegin(), v.rend(), [](const shared_ptr<Student> left, const shared_ptr<Student> right) {return left->average < right->average; });
}

#pragma endregion

#pragma region [editing]

void editAllParameters(vector<shared_ptr<Student>>& v) {
	int ID=-1,a=0;
	string surname, specialization;
	float average;
	do {
		do {
			cout << "Podaj ID: ";
			if (!(cin >> ID)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (ID == -1);
		for (unsigned int i = 0; i < v.size(); i++)
			if (v[i]->id == ID)
				a = i;
	} while(a==0);
	cout << "Podaj nazwisko: ";
	cin >> surname;
	cout << "Podaj specjalizacje: ";
	cin >> specialization;
	do {
		cout << "Podaj srednia: ";
		if (!(cin >> average)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (average > 5 || average < 2);
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i]->id == ID)
			v[i] = make_shared<Student>(ID, surname, specialization, average);
}

void editSurname(vector<shared_ptr<Student>>& v) {
	int ID=-1,a=0;
	string surname, specialization;
	float average;
	do {
		do {
			cout << "Podaj ID: ";
			if (!(cin >> ID)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (ID == -1);
		for (unsigned int i = 0; i < v.size(); i++)
			if (v[i]->id == ID)
				a = i;
	} while (a == 0);
	cout << "Podaj nazwsko: ";
	cin >> surname;
	specialization = v[a]->course;
	average = v[a]->average;
	v[a] = make_shared<Student>(ID, surname, specialization, average);
}

void editCourse(vector<shared_ptr<Student>>& v) {
	int ID=-1,a=0;
	string surname, specialization;
	float average;
	do {
		do {
			cout << "Podaj ID: ";
			if (!(cin >> ID)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (ID == -1);
		for (unsigned int i = 0; i < v.size(); i++)
			if (v[i]->id == ID)
				a = i;
	} while (a == 0);
	surname = v[a]->surname;
	cout << "Podaj specjalizacje: ";
	cin >> specialization;
	average = v[a]->average;
	v[a] = make_shared<Student>(ID, surname, specialization, average);
}

void editAverage(vector<shared_ptr<Student>>& v) {
	int ID=-1,a=0;
	string surname, specialization;
	float average;
	do {
		do {
			cout << "Podaj ID: ";
			if (!(cin >> ID)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (ID == -1);
		for (unsigned int i = 0; i < v.size(); i++)
			if (v[i]->id == ID)
				a = i;
	} while (a==0);
	surname = v[a]->surname;
	specialization = v[a]->course;
	do {
		cout << "Podaj srednia: ";
		if (!(cin >> average)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (average > 5 || average < 2);
	v[a] = make_shared<Student>(ID, surname, specialization, average);
}

#pragma endregion

#pragma region [searching]

void searchingID(vector<shared_ptr<Student>> v) {
	int ID=-1,a=0;
	do {
		do {
			cout << "Podaj ID: ";
			if (!(cin >> ID)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (ID == -1);
		for (unsigned int i = 0; i < v.size(); i++)
			if (v[i]->id == ID)
				a = i;
	} while (a == 0);
	cout << setw(2) << v[a]->id << setw(15) << v[a]->surname << setw(20) << v[a]->course << setw(9) << fixed << setprecision(2) << v[a]->average << '\n';
}

void searchingSurname(vector<shared_ptr<Student>> v) {
	string surname;
	bool a = false;
	do {
		cout << "Podaj Nazwisko: ";
		cin >> surname;
		surname[0] = toupper(surname[0]);
		for (unsigned int i = 0; i < v.size(); i++)
			if (v[i]->surname == surname)
				a = true;
	} while (a != true);
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i]->surname == surname) {
			cout << setw(2) << v[i]->id << setw(15) << v[i]->surname << setw(20) << v[i]->course << setw(9) << fixed << setprecision(2) << v[i]->average << '\n';
		}
}

void searchingCourse(vector<shared_ptr<Student>> v) {
	string course;
	bool a = false;
	do {
		cout << "Podaj Specjalizacje: ";
		cin >> course;
		course[0] = toupper(course[0]);
		for (unsigned int i = 0; i < v.size(); i++)
			if (v[i]->course == course)
				a = true;
	} while (a != true);
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i]->course == course) {
			cout << setw(2) << v[i]->id << setw(15) << v[i]->surname << setw(20) << v[i]->course << setw(9) << fixed << setprecision(2) << v[i]->average << '\n';
		}
}

void searchingAverage(vector<shared_ptr<Student>> v) {
	float average;
	do {
		cout << "Podaj Srednia: ";
		if (!(cin >> average)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (average > 5 || average < 2);
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i]->average == average)
			cout << setw(2) << v[i]->id << setw(15) << v[i]->surname << setw(20) << v[i]->course << setw(9) << fixed << setprecision(2) << v[i]->average << '\n';
}

#pragma endregion

int main()
{
	vector<shared_ptr<Student>>w;
	loadDatabese(w);
	menu();
	char selection,choice,choice2;
	do{
		cout << "Wybierz co chcesz zrobic: ";
		cin >> selection;
		switch (selection) {
		case '1': 
			addStudent(w);
			system("cls");
			menu();
			break;
		case '2':
			saveDatabase(w);
			system("cls");
			menu();
			break;
		case '3':
			displayDatabase(w);
			break;
		case'4':
			displayDatabase(w);
			deleteStudent(w);
			system("pause");
			system("cls");
			menu();
			break;
		case'5':
			sortingMenu();
			cin >> choice;
			switch(choice) {
			case '1':
				sortingMR();
				cin >> choice2;
				switch(choice2) {
				case'1': sortIDr(w); break;
				case'2': sortIDm(w); break;
				default:
					cout << "Nie wybrano poprawnej opcji!\n";
				}
				system("cls");
				menu();
				break;
			case '2':
				sortingMR();
				cin >> choice2;
				switch (choice2) {
				case'1': sortNazwiskoR(w); break;
				case'2': sortNazwiskoM(w); break;
				default:
					cout << "Nie wybrano poprawnej opcji!\n";
				}
				system("cls");
				menu();
				break;
			case '3':
				sortingMR();
				cin >> choice2;
				switch (choice2) {
				case'1': sortSpecjalizacjaR(w); break;
				case'2': sortSpecjalizacjaM(w); break;
				default:
					cout << "Nie wybrano poprawnej opcji!\n";
				}
				system("cls");
				menu();
				break;
			case '4':
				sortingMR();
				cin >> choice2;
				switch (choice2) {
				case'1': sortSredniaR(w); break;
				case'2': sortSredniaM(w); break;
				default:
					cout << "Nie wybrano poprawnej opcji!\n";
				}
				system("cls");
				menu();
				break;
			default:
				cout << "Nie wybrano poprawnego polecenia!\n";
			}
			break;
		case'6':
			displayDatabase(w);
			cout << "Edytuj:\n";
			cout << "1.Wszystkie elementy.\n";
			cout << "2.Wybrany element.\n";
			cin >> choice;
			switch (choice) {
			case'1':
				editAllParameters(w);
				break;
			case'2':
				cout << "Ktory:\n";
				cout << "1.Nazwisko.\n";
				cout << "2.Specjalizacja.\n";
				cout << "3.Srednia.\n";
				cin >> choice2;
				switch (choice2) {
				case'1': editSurname(w); break;
				case'2': editCourse(w); break;
				case'3': editAverage(w); break;
				default:
					cout << "Nie wybrano poprawnej odpowiedzi!\n";
				}
				break;
			default:
				cout << "Nie wybrano poprawnej opcji!\n";
			}
			system("cls");
			menu();
			break;
		case'7':
			cout << "Wyszukjak po:\n";
			cout << "1.ID.\n";
			cout << "2.Nazwisko.\n";
			cout << "3.Specjalizacja.\n";
			cout << "4.Srednia.\n";
			cin >> choice;
			switch (choice) {
			case'1': searchingID(w); break;
			case'2': searchingSurname(w); break;
			case'3': searchingCourse(w); break;
			case'4': searchingAverage(w); break;
			default:
				cout << "Nie wybrano poprawnej odpowiedzi\n";
			}
			system("pause");
			system("cls");
			menu();
			break;
		case'8':
			break;
		default:
			cout << "Nie wybrano poprawnej odpowiedzi!\n";
		}
	} while (selection != '8');
	cout << endl;
}

