#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Calendar.h"

int main(int argc, char ** argv){
	//processing inputs from the user
	char * input_month = argv[1];
	char * input_year = argv[2];
	int month = atoi(input_month); int year = atoi(input_year);

	struct calendar myCalendar; 
	BuildCalendar(myCalendar);
	int ti, ti2;
	char * ts1, ts2, ts3;
	ti = myCalendar.years[2342].num;	
	ts1 = myCalendar.years[2342].months[4].name;	
	ti2 = myCalendar.years[2342].months[4].dates[21].num;	
	//DisplayCalendar(month, year, myCalendar);	
	//
	printf("Year : %d\nMonth: %s\nDate: %i", ti, ts1, ti2);
}

void BuildCalendar (struct calendar cal){
	int i = 0;
	while (i < 10000) {
		struct year * curr = &cal.years[i];
		curr -> num = 1584 + i;
		if ( i == 0 ) {
			curr -> prev = NULL;
		}
		else {
			curr -> prev = &cal.years[i-1];
		}

		if ( i == 9999 ) {
			curr -> next = NULL;
		}
		else {
			curr -> next = &cal.years[i+1];
		}
		
		int j = 0;
		while ( j < 12 ) {
			struct month * curr_month = &(curr -> months[j]);	
	 		curr_month -> name = months_of_the_year[j]; 
			curr_month -> num = j + 1;
			
			//handling previous and next months

			if ( j == 0 && i != 0 ) {
				curr_month -> prev = &((curr -> prev) -> months[11]);
			}
			else if ( j == 0 && i == 0) {
				curr_month -> prev = NULL;
			}

			else {
				curr_month -> prev = &(curr -> months[j-1]);
			}

			if ( j == 11 && i == 9999){
				curr_month -> next = &((curr -> next) -> months[0]);
			}
			else if ( j == 11 && i == 9999) {
				curr_month -> next = NULL;
			}
			else {
				curr_month -> next = &(curr -> months[j+1]);
			}
			
			//handling dates
			int k = 0;
			while ( k < daysInMonth(curr_month, curr)){
				struct date * curr_date = &(curr_month -> dates[k]);
				curr_date -> num = k + 1;
				int last_index = daysInMonth(curr_month, curr) - 1;
				
				//handling previous and next dates for each of the following cases:
				//general case -> k = 0 or k = last_index
				//if (j = 0 and k = 0) or (j = 11 and k = last_index)
				//if (i = 0 and j = 0 and k = 0) or (i = 9999 and j = 11 and k = last_day)
				
				if ( k != 0 && k != last_index ){
					curr_date -> prev = &(curr_month -> dates[k-1]);
					curr_date -> next = &(curr_month -> dates[k+1]);
				}

				else if (k == 0 && j != 0) {
					curr_date -> prev = &(curr_month -> prev -> dates[last_index]);
					curr_date -> next = &(curr_month -> dates[1]);
				}

				else if (k == last_index && j != 11){
					curr_date -> prev = &(curr_month -> dates[k+1]);
					curr_date -> next = &(curr_month -> next -> dates[0]);
				}

				else if (k == 0 && j == 0 && i != 0){
					curr_date -> prev = &(curr -> prev -> months[11].dates[last_index]);
					curr_date -> next = &(curr_month -> dates[1]);
				}

				else if (k == last_index && j == 11 && i != 9999){
					curr_date -> prev = &(curr_month -> dates[k-1]);
					curr_date -> next = &(curr -> months[0].dates[0]);
				}
				
				else if (k == 0 && j == 0 && i == 0) {
					curr_date -> prev = NULL;
					curr_date -> next = &(curr_month -> dates[1]);
				}

				else if (k == last_index && j == 11 && i == 9999) {
					curr_date -> prev = &(curr_month -> dates[k-1]);
					curr_date -> next = NULL;
				}
				
				k++;
					
			}

			j++;
		}
		i++;
	}
}

//void DisplayCalendar (int month, int year, struct calendar cal){}
struct date * last_date(struct month * mon, struct year * yr){
	int last_index = daysInMonth(mon, yr) - 1;
	struct date * last_date_of_month = &(yr -> months[(mon -> num) - 1].dates[last_index]);

	return last_date_of_month;
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
		
bool IsLeap(int year){
	bool result;
	if (year % 4 == 0){
		result = true;
		if (year % 100 != 0){
			result = false;
			if(year % 400 == 0){
				result = true;
			}
		}
	}
	return result;
}
