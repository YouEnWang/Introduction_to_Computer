// PA1: Antibody Calculator

#include <iostream>
#include <iomanip>


using namespace std;

int main()
{
    unsigned int Age = 0;
    char Vaccine;                // Vaccine brand: A(AZ), B(BNT), M(Moderna)
    char Prior_infection;        // prior infection: y, Y, n, N
    int selection;              // selection: 1, 2, 3, R, 0
    float slope;                // slope is decided based on the age range. option of slope: -2, -3, -3.5
    int baseline = 0;               // baseline is an anchor of antibody concentration and varies with different vaccine brands
    float alpha;                // alpha is a parameter that can reflect the influence of age
    float beta = 0;                 // beta is used to reflect the prior infected. option of beta: 1 or 0.5
    double antibody;            // The antibody concentration should round off to the 2nd decimal place.

    int day_before, day_today;
    int month_before, month_today;
    int year_before, year_today;
    int leap_before, leap_today;
    int sum_before = 0;
    int sum_today = 0;
    int sum;
    int date_before, date_today;


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
                    cout << "Enter the date you were vaccinated(yyyymmdd): ";
                    cin >> date_before;
                    {
                        year_before = (date_before)/10000;
                        month_before = (date_before - year_before* 10000)/100;
                        day_before = (date_before - year_before*10000 - month_before*100)/1;

                        while (year_before < 2019 || year_before > 2022 || month_before < 1 || month_before > 12 || day_before < 1 || day_before > 31
                               ||(month_before == 2 && day_before == 30)||(month_before == 2 && day_before == 31)||(month_before == 4 && day_before == 31)
                                ||(month_before == 6 && day_before == 31)||(month_before == 9 && day_before == 31)||(month_before == 11 && day_before == 31)
                               ||(year_before == 2019 && month_before == 2 && day_before == 29)||(year_before == 2021 && month_before == 2 && day_before == 29)
                                ||(year_before == 2022 && month_before == 2 && day_before == 29))
                        {
                            cout << "Invalid input! Please enter again" << endl;
                            cin >> date_before;

                            year_before = (date_before)/10000;
                            month_before = (date_before - year_before* 10000)/100;
                            day_before = (date_before - year_before*10000 - month_before*100)/1;
                        } // end while


                        // cout << year_before << " " << month_before << " " << day_before << endl;         // method of debugger

                        if (month_before == 1)             // 先計算某月以前月份的總天數
                            sum_before = 0;
                        else if (month_before == 2)
                            sum_before = 31;
                        else if (month_before == 3)
                            sum_before = 59;
                        else if (month_before == 4)
                            sum_before = 90;
                        else if (month_before == 5)
                            sum_before = 120;
                        else if (month_before == 6)
                            sum_before = 151;
                        else if (month_before == 7)
                            sum_before = 181;
                        else if (month_before == 8)
                            sum_before = 212;
                        else if (month_before == 9)
                            sum_before = 243;
                        else if (month_before == 10)
                            sum_before = 273;
                        else if (month_before == 11)
                            sum_before = 304;
                        else
                            sum_before = 334;
                        sum_before = sum_before + day_before;        // 加上某天的天數

                        if (year_before%400 == 0 || ((year_before%4 == 0) && (year_before%100 != 0)))        // 判斷是否為閏年
                            leap_before = 1;
                        else
                            leap_before = 0;

                        if (leap_before == 1 && month_before > 2)
                            sum_before++;                      // 若是閏年且月份大於2，總天數應該加一天

                        sum_before = sum_before + (year_before - 2019)*365;  // 最後加上某年之前的天數
                    }
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
                    if (Age != 0 && baseline != 0 && beta != 0){
                        cout << "Enter the date today(yyyymmdd): ";
                        cin >> date_today;
                        {
                            year_today = date_today/10000;
                            month_today = (date_today - year_today* 10000)/100;
                            day_today = (date_today - year_today*10000 - month_today*100)/1;


                            while (year_today < 2019 || year_today > 2022 || month_today < 1 || month_today > 12 || day_today < 1 || day_today > 31
                                   ||(month_today == 2 && day_today == 30)||(month_today == 2 && day_today == 31)||(month_today == 4 && day_today == 31)
                                   ||(month_today == 6 && day_today == 31)||(month_today == 9 && day_today == 31)||(month_today == 11 && day_today == 31)
                                   ||(year_today == 2019 && month_today == 2 && day_today == 29)||(year_today == 2021 && month_today == 2 && day_today == 29)
                                   ||(year_today == 2022 && month_today == 2 && day_today == 29))
                            {
                                cout << "Invalid input! Please enter again" << endl;
                                cin >> date_today;

                                year_today = date_today/10000;
                                month_today = (date_today - year_today* 10000)/100;
                                day_today = (date_today - year_today*10000 - month_today*100)/1;
                            } // end while

                            // cout << year_today << " " << month_today << " " << day_today << endl;        // method of debugger

                            if (month_today == 1)             // 先計算某月以前月份的總天數
                                sum_today = 0;
                            else if (month_today == 2)
                                sum_today = 31;
                            else if (month_today == 3)
                                sum_today = 59;
                            else if (month_today == 4)
                                sum_today = 90;
                            else if (month_today == 5)
                                sum_today = 120;
                            else if (month_today == 6)
                                sum_today = 151;
                            else if (month_today == 7)
                                sum_today = 181;
                            else if (month_today == 8)
                                sum_today = 212;
                            else if (month_today == 9)
                                sum_today = 243;
                            else if (month_today == 10)
                                sum_today = 273;
                            else if (month_today == 11)
                                sum_today = 304;
                            else
                                sum_today = 334;
                            sum_today = sum_today + day_today;        // 加上某天的天數

                            if (year_today%400 == 0 || ((year_today%4 == 0) && (year_today%100 != 0)))        // 判斷是否為閏年
                                leap_today = 1;
                            else
                                leap_today = 0;

                            if (leap_today == 1 && month_today > 2)
                                sum_today++;                      // 若是閏年且月份大於2，總天數應該加一天

                            sum_today = sum_today + (year_today - 2019)*365;  // 最後加上某年之前的天數
                        }
                            sum = sum_today - sum_before + 1;           // The duration includes the day the user is vaccinated.

                        if (sum <= 14){
                            antibody = baseline * (1 + alpha) * (sum/14.0);    // we should present '14' as '14.0', or the data type of (sum/14) would be integer
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
                            antibody = baseline * (1 + alpha) + slope * (sum - 14) * beta;
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
                        // cout << baseline << " " << alpha << " " << sum << " " << slope << " " << beta << endl;  // method of debugger
                    }
                    else
                    {
                        // cout << baseline << " " << alpha << " " << sum << " " << slope << " " << beta << endl;  // method of debugger
                        cout << "Data is not enough." << endl;
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

