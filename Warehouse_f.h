#pragma once

const int NAME_SIZE = 50;
const int MANUFACTURER_SIZE = 50;
const int CATEGORY_SIZE = 30;
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

void fillProductEmpty(Product& product) // Filling product ID with zero value in order to count empty products in the warehouse at the beginning
{
	product.id = 0;
	strcpy_s(product.name, "");
	strcpy_s(product.manufacturer, "");
	strcpy_s(product.category, "");
	strcpy_s(product.dateOfReceipt, "");
	strcpy_s(product.dateOfExpiry, "");
	product.price = 0.0f;

}

void fillWarehouseEmpty(Product* warehouse, size_t capacity) // Filling the whole warehouse with empty products
{
	for (size_t i = 0; i < capacity; i++)
	{
		fillProductEmpty(warehouse[i]);
	}
}

size_t countExistingProducts(Product* warehouse, size_t capacity) // Counting existing products in the warehouse by checking product IDs
{
	size_t count = 0;
	for (size_t i = 0; i < capacity; i++)
	{
		if (warehouse[i].id != 0)
		{
			count++;
		}
	}

	return count;
}


void fillProduct(Product& product) // Filling product with user input data. Id is populated automatically through function addProduct()
{
	cin.ignore();
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

}

void fillProductId(Product* warehouse, size_t count) // Filling product ID in order after operations of addition and removal
{
	for (size_t i = 0; i < count; i++)
	{
		warehouse[i].id = i + 1;
	}
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

void showWarehouse(Product* warehouse, size_t count) // Displaying all products in the warehouse
{
	for (size_t i = 0; i < count; i++)
	{
		cout << "Product #" << i + 1 << ": " << endl;
		showProduct(warehouse[i]);
		cout << endl;
	}
	cout << "\nCurrently in the warehouse: " << countExistingProducts(warehouse, count) << " products." << endl;
}

Product* addProduct(Product* warehouse, size_t& capacity, size_t& count, size_t productsToAdd) // Adding products to the warehouse. If there is not enough capacity, 
// then creating a new warehouse with adding products from old warehouse and adding new products
{
	if (warehouse != nullptr)
	{
		if (count + productsToAdd <= capacity)
		{
			for (size_t i = 0; i < productsToAdd; i++)
			{
				fillProduct(warehouse[count + i]);
			}

			count += productsToAdd;

			fillProductId(warehouse, count);
		}
		else
		{
			size_t newCapacity = count + productsToAdd;
			Product* newWarehouse = new Product[newCapacity];

			for (size_t i = 0; i < newCapacity; i++)
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
			capacity = newCapacity;
			count += productsToAdd;

			fillProductId(warehouse, count);
		}
	}

	else
	{
		cout << "Warehouse doesn't exist!";
	}

	return warehouse;
}


Product* removeProduct(Product* warehouse, size_t& capacity, size_t& count, size_t idToRemove) // Removing product by ID in the warehouse
{
	if (count == 0) {
		return warehouse;
	}
	else {
		size_t newCapacity = --count;
		Product* newWarehouse = new Product[newCapacity];

		for (size_t i = 0, j = 0; j < newCapacity; i++)
		{
			if (warehouse[i].id != idToRemove)
			{
				newWarehouse[j++] = warehouse[i];

			}

		}

		delete[] warehouse;
		warehouse = newWarehouse;
		capacity = newCapacity;

		return warehouse;
	}
		
}

bool checkProductId(Product* warehouse, size_t capacity, size_t idToRemove) // Checking product ID for its existence in the warehouse
{
	bool found = false;

	for (size_t i = 0; i < capacity; i++)
	{
		if (warehouse[i].id == idToRemove)
		{
			found = true;
		}
	}

	return found;
}

void changeProduct(Product* warehouse, size_t capacity, size_t idToChange) // Changing product
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (warehouse[i].id == idToChange)
		{
			fillProduct(warehouse[i]);
		}
	}
}


int searchChar(Product* warehouse, size_t capacity, const char* criteria, int searchChoice) // Searching product by char type of field
{
	for (size_t i = 0; i < capacity; i++)
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

int searchFloat(Product* warehouse, size_t capacity, float criteria, int searchChoice) // Searching product by float type of field
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (searchChoice == 3 && warehouse[i].price == criteria) {
			return warehouse[i].id;
		}
	}

	return -1;
}

void sortByPrice(Product* warehouse, size_t capacity) // Sorting by price
{
	for (size_t i = 0; i < capacity - 1; i++)
	{
		for (size_t j = 0; j < capacity - 1 - i; j++)
		{
			if (warehouse[j].price > warehouse[j + 1].price) {
				Product temp = warehouse[j];
				warehouse[j] = warehouse[j + 1];
				warehouse[j + 1] = temp;
			}
		}
	}
}

void sortByCategory(Product* warehouse, size_t capacity) // Sorting by category
{
	for (size_t i = 0; i < capacity - 1; i++)
	{
		for (size_t j = 0; j < capacity - 1 - i; j++)
		{
			if (strcmp(warehouse[j].category, warehouse[j + 1].category) > 0) {
				Product temp = warehouse[j];
				warehouse[j] = warehouse[j + 1];
				warehouse[j + 1] = temp;
			}
		}
	}
}
