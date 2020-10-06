#include <iostream>
using namespace std;
#define N 512
#define PLAGIARISMRATE 40

bool isPlagiarism(char myText[], char originalText[]);
bool isStringConsistWord(char text[], char word[]);
void copyString(char newString[], char oldString[]);
bool compareString(char newString[], char oldString[]);
bool isSeparator(char c);
void printfString(char string[]);

int main() {
	char myText[N] = "To fix this error, compare compare use of identifier identifier to the identifier declaration for case and spelling. Verify that scope resolution operators and namespace using directives are used correctly!";
	//char text2[N] = "To remove this remove, functions from of the to the declaration case for case and Verify. Verscopeify that Verify namespace operators and directives using used are used correctly!";
	char originalText[N] = "Changes to remove obsolete functions from the C Runtime Library in Visual Studio 2015 can cause C3861. To resolve this error, remove references to these functions or replace them with their secure alternatives, if any. For more information, see Obsolete Functions!";
	
	
	cout << "myText:" << endl;
	printfString(myText);
	cout << endl << "originalText:" << endl;
	printfString(originalText);

	if (isPlagiarism(myText, originalText) == true)
		cout << endl << "MyText and originalText - plagiarism.";
	else
		cout << endl << "MyText and originalText - are not plagiarized.";

	return 0;
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

bool isSeparator(char c) {
	char separator[] = " ,.;:?!";
	for (int i = 0; separator[i] != '\0'; i++)
		if (c == separator[i])
			return true;
	return false;
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

bool isStringConsistWord(char text[], char word[])
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

bool isPlagiarism(char myText[], char originalText[])
{
	char word[N];
	int length = 0, sameWords = 0, wordText1 = 0;
	for (int i = 0; myText[i] != '\0'; i++)
	{
		if (isSeparator(myText[i]) != true) {
			word[length] = myText[i];
			length++;
			if (isSeparator(myText[i + 1]) or myText[i + 1] == '\0') {
				word[length] = '\0';
				length = 0;

				wordText1++;
				if (isStringConsistWord(originalText, word) == true)
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