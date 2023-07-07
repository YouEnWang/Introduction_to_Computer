// Programming Assignment 3: Big Number Calculator
#include <iostream>
#include <string>

using namespace std;

void read_number(string str, const int arraysize, int number[])
{
    for(int i = arraysize-1; i >= 0; i--)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            number[arraysize - i - 1] = str[i] - '0';
        }
        else
        {
            number[arraysize - i - 1] = str[i] - 'A' + 10;
        }
    }
}

void show_hex_answer(int answer[], string answer_hex, const int arraysize)
{
    // 將10進位轉換為各自的16進位(ex: 10 -> 'A')
    // 將數字反向存進string，即array從左至右各element的16進位會由右至左存進string
    // 此轉換可較方便的印出16進位的答案
    cout << "Result(hex): ";

    for(int i = 0; i < arraysize; i++)            // 將十進位的answer轉為十六進位
    {
        if(answer[i] >= 0 && answer[i] <= 9)
        {
            answer_hex[arraysize-i-1] = answer[i] + 48;
        }
        else
        {
            answer_hex[arraysize-i-1] = answer[i] + 65 - 10;
        }
    }

    int counter = 0;

    for(int i = 0; i < arraysize; i++)              // 尋找answer_hex從開頭起第幾個字母非0
    {
        if(answer_hex[i] == '0')
        {
            counter++;
        }
        else
        {
            break;
        }
    }

    if(counter < arraysize)
    {
        for(int i = counter; i < arraysize; i++)
        {
            cout << answer_hex[i];
        }
    }
    else
    {
        cout << "0";                                // 當answer_hex為0時，需要有辦法印出0
    }

    cout << "\n" << endl;
}

void addition(int a[], int b[], int answer[], const int arraysize)
{
    int carry = 0;
    string answer_hex;

    for(int i = 0; i < arraysize; i++)
    {
        answer[i] = a[i] + b[i] + carry;
        carry = answer[i]/16;                       // 計算相加後的進位
        answer[i] = answer[i]%16;                   // 將正確(小於16)的數值放進answer中
    }

    show_hex_answer(answer, answer_hex, arraysize);
}

void subtraction(int a[], int b[], int answer[], const int arraysize)
{
    int borrow = 0;
    string answer_hex;

    for(int i = 0; i < arraysize; i++)
    {
        answer[i] = a[i] - b[i] - borrow;
        if(answer[i] < 0)
        {
            borrow = 1;                             // 借16給下一位數，所以在下次的for-loop中會被多減1
            answer[i] += 16;                        // 若計算後為負數，則跟上一位數借16來相加
        }
        else
        {
            borrow = 0;
        }
    }

    show_hex_answer(answer, answer_hex, arraysize);
}

void multiplication(int a[], int b[], int answer[], const int arraysize)
{
    int carry = 0;
    string answer_hex;

    for(int i = 0; i < arraysize; i++)
    {
        if(a[i] == 0)
        {
            continue;
        }
        for(int j = 0; i+j < arraysize; j++)
        {
            answer[i+j] = answer[i+j] + a[i]*b[j];
        }
    }

    for(int k = 0; k < arraysize; k++)
    {
        answer[k] += carry;                               // 將數值加上進位
        carry = answer[k]/16;                             // 計算相乘後的進位
        answer[k] = answer[k]%16;                         // 將正確(小於16)的數值放進answer中
    }

    show_hex_answer(answer, answer_hex, arraysize);
}

bool handle_out_of_range(string str, const int arraysize)
{
    bool correct_number = true;

    for(int i = 0; i < arraysize; i++)
    {
        if(str[0] == '-')                                    // 錯誤的輸入number，回傳false
        {
            correct_number = false;
            break;
        }
        else if((str[i] >= '0' && str[i] <= '9') || str[i] == 'A' || str[i] == 'B' || str[i] == 'C' || str[i] == 'D' || str[i] == 'E' || str[i] == 'F')
        {
            continue;
        }
        else
        {
            correct_number = false;                         // 錯誤的輸入number，回傳false
            break;
        }
    }
    return correct_number;
}

