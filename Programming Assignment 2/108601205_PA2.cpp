// PA2: X-Linked Rings Puzzle
#include <iostream>

using namespace std;

void get_state(int [], int, int);                                   // ����ϥΪ̿�J��state
void show_state(int [], int, int);                                  // ��ܥ����������A
int do_XOR(int, int, int);                                          // ���F��Xf(x)�Ұ���XOR
void Finite_Automation(int [], int, int);                           // �D�Xf(x)
void array_assign(int [], int[], int, int);                         // ���F�קK�b�{��������̪�����state�A�Φ�recursion�i��array��assign
void run_R_rule_once(int [], int);                                  // �ާ@�@��R-rule
void R_rule(int [], int);                                           // �}�l�����ɩҾާ@��R-rule
void run_S_rule_once(int [], int);                                  // �ާ@�@��S-rule
void S_rule(int [], int);                                           // �}�l�����ɩҾާ@��S-rule
int success_solve(int [], int, int, int);                           // �P�_�O�_�N�����ƸѶ}
void start_solve(int [], int [], int, int, int, int);            // �}�l�����ҥΪ�recursion

int main()
{
    int rings;
    int i = 1;          // �p�ƥΪ��ܼ�
    int steps = 0;      // �Ѷ}���һݪ��B��
    int total = 0;      // �p��Ҧ������A�`�M���ƭȡA�ΥH�P�_�O�_�N�����ƸѶ}

    cout << "Welcome to play X-Linked Ring!" << endl;
    cout << "How many X-Linked Ring do you want to solve?" << endl;
    cin >> rings;
    cout << "\n" << endl;

    // ��state_all�o��array�s�U�ϥΪ̿�J��state
    const int arraySize = rings;
    int state_all[arraySize];

    // To avoid changing to array state_all, create the other four arrays
    int f[arraySize];
    int run_R_rule_once_array[arraySize];
    int run_S_rule_once_array[arraySize];

    // prompt user to input the rings state
    cout << "What the " << rings << "-Linked Ring look like?" << endl;
    cout << "Please enter the rings state from inside to outside." << endl;
    cout << "If the ring is on the sword, please input 1. Otherwise, please enter 0." << endl;

    get_state(state_all, i,rings);                      // ���array state_all

    array_assign(f, state_all, i ,rings);               // assign array state_all to array f
    Finite_Automation(f, i, rings);                     // create f(x)

    // Show original state of X-Linked rings
    cout << endl;
    cout << "The rings state of " << rings << "-Linked Ring is: ";
    show_state(state_all, i, rings);
    cout << endl;

    // Show the rings state after running R-rule once.
    cout << "If run R-rule once, the rings state of " << rings << "-Linked Ring is: ";
    array_assign(run_R_rule_once_array, state_all, i, rings);       // assign array state_all to array run_R_rule_once_array
    run_R_rule_once(run_R_rule_once_array, rings);
    show_state(run_R_rule_once_array, i, rings);

    // Show the rings state after running S-rule once.
    cout << endl;
    cout << "If run S-rule once, the rings state of " << rings << "-Linked Ring is: ";
    array_assign(run_S_rule_once_array, state_all, i, rings);       // assign array state_all to array run_S_rule_once_array
    run_S_rule_once(run_S_rule_once_array, rings-1);
    show_state(run_S_rule_once_array, i, rings);

    // Start to  solve the rings.
    cout << "\n" << endl;
    cout << "Let's start to solve the " << rings << "-Linked Ring." << endl;

    // �P�_�ϥΪ̿�J����lstate�O�_�����ƸѶ}�����A
    if (success_solve(state_all, i, rings, total) != 0){
        if (f[rings-1] == 1){
            cout << "Start with R-rule !!" << endl;
        }
        else{
            cout << "Start with S-rule !!" << endl;
        }
    }

    start_solve(state_all, f, i, rings, steps, total);         // start to solve the rings

    return 0;
}

void get_state(int state_all[], int i, int rings)
{
    if (i <= rings){
        cout << "What the state of " << i;
        if (i == 1){
            cout << "st";
        }
        else if (i == 2){
            cout << "nd";
        }
        else if (i == 3){
            cout << "rd";
        }
        else{
            cout << "th";
        }
        cout << " rings?" << endl;

        cin >> state_all[i-1];

        get_state(state_all, i+1, rings);
    }
}

void show_state(int any_state[], int i, int rings)
{
    if (i <= rings){
        cout << any_state[i-1];
        show_state(any_state, i+1, rings);
    }
}

int do_XOR(int x, int y, int rings)
{
    int Z1, Z2;

    // Z1 + Z2 = (x'* y) + (x + y')
    if (x == 1){
        x = 0;
        Z1 = x * y;
        x = 1;
    }
    else{
        x = 1;
        Z1 = x * y;
        x = 0;
    } // Z1 = x'* y

    if (y == 1){
        y = 0;
        Z2 = x * y;
        y = 1;
    }
    else{
        y = 1;
        Z2 = x * y;
        y = 0;
    } // Z2 = x * y'

    return (Z1 + Z2);
}

