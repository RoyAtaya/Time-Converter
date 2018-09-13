/**
 * @file lab6.cpp
 * @author Farid Roy Ataya * @Date 25/06/2018
 * @version 1.0
 * @section this code converts military time to standard time
 */
// I declare that this assignment is my own work and that I have correctly acknowledged the
// work of others. I acknowledged that I have read and followed the Academic Honesty and
// Integrity related policies as outlined in the syllabus. //
// _____ Farid Roy Ataya ____ _____25/06/2018______________ //
// ____ 301161512 ______ //

#include <iostream>
#include <iomanip>
using namespace std;

int getInput(void); // get the time from the user in 24 hour notation
void standardTime(int input); // converts 24 hour time to 12 hour time
bool again(void); // asks the user if they want to repeat the program
bool validInput(int hour, int minute); // checks if input is a valid time
bool checkInput(string input); // checks if input is a number

// global constants
const int HUNDRED = 100;
const int TWELVE = 12;
const int ZERO = 0;
const int MAXHOUR = 23;
const int MAXMINUTE = 59;

class TimeFormatMistake{
public:
    // constructor
    TimeFormatMistake();
    // constructor
    TimeFormatMistake(string userInH, string userInM){
        hourError = userInH;
        minuteError = userInM;
    }
    
    string getHour(){ // get hour
        return hourError;
    }
    
    string getMinute(){ // get minute
        return minuteError;
    }
private:
    string hourError;
    string minuteError;
};


int main() {
    do {
        standardTime(getInput()); // driver program
    } while (again());
    cout << "End of program\n";
    return 0;
}


/*
 *   @brief  This function gets input from user
 *   @param  void
 *   @return int
 */
int getInput(void){
    string input = " "; // store user input
    string strHour = " "; // store hours
    string colon = " "; // store colon
    string strMinute = " "; // store minutes
    int hour = 0;
    int minute = 0;
    int Time_24_HR = 0; // 24 hour time
    bool loop = false; // control do while loop
    
    do {
        try {
            cout << "Enter time in 24-hour notation:" << endl;
            getline(cin,input);
            strHour = input.substr(0,2); // splits hour from input
            colon = input.substr(2,1); // splits colon from input
            strMinute = input.substr(3); // splits minute from input
            loop = false; // loop condition is false
            
            // checks if input contains any other characters other than numbers
            if (!checkInput(strHour) || !checkInput(strMinute)) {
                throw TimeFormatMistake(strHour, strMinute);
            }
            
            hour = stoi(strHour); // converts hour to integer
            minute = stoi(strMinute); // converts minute to integer
            
            // checks if hour and minute are within the allowed parameters
            if (!validInput(hour, minute)) {
                throw TimeFormatMistake(strHour, strMinute);
            }
            
            Time_24_HR = (hour*HUNDRED) + minute; // combines hour and minutes to a full time
        }
        catch (TimeFormatMistake e) {
            cout << "There is no such time as "<< e.getHour() << colon << e.getMinute() << endl;
            cout << "Try again"<<endl;
            loop = true;
        }
    } while (loop == true);
    
    return Time_24_HR;
}


/*
 *   @brief  This function uses the find_first_not_of function
 *           from the string library to check whether the input
 *           has any non numbers
 *   @param  input is an initialized string variable
 *   @return bool true or false
 */
bool checkInput(string input){
    return input.find_first_not_of("0123456789") == string::npos;
}


/*
 *   @brief  This function checks whether the time inputed is a valid time
 *   @param  hour is an initialized int variable
 *   @param  minute is an initialized int variable
 *   @return bool true or false
 */
bool validInput(int hour, int minute){
    bool check = true;
    if (hour < ZERO || hour > MAXHOUR) { // check if hour is within the allowed parameters
        check = false;
    }
    if (minute < ZERO || minute > MAXMINUTE) { // check if minute is within the allowed parameters
        check = false;
    }
    return check;
}


/*
 *   @brief  This function converts military time to standard time
 *   @param  input is an initialized int variable
 *   @return void
 */
void standardTime(int input){
    int hour = 0;
    int minute = 0;
    string pm = "PM";
    string am = "AM";
    hour = input/HUNDRED;
    minute = input%HUNDRED;
    
    if (hour > TWELVE) { // if the time is after noon
        hour = hour - TWELVE;
        cout << "That is the same as" << endl;
        cout << hour << ":" << setfill('0') << setw(2) << minute << " " << pm << endl;
    }
    else if (hour == TWELVE){ // if the time is noon
        cout << "That is the same as" << endl;
        cout << TWELVE << ":" << setfill('0') << setw(2) << minute << " " << pm << endl;
    }
    else if (hour == ZERO){ // if the time is 12 am
        cout << "That is the same as" << endl;
        cout << TWELVE << ":" << setfill('0') << setw(2) << minute << " " << am << endl;
    }
    else{ // time is the morning
        cout << "That is the same as" << endl;
        cout << hour << ":" << setfill('0') << setw(2) << minute << " " << am << endl;
    }
}


/*
 *   @brief  This function asks the user if they want to run the program again
 *   @param  void
 *   @return bool true or false
 */
bool again(void){
    char loopAgain = '\0';
    cout << "Again?(y/n):\n";
    cin >> loopAgain;
    cin.ignore(100000, '\n');
    cin.clear();
    if (toupper(loopAgain) == 'Y') {
        return true;
    }
    return false;
}

