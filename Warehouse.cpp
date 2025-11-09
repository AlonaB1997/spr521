#include <iostream>
using namespace std;


const int NAME_SIZE = 50;
const int MANUFACTURER_SIZE = 50;
const int CATEGORY_SIZE = 30;
const int DATE_OF_RECEIPT_SIZE = 10;
const int DATE_OF_EXPIRY_SIZE = 10;

struct Product // Product object structure
{
	int id;
	char name[NAME_SIZE];
	char manufacturer[MANUFACTURER_SIZE];
	char category[CATEGORY_SIZE];
	char dateOfReceipt[DATE_OF_RECEIPT_SIZE];
	char dateOfExpiry[DATE_OF_EXPIRY_SIZE];
	float price;

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


void fillProduct(Product& product) // Filling product with user input data. Checking for positive product ID
{
	cout << "Enter product ID (positive value): ";
	do {
		cin >> product.id;
		if (product.id <= 0)
		{
			cout << "Product ID cannot be zero or less than zero. Please enter again: ";
		}
	}
	while (product.id <= 0);
	cout << "Enter product name: ";
	cin >> product.name;
	cout << "Enter manufacturer: ";
	cin >> product.manufacturer;
	cout << "Enter category: ";
	cin >> product.category;
	cout << "Enter date of receipt (DD.MM.YYYY): ";
	cin >> product.dateOfReceipt;
	cout << "Enter date of expiry (DD.MM.YYYY): ";
	cin >> product.dateOfExpiry;
	cout << "Enter price: ";
	cin >> product.price;

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
	}
}

Product* addProduct(Product* warehouse, size_t& capacity, size_t& count, size_t productsToAdd) // Adding products to the warehouse. If there is not enough capacity, 
																							   // then creating a new warehouse with adding products from old warehouse and adding new products
{
	if (count + productsToAdd <= capacity)
	{
		for (size_t i = 0; i < productsToAdd; i++)
		{
			fillProduct(warehouse[count + i]);
		}
		count += productsToAdd;
	}
	else
	{
		size_t newCapacity = count + productsToAdd;
		Product* newWarehouse = new Product[newCapacity];

		for (size_t i = 0; i < count; i++)
		{
			newWarehouse[i] = warehouse[i];
		}

		delete[] warehouse;
		warehouse = newWarehouse;
		capacity = newCapacity;

		for (size_t i = 0; i < productsToAdd; i++)
		{
			fillProduct(warehouse[count + i]);
		}
		count += productsToAdd;
	}

	return warehouse;
}





int main()
{
	int choice; 
	size_t capacity, count, productsToAdd;	
	cout << "Enter warehouse capacity: ";
	cin >> capacity;

	Product* warehouse = new Product[capacity]; // Creating warehouse with given capacity

	fillWarehouseEmpty(warehouse, capacity); // Filling warehouse with empty products
	
	count = countExistingProducts(warehouse, capacity); // Counting existing products in the warehouse for future checks

	
	do
	{	
		cout << "Choose operation (1 - Add product, 2 - Remove product, 3 - Change product, 4 - Search product, 5 - Sort products, 0 - Exit): ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter number of products to add: ";
			cin >> productsToAdd;
			warehouse = addProduct(warehouse, capacity, count, productsToAdd);
			cout << "Products in the warehouse after addition: " << endl;
			showWarehouse(warehouse, count);
		}

	}
	while (choice != 0);







	return 0;
}