#include <iostream>
using namespace std;


const int COLOR_SIZE = 20;
struct Auto
{
	float lengthInMetres;
	float clearanceInSantimetres;
	float engineVolumeInLitres;
	float horsePower;
	float wheelDiameterInSantimetres;
	char color[COLOR_SIZE];
	char gearbox[COLOR_SIZE];
};


void fillAuto(Auto& car)
{
	cout << "Enter car's length in metres: ";
	cin >> car.lengthInMetres;
	cout << "Enter car's clearance in santimetres: ";
	cin >> car.clearanceInSantimetres;
	cout << "Enter car's engine volume in litres: ";
	cin >> car.engineVolumeInLitres;
	cout << "Enter car's horsePower: ";
	cin >> car.horsePower;
	cout << "Enter car's wheel diameter in santimetres: ";
	cin >> car.wheelDiameterInSantimetres;
	cout << "Enter car's color: ";
	cin >> car.color;
	cout << "Enter car's gearbox: ";
	cin >> car.gearbox;
}

void showAuto(const Auto& car)
{
	cout << "Car's lenght in metres: " << car.lengthInMetres << endl;
	cout << "Car's clearance in santimetres: " << car.clearanceInSantimetres << endl;
	cout << "Car's engine volume in litres: " << car.engineVolumeInLitres << endl;
	cout << "Car's horsePower: " << car.horsePower << endl;
	cout << "Car's wheel diameter in santimetres: " << car.wheelDiameterInSantimetres << endl;
	cout << "Car's color: " << car.color << endl;
	cout << "Car's gearbox: " << car.gearbox << endl;
}

void sortingByColorAsc(Auto* cars, unsigned int n)
{
	

	for (size_t i = 0; i < n - 1; i++)
	{
		for (size_t j = 0; j < n - 1 - i; j++)
		{
			if (strcmp(cars[j].color, cars[j + 1].color) == 1)
			{
				swap(cars[j], cars[j + 1]);
			}

		}
	}
}


void changeRegisterColorAndGear(Auto* cars, unsigned int n)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j=0; j<strlen(cars[i].color); j++)
			if (cars[i].color[j] >= 'A' && cars[i].color[j] <= 'Z')
			{
				cars[i].color[j] = cars[i].color[j] + 32;
			}
		for (size_t j = 0; j < strlen(cars[i].gearbox); j++)
			if (cars[i].gearbox[j] >= 'A' && cars[i].gearbox[j] <= 'Z')
			{
				cars[i].gearbox[j] = cars[i].gearbox[j] + 32;
			}
	}
}

void findCarColor(Auto* cars, unsigned int n, const char* color)
{
	bool found = false;
	for (size_t i = 0; i < n; i++)
	{
		if (strcmp(cars[i].color, color) == 0)
		{
			cout << "Car by color " << color << " found: " << endl;
			showAuto(cars[i]);
			found = true;
		}
	}
}


int main()
{
	unsigned int n;
	cout << "Enter number of cars: ";
	cin >> n;
	Auto* cars = new Auto[n];

	for (size_t i = 0; i < n; i++)
	{
		cout << "Enter parameters of car #" << i + 1 << ": " << endl;
		fillAuto(cars[i]);
	}

	for (size_t i = 0; i < n; i++)
	{
		cout << "Parameters of car#" << i + 1 << ": " << endl;
		showAuto(cars[i]);
	}

	changeRegisterColorAndGear(cars, n);


	sortingByColorAsc(cars, n);

	cout << "Sorted cars by color in ascending order: " << endl;

	for (size_t i = 0; i < n; i++)
	{
		cout << "Parameters of car#" << i + 1 << ": " << endl;
		showAuto(cars[i]);
	}
	
	const int COLOR_SIZE = 20;
	char color[COLOR_SIZE];
	cout << "Enter color to find car: ";
	cin >> color;

	findCarColor(cars, n, color);

	delete[] cars;
	return 0;

}