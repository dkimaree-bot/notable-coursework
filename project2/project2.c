#include <stdio.h>
#include "project2.h"
#include <ctype.h>
#include <string.h>



//DATA RETRIEVAL/CONVERSION------------------------------------------------------------------------------
//moves data from file into the array of structs
void retrieveData(struct Record data[], int* count){

int year;
int freq;
char name[MAXNAME];

*count = 0;

    FILE* fnamefp = fopen("femalebabynames.csv", "r");

    if(fnamefp == NULL){
        printf("Could not open the female baby name file.\n");
    }

    fscanf(fnamefp, "%*[^\n]\n");


    while (fscanf(fnamefp, "%d,%[^,],%d", &year, name, &freq) == 3){
        toUpper(name); //convert before storing

        data[*count].year = year;
        strcpy(data[*count].name, name);
        data[*count].freq = freq;
        data[*count].gender = 'F';
        (*count)++;
    }

    fclose(fnamefp);



    FILE* mnamefp = fopen("malebabynames.csv", "r");


    if(mnamefp == NULL){
        printf("Could not open the male baby name file.\n");
    }

    fscanf(mnamefp, "%*[^\n]\n");

    while (fscanf(mnamefp, "%d,%20[^,],%d", &year, name, &freq) == 3){
        toUpper(name);

        data[*count].year = year;
        strcpy(data[*count].name, name);
        data[*count].freq = freq;
        data[*count].gender = 'M';
        (*count)++;
    }

     fclose(mnamefp);

    
}

void toUpper(char* str) {
    int i;
    for (i = 0; str[i] != '\0'; i++)
        str[i] = toupper(str[i]);
}

void normalizeName(char* str) {
    char newStr[21];
    int j = 0;

    for (int i = 0; str[i] != '\0' && j < 20; i++) {
        if (isalpha(str[i]) || str[i] == ' ' || str[i] == '-') 
        {
            newStr[j++] = str[i];
        }
        // ignore everything else
    }

    newStr[j] = '\0';
    strcpy(str, newStr);
}






//STARTING/ENDING FUNCTIONS---------------------------------------------------------------------------

//prints welcome message
void printWelcome(){
    printf("oooo     oooo ooooooooooo ooooo          oooooooo8   ooooooo   oooo     oooo ooooooooooo\n");
    printf(" 88   88  88   888    88   888         o888     88 o888   888o  8888o   888   888    88 \n");
    printf("  88 888 88    888ooo8     888         888         888     888  88 888o8 88   888ooo8  \n");
    printf("   888 888     888    oo   888      o  888o     oo 888o   o888  88  888  88   888    oo  \n");
    printf("    8   8     o888ooo8888 o888ooooo88   888oooo88    88ooo88   o88o  8  o88o o888ooo8888  \n");


    printf(" _____ _____ _____ __ __    _____ _____ _____ _____    ____  _____ _____ _____    _____ _____ _____ _ _ _ _____ _____ \n");
    printf("| __  |  _  | __  |  |  |  |   | |  _  |     |   __|  |    \\|  _  |_   _|  _  |  |  |  |     |   __| | | |   __| __  |\n");
    printf("| __ -|     | __ -|_   _|  | | | |     | | | |   __|  |  |  |     | | | |     |  |  |  |-   -|   __| | | |   __|    -|\n");
    printf("|_____|__|__|_____| |_|    |_|___|__|__|_|_|_|_____|  |____/|__|__| |_| |__|__|   \\___/|_____|_____|_____|_____|__|__|\n");
    printf("\nLets get started! What are you here to do?\n\n\n");

}

//provides a menu that allows the user to choose an action, validates their entry, then returns the inputted value.
int menuChoice(){
    
    int userChoice;
                                                                                 
    printf("                     ____ ____ ____ ____ \n");
    printf("                    ||m |||e |||n |||u ||\n");
    printf("--------------------||__|||__|||__|||__||--------------------\n");
    printf("                    |/__\\|/__\\|/__\\|/__\\|\n\n");

              
    printf("\t1. Number of babies born with a given name\n");
    printf("\t2. Top 5 names in a given year\n");
    printf("\t3. A histogram of a given name's popularity over time\n");
    printf("\t4. Exit program\n");
    printf("\nPlease enter a number: ");

    scanf("%d", &userChoice);
    

    while(userChoice < 1 || userChoice > 4){
        printf("Error! Number MUST be between 1 and 4 inclusive!\n");
        printf("Please enter again: ");

        scanf("%d", &userChoice);
    }


   return userChoice;
}


//redirection (a function) has multiple functions and calls one of those functions based on what num is in usrSelection
int redirection(struct Record data[], int dataCount, int userChoice, char name[]){

    if(userChoice == 1){
        printf("\nAwesome!\n");
        getName(name);
        nameCounter(data, dataCount, name);

    }

    else if(userChoice == 2){
    
        printf("Understood.\n");
        topNamesOfYear(data, dataCount);

        return 0;
    }

    else if(userChoice == 3){
        printf("Good choice!!\n");
        histogramD(data, dataCount);

    }


return 0;

}

void printGoodbye(){

    printf("     _        ___    _      _    _   _  __     __   _      \n");
    printf(" )_) /_) \\  / )_     /_)    / _  / ) / ) ) )    ) ) /_) \\_) \n");
    printf("( ( / /   \\/ (__    / /    (__/ (_/ (_/ /_/    /_/ / /   / \n");

}



//OPTION 1 FUNCTIONS----------------------------------------------------------------------------
void getName(char dest[]){
    char name[21];
    printf("Please enter the name: ");
    scanf(" %20[^\n]", name);

    toUpper(name);
    normalizeName(name);


    strcpy(dest, name);

    
}

void nameCounter(struct Record data[], int count, const char* name) {

    int totalMname = 0;
    int totalFname = 0;

    printf("\nThe following is the yearly results for %s:\n", name);

    int year;
    for (year = 1914; year <= 2023; year++) {
        int yearCount = 0;

    int i;
        for (i = 0; i < count; i++) {
            if (data[i].year == year && strcmp(data[i].name, name) == 0) {
                yearCount += data[i].freq;

                if (data[i].gender == 'M'){
                    totalMname += data[i].freq;
                
                }

                else{
                    totalFname += data[i].freq;
                }
            }
        }

        if (yearCount > 0) {
            printf("%d: %d babies\n", year, yearCount);
        }
    }

    int total = totalMname + totalFname;

    printf("\nTotals:\n");
    printf("Female: %d\n", totalFname);
    printf("Male:   %d\n", totalMname);
    printf("Total:  %d\n", total);
}





//OPTION 2 FUNCTIONS-----------------------------------------------------------------------------
int yearValidation(){
   int year;
    printf("Please enter the year: ");
    scanf("%d", &year);

    while(year < 1914 || year > 2023){
        printf("\nYear entered is invalid. The year MUST be between 1914 and 2023 inclusive!!\n");
        printf("Please enter again: ");

        scanf("%d", &year);
    }

    //printf("Results for %d: \n", year);

    return year;

}

int compareFreq(const void *freqOne, const void *freqTwo) {
    return ((struct Record*)freqTwo)->freq - ((struct Record*)freqOne)->freq;
}

void addToOverall(struct Record overall[], int *bCount, struct Record temp) {
    for (int i = 0; i < *bCount; i++) {
        if (strcmp(overall[i].name, temp.name) == 0) {
            overall[i].freq += temp.freq;
            return;
        }
    }
    overall[*bCount] = temp;
    (*bCount)++;
}

void topNamesOfYear(struct Record data[], int count) { 
    int year;
    year = yearValidation();

    struct Record female[6000]; //struct initialization for year given (females)
    struct Record male[6000]; //struct initialization for year given (males)
    struct Record overall[6000]; //struct initialization for year given (both genders)

    int fCount = 0;
    int mCount = 0;
    int bothCount = 0;


    // collect year data
    for (int i = 0; i < count; i++) {
        if (data[i].year == year) {
            if (data[i].gender == 'F')
                female[fCount++] = data[i];
            else
                male[mCount++] = data[i];
        }
    }

    // increase overall
    for (int i = 0; i < fCount; i++)
        addToOverall(overall, &bothCount, female[i]);

    for (int i = 0; i < mCount; i++)
        addToOverall(overall, &bothCount, male[i]);

    // sort
    sortByF(female, fCount);
    sortByF(male, mCount);
    sortByF(overall, bothCount);

    // print
    printTop(female,  fCount, "FEMALE", year);
    printTop(male,    mCount, "MALE", year);
    printTop(overall, bothCount, "OVERALL", year);
}

void sortByF(struct Record arr[], int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (arr[j].freq < arr[j+1].freq) {
                struct Record temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void printTop(struct Record arr[], int num, const char *input, int year) {
    printf("\nTop 5 %s names in %d:\n", input, year);
    for (int i = 0; i < 5 && i < num; i++)
        printf("%d. %s (%d)\n", i+1, arr[i].name, arr[i].freq);
}





//OPTION 3--------------------------------------------------------------------------------------


// figure out which cohort a year belongs to
int cohortIndex(int year) {
    int index = -1;
    
    if (year >= 1914 && year <= 2023) {
        index = (year - 1914) / 5;
    }
    
    return index;
}

// scan entire dataset and build cohort totals
void buildCohortTotals(struct Record data[], int count, const char *name, long long cohortName[], long long cohortTotal[]) {
    for (int i = 0; i < count; i++) {
        int idx = cohortIndex(data[i].year);
        
        if (idx >= 0) {
            cohortTotal[idx] += data[i].freq;
            
            if (strcmp(data[i].name, name) == 0) {
                cohortName[idx] += data[i].freq;
            }
        }
    }
}


//compute bar length relative to the max
int computeBarLength(long long nameTotal, long long total, double maxPercent, int maxWidth) {
    int len;
    double percent;
    double scaledPercent;
    
    //1. check for valid data
    if (total == 0 || maxPercent == 0.0) {
        len = 0;
    }
    else {
        // 2. calculate what percentage the cohort is
        // ex: 5 babies named bob out of 25 total = 0.20 (20%)
        percent = (double)nameTotal / (double)total;
        
        //3. scale it relative to the highest
        scaledPercent = percent / maxPercent;
        
        //4. convert to number of stars
        //would be something like 0.5 × 60 = 30 stars
        len = (int)(scaledPercent * maxWidth + 0.5);
        
        //5. make sure it doesnt go over the max
        if (len > maxWidth) {
            len = maxWidth;
        }
    }
    
    return len;
}


//histogramD function
void histogramD(struct Record data[], int count) {
    char name[21];
    getName(name);
    
    const int numCohorts = 22;
    long long cohortName[22] = {0};
    long long cohortTotal[22] = {0};
    
    buildCohortTotals(data, count, name, cohortName, cohortTotal);
    
    //find the maxpercentage
    double maxPercent = findMaxPercentage(cohortName, cohortTotal, numCohorts);
    
    if (maxPercent == 0.0) {
        printf("\nNo data found for name: %s\n", name);
        return;
    }
    
    printf("\nHistogram for %s:\n", name);
    printf("(Bars scaled to this name's most popular period)\n\n");
        
    
    const int maxBar = 60;
    
    //print from newest to oldest
    for (int i = numCohorts - 1; i >= 0; i--) {
        int startYear = 1914 + (i * 5);
        int endYear = startYear + 4;
        if (endYear > 2023) endYear = 2023;
        
        int barLen = computeBarLength(cohortName[i], cohortTotal[i], maxPercent, maxBar);
        
        printf("%d-%d | ", startYear, endYear);
        for (int i = 0; i < barLen; i++) {
            printf("*");
        }
        printf("\n");
    }
}


// find the maximum percentage across cohorts
double findMaxPercentage(long long cohortName[], long long cohortTotal[], int numCohorts) {
    double maxPercent = 0.0;
    
    for (int i = 0; i < numCohorts; i++) {
        if (cohortTotal[i] > 0) {
            double percent = (double)cohortName[i] / (double)cohortTotal[i];
            if (percent > maxPercent) {
                maxPercent = percent;
            }
        }
    }
    
    return maxPercent;
}





//WRITETOFILE--------------------------------------------------------------------------------------
void sortRecords(struct Record data[], int count) {
    int i, j, minIdx;
    struct Record temp;
    
    for (i = 0; i < count - 1; i++) {
        minIdx = i;
        
        //find the minimum i
        for (j = i + 1; j < count; j++) {
            int shouldReplace = 0;
            
            //compare year
            if (data[j].year < data[minIdx].year) {
                shouldReplace = 1;
            }
            else if (data[j].year == data[minIdx].year) {
                //if years are equal then compare names
                if (strcmp(data[j].name, data[minIdx].name) < 0) {
                    shouldReplace = 1;
                }
            }
            
            if (shouldReplace) {
                minIdx = j;
            }
        }
        
        if (minIdx != i) {
            temp = data[i];
            data[i] = data[minIdx];
            data[minIdx] = temp;
        }
    }
}



void writeCombinedFile(struct Record data[], int count) {
    FILE *fp;
    int i;
    
    printf("\nSorting data for combined file\n");
    sortRecords(data, count);
    
    fp = fopen("combined.txt", "w");
    
    if (fp == NULL) {
        printf("Error: Could not create combined.txt\n");
    }
    else {
        i = 0;
        while (i < count) {
            int totalFreq = data[i].freq;
            int year = data[i].year;
            char name[MAXNAME];
            strcpy(name, data[i].name);
            
            // combine matching records 
            i++;

            while (i < count && data[i].year == year && strcmp(data[i].name, name) == 0) {
                totalFreq += data[i].freq;
                i++;
            }
            
            //write combined entry
            fprintf(fp, "%d,%s,%d\n", year, name, totalFreq);
        }
        
        fclose(fp);

        printf("Data written to combined.txt\n");
    }
}