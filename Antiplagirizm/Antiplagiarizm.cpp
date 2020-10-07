#include <iostream>
using namespace std;
#define N 512
#define PLAGIARISMRATE 40
#define WORDSINPHRASE 3

double getPercentPlagiarism(char myText[], char originalText[]);
bool isStringConsistPhrase(char text[], char word[]);
void copyString(char newString[], char oldString[]);
bool compareString(char newString[], char oldString[]);
bool isSeparator(char c);
void printfString(char string[]);
void normalizerString(char string[]);
void clearExcessSymbol(char string[]);
void convertStringToLowerCase(char string[]);

int main() 
{	
	        char myText[N] = "love ,,,, play ?? in..,.,., footbol !!!ivnin????";
	//char originalText[N] = "i love play in footbol ivning";
	char originalText[N] = "To error i compare play footbol in compare use of identifier identifier to the identifier declaration for case and spellg Verify that scope resolution operators and namespace using directives are correctly";
	//char originalText[N] = "To remove this remove, functions from of the to the declaration case for case and Verify. Verscopeify that Verify namespace operators and directives using used are used correctly!";
	//char originalText[N] = "Changes to I love play in footbol ivning To fix this remove obsolete functions from the C Runtime Library in Visual Studio 2015 can cause C3861 To resolve this error remove references to these functions or replace them with their secure alternatives if any For more information see Obsolete Functions";
	
	cout << "myText:" << endl;
	printfString(myText);
	cout << endl << "originalText:" << endl;
	printfString(originalText);

	normalizerString(myText);
	normalizerString(originalText);

	cout << endl << endl << "myText norm:" << endl;
	printfString(myText);
	cout << endl << "originalText norm:" << endl;
	printfString(originalText);

	double percentPlagiarism = getPercentPlagiarism(myText, originalText);

	if (percentPlagiarism >= PLAGIARISMRATE)
		cout << endl << endl << " MyText and originalText - plagiarism.";
	else
		cout << endl << endl << "MyText and originalText - are not plagiarized.";
	cout << " PercentPlagiarism - " << percentPlagiarism << " %.";

	return 0;
}

void normalizerString(char string[])
{
	clearExcessSymbol(string);
	convertStringToLowerCase(string);
}

void clearExcessSymbol(char string[])
{
	char tempString[N];
	bool isPreviousValueSpace = false;
	int i = 0, countMissValue = 0;

	copyString(string, tempString);
	
	for (i; tempString[i] != '\0'; i++)
	{
		if (isPreviousValueSpace == true and tempString[i] == ' ' or isSeparator(tempString[i]))
		{
			countMissValue++;
			continue;
		}
		else if (tempString[i] == ' ')
			isPreviousValueSpace = true;
		
		string[i - countMissValue] = tempString[i];
		
		if (string[i - countMissValue] != ' ')
			isPreviousValueSpace = false;
	}
	string[i - countMissValue] = '\0';
}

bool isSeparator(char c) 
{
	char separator[] = ",.;:?!()*^№<>/{}[]&-=+#@";
	for (int i = 0; separator[i] != '\0'; i++)
		if (c == separator[i])
			return true;
	return false;
}

void convertStringToLowerCase(char string[])
{
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (string[i] >= 'A' and string[i] <= 'Z')
		{
			string[i] += 32;
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

bool isStringConsistPhrase(char text[], char phrase[])
{
	for (int i = 0; text[i] != '\0'; i++)
	{
		for (int j = 0; phrase[j] != '\0'; j++)
		{
			if (phrase[j] != text[i + j])
				break;
			if (phrase[j + 1] == '\0')
				return true;
		}
	}
	return false;
}

void printfString(char string[])
{
	for (int i = 0; string[i] != '\0'; i++)
		cout << string[i];
}

double getPercentPlagiarism(char myText[], char originalText[])
{
	char phrase[N];
	int length = 0, coincidences = 0, countWordMyText = 0, countSpace = 0, indexStartSecondWord = 0;  // i love play in footbol ivning
	bool isEnd = false;

	int i = 0;
	while (isEnd != true)
	{
		if (myText[i + 1] == '\0')
			isEnd = true;

		phrase[length] = myText[i];
		length++;

		if ((myText[i + 1] == ' ' or myText[i + 1] == '\0') and countSpace < WORDSINPHRASE)
		{
			if (countSpace == 0)
				indexStartSecondWord = i + 1;

			countWordMyText++;
			countSpace++;
			if (countSpace == WORDSINPHRASE)
			{
				phrase[length] = '\0';
				length = 0;
				countSpace = 0;

				if (isStringConsistPhrase(originalText, phrase))
					coincidences++;
				i = indexStartSecondWord;
			}
		}

		i++;
	}

	return 100 * coincidences  * WORDSINPHRASE / countWordMyText;
}