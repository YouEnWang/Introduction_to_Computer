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
    // �N10�i���ഫ���U�۪�16�i��(ex: 10 -> 'A')
    // �N�Ʀr�ϦV�s�istring�A�Yarray�q���ܥk�Uelement��16�i��|�ѥk�ܥ��s�istring
    // ���ഫ�i����K���L�X16�i�쪺����
    cout << "Result(hex): ";

    for(int i = 0; i < arraysize; i++)            // �N�Q�i�쪺answer�ର�Q���i��
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

    for(int i = 0; i < arraysize; i++)              // �M��answer_hex�q�}�Y�_�ĴX�Ӧr���D0
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
        cout << "0";                                // ��answer_hex��0�ɡA�ݭn����k�L�X0
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
        carry = answer[i]/16;                       // �p��ۥ[�᪺�i��
        answer[i] = answer[i]%16;                   // �N���T(�p��16)���ƭȩ�ianswer��
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
            borrow = 1;                             // ��16���U�@��ơA�ҥH�b�U����for-loop���|�Q�h��1
            answer[i] += 16;                        // �Y�p��ᬰ�t�ơA�h��W�@��ƭ�16�Ӭۥ[
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
        answer[k] += carry;                               // �N�ƭȥ[�W�i��
        carry = answer[k]/16;                             // �p��ۭ��᪺�i��
        answer[k] = answer[k]%16;                         // �N���T(�p��16)���ƭȩ�ianswer��
    }

    show_hex_answer(answer, answer_hex, arraysize);
}

bool handle_out_of_range(string str, const int arraysize)
{
    bool correct_number = true;

    for(int i = 0; i < arraysize; i++)
    {
        if(str[0] == '-')                                    // ���~����Jnumber�A�^��false
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
            correct_number = false;                         // ���~����Jnumber�A�^��false
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

            if(str1.length() >= str2.length())                       // �P�_���@�ӿ�J��number�����A�ñN��]��arraysize
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

            if(str1.length() >= str2.length())                       // �P�_���@�ӿ�J��number�����A�ñN��]��arraysize
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

            arraysize = str1.length() + str2.length();              // arraysize�����number(str1�Pstr2)�����׬ۥ[

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
