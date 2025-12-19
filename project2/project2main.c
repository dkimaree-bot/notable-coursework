#include <stdio.h>
#include "project2.h"
#include <ctype.h>
#include <string.h>



int main(void) {
    
    struct Record data[180000]; //struct for babies born with a given name initialized 

    int dataCount = 0;
    char name[MAXNAME];

    retrieveData(data, &dataCount);



    printWelcome();  //welcome message

    int choice = 0;      // what the user chooses in the menu

        // ask the user what they want to do
    while (choice != 4) {
        choice = menuChoice();
        redirection(data, dataCount, choice, name);
    }

    writeCombinedFile(data, dataCount);
    //write combined file befoore exiting
    
    printGoodbye();
 
    
    return 0; 
}
