/* 
 * file: ahnentafel.c
 * date: 2/24/19
 * @author Mike Cao
 */

#include <stdio.h>	// printf
#include <stdlib.h>	// EXIT_SUCCESS
#include <string.h>	// strlen
#define MAX 500

/*
 * checkCinary function
 * Checks if the number is binary
 * Returns 't' if true or 'f' if false
 */
char checkBinary(char b2[]) {
	char bin = 't';
	int length = strlen(b2);
	// check if all the numbers in the string are 0 or 1
	for(int i = 0; i < length - 1; i++) {
		if(b2[i] != '1' && b2[i] != '0') 
			bin = 'f';
	}
	if(b2[0] == '\n')
		bin = 'f';
	// return 't' or 'f'
	return bin;
}

/*
 * Menu function
 * prints the options
 */
void menu() {
	printf("\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s", "1) description", 
			"2) ahnentafel number (base 10)", 
			"3) ahnentafel number (base 2)", 
			"4) relation (e.g. mother's mother's father)", 
			"5) female X chromosome inheritance", 
			"6) exit",
			"> ");
}

/*
 * Description function for option 1
 * Prints the description of ahnentafel
 */
void description() {
	printf("%s\n", "The ahnentafel number is used to determine the relation between an individual and each of his/her direct ancestors.");
}

/*
 * genBack function
 * prints the number of generations back
 * @param generations number of generations
 */
void genBack(int generations) {
	printf("generations back: %d\n", generations);
}

/*
 * familyRelationship function
 * Calculates the family relationship depending on the input which is binary
 * @param b2 binary number
 */
void calculateFamilyRelationship(char *b2, int generations) {
	// if the generations count is just 1 and the first char in b2 is '1'
	// then the relation is self
	if(generations == 1 && b2[0] == '1') {
		printf("self\n");
	} else {
		printf("family relation: ");
		// for generations 2 and up which is self's parents and their 
		// parents and so on...
		if(generations >= 2) {  
			// interpret the first two numbers of b2, if the binary
			// number begins with "10..." then begin with father
			if((b2[0] == '1') && (b2[1] == '0')) {
		        	printf("father's ");
			// if the binary number begins with "11..." then begin
			// with mother
			} else if ((b2[0] == '1') && (b2[1] == '1')) {
				printf("mother's ");
			}
			// index for starting at the third character of the b2
			// array
			int i = 2;
			// iterate through every generation besides the last
			while(i < generations - 1) {
				// if the element of the array is a '0' then it
				// is the father
				if(b2[i] == '0') {
					printf("father's ");
				// if the element of the array is a '1' then it
				// is the mother
				} else if (b2[i] == '1') {
					printf("mother's ");
				}
				// increment to the last generation
				i++;
			}
			// if the element is '0' then print father otherwise
			// mother
			printf("%s\n", (b2[i] == '0') ? "father": "mother");
		} else {
			// if there are only two characters in b2, then if
			// the second character is a '0' then print father 
			// otherwise mother
			printf("%s\n", (b2[1] == '0') ? "father": "mother");
		}
	}
}

/*
 * calculateGenerations function
 * Calculates the number of generations
 * @param num decimal number
 * Returns the number of generations
 */
int calculateGenerations(int num) {
	int generations = 0;
	// calculate generations
	while(num != 0) {
		num = num / 2;
		generations++;
	}
	return generations;
}

/*
 * convertToBaseTwo function
 * Converts the argument from decimal to binary 
 * @param num number to be converted to binary
 */
void convertToBaseTwo(int num, char b2[]) {
	int generations = 0;
	int remainder[MAX];
	// assigns the remainders to remainder array and increments generations
	while(num != 0) {
		remainder[generations] = num % 2;
		num = num / 2;
		generations++;
	}
	//int b2[generations];
	int ind2 = 0;
	// reverses the array 
	for(int ind = generations - 1; ind >= 0; ind--) {
		// assign remainder backwards to b2
		b2[ind2] = '0' + remainder[ind]; 
		ind2++;
	}
}

/*
 * convertToBaseTen function
 * Converts the argument from binary to decimal
 * @param num number to be converted to decimal
 */
long int convertToBaseTen(char *b2) {
	return strtol(b2, NULL, 2);
}

/*
 * ahnentafel2 function for option 3
 * receives an input in base 2 or binary to convert to decimal or base 10 and
 * prints an English description of the connection from the base individual
 * to the target ancestor
 */
void ahnentafel2() {
        // prompts the user to enter a number in base 2 or binary
        printf("Enter the ahnentafel number in binary: ");
        // stores the user's next input
        char b2[MAX];
	char bin = 'f';
	while(bin == 'f') {
		// gets the next input, grabs a \n
		fgets(b2, sizeof(b2), stdin);
		// if the previous fgets gets \n, perform fgets again
		if(b2[0] == '\n')
			fgets(b2, sizeof(b2), stdin);
		// check if the input is binary
		bin = checkBinary(b2);
		if(bin == 'f')
			printf("Please enter a valid binary number: ");
	}
	// convert the binary number input to decimal
	long int b10 = convertToBaseTen(b2);
	// print the converted number
	printf("base-10 value: %ld\n", b10);
	// calculate generations back
	int generations = calculateGenerations(b10);
	// calculate the family relationship
	calculateFamilyRelationship(b2, generations);
	// print number of generations back
	genBack(generations - 1);
}

void command_ahnentafel2(char input[]) {
        // stores the user's next input
        char b2[strlen(input) - 1];
        char bin = 'f';
        for(int i = 0; i < strlen(input) - 1; i++) {
		b2[i] = input[i];
	}
        // convert the binary number input to decimal
        long int b10 = convertToBaseTen(b2);
        // print the converted number
        printf("base-10 value: %ld\n", b10);
        // calculate generations back
        int generations = calculateGenerations(b10);
        // calculate the family relationship
        calculateFamilyRelationship(b2, generations);
        // print number of generations back
        genBack(generations - 1);

}

/*
 * ahnentafel10 function for option 2
 * receives an input in base 10 to convert to binary and
 * prints an English description of the connection from the base individual
 * to the target ancestor
 */
void ahnentafel10() {
	// prompts the user to enter a number in base 10
	printf("Enter the ahnentafel number in base-10: ");
	// stores the user's next input
	int b10;
	scanf("%d", &b10);
	// ptints the converted number and store the number of generations
	printf("ahnentafel number in binary: ");
	//Calculate the number of generations
	int generations = calculateGenerations(b10);
	// string for binary conversion
	char b2[generations]; 
	// convert the decimal number and store it in b1
	convertToBaseTwo(b10, b2);
	// print the binary number
	for(int i = 0; i < generations; i++) 
		printf("%c", b2[i]);
	// add a newline
	putchar('\n');
	// print family relationships
	calculateFamilyRelationship(b2, generations);
	// print the number of generations back
	genBack(generations - 1);
}

/*
 * command_ahnentafel10 function for option 2 if there are valid command line
 * arguments
 * Does the same as ahnentafel10 function
 * converts the string which represents a decimal number and converts it to
 * binary and prints an English description of the connection from the base
 * individual to the target ancester
 * @param input string
 */
void command_ahnentafel10(char input[]) {
	long int b10 = strtol(input, NULL, 10);
	// ptints the converted number and store the number of generations
        printf("ahnentafel number in binary: ");
        //Calculate the number of generations
        int generations = calculateGenerations(b10);
        // string for binary conversion
        char b2[generations];
        // convert the decimal number and store it in b1
        convertToBaseTwo(b10, b2);
        // print the binary number
        for(int i = 0; i < generations; i++)
                printf("%c", b2[i]);
        // add a newline
        putchar('\n');
        // print family relationships
        calculateFamilyRelationship(b2, generations);
        // print the number of generations back
        genBack(generations - 1);
}

/*
 * reverseFamilyRelation
 * Depending on the tokens, print something
 * Returns 't' or 'f' if the input is invalid or misspelled
 */
char reverseFamilyRelation(char b2[], char input[], int generations) {
	char error = 'f';
	// if the input is mother, append a '1' to b2
	if(strcmp(input, "mother") == 0) {
		b2[generations] = '1';
	// if the input is father, append a '0' to b2
	} else if(strcmp(input, "father") == 0) {
		b2[generations] = '0';
	// if the input is s, ignore it
	} else if(strcmp(input, "s") == 0) {
		// do nothing
	// interpret everything else as an invalid input or a mispelled word
	} else {
		printf("Invalid string format!\n");
		// determines whether or not to calculate the rest of the info
		error = 't';
	}	
	return error;
}

/*
 * relation function for option 4
 * Allow the user to enter the relation and print out the ahnentafel number
 * in binary and decimal as well as the number of generations back
 */
void relation() {
	// stores the relation
	char rel[MAX];
	// stores the tokens of relation when calling strtok()
	char *input;
	// determines if there was an error with the initial input by the user
	char error = 'f';
	// prompt the user for the relation
	printf("Enter family relation (e.g.) \"father's mother\": ");
	// get an input
	fgets(rel, sizeof(rel), stdin);
        // if the previous fgets gets \n, perform fgets again
        if(rel[0] == '\n')
        	fgets(rel, sizeof(rel), stdin);
	// get the first token
	input = strtok(rel, "'\n ");
	// if the first token, or the whole input is self, then print the 
	// appropriate information
	if(strcmp("self", input) == 0) {
		printf("ahnentafel number in binary: 1\n");
		printf("ahnentafel number in base-10: 1\n");
		printf("generations back: 0\n");
	} else {
		// stores the binary representation of the family relations
		char b2[MAX];
		// the initial element of the binary number is always '1'
		b2[0] = '1';
		// start from the second element
		int generations = 1;
		// keep going until a null terminator is reached...
		while(input != NULL) {
			// if the input was not an "s" and not null, call 
			// reverseFamilyRelation function
			if(input != NULL && strcmp(input, "s") != 0) {
                                error = reverseFamilyRelation
                                        (b2, input, generations);
				// increment to the next generation
				generations++;
			}
			// update input with the next token
			input = strtok(NULL, "'\n ");		
		}
		// if there was no errors with the input...
		if (error == 'f') {
			printf("ahnentafel number in binary: ");
			// print the binary ahnentafel number
			for(int i = 0; i < generations; i++) 
				printf("%c", b2[i]);
			// print the decimal ahnentafel number
			printf("\nahnentafel number in base-10: %ld\n",
					convertToBaseTen(b2));
			// print the number of generations back
			genBack(generations - 1);
		}
	}
}

/*
 * command_relation function
 * appends '0' or '1' to the relation array depending on the input
 */
void command_relation(char input[], int index, char relation[]) {
	// if the input was mother or mother's append a '1'
	if((strcmp(input, "mother") == 0) || (strcmp(input, "mother's") == 0)) {
		relation[index] = '1';
	// if the input was father or father's append a '0'
	} else if((strcmp(input, "father") == 0) || 
			(strcmp(input, "father's") == 0)) {
		relation[index] = '0';
	}
}							

/*
 * getFemaleParent function
 * stores the individual's mother in the list
 */
void getFemaleParent(int list[], int index, int individual) {
	list[index] = individual * 2 + 1;
}

/*
 * getMaleParent function
 * stores the individual;s father in the list
 */
void getMaleParent(int list[], int index, int individual) {
	list[index] = individual * 2;
}

/*
 * inheritance function for option 5
 * Prompt the user to enter a number of generations back to consider within
 * the range from 0 to 9, which the program will calculate and display 
 * the ahnentafel numbers afterwards
 */
void inheritance() {
	printf("Number of generations back: ");
	// Prompts the user for number of generations back
	int generationsBack;
	scanf("%d", &generationsBack);
	// check if the input is between 0 and 9
	while(generationsBack < 0 || generationsBack > 9) {
		fprintf(stderr, "Invalid input, number of generations must be between 0 and 9!");
		printf("\nNumber of generations back: ");
		scanf("%d", &generationsBack);
	}
	// create a binary string and assign '1' to every register
	char b2[generationsBack];
	for(int i = 0; i < generationsBack; i++) {
		b2[i] = '1';
	}	
	// convert b2 into the decimal ahnentafel number of the last individual
	// in generationsBack - 1
	long int b10 = convertToBaseTen(b2);
	
	printf("Showing %d generations back: \n1, ", generationsBack);

	// list for holding decimal ahnentafel numbers of valid ancestors	
	int list[MAX];
	// list for holding decimal ahnentafel numbers of invalid ancestors
	int mark[MAX];
	// string for temporarily holding the binary ahnentafel number of 
	// the individual
	char temp[MAX];
	// the index of the mark array
	int markIndex = 0;
	// the index of the list array
	int index = 0;
	// holds 't' or 'f' depending on whether or not the individual 
	// ahnentafel number is marked
	char proceed;
	// tells what generation the individual is in
	int generations = 1;
	// holds the father's ahnentafel number
	int father = 0;
	// Iterate through each individual from the 0th generation to the
	// inputted generations back - 1
	for(int individual = 1; individual <= b10; individual++) {
		// Initially set proceed to 't' for every individual
		proceed = 't';
		// if the individual is marked, then proceed is set to 'f'
		for(int i = 0; i < markIndex; i++) {
			if(individual == mark[i])
				proceed = 'f';
		}
		// if proceed is 't' and the individual ahnentafel number
		// is even (male) then get the female parent only
		// while marking the father and his ancestry
		if(individual % 2 == 0 && proceed == 't') {
			// get the mother
			getFemaleParent(list, index, individual);
			// father's ahnentafel number
			father = individual * 2;
			// mark the father
			mark[markIndex] = father;
			markIndex++;
			// mark father's ancestry
			for(int i = 0; i < generationsBack - generations; i++) {				// mark father's father
				mark[markIndex] = father * 2;
				markIndex++;
				// mark father's mother
				mark[markIndex] = father * 2 + 1;
				markIndex++;
			}
			index++;
		// if proceed is 't' and the individual ahnentafel number is
		// odd (female) then get both parents and mark none
		} else if(individual % 2 != 0 && proceed == 't') {
			// get the father
			getMaleParent(list, index, individual);
			index++;
			// get the mother
			getFemaleParent(list, index, individual);
			index++;
		}
		// convert indivual to binary and store it in temp
		convertToBaseTwo(individual, temp);
		// calculate the generation count from the binary number
		generations = strlen(temp);
	}
	// print the list items or the ahnentafel numbers of valid individuals
	for(int i = 0; i < index; i++) { 
		printf("%d", list[i]);
		// print a comma and a space if the individual is not the last
		// one
		if(i < index - 1)
			printf(", ");
	}
	putchar('\n');
}	

/*
 * prompt function
 * Until the user specifies 6 or exit, prompt the user with the menu  
 */
void prompt() {
	// Holds the input
        char input;
        // Determines whether or not the loop should continue
        char go = 't';
	// Keep looping until the user inputs a 6 which changes go from
	// 't' to 'f'
	while(go != 'f') {
		// Prompt the user for the next command
                input = getchar();
		// Call specific functions depending on input
                switch(input) {
                        case '1':
				// Gives a description of ahnentafel
                                description();
                                menu();
                                break;
                        case '2':
				// Asks for ahnentafel number in decimal to
				// convert to binary and to calculate the 
				// number of generations back
				ahnentafel10();
                                menu();
                                break;
                        case '3':
				// Asks for ahnentafel number in binary to 
				// convert to decimal and to calculate the 
				// number of generations back
				ahnentafel2();
                                menu();
                                break;
                        case '4':
				// Asks for the family relation and print out
				// the binary and decimal ahnentafel number
				// and the number of generations back
				relation();
                                menu();
                                break;
                        case '5':
				// Asks for the number of generations back to 
				// calculate female X chromosome inheritance
				inheritance();
                                menu();
                                break;
                        case '6':
				// Sets go to 'f' which will stop the loop
                                printf("Goodbye.\n\n");
                                go = 'f';
				break;
			case '\n':
				// Ignore newline 
				break;
                        default:
				// If user entered invalid command,
                                fprintf(stderr, "Unknown Operation!\n");
				menu();
                                break;
                }
        }
}

/*
 * numTest function
 * checks if the input is a decimal number
 * @param input string 
 * return test 't' or 'f'
 */
char numTest(char input[]) {
	// initial test is 't'
	char test = 't';
	// if any of the characters in input is not an integer, set test to 'f'
	for(int i = 0; i < strlen(input); i++) {
        	if(input[i] != '0' &&
			input[i] != '1' &&
			input[i] != '2' &&
			input[i] != '3' &&
			input[i] != '4' &&
			input[i] != '5' &&
			input[i] != '6' &&
			input[i] != '7' &&
			input[i] != '8' &&
			input[i] != '9') {
			test = 'f';
        	}
	}
	return test;
}

/*
 * binaryTest function
 * checks if the input is a binary number followed by a 'b'
 * @param input string 
 * return test 't' or 'f'
 */
char binaryTest(char input[]) {
	// initial test is 't'
	char test = 't';
	// if any character besides the last character of input is not a '0;
	// or a '1' set test to 'f'
	for(int i = 0; i < strlen(input) - 1; i++) {
                if(input[i] != '0' && input[i] != '1') {
                        test = 'f';
                }
        }
	// check if the last character is a 'b' and set test to 't' or 'f'
	// accordingly
	if(input[strlen(input) - 1] != 'b') 
		test = 'f';
        return test;
}

/*
 * relationTest function
 * checks if the spelling or the input is valid
 * @param input string 
 * return test 't' or 'f'
 */
char relationTest(char input[]) {
	// initial test is 't'
	char test = 't';
	// get the first token
	char *ptr = strtok(input, "\n' ");
	// until it reaches '\0'.....
	while(ptr != NULL) {
		// if the token is not father, mother, self, or the s which is 
		// after \', set test = 'f'
		if(strcmp(ptr, "father") != 0 &&
			strcmp(ptr, "mother") != 0 &&
			strcmp(ptr, "self") != 0 &&
			(strcmp(ptr, "s") != 0 && strlen(ptr) == 1)) {
				test = 'f';
		}
		// get the next token
		ptr = strtok(NULL, "\n' ");
	}
	return test;
}

/*
 * Main function
 * @param argc Number of arguments
 * @param argv Command line arguments
 */
int main(int argc, char **argv) {
	// if there is another argument besides the filename
	if(argc >= 2) {
		// chars for holding test results to check which function 
		// to call for the command line arguments
		char b10;
		char b2;
		char relation;
		// test for decimal
		b10 = numTest(argv[1]);
		// test for binary
		b2 = binaryTest(argv[1]);
		// test for relation
		relation = relationTest(argv[1]);
		if(b10 == 't') {
			command_ahnentafel10(argv[1]);
			putchar('\n');
			return EXIT_SUCCESS;
		} else if(b2 == 't') {
			command_ahnentafel2(argv[1]);
			putchar('\n');
			return EXIT_SUCCESS;
		} else if(relation == 't') {
			// if argv[1] is self
			if(strcmp(argv[1], "self") == 0) {
				printf("ahnentafel number in binary: 1\n");
				printf("ahnentafel number in base-10: 1\n");
				genBack(0);
			// if not...
			} else {
				int generationsBack = argc - 1;
				// holds the binary number
				char binaryRelation[MAX];
				// holds the decimal number
				long int decimalRelation;
				binaryRelation[0] = '1';
				int binaryIndex = 1;
				for(int i = 1; i < argc; i++) {
					// check the input
					command_relation(argv[i],
						binaryIndex, binaryRelation);
					binaryIndex++;
				}
				// print the rest of the information
				printf("ahnentafel number in binary: ");
				for(int i = 0; i < strlen(binaryRelation); i++) 
					printf("%c", binaryRelation[i]);
				decimalRelation = convertToBaseTen
					(binaryRelation);
				printf("\nahnentafel number in base-10: %ld\n",
					decimalRelation);
				genBack(generationsBack);
			}
			putchar('\n');
			return EXIT_SUCCESS;
		} else { 
			// input is completely invalid....
			printf("Invalid argument!");
			return EXIT_FAILURE;
		}
	// Checks if there are no command line arguments
	} else if(argc < 2) {
		// Print options
		menu();
	}
	// Keeps giving user menu until they want to exit
	prompt();

	return EXIT_SUCCESS;

}
