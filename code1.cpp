#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

double extractNumeric (const string& str) {
    double num=0, sign=1, decimal=0;
    int decimCount=0;
    //first checks for any bad input such as: misplaced sign, multiple decimal, unrecognized letters
    for (int i=0; i < str.length(); i++) {
        //checks for unregcognized characters
        if (!(isdigit(str[i])) && str[i] != '+' && str[i] != '-' && str[i] != '.') {
            return -999999.99;
        }

        if (i > 0) {
            //checks after the first index for misplaced signs
            if (str[i] == '+' || str[i] == '-') {
                return -999999.99;
            }
        }
        if (str[i] == '.') {
            //counts for if there's more than 1 decimal
            decimCount++;
        }
    }
    if (decimCount > 1) {
        return -999999.99;
    }

    //assigns sign for extracted number
    if (str[0] == '-') {
        sign = -1;
    }
    else {
        sign = 1;
    }

    float x = 1;    //acts as a place value for digits in the number
    for (int i=str.length()-1; i >= 0; i--) {
        //iterates from right to left
        if (str[i] == '+' || str[i] == '-') {
            //assuming good input, once the sign is reached, will break, else, will end naturally once first index is reached
            break;
        }
        else if (isdigit(str[i])) {
            //adds each digit by their place value one by one
            num = num + (str[i] - '0') * x; //str[i] - '0' converts the char to an int for calculation
        }
        else {
            //assuming good input, only other possibility is a decimal
            decimal = num;
            for (int i=1; i<x; i=i*10) {
                //puts a decimal infront of the so far obtained number, making up the right portion of the decimal
                decimal = decimal/10;
            }
            num=0;  //resets num to 0 for left side
            x=0.1;  //sets x to 0.1 to start at 10 for next iteration
        }
        x = x * 10;
    }

    return sign*(num+decimal);
}

int main() {
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double number = extractNumeric(input);

        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        }
        else {
            cout << "The input is invalid." << endl;
        }
    }
    return 0;
}