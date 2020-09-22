#include <iostream>
#include <string>
#include <sstream>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;
bool is_larger(string lhs, string rhs) {
    for (int i = 0; i < static_cast<int>(lhs.size()); i++) {
        if (rhs.at(i) < lhs.at(i)) {
            return true;
        }
        else if (rhs.at(i) > lhs.at(i)) {
            return false;
        }
    }
    return true;
}
unsigned int digit_to_decimal(char digit) {
    if (digit < 48 || digit > 57) {
        throw std::invalid_argument("");
    }
    return digit - 48;
}

char decimal_to_digit(unsigned int decimal) {
    if (decimal > 9) {
        throw std::invalid_argument("");
    }
    return static_cast<char>(decimal + 48);
}

string trim_leading_zeros(string num) {
    int counter = 0;
    bool other = false;
    int index = 0;
    if (num.at(0) == '-') {
            index++;
        }
    for(int i = index; i < static_cast<int>(num.size()); i++) {
        if (num.at(i) == '0') {
            counter++;
        }
        else {
            other = true;
            break;
        }
    }
    if (!other) {
        return "0";
    }
    if (counter >= 1) {
        return num.replace(num.find('0'), counter, "");
    }
    return num;
}
string add(string lhs, string rhs) {
    string result = "";
    if (lhs.at(0) != '-' && rhs.at(0) != '-') {
        lhs = trim_leading_zeros(lhs);
        rhs = trim_leading_zeros(rhs);
        int carry = 0;
        for (int i = 1; i <= static_cast<int>(std::min(lhs.size(), rhs.size())); i++) {
            int tempNum = digit_to_decimal(lhs.at(lhs.size() - i)) + digit_to_decimal(rhs.at(rhs.size() - i)) + carry;
            result.replace(0, 0, " ");
            result.at(0) = decimal_to_digit(tempNum % 10);
            carry = tempNum / 10;
        }
        for (int j = static_cast<int>(rhs.size()) + 1; j <= static_cast<int>(lhs.size()); j++) {
            int tempLeftNum = digit_to_decimal(lhs.at(lhs.size() - j)) + carry; 
            result.replace(0, 0, " ");
            result.at(0) = decimal_to_digit(tempLeftNum % 10);
            carry = tempLeftNum / 10;
        }
        for (int k = static_cast<int>(lhs.size()) + 1; k <= static_cast<int>(rhs.size()); k++) {
            int tempRightNum = digit_to_decimal(rhs.at(rhs.size() - k)) + carry; 
            result.replace(0, 0, " ");
            result.at(0) = decimal_to_digit(tempRightNum % 10);
            carry = tempRightNum / 10;
        }
        if (carry != 0) {
            result.replace(0, 0, " ");
            result.at(0) = decimal_to_digit(carry);
        }
    }
    else if (lhs.at(0) == '-' && rhs.at(0) == '-') {
        result = "-";
        result.append(add(lhs.replace(0, 1, ""), rhs.replace(0, 1, "")));
    }
    else if(lhs.at(0) == '-') {
        result = subtract(rhs,lhs.replace(0, 1, ""));
    }
    else {
        result = subtract(lhs, rhs.replace(0, 1, ""));
    }
    return result;
}

string subtract(string lhs, string rhs) {
    string result = "";
    if (lhs.at(0) != '-' && rhs.at(0) != '-') {
        lhs = trim_leading_zeros(lhs);
        rhs = trim_leading_zeros(rhs);
        if((lhs.size() > rhs.size()) || ((lhs.size() == rhs.size()) && (is_larger(lhs, rhs)))) {
            int carry = 0;
            for (int i = 1; i <= static_cast<int>(std::min(lhs.size(), rhs.size())); i++) {
                int tempNum = (digit_to_decimal(lhs.at(lhs.size() - i)) + carry + 10) - digit_to_decimal(rhs.at(rhs.size() - i));
                result.replace(0, 0, " ");
                result.at(0) = decimal_to_digit(tempNum % 10);
                carry = tempNum / 10 - 1;
            }
            for (int j = static_cast<int>(rhs.size()) + 1; j <= static_cast<int>(lhs.size()); j++) {
                int tempLeftNum = digit_to_decimal(lhs.at(lhs.size() - j)) + 10 + carry; 
                result.replace(0, 0, " ");
                result.at(0) = decimal_to_digit(tempLeftNum % 10);
                carry = tempLeftNum / 10 - 1;
            }
            result = trim_leading_zeros(result); 
        }
        else {
            result = "-";
            result.append(subtract(rhs, lhs));
        }
    }
    else if (lhs.at(0) == '-' && rhs.at(0) == '-') {
        result = subtract(rhs.replace(0, 1, ""), lhs.replace(0, 1, ""));
    }
    else if (lhs.at(0) == '-') {
        result = add(lhs, rhs.replace(0, 0, "-"));
    }
    else {
        result = add(lhs, rhs.replace(0, 1, ""));
    }
    return result;
}
string multiply(string lhs, string rhs) {
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    string sign = "";
    if ((lhs.at(0) == '-' || rhs.at(0) == '-') && !(lhs.at(0) == '-' && rhs.at(0) == '-')) {
        sign = "-";
    }
    if (lhs.at(0) == '-') {
        lhs.replace(0, 1, "");
    }
    if (rhs.at(0) == '-') {
        rhs.replace(0, 1, "");
    }
    int power = 0;
    string result = "0";
    while (power < static_cast<int>(rhs.size())) {
        string tempRes = "0";
        for (int i = 0; i < static_cast<int>(digit_to_decimal(rhs.at(static_cast<int>(rhs.size()) - power - 1))); i++) {
            tempRes = add(tempRes, lhs);
        }
        for (int j = 0; j < power; j++) {
            tempRes.append("0");
        }
        result = add(result, tempRes);
        power++;
    }
    result.replace(0, 0, sign);
    return result;
}