void array_assign(int any_array[], int state_all[], int i, int rings)
{
    if (i <= rings){
        any_array[i-1] = state_all[i-1];
        array_assign(any_array, state_all, i+1, rings);
    }
}

void Finite_Automation(int f[],int i, int rings)
{
    f[0] = do_XOR(0, f[0], rings);

    if (i <= rings-1){
        f[i] = do_XOR(f[i-1], f[i], rings);
        Finite_Automation(f, i+1, rings);
    }
}

void run_R_rule_once(int run_R_rule_once_array[], int rings)
{
    if (run_R_rule_once_array[rings-1] == 1){
        run_R_rule_once_array[rings-1] = 0;                         // R-rule down ring
    }
    else{
        run_R_rule_once_array[rings-1] = 1;                         // R-rule on ring
    }
}

void R_rule(int state_all[], int rings)
{
    if (state_all[rings-1] == 1){
        cout << "!! Turn the " << rings;
        if (rings == 1){
            cout << "st";
        }
        else if (rings == 2){
            cout << "nd";
        }
        else if (rings == 3){
            cout << "rd";
        }
        else{
            cout << "th";
        }
        cout << " ring down !!" << endl;
        state_all[rings-1] = 0;                         // R-rule down ring
    }
    else{
        cout << "!! Turn the " << rings;
        if (rings == 1){
            cout << "st";
        }
        else if (rings == 2){
            cout << "nd";
        }
        else if (rings == 3){
            cout << "rd";
        }
        else{
            cout << "th";
        }
        cout << " ring on !!" << endl;
        state_all[rings-1] = 1;                         // R-rule on ring
    }
}

void run_S_rule_once(int run_S_rule_once_array[], int last_ring)
{
    if (run_S_rule_once_array[last_ring] == 1){
        if (run_S_rule_once_array[last_ring-1] == 1){
            run_S_rule_once_array[last_ring-1] = 0;                 // S-rule down ring
        }
        else{
            run_S_rule_once_array[last_ring-1] = 1;                 // S-rule on ring
        }
    }
    else{
        run_S_rule_once(run_S_rule_once_array, last_ring-1);        // go back to find 11 or 01 again
    }
}

void S_rule(int state_all[], int last_ring)
{
    if (state_all[last_ring] == 1){
        if (state_all[last_ring-1] == 1){
            cout << "!! Turn the " << last_ring;
            if (last_ring == 1){
                cout << "st";
            }
            else if (last_ring == 2){
                cout << "nd";
            }
            else if (last_ring == 3){
                cout << "rd";
            }
            else{
                cout << "th";
            }
            cout << " ring down !!" << endl;
            state_all[last_ring-1] = 0;                 // S-rule down ring
        }
        else{
            cout << "!! Turn the " << last_ring;
            if (last_ring == 1){
                cout << "st";
            }
            else if (last_ring == 2){
                cout << "nd";
            }
            else if (last_ring == 3){
                cout << "rd";
            }
            else{
                cout << "th";
            }
            cout << " ring on !!" << endl;
            state_all[last_ring-1] = 1;                 // S-rule on ring
        }
    }
    else{
        S_rule(state_all, last_ring-1);                 // go back to find 11 or 01 again
    }
}

int success_solve(int state_all[], int i, int rings, int total)
{
    // ��funtion return��total�Ȭ�0�ɡA��ܤw���\�N���Ѷ}
    if (i <= rings){
        total += state_all[i-1];
        success_solve(state_all, i+1, rings, total);
    }
    else{
        return total;
    }
}

void start_solve(int state_all[], int f[], int i, int rings, int steps, int total)
{
    if (success_solve(state_all, i, rings, total) != 0){                  // �P�_�O�_�w�N�����ƸѶ}
        if (f[rings-1] == 1){
            R_rule(state_all, rings);
            cout << "The rings state of " << rings << "-Linked Ring is: ";
            show_state(state_all, i, rings);
            steps++;
            cout << endl;

            if (success_solve(state_all, i, rings, total) != 0){
                S_rule(state_all, rings-1);
                cout << "The rings state of " << rings << "-Linked Ring is: ";
                show_state(state_all, i, rings);
                steps++;
                cout << endl;
            }
        }
        else{
            S_rule(state_all, rings-1);
            cout << "The rings state of " << rings << "-Linked Ring is: ";
            show_state(state_all, i, rings);
            steps++;
            cout << endl;

            if (success_solve(state_all, i, rings, total) != 0){
                R_rule(state_all, rings);
                cout << "The rings state of " << rings << "-Linked Ring is: ";
                show_state(state_all, i, rings);
                steps++;
                cout << endl;
            }
        }
        start_solve(state_all, f, i, rings, steps, total);
    }
    else{
        cout << endl;
        cout << "The " << rings << "-Linked Ring is solved in " << steps;
        if (steps <= 1){
            cout << " step." << endl;
        }
        else{
            cout << " steps." << endl;
        }
        cout << "Thanks for using!! Goodbye ~" << endl;
    }
}
