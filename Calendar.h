#define DAYS_NORMAL 365;
#define DAYS_LEAP 366;
#define START_YEAR 1583;

char * days_of_the_week[7] = {"Sunday","Monday", "Tuesaday", "Wednesday", "Thursday", "Friday", "Saturday"};
char * months_of_the_year[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char * months_with_31[7] = {"January", "March", "May", "July", "August", "October", "December"};
char * months_with_30[4] = {"April", "June", "September", "November"};


struct date {
	int num;
	struct date * next;
	struct date * prev;
};

struct month {
	char * name;
	int num;
	struct date * dates;
	struct month * next;
	struct month * prev;
};

struct year {
	int num;
	struct month months[12];
	struct year * prev;
	struct year * next;
};

struct calendar {
	struct year years[10000];
};

int daysInMonth(struct month * mon, struct year * yr);
void BuildCalendar(struct calendar cal);
void DisplayCalendar(int month, int year, struct calendar cal);