int main()
{
    int selection = 0;

    while(true)
    {
        string str1;
        string str2;
        int arraysize = 0;

        cout << "----Welcome to big number calculator----" << endl;
        cout << "Please choose the function" << endl;
        cout << "0. Exit" << endl << "1. Addition" << endl << "2. Subtraction" << endl << "3. Multiplication" << endl;
        cout << "--------------------------" << endl;
        cin >> selection;
        while(selection != 0 && selection != 1 && selection != 2 && selection != 3)
        {
            cout << "Error! Please try again." << endl;
            cout << endl;
            cout << "----Welcome to big number calculator----" << endl;
            cout << "Please choose the function" << endl;
            cout << "0. Exit" << endl << "1. Addition" << endl << "2. Subtraction" << endl << "3. Multiplication" << endl;
            cout << "--------------------------" << endl;
            cin >> selection;
        }

        if (selection == 1)
        {
            int a[100] = {};
            int b[100] = {};
            int answer[200] = {};
            bool correct_range1 = true;
            bool correct_range2 = true;

            cout << endl;
            cout << "----Now for Addition----" << endl;
            cout << "Please enter the two numbers(hex)." << endl;
            cin >> str1;
            cin >> str2;

            correct_range1 = handle_out_of_range(str1, str1.length());
            correct_range2 = handle_out_of_range(str2, str2.length());

            while(correct_range1 == false || correct_range2 == false)
            {
                cout << "Please enter the two numbers(hex) again." << endl;
                cin >> str1;
                cin >> str2;
                correct_range1 = handle_out_of_range(str1, str1.length());
                correct_range2 = handle_out_of_range(str2, str2.length());
            }

            if(str1.length() >= str2.length())                       // 判斷哪一個輸入的number較長，並將其設為arraysize
            {
                arraysize = str1.length()+1;
            }
            else
            {
                arraysize = str2.length()+1;
            }

            read_number(str1, str1.length(), a);
            read_number(str2, str2.length(), b);
            addition(a, b, answer, arraysize);
        }
        else if (selection == 2)
        {
            int a[100] = {};
            int b[100] = {};
            int answer[200] = {};
            bool correct_range1 = true;
            bool correct_range2 = true;

            cout << endl;
            cout << "----Now for Subtraction----" << endl;
            cout << "Please enter the two numbers(hex)." << endl;
            cin >> str1;
            cin >> str2;

            correct_range1 = handle_out_of_range(str1, str1.length());
            correct_range2 = handle_out_of_range(str2, str2.length());

            while(correct_range1 == false || correct_range2 == false)
            {
                cout << "Please enter the two numbers(hex) again." << endl;
                cin >> str1;
                cin >> str2;
                correct_range1 = handle_out_of_range(str1, str1.length());
                correct_range2 = handle_out_of_range(str2, str2.length());
            }

            if(str1.length() >= str2.length())                       // 判斷哪一個輸入的number較長，並將其設為arraysize
            {
                arraysize = str1.length();
            }
            else
            {
                arraysize = str2.length();
            }

            read_number(str1, str1.length(), a);
            read_number(str2, str2.length(), b);
            subtraction(a, b, answer, arraysize);
        }
        else if (selection == 3)
        {
            int a[100] = {};
            int b[100] = {};
            int answer[200] = {};
            bool correct_range1 = true;
            bool correct_range2 = true;

            cout << endl;
            cout << "----Now for Multiplication----" << endl;
            cout << "Please enter the two numbers(hex)." << endl;
            cin >> str1;
            cin >> str2;

            correct_range1 = handle_out_of_range(str1, str1.length());
            correct_range2 = handle_out_of_range(str2, str2.length());

            while(correct_range1 == false || correct_range2 == false)
            {
                cout << "Please enter the two numbers(hex) again." << endl;
                cin >> str1;
                cin >> str2;
                correct_range1 = handle_out_of_range(str1, str1.length());
                correct_range2 = handle_out_of_range(str2, str2.length());
            }

            arraysize = str1.length() + str2.length();              // arraysize為兩個number(str1與str2)的長度相加

            read_number(str1, str1.length(), a);
            read_number(str2, str2.length(), b);
            multiplication(a, b, answer, arraysize);
        }
        else
        {
            cout << "Good bye!" << endl;
            break;
        }
    }

    return 0;
}
