#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXNAME 21
struct Record {
    int year;
    char name[MAXNAME];
    int freq;
    char gender;
};


//DATA RETRIEVAL/CONVERSION---------------------------------------------------------------------
void toUpper (char* str);
void normalizeName(char* str);
void retrieveData(struct Record data[], int* count);






//STARTING/ENDING FUNCTIONS---------------------------------------------------------------------------
void printWelcome();
//prints welcome message

int menuChoice();
//provides a menu that allows the user to choose an action, validates their entry, then returns the inputted value.

int redirection(struct Record data[], int dataCount, int userChoice, char name[]);
//redirection (a function) has multiple functions and calls one of those functions based on what num is in usrSelection

void printGoodbye();






//OPTION 1 FUNCTIONS----------------------------------------------------------------------------

void nameCounter(struct Record data[], int count, const char* name);
void getName(char dest[]);







//OPTION 2 FUNCTIONS-----------------------------------------------------------------------------
int yearValidation();

//find top 5 most popular name in a given year
int compareFreq(const void *a, const void *b);

void sortByF(struct Record arr[], int num);

void printTop(struct Record arr[], int num, const char *input, int year);

void addToOverall(struct Record overall[], int *bCount, struct Record r);

void topNamesOfYear(struct Record data[], int count);


//OPTION 3-----------------------------------------------------------------------------------------

void histogramD(struct Record data[], int count);
double findMaxPercentage(long long cohortName[], long long cohortTotal[], int numCohorts);
int computeBarLength(long long nameTotal, long long total, double maxPct, int maxWidth);
void buildCohortTotals(struct Record data[], int count, const char *name, long long cohortName[], long long cohortTotal[]);
int cohortIndex(int year);


//WRITETOFILE------------------------------------------------------------------------------------------
void sortRecords(struct Record data[], int count);
void writeCombinedFile(struct Record data[], int count);