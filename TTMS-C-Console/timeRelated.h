extern int currentSecond();

extern struct tm totalSecondToStruct_tm(int secondValue);

extern int totalSecondToYear(int secondValue);

extern int totalSecondToMonth(int secondValue);

extern int totalSecondToYearDay(int secondValue);

extern int totalSecondToMonthDay(int secondValue);

extern int totalSecondToWeekDay(int secondValue);

extern int totalSecondToHour(int secondValue);

extern int totalSecondToMinute(int secondValue);

extern int totalSecondToSecond(int secondValue);

extern void printTimeString(int secondValue);

extern int timeStringLength(int secondValue);

extern void printTimeStringUpToMinute(int secondValue);

//extern int user_date_t_And_user_time_t_ToSecond(user_date_t date, user_time_t time);