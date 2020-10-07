/*
	1. Найдите самое длинное слово в тексте
	2. Ошибка наборщика(дублирование слова). выводит слова веденные дважды
	3. АНТИПЛАГИАТ. проверка текста на плагиат(по два(три) словам. если больше 40% то плагиат)
*/

#include <iostream>
using namespace std;
#define N 512
#define PLAGIARISMRATE 40

bool isSeparator(char c);
void printfDuplicateWords(char text[]);
void copyString(char newString[], char oldString[]);
bool compareString(char newString[], char oldString[]);
void printfMaxLengthWord(char text[], char maxLengthWord[]);
void printfString(char string[]);
bool getPercentPlagiarism(char text1[], char text2[]);
bool isStringConsistPhrase(char text[], char word[]);

int main() {
	char text1[N] = "To fix        this !! error, compare compare use of identifier identifier to the identifier declaration for case and spelling. Verify that scope resolution operators and namespace using directives are used correctly!";
	//char text2[N] = "To remove this remove, functions from of the to the declaration case for case and Verify. Verscopeify that Verify namespace operators and directives using used are used correctly!";
	char text2[N] = "Changes to remove obsolete functions from the C Runtime Library in Visual Studio 2015 can cause C3861. To resolve this error, remove references to these functions or replace them with their secure alternatives, if any. For more information, see Obsolete Functions!";
	char maxLengthWord[N];

	cout << "Task 1. Longest word in the text: ";
	printfMaxLengthWord(text1, maxLengthWord);
	printfString(maxLengthWord);
	
	cout << endl << endl << "Task 2. Find duplicate words:" << endl;
	printfDuplicateWords(text1);

	cout << endl << "Task 3. Plagiarism." << endl;
	cout << "Text1:" << endl;
	printfString(text1);
	cout << endl << "Text2:" << endl;
	printfString(text2);
	if (getPercentPlagiarism(text1, text2))
		cout << endl << "Text1 and text2 - plagiarism.";
	else
		cout << endl << "Text1 and text2 are not plagiarized.";

	return 0;
}

bool getPercentPlagiarism(char text1[], char text2[])
{
	char word[N];
	int length = 0, sameWords = 0, wordText1 = 0;
	for (int i = 0; text1[i] != '\0'; i++)
	{
		if (isSeparator(text1[i]) != true) {
			word[length] = text1[i];
			length++;
			if (isSeparator(text1[i + 1]) or text1[i + 1] == '\0') {
				word[length] = '\0';
				length = 0;

				wordText1++;
				if (isStringConsistPhrase(text2, word) == true)
				{
					sameWords++;
				}
			}
		}
	}

	double procentPlagiarism = 100 * sameWords / wordText1;
	if (PLAGIARISMRATE <= procentPlagiarism)
		return true;
	else
		return false;
}

bool isStringConsistPhrase(char text[], char word[])
{
	for (int i = 0; text[i] != '\0'; i++)
	{
		for (int j = 0; word[j] != '\0'; j++)
		{
			if (word[j] != text[i + j])
				break;
			if (word[j + 1] == '\0')
			{
				return true;
			}
		}
	}
	return false;
}

void printfString(char string[])
{
	for (int i = 0; string[i] != '\0'; i++)
		cout << string[i];
}

bool isSeparator(char c) {
	char separator[] = " ,.;:?!";
	for (int i = 0; separator[i] != '\0'; i++)
		if (c == separator[i])
			return true;
	return false;
}

void printfMaxLengthWord(char text[], char maxLengthWord[])
{
	char word[N];
	int length = 0;
	int max = 0;

	for (int i = 0; text[i] != '\0'; i++)
	{
		if (isSeparator(text[i]) != true) {

			word[length] = text[i];
			length++;
			if (isSeparator(text[i + 1]) or text[i + 1] == '\0') {
				word[length] = '\0';
				if (max < length)
				{
					max = length;
					copyString(word, maxLengthWord);
				}
				length = 0;
			}
		}
	}
}

void printfDuplicateWords(char text[])
{
	char oldWord[N], newWord[N];
	int iw = 0;

	for (int i = 0; text[i] != '\0'; i++)
	{
		if (isSeparator(text[i]) != true) {
			newWord[iw] = text[i];
			iw++;
			if (isSeparator(text[i + 1]) or text[i + 1] == '\0') {
				newWord[iw] = '\0';
				iw = 0;
				if (compareString(newWord, oldWord))
					cout << newWord << endl;
				copyString(newWord, oldWord);
			}
		}
	}
}

void copyString(char string[], char emptyString[]) 
{
	int i = 0;
	for (i; string[i] != '\0'; i++)
	{
		emptyString[i] = string[i];
	}
	emptyString[i] = '\0';
}

bool compareString(char newString[], char oldString[])
{
	for (int i = 0; newString[i] != '\0'; i++)
	{
		if (newString[i] != oldString[i])
			return false;
	}
	return true;
}