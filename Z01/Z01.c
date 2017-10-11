#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <ctype.h>

int32_t string_to_number(const char* str, uint8_t* error) {
	int32_t val = 0;
	int8_t sign = 1;

	if (*str == '-') {
		sign = -1;
		str++;
	}
	else if (*str == '+') {
		str++;
	}

	while (*str) {
		if (isdigit(*str)) {
			val *= 10;
			val += *str++ - '0';
		}
		else {
			*error = 1;
			return 0;
		}
	}
	*error = 0;

	return val*sign;
}

uint32_t number_to_string(char* str, int32_t num) {
	char buf[20] = "";
	char* bgn = str;
	int8_t i = 0;

	if (num < 0) {
		*str++ = '-';
		num = -num;
	}

	while (num > 0) {
		buf[i++] = '0' + num % 10;
		num /= 10;
	}
	buf[i--] = '\0';

	while (i >= 0) {
		*str++ = buf[i--];
	}
	*str = '\0';

	return num;
}

void upper_case(char* str) {
	while (*str) {
		if (isalpha(*str)) {
			*str = 'A' + (*str - 'a');
		}
		str++;
	}
}

void lower_case(char* str) {
	while (*str) {
		if (isalpha(*str)) {
			*str = 'a' + (*str - 'A');
		}
		str++;
	}
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - String to number.\n");
	printf("2 - Number to string.\n");
	printf("3 - Upper case.\n");
	printf("4 - Lower case.\n");
	printf("5 - Exit.\n");
	printf("Input choce: ");

	scanf("%hhu", &ch);

	return ch;
}

int main(void) {
	char instr[20] = "";
	char outstr[20] = "";
	int32_t val = 0;
	uint8_t mes = 0;
	uint8_t ch = 0;

	while ((ch = menu()) != 5) {
		switch (ch) {
		case 1:
			printf("Input string: ");
			scanf("%s", instr);

			val = string_to_number(instr, &mes);
			if (!mes) {
				printf("Result of string to number: %i.\n", val);
			}
			else {
				printf("The string can't be transform to number!\n");
			}

			break;

		case 2:
			printf("Input number: ");
			scanf("%i", &val);

			if (!number_to_string(outstr, val)) {
				printf("Result of number to string: %s.\n", outstr);
			}
			else {
				printf("The number can't be transform to string!\n");
			}

			break;

		case 3:
			printf("Input string: ");
			scanf("%s", instr);
			upper_case(instr);
			printf("Result of upper case: %s.\n", instr);

			break;

		case 4:
			printf("Input string: ");
			scanf("%s", instr);
			lower_case(instr);
			printf("Result of upper case: %s.\n", instr);
			break;

		default:
			printf("Wrong input!\n");
		}

		printf("Done. Print any key.\n");
		_getch();
	}

	return 0;
}