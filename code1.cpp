#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

double extractNumeric (const string& str) {
    double num=0, sign=1, decimal=0;
    int decimCount=0;
    //first checks for any bad input such as: misplaced sign, multiple decimal, unrecognized letters
    for (int i=0; i < str.length(); i++) {
        //checks if first index is bad input
        if (!(isdigit(str[0])) && str[0] != '+' && str[0] != '-' && str[0] != '.') {
            return -999999.99;
        }

        if (i > 0) {
            //checks after the first index for misplaced signs and bad input
            if (str[i] == '+' || str[i] == '-') {
                return -999999.99;
            }

            else if (!(isdigit(str[i])) && str[i] != '.') {
                return -999999.99;
            }
        }
        if (str[i] == '.') {
            decimCount++;
        }
    }
    if (decimCount > 1) {
        return -999999.99;
    }

    if (str[0] == '-') {
        sign = -1;
    }
    else {
        sign = 1;
    }

    float x = 1;
    for (int i=str.length()-1; i >= 0; i--) {
        if (str[i] == '+' || str[i] == '-') {
            break;
        }
        else if (isdigit(str[i])) {
            num = num + (str[i] - '0') * x;
        }
        else {
            decimal = num;
            for (int i=1; i<x; i=i*10) {
                decimal = decimal/10;
            }
            num=0;
            x=0.1;
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