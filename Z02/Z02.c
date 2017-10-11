#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

uint8_t menu(const char* text) {
	uint8_t ch = 0;

	system("cls");
	puts(text);

	printf("Menu\n");
	printf("1 - Number of words in the text.\n");
	printf("2 - Number of sentenses in the text.\n");
	printf("3 - Number of dots and comas in the text.\n");
	printf("4 - Reverse the text.\n");
	printf("5 - Reverse the sentences.\n");
	printf("6 - Exit.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

uint8_t numberWord(const char* text, char* word) {
	uint8_t num = 0;

	while (text = strstr(text, word)) {
		num++;
		text++;
	}

	return num;
}

uint8_t numberSentence(const char* text) {
	char buf[500] = "";
	uint8_t num = 0;
	const char* tok = ".!?";
	
	strcpy(buf, text);
	text = strtok(buf, tok);

	while (text) {
		text = strtok(NULL, tok);
		num++;
	}

	return num;
}

uint8_t numberPunct(const char* text) {
	uint8_t num = 0;

	while (*text) {
		if (*text == '.' || *text == ',') {
			num++;
		}

		text++;
	}

	return num;
}

void addWord(const char* intext, char* outtext, uint8_t bytes) {
	char buf[500] = "";

	strncat(buf, intext, bytes);
	strcat(buf, outtext);
	strcpy(outtext, buf);
}

void textReverse(const char* bgn, char* outtext) {
	const char* end = NULL;

	while (end = strpbrk(bgn, " .,!?")) {
		addWord(bgn, outtext, end - bgn);

		while (!isalpha(*end) && *end) {
			addWord(end, outtext, 1);
			end++;
		}
		bgn = end;
	}
}

void sentenceReverse(const char* bgn, char* outtext) {
	const char* end = NULL;
	char centence[500] = "";
	char buf[500] = "";

	while (end = strpbrk(bgn, ".!?")) {
		end++;
		strncat(buf, bgn, end - bgn);
		textReverse(buf, centence);
		strcat(outtext, centence);
		bgn = end;

		while (!isalpha(*end) && *end++);
		strncat(outtext, bgn, end - bgn);
		bgn = end;

		memset(buf, '\0', strlen(buf));
		memset(centence, '\0', strlen(centence));
	}
}

int main(void) {
	const char* text = "London is the capital of Great Britain, its political, economic and cultural centre! London is one of the largest cities in the world. Its population is more than million people. London is situated on the river Thames. The city is very old and beautiful. It was founded more than two thousand years ago.";
	char word[10] = "";
	uint8_t ch = 0;

	while ((ch = menu(text)) != 6) {
		switch (ch) {
		case 1:
			printf("Input word for search: ");
			scanf("%s", word);

			printf("There are %hhu \"%s\" in text.\n", numberWord(text, word), word);

			break;

		case 2:
			printf("There are %hhu sentenses in text.\n", numberSentence(text));
			break;

		case 3:
			printf("There are %hhu dots and comas in the text.\n", numberPunct(text));
			break;

		case 4: {
			char outtext[500] = "";
			printf("Text after reverse: ");
			textReverse(text, outtext);
			puts(outtext);
			break;
		}

		case 5: {
			char outtext[500] = "";
			printf("Text after reverse: ");
			sentenceReverse(text, outtext);
			puts(outtext);
			break;
		}
			

		default:
			printf("Wrong input!");
		}

		printf("Done. Press any key.");
		_getch();
	}

	return 0;
}