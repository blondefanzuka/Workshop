#include<iostream>
#include<cmath>
using namespace std;

//Print out whatever arrays of bits we want
void printer(int* bits, int* size) {
	for (int* output = bits; output < bits + *size; output++) {
		cout << *output;
	}
	cout << endl;
}

//Flips each bit and stores the result in a separate array
void flip(int* binary, int* flipped, int* size) {
	int* flipper = flipped;

	for (int* flippee = binary; flippee < binary + *size; flippee++, flipper++) {
		if (*flippee == 0) {
			*flipper = 1;
		}
		else *flipper = 0;
	}
}

//Adds 1 to the given binary number
void oneAdder(int* flipped, int* binary, int* size) {
	int* carry = new int{ 1 };
	int* f = flipped + *size;
	int* b = binary + *size;

	//Start from the rightmost bit since that's where addition begins
	while (b > binary) {
		f--;
		b--;
		*b = (*f + *carry) % 2; //This checks the sum of the numbers (2 assigns 0 while 1 assigns 1)
		*carry = (*f + *carry) / 2; //Saves the carry for the next addition
	}

	delete carry;
}

//Convert the signed decimal number into binary 
void toBinary(long long* num, int* binary, int* size) {
	unsigned long long* numPos = new unsigned long long; //We use unsigned because otherwise we don't get the proper minimum

	//Get the positive value first, even for the smallest 64-bit number 
	//(That's why we first add 1, then make it negative and then add it back)
	if (*num < 0)
	{
		*numPos = -(*num + 1);
		(*numPos)++;
	}
	else
		*numPos = *num;

	int* last = new int{ *size - 1 };
	//Repeatedly divide by 2 and fill the array from right to left
	while (*numPos != 0) {
		binary[*last] = *numPos % 2;
		*numPos = *numPos / 2;
		(*last)--;
	}

	//Negative numbers need to be converted using two's complement
	if (*num < 0) {
		int* flipped = new int[*size]();
		flip(binary, flipped, size);
		oneAdder(flipped, binary, size);
		delete[]flipped;
	}

	delete last;
	delete numPos;
}

//Checks if the number fits and handles the three conversions
void converter(long long* num, int* size) {
	//No extra range check needed for 64 bits since we're using long long
	if (*size != 64 && (*num > (pow(2, *size - 1) - 1) || *num < -pow(2, *size - 1))) {
		cout << "The given number can't convert to " << *size << "-bits" << endl;
		return;
	}

	//Initialize all arrays with zeros so the output has the correct number of bits
	int* binary = new int[*size]();
	int* ones = new int[*size]();
	int* twos = new int[*size]();
	// Call all the needed functions
	toBinary(num, binary, size);
	flip(binary, ones, size);
	oneAdder(ones, twos, size);
	//Output all the calculations
	cout << "Binary: ";
	printer(binary, size);
	cout << "One's complement: ";
	printer(ones, size);
	cout << "Two's complement: ";
	printer(twos, size);

	//Free the memory used by the arrays
	delete[] binary;
	delete[] ones;
	delete[] twos;
}

//The main menu which manages what bit and number we are working on. Keeps running until the user chooses to exit
void Menu() {
	while (true) {
		cout << "----------------Bit level manipulator----------------" << endl;
		cout << "Choose your bit option (4, 8, 16, 32, 64) or type 0 to exit: ";
		int* choice = new int;

		//Check if the input is valid and matches the bits we are working on
		while (!(cin >> *choice) || (*choice != 4 && *choice != 8 && *choice != 16 && *choice != 32 && *choice != 64 && *choice != 0)) {
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "Invalid choice, please enter a valid option: ";
		}

		//Checks if they want to exit the program
		if (*choice == 0) {
			delete choice;
			return;
		}

		cout << "Enter your decimal number to convert into a " << *choice << "-bit number: ";
		long long* num = new long long;

		//Make sure the decimal input is valid before converting
		while (!(cin >> *num)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid choice, please enter a valid number: ";
		}
		converter(num, choice);
		delete num;
		delete choice;
		
		//We check if the user would like to continue calculating or exit out of the program
		char* repeat = new char;
		while (true) {
			cout << "Would you like to perform another calculation? Enter y or n: ";
			cin >> *repeat;
			if (*repeat == 'y' || *repeat == 'Y' ||*repeat == 'n' || *repeat == 'N') 
				break;
			else
			cout << "Please type y or n" << endl;
		}

		if (*repeat == 'n' || *repeat == 'N') {
			delete repeat;
			break;
		}

		delete repeat;
	}
}

int main()
{
	Menu();
}
