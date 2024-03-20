#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <algorithm>

using namespace std;

enum ForeColour {
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
};

void setConsoleColor(ForeColour color) {
    cout << "\x1b[" << color << "m" << "■" << endl;
    cout << "\x1b[033m";
}

string decimalToBinary(int num) {
    if (num == 0) return "0";
    string binary = "";
    while (num > 0) {
        binary += (num % 2 == 0 ? "0" : "1");
        num /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

int main() {
    int num;
    string binary;

    cout << "\x1b[033m" << "아름다운 색!! 우왕" << endl;
    cout << "화면에 그림을 그리는 프로그램입니다." << endl;
    cout << "학번 : 202227058" << endl;
    cout << "이름 : 서은유" << endl;

    while (true) {
        cout << "화면에 그릴 물체코드를 입력하세요 : ";
        cin >> num;

        binary = decimalToBinary(num);

        if (binary == "1") {setConsoleColor(White);}
        else if (binary == "10") {setConsoleColor(Red);}
        else if (binary == "100") { setConsoleColor(Green); }
        else if (binary == "1000") { setConsoleColor(Yellow); }
        else if (binary == "10000") { setConsoleColor(Cyan); }
        else if (binary == "100000") { setConsoleColor(Magenta); }
        else if (binary == "1000000") { return 0; }
        else { return 0; }
    }

    return 0;
}
