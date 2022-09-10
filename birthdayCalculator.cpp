#include <iostream>
#include <string>
#include <ctime>

using namespace std;
#define SECONDS_IN_MINUTE 60
#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24

int main()
{
    cout << "BIRTHDAY COUNTDOWN!!!" << endl;
    cout << "Enter your date of birth (MM/DD/YYYY): ";
    
    string userDob;
    getline(cin, userDob);

    time_t nowInSeconds = time(0);
    tm* nowAsTmPointer = localtime(&nowInSeconds);

    string userDobMonth = userDob.substr(0, 2);
    string userDobDay = userDob.substr(3, 2);
    string userDobYear = userDob.substr(6);

    tm userDobTime = {};
    userDobTime.tm_year = stoi(userDobYear) - 1900;
    userDobTime.tm_mon = stoi(userDobMonth) - 1;
    userDobTime.tm_mday = stoi(userDobDay);
    userDobTime.tm_hour = 0;
    userDobTime.tm_min = 0;
    userDobTime.tm_sec = 0;

    bool isNextBdayNextYear = nowAsTmPointer->tm_mon > userDobTime.tm_mon
        || (nowAsTmPointer->tm_mon == userDobTime.tm_mon && nowAsTmPointer->tm_mday >= userDobTime.tm_mday);

    tm userNextBirthday = {};
    userNextBirthday.tm_year = isNextBdayNextYear ? nowAsTmPointer->tm_year + 1 : nowAsTmPointer-> tm_year;
    userNextBirthday.tm_mon = stoi(userDobMonth) - 1;
    userNextBirthday.tm_mday = stoi(userDobDay);
    userNextBirthday.tm_hour = 0;
    userNextBirthday.tm_min = 0;
    userNextBirthday.tm_sec = 0;

    time_t userDobTimeInSeconds = mktime(&userDobTime);
    time_t userNextBirthdayInSeconds = mktime(&userNextBirthday);
    time_t secondsUntilNextBirthday = userNextBirthdayInSeconds - nowInSeconds;
    int numberOfDaysUntilNextBirthday = (secondsUntilNextBirthday / SECONDS_IN_MINUTE / MINUTES_IN_HOUR / HOURS_IN_DAY) + 1;
    int yearsOldOnNextBirthday = userNextBirthday.tm_year - userDobTime.tm_year;
    string uglyUserNextBirthday = asctime(&userNextBirthday);
    string prettyUserNextBirthday = uglyUserNextBirthday.substr(0, 10) + ", " + uglyUserNextBirthday.substr(20, 4); 
    string daysMessage = numberOfDaysUntilNextBirthday == 1 ? " day on " : " days on ";
    string yearsMessage = yearsOldOnNextBirthday == 1 ? " year old." : " years old.";

    cout << endl;
    cout << "Your next birthday is in " << numberOfDaysUntilNextBirthday << daysMessage << prettyUserNextBirthday << " and you will be " << yearsOldOnNextBirthday << yearsMessage << "\n" << endl;
}