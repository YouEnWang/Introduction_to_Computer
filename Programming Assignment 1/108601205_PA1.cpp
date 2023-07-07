// PA1: Antibody Calculator

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    unsigned int Age = 0;
    char Vaccine;                // Vaccine brand: A(AZ), B(BNT), M(Moderna)
    int day = 0;                // The range of days pass by since vaccinated is [1~2^31-1]
    char Prior_infection;        // prior infection: y, Y, n, N
    int selection;              // selection: 1, 2, 3, R, 0
    float slope;                // slope is decided based on the age range. option of slope: -2, -3, -3.5
    int baseline = 0;               // baseline is an anchor of antibody concentration and varies with different vaccine brands
    float alpha;                // alpha is a parameter that can reflect the influence of age
    float beta = 0;                 // beta is used to reflect the prior infected. option of beta: 1 or 0.5
    double antibody;            // The antibody concentration should round off to the 2nd decimal place.



    cout << "***Antibody Calculator***" << endl;
    cout << "Enter 1 to input body data" << endl;
    cout << "Enter 2 to input vaccine data" << endl;
    cout << "Enter 3 to input prior infection" << endl;
    cout << "Enter R to calculate antibody" << endl;
    cout << "Enter 0 to exit system" << endl;


    // loop until user types end-of-file key sequence
    while ( ( selection = cin.get() ) != EOF)
    {
        // determine which selection was entered
        switch (selection)
        {
            case '1':
                {
                    cout << "Enter your age: ";
                    cin >> Age;
                            while ( !(Age >= 1 && Age <= 120) )
                            {
                                cout << "Invalid input! Please enter again" << endl;
                                cin >> Age;
                            } // end while

                            if (Age >= 1 && Age <= 40){
                                alpha = 0.05;
                                slope = -2;
                            }
                            else if (Age >= 41 && Age <= 80){
                                alpha = 0;
                                slope = -3;
                            }
                            else{
                                alpha = -0.05;
                                slope = -3.5;
                            }
                }
                break; // exit switch

            case '2':
                {
                    cout << "Enter how many days pass by since you were vaccinated: ";
                    cin >> day;
                        while (day <= 0)
                        {
                            cout << "Invalid input! Please enter again" << endl;
                            cin >> day;
                        } // end while

                    cout << "Enter the brand(A/B/M): ";
                    cin >> Vaccine;
                        while ( !(Vaccine == 'A' || Vaccine == 'B' || Vaccine == 'M') )
                        {
                            cout << "Invalid input! Please enter again" << endl;
                            cin >> Vaccine;
                        } // end while

                        if (Vaccine == 'A'){
                            baseline = 300;
                        }
                        else if (Vaccine == 'B'){
                            baseline = 800;
                        }
                        else
                            baseline = 900;
                }
                break; // exit switch

            case '3':
                {
                    cout << "Did you have a prior infection(y/n): ";
                    cin >> Prior_infection;
                        while (!(Prior_infection == 'y' || Prior_infection == 'Y' || Prior_infection == 'n' || Prior_infection == 'N'))
                        {
                            cout << "Invalid input! Please enter again" << endl;
                            cin >> Prior_infection;
                        } // end while

                        if (Prior_infection == 'y' || Prior_infection == 'Y'){
                            beta = 0.5;
                        }
                        else
                            beta = 1;
                }
                break;

            case 'R':
             // cout << alpha << " " << day << " " << baseline << " " << beta << " " << slope << endl;      // method of debugger
                {
                    if (Age != 0 && day != 0 && baseline != 0 && beta != 0){
                        if (day <= 14){
                            antibody = baseline * (1 + alpha) * (day/14.0);    // we should present '14' as '14.0', or the data type of (day/14) would be integer
                            if (antibody < 0){
                                antibody = 0;
                            }
                            cout << "Your antibody is " << setprecision(2) << fixed << antibody << endl;
                            if (antibody >= 50){
                                cout << "You are safe!" << endl;
                            }
                            else
                                cout << "Watch out! Antibody is low." << endl;
                        }
                        else
                        {
                            antibody = baseline * (1 + alpha) + slope * (day - 14) * beta;
                            if (antibody < 0){
                                antibody = 0;
                            }
                            cout << "Your antibody is " << setprecision(2) << fixed << antibody << endl;
                            if (antibody >= 50){
                                cout << "You are safe!" << endl;
                            }
                            else
                                cout << "Watch out! Antibody is low." << endl;
                        }
                        // cout << baseline << " " << alpha << " " << day << " " << slope << " " << beta << endl;  // method of debugger
                    }
                    else{
                        // cout << baseline << " " << alpha << " " << day << " " << slope << " " << beta << endl;  // method of debugger
                        cout << "Data is not enough." << endl;
                    }
                }
                break;

            case '0':
                cout << "\nbye~" << endl;
                return 0;

            case '\n':
            case '\t':
            case ' ':
                continue;

            default:
                cout << "Invalid input! Please enter again" << endl;
                continue;  // 要繼續輸入正確的selection才可繼續操作其他的case

        } // end switch

        cout << "\n";
     // cout << selection << endl;      // method of debugger
        cout << "***Antibody Calculator***\n"
             << "Enter 1 to input body data\n"
             << "Enter 2 to input vaccine data\n"
             << "Enter 3 to input prior infection\n"
             << "Enter R to calculate antibody\n"
             << "Enter 0 to exit system" << "\n";
     // cout << selection << endl;      // method of debugger

    } // end while

    return 0;
}
