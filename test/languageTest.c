#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef __Win32
# include "..\src\Language.c"
#else
# include "../src/Language.c"
#endif

int testInt(int expression, int expected) {
	if (expected == expression) {
		printf("\x1b[32m Test Succesfully passed : \n\t expected %d and got %d \x1b[0m \n", expected, expression);
	}
	else {
		printf("\x1b[31m Test Error : \n\t expected %d and got %d \x1b[0m \n", expected, expression);
	}
	printf("\n");
}
int testString(char * expression, char * expected) {
	if (!strcmp(expected, expression)) {
		printf("\x1b[32m Test Succesfully passed : \n\t expected %s and got %s \x1b[0m \n", expected, expression);
	}
	else {
		printf("\x1b[31m Test Error : \n\t expected %s and got %s \x1b[0m \n", expected, expression);
	}
	printf("\n");
}
int testPointer(void * expression, void * expected, bool equal) {
	char temp[4] = "";
	if (!equal) sprintf(temp, "not");

	if ( (equal && expected == expression) || (!equal && expected != expression) ) {
		printf("\x1b[32m Test Succesfully passed : \n\t expected %s %p and got %p \x1b[0m \n", temp, expected, expression);
	}
	else {
		printf("\x1b[31m Test Error : \n\t expected %s %p and got %p \x1b[0m \n", temp, expected, expression);
	}
	printf("\n");
}

int main(int argc, char** argv) {
	printf("Open file test \n");
	testInt(loadLanguage("en_us"), 0);

	printf("Open not existing file test \n");
	testInt(loadLanguage("en_fr"), -1);

	unloadLanguage();
	printf("Data Null before language change test \n");
	testPointer(Data, NULL, true);

	loadLanguage("en_us");
	printf("Data not Null after language change test \n");
	testPointer(Data, NULL, false);

	printfTranslationList();

	printf("Language translation with existing id test \n");
	testString(getTranslatedText("test.1"), "test");

	printf("Language translation with not existing id test \n");
	testString(getTranslatedText("test.2"), "test.2");
}

