#pragma once
#include "Excepcion.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <conio.h>
#include <stdio.h>

class Interfaz {
public:
	// Program entry
	static void showWelcome();
	static void showMenu();
	static int getMenuOption();
	static void waitAndClear();
	static void clearScreen();
	static void showSaveSuccess();
	static void showFarewell();
	// -----------Opcion 1 del menu------------
	static void showMaterialTypeMenu();
	static int getMaterialType();
	static void showAddBookInterface();
	static void showAddMagazineInterface();
	static void showAddDigitalInterface();
	// Guardar componentes del material
	static int getQuantity();
	static int getClassificationNumber();
	static std::string getCatalogNumber();
	static std::string getTitle();
	static std::string getAuthor();
	static std::string getKeyword();
	static std::string getStatus();
	// Guardar datos de material nuevo -> libro
	static std::string getBookType();
	// Guardar datos de material nuevo -> revista
	static std::string getMagazineType();
	static int getVolume();
	static int getIssueNumber();
	// Guardar datos de material nuevo -> digital
	static std::string getDigitalType();
	static std::string getDigitalFormat();
	static std::string getFileFormat();
	static bool getAccessStatus();
	// -----------Opcion 2 del menu------------
	static void showEditError();
	static std::string searchByTitle();
	static int getMaterialIndex();
	static int getEditTypeOption();
	static void showEditBookMenu();
	static int getEditBookOption();
	static void showEditMagazineMenu();
	static int getEditMagazineOption();
	static void showEditDigitalMenu();
	static int getEditDigitalOption();
	static void showEditBookInterface();
	static void showEditMagazineInterface();
	static void showEditDigitalInterface();
	// -----------Opcion 3 del menu------------
	static void showAddUserMessage();
	static std::string getNewUserID();
	static std::string getNewUserName();
	static std::string getNewUserSurname();
	static bool getNewUserAvailability();
	static void showUserSaved();
	// -----------Opcion 4 del menu------------
	static void showEditUserInterface();
	static void showIDWarning();
	// ----------Opcion 5 del menu------------
	static void showLoanReturnMenu();
	static int getLoanOption();
	static void showExistingIDWarning();
	// -----------Opcion 6 del menu------------
	static void showInventoryReport();
	static int getMaterialReportOption();
	// -----------Opcion 7 del menu------------
	static void showUserReport();
	static int getActivityReportOption();
	static void showLoanSuccess();
	static void showReturnSuccess();
	static void showEmptyMessage();
	// -----------Opcion 8 del menu------------
	static int getLoanReportOption();
	static void showLoanTypeInterface();
	static int getLoanType();
	// -----------Opcion 9 del menu------------
	static void showUserLoansReport();
	static void showInvalidEntry();
};