#pragma once

const int NAME_SIZE = 50;
const int MANUFACTURER_SIZE = 50;
const int CATEGORY_SIZE = 50;
const int DATE_OF_RECEIPT_SIZE = 10;
const int DATE_OF_EXPIRY_SIZE = 10;

struct Product // Product object structure
{
	char name[NAME_SIZE];
	char manufacturer[MANUFACTURER_SIZE];
	char category[CATEGORY_SIZE];
	char dateOfReceipt[DATE_OF_RECEIPT_SIZE];
	char dateOfExpiry[DATE_OF_EXPIRY_SIZE];
	float price;
	size_t id;

};

void fillProductId(Product* warehouse, size_t count) // Filling product ID in order after operations of addition and removal
{
	for (size_t i = 0; i < count; i++)
	{
		warehouse[i].id = i + 1;
	}
}

void fillProduct(Product& product) // Filling product with user input data. Id is populated automatically through function addProduct()
{
	cout << "Enter product name: ";
	cin.getline(product.name, NAME_SIZE);
	cout << "Enter manufacturer: ";
	cin.getline(product.manufacturer, MANUFACTURER_SIZE);
	cout << "Enter category: ";
	cin.getline(product.category, CATEGORY_SIZE);
	cout << "Enter date of receipt (DD.MM.YYYY): ";
	cin.getline(product.dateOfReceipt, DATE_OF_RECEIPT_SIZE);
	cout << "Enter date of expiry (DD.MM.YYYY): ";
	cin.getline(product.dateOfExpiry, DATE_OF_EXPIRY_SIZE);
	cout << "Enter price: ";
	cin >> product.price;
	cin.ignore();

}

Product* addProduct(Product* warehouse, size_t& count, size_t productsToAdd)
{
	if (warehouse != nullptr)
	{
		Product* newWarehouse = new Product[count + productsToAdd];

		for (size_t i = 0; i < (count + productsToAdd); i++)
		{
			if (i < count)
			{
				newWarehouse[i] = warehouse[i];
			}
			else
			{
				fillProduct(newWarehouse[i]);
			}
		}

		delete[] warehouse;
		warehouse = newWarehouse;
		count += productsToAdd;
		fillProductId(warehouse, count);
	}

	else
	{
		cout << "Warehouse doesn't exist!";
	}

	return warehouse;
}




void showProduct(const Product& product) // Displaying product information
{
	cout << "Product ID: " << product.id << endl;
	cout << "Product name: " << product.name << endl;
	cout << "Manufacturer: " << product.manufacturer << endl;
	cout << "Category: " << product.category << endl;
	cout << "Date of receipt: " << product.dateOfReceipt << endl;
	cout << "Date of expiry: " << product.dateOfExpiry << endl;
	cout << "Price: " << product.price << endl;
}


void showWarehouse(Product* warehouse, size_t count) // Displaying all products
{
	cout << "\nCurrently in the warehouse: " << count << " products: " << endl;

	for (size_t i = 0; i < count; i++)
	{
		cout << "Product #" << i + 1 << ": " << endl;
		showProduct(warehouse[i]);
		cout << endl;
	}

}

bool checkProductId(Product* warehouse, size_t count, size_t idToRemove) // Checking product ID for its existence
{
	bool found = false;

	for (size_t i = 0; i < count; i++)
	{
		if (warehouse[i].id == idToRemove)
		{
			found = true;
		}
	}

	return found;
}

Product* removeProduct(Product* warehouse, size_t& count, size_t idToRemove) // Removing product by ID
{
	if (warehouse != nullptr)
	{
		--count;
		Product* newWarehouse = new Product[count];

		for (size_t i = 0, j = 0; j < count; i++)
		{
			if (warehouse[i].id != idToRemove)
			{
				newWarehouse[j++] = warehouse[i];

			}

		}

		delete[] warehouse;
		warehouse = newWarehouse;
		fillProductId(warehouse, count);
	}
	else
	{
		cout << "Warehouse doesn't exist!";
	}

	return warehouse;
}

void changeProduct(Product* warehouse, size_t count, size_t idToChange) // Changing product by ID
{
	for (size_t i = 0; i < count; i++)
	{
		if (warehouse[i].id == idToChange)
		{
			fillProduct(warehouse[i]);
		}
	}
}

int searchChar(Product* warehouse, size_t count, const char* criteria, int searchChoice) // Searching product by char type of field
{
	for (size_t i = 0; i < count; i++)
	{
		switch (searchChoice) {
		case 1:

			if (strcmp(warehouse[i].name, criteria) == 0) {
				return warehouse[i].id;
			}
			break;

		case 2:

			if (strcmp(warehouse[i].manufacturer, criteria) == 0) {
				return warehouse[i].id;
			}
			break;

		case 4:

			if (strcmp(warehouse[i].category, criteria) == 0) {
				return warehouse[i].id;
			}
			break;

		case 5:

			if (strcmp(warehouse[i].dateOfReceipt, criteria) == 0) {
				return warehouse[i].id;
			}
			break;

		case 6:

			if (strcmp(warehouse[i].dateOfExpiry, criteria) == 0) {
				return warehouse[i].id;
			}
			break;
		}

	}

	return -1;

}

int searchFloat(Product* warehouse, size_t count, float criteria, int searchChoice) // Searching product by float type of field
{
	for (size_t i = 0; i < count; i++)
	{
		if (searchChoice == 3 && warehouse[i].price == criteria) {
			return warehouse[i].id;
		}
	}

	return -1;
}

void sortByPrice(Product* warehouse, size_t count) // Sorting by price
{
	for (size_t i = 0; i < count - 1; i++)
	{
		for (size_t j = 0; j < count - 1 - i; j++)
		{
			if (warehouse[j].price > warehouse[j + 1].price) {
				Product temp = warehouse[j];
				warehouse[j] = warehouse[j + 1];
				warehouse[j + 1] = temp;
			}
		}
	}

	fillProductId(warehouse, count);
}

void sortByCategory(Product* warehouse, size_t count) // Sorting by category
{
	for (size_t i = 0; i < count - 1; i++)
	{
		for (size_t j = 0; j < count - 1 - i; j++)
		{
			if (strcmp(warehouse[j].category, warehouse[j + 1].category) > 0) {
				Product temp = warehouse[j];
				warehouse[j] = warehouse[j + 1];
				warehouse[j + 1] = temp;
			}
		}
	}

	fillProductId(warehouse, count);
}