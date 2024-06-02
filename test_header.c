#include <stdio.h>
#include "Calendar.h"
#include <stdbool.h>

bool IsLeap(int year){
	year = (float) year;
	bool result;
	if (year % 4 == 0){
		result = true;
		if (year % 100 == 0){
			result = false;
			if(year % 400 == 0){
				result = true;
			}
		}
	}
	return result;
}
int daysInMonth(struct month * mon, struct year * yr){
	int result;
	int month_type;
	if ((mon -> num) == 1 || (mon -> num) == 3 || (mon -> num) == 5 || (mon -> num) == 7 ||\
			(mon -> num) == 8 || (mon -> num) == 10 || (mon -> num) == 12) {
		month_type = 1;
	}

	else if ((mon -> num) == 4 || (mon -> num) == 6 || (mon -> num) == 9 || (mon -> num) == 11){
		month_type = 3;
	}
	
	else if ((mon -> num) == 2) {
		month_type = 2;
	}


	switch (month_type){
		case (1):
			result = 31;
			break;
		
		case 2:
			if (IsLeap(yr -> num) == true){
				result = 29;
			}
			else {
				result = 28;
			}
			break;
		
		case 3 :
			result = 30;
			break;
		
	}
	return result;
}		


int main() {
	struct month * mon;
	mon -> num = 2;
	struct year * yr;
	yr -> num = 2023;
	printf("%d", mon -> num);
}
