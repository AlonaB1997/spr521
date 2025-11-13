#include <iostream>
using namespace std;
#include "Warehouse_F.h"

int main()
{
	int choice, searchChoice, searchId, sortChoice;; // To choose type of operation
	bool foundId; // To find if specific ID for operation 2, 3 or 4 has been found
	size_t count = 0, productsToAdd, idToRemove, idToChange; // Initially warehouse is considered empty
	Product* warehouse = new Product[count]; // Creating empty warehouse


	do {
		cout << "Choose operation (1 - Add product, 2 - Remove product, 3 - Change product, 4 - Search product, 5 - Sort products, 0 - Exit programm): ";
		cin >> choice;

		if (choice >= 1 && choice <= 5)
		{
			switch (choice) {
			case 1:
				cout << "\nEnter number of products to add: ";
				cin >> productsToAdd;
				cin.ignore();
				warehouse = addProduct(warehouse, count, productsToAdd); // Filling warehouse with given products

				cout << "\nProducts have been successfully added to the warehouse!" << endl;
				showWarehouse(warehouse, count);
				break;

			case 2:
				if (count != 0)
				{
					do {
						cout << "\nEnter ID of product to remove or 0 (to exit operation): ";
						cin >> idToRemove;
						foundId = checkProductId(warehouse, count, idToRemove);

						if (foundId && idToRemove != 0)
						{
							warehouse = removeProduct(warehouse, count, idToRemove);
							cout << "\nProduct has been successfully removed from the warehouse!" << endl;
							showWarehouse(warehouse, count);

						}
						else if (idToRemove == 0)
						{
							cout << "\nExiting operation..." << endl;
						}
						else
						{
							cout << "\nProduct ID to remove has not been found. Please try again." << endl;

						}

					} while (idToRemove != 0);
				}
				else
				{
					cout << "\nProhibited to remove products from empty warehouse! Exiting operation..." << endl;
				}
				break;

			case 3:
				if (count != 0)
				{
					do {
						cout << "\nEnter ID product to change or 0 (to exit operation): ";
						cin >> idToChange;

						foundId = checkProductId(warehouse, count, idToChange);

						if (foundId && idToChange != 0)
						{
							cin.ignore();
							changeProduct(warehouse, count, idToChange);
							cout << "\nProduct has been successfully changed!" << endl;
							showWarehouse(warehouse, count);

						}
						else if (idToChange == 0)
						{
							cout << "\nExiting operation..." << endl;
						}
						else
						{
							cout << "\nProduct ID to change has not been found. Please try again." << endl;
						}

					} while (idToChange != 0);
				}
				else
				{
					cout << "\nProhibited to change products in empty warehouse! Exiting operation..." << endl;
				}
				break;

			case 4:
				if (count != 0)
				{
					do {
						cout << "\nEnter criteria for search (1 - by name, 2 - by manufacturer, 3 - by price, 4 - by category, 5 - by date of receipt, 6 - by date of expiry, 0 - to exit operation): ";
						cin >> searchChoice;
						if (searchChoice != 3 && searchChoice != 0)
						{
							cin.ignore();
						}

						if (searchChoice >= 1 && searchChoice <= 6)
						{
							switch (searchChoice) {
							case 1:
								char searchName[NAME_SIZE];
								cout << "\nEnter search name: ";
								cin.getline(searchName, NAME_SIZE);
								searchId = searchChar(warehouse, count, searchName, searchChoice);
								if (searchId != -1)
								{
									showProduct(warehouse[searchId - 1]);
								}
								else
								{
									cout << "\nProduct has not been found!" << endl;
								}
								break;

							case 2:
								char searchManufacturer[MANUFACTURER_SIZE];
								cout << "\nEnter search manufacturer's name: ";
								cin.getline(searchManufacturer, MANUFACTURER_SIZE);
								searchId = searchChar(warehouse, count, searchManufacturer, searchChoice);
								if (searchId != -1)
								{
									showProduct(warehouse[searchId - 1]);
								}
								else
								{
									cout << "\nProduct has not been found!" << endl;
								}
								break;

							case 3:
								float searchPrice;
								cout << "\nEnter search price: ";
								cin >> searchPrice;
								searchId = searchFloat(warehouse, count, searchPrice, searchChoice);
								if (searchId != -1)
								{
									showProduct(warehouse[searchId - 1]);
								}
								else
								{
									cout << "\nProduct has not been found!" << endl;
								}
								break;


							case 4:
								char searchCategory[CATEGORY_SIZE];
								cout << "\nEnter search category: ";
								cin.getline(searchCategory, CATEGORY_SIZE);
								searchId = searchChar(warehouse, count, searchCategory, searchChoice);
								if (searchId != -1)
								{
									showProduct(warehouse[searchId - 1]);
								}
								else
								{
									cout << "\nProduct has not been found!" << endl;
								}
								break;

							case 5:
								char searchDateOfReceipt[DATE_OF_RECEIPT_SIZE];
								cout << "\nEnter search date of receipt: ";
								cin.getline(searchDateOfReceipt, DATE_OF_RECEIPT_SIZE);
								searchId = searchChar(warehouse, count, searchDateOfReceipt, searchChoice);
								if (searchId != -1)
								{
									showProduct(warehouse[searchId - 1]);
								}
								else
								{
									cout << "\nProduct has not been found!" << endl;
								}
								break;

							case 6:
								char searchDateOfExpiry[DATE_OF_EXPIRY_SIZE];
								cout << "\nEnter search date of expiry: ";
								cin.getline(searchDateOfExpiry, DATE_OF_EXPIRY_SIZE);
								searchId = searchChar(warehouse, count, searchDateOfExpiry, searchChoice);
								if (searchId != -1)
								{
									showProduct(warehouse[searchId - 1]);
								}
								else
								{
									cout << "\nProduct has not been found!" << endl;
								}
								break;
							}
						}
						else if (searchChoice == 0)
						{
							cout << "\nExiting operation..." << endl;
						}
						else
						{
							cout << "\nEnter valid criteria for search!" << endl;
						}

					} while (searchChoice != 0);
				}
				else
				{
					cout << "\nProhibited to search for products in empty warehouse! Exiting operation..." << endl;
				}
				break;
			case 5:
				if (count != 0)
				{
					do {
						cout << "\nEnter criteria for sort (1 - by price, 2 - by category, 0 - to exit operation): ";
						cin >> sortChoice;

						if (sortChoice >= 1 && sortChoice <= 2)
						{
							switch (sortChoice) {
							case 1:
								sortByPrice(warehouse, count);
								cout << "\nWarehouse after sort by price: " << endl;
								showWarehouse(warehouse, count);
								break;

							case 2:
								sortByCategory(warehouse, count);
								cout << "\nWarehouse after sort by category: " << endl;
								showWarehouse(warehouse, count);
								break;
							}
						}
						else if (sortChoice == 0)
						{
							cout << "\nExiting operation..." << endl;
						}
						else
						{
							cout << "\nEnter valid criteria for sort!" << endl;
						}


					} while (sortChoice != 0);
				}
				else
				{
					cout << "\nProhibited to sort products in empty warehouse! Exiting operation..." << endl;
				}

			}
		}
		else if (choice == 0)
		{
			cout << "\nExiting programm..." << endl;
		}
		else
		{
			cout << "\nEnter valid operation for programm!" << endl;
		}

	} while (choice != 0);

	return 0;
}