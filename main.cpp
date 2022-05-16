//Program 3: Typing
//    Displays random words from dictionary and misspelled words
//
//System: Mac using Xcode

//Running the program looks like:

//          There are 263533 words in the full dictionary.
//          There are 114 commonly misspelled words.
//
//          Select a menu option:
//             1. Spell commonly misspelled words (timed)
//             2. Type random words from full dictionary (timed)
//             3. Display some words from one of the lists
//             4. Use binary search to lookup a word in full dictionary
//             5. Set word length to use with full dictionary
//             6. Exit the program
//          Your choice -->
//
//                              ..............

#include <iostream>     //header for input output functions
#include<fstream>       //header for file functions
#include<vector>        //header for vector function
#include<cassert>       //header to assert if the file opened
#include<cctype>        //header for toupper function
#include<ctime>         //header for time keeping
using namespace std;    //So that we don't need to preface cin and cout with std::

//READ DICTIONARY WORDS FROM FILE TO A VECTOR
void readWordsIntoDictionary( vector <string> & dictionary){
    
   // Read in dictionary into dictionary vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( "dictionary.txt");       // Open dictionary file
    assert( inStream.fail() == false );     // Ensure file open worked
    
    // If you had previously used vector dictionary, then you might want to clear it
    // before continuing to use it, though that is not the case here.
    dictionary.clear();
    
    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while( inStream >> newWord) {           // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        dictionary.push_back( newWord);
    }
    
    // Close the dictionary file
    inStream.close();
}

//READ MISSPELLED WORDS FROM FILE TO A VECTOR
void readWordsIntoMisspelledWords( vector <string> & misspelledWords)
{
   // Read in dictionary into dictionary vector
    ifstream onStream;                      // Declare an input stream for reading
    onStream.open( "misspelledWords.txt");       // Open dictionary file
    assert( onStream.fail() == false );     // Ensure file open worked
    
    // If you had previously used vector dictionary, then you might want to clear it
    // before continuing to use it, though that is not the case here.
    misspelledWords.clear();
    
    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while( onStream >> newWord) {           // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        misspelledWords.push_back( newWord);
    }
    
    // Close the dictionary file
    onStream.close();
}

//SPLIT MISSPLELLED WORDS IN RIGHT AND WRONG
void split_misspelledWords(vector <string> & misspelledWords_wrong, vector <string> & misspelledWords_correct,vector <string> misspelledWords){
    
    //a loop to split correct misspelled words from wrong misspelled words by checking their index value (even or odd)
    for(long unsigned int i = 0 ; i<misspelledWords.size() ; i++){
        if(i%2==0)
            misspelledWords_wrong.push_back(misspelledWords.at(i));
      
        else
            misspelledWords_correct.push_back(misspelledWords.at(i));
    }
}

//DISPLAY THE TIME TAKEN TO MAKE A MOVE AND DISPLAY THE WRONG WORDS FOR OPTION 1 AND 2
void displayMispelledWordsANDtimeTaken(int incorrectWord, vector <string> incorrectWords, vector <string> correctWords_toDisplay, int &bonusDifference, int &pointBonus, int elapsedSeconds){
    
    //if incorrect words are entered
    if(incorrectWord>0){
       cout<<" Misspelled words:"<<endl;
       for(int i =0 ; i<incorrectWord ; ++i){
          cout<<"     "<<incorrectWords.at(i)<<" should be: "<<correctWords_toDisplay.at(i)<<endl;
          }
    }
    //if no incorrect words are entered
    else{
        cout<<"No misspelled words!"<<endl;
    }
     
    //calculte the timwe more or less than 15 seconds and display the timescore accordingly
    bonusDifference = 15 - elapsedSeconds;
    cout << "Elapsed time: " << elapsedSeconds << " seconds. ";
    if(elapsedSeconds>15){
        pointBonus = 3 * bonusDifference;
        bonusDifference = -bonusDifference;
        cout<<pointBonus<<" point bonus for finishing "<<bonusDifference<<" seconds late."<< endl;
    }
    else if(elapsedSeconds<15){
        pointBonus = 2 * bonusDifference;
        cout<<pointBonus<<" point bonus for finishing "<<bonusDifference<<" seconds early."<< endl;
    }
}

//DISPLAY RANDOM WORDS FROM DICTIONARY AND DISPLAY THE SCORE
void optionOne(vector <string> misspelledWords_wrong, vector <string> misspelledWords_correct, int &finalScore){
    int elapsedSeconds = 0, pointBonus = 0, bonusDifference = 0, correctWord = 0, incorrectWord = 0, pointCorrect = 0, pointWrong = 0, total = 0 ;
    long unsigned int size = misspelledWords_wrong.size();
    string random_words[5], answer;                     //intialise vectors and variables for score calculation, storing user input, and computation
    vector <string> userInput;
    vector <string> incorrectWords;
    vector <string> correctWords;
    vector <string> correctWords_toDisplay;
   cout<<"Using commonly misspelled words"<<endl;
   
    //a loop to generate 5 random words
   for( int i = 0; i < 5; i++){
      int position = rand() % (size);
      random_words[i] = misspelledWords_wrong.at(position);
      correctWords.push_back(misspelledWords_correct.at(position));
      cout << random_words[i] <<" ";
    }
    cout << endl;
    
    //a loop to take 5 user input
    cout<<"Type in those words within goal of 15 seconds:"<<endl;
    time_t startTime = time( NULL);
    for(int i =0; i<5; ++i){
        cin>>answer;
        userInput.push_back(answer);
    }
    
    elapsedSeconds = difftime( time( NULL), startTime);
    
    //a loop to check nu=mber of correct and incorrect words
    for(int i = 0 ; i<5 ; ++i){
       if(userInput.at(i) == correctWords.at(i)){
          correctWord++;
       }
       
       else{
       incorrectWords.push_back(userInput.at(i));
       correctWords_toDisplay.push_back(correctWords.at(i));
       incorrectWord++;
       }
    }
      
    // a function to calculate time taken and display the incorrect words
    displayMispelledWordsANDtimeTaken(incorrectWord, incorrectWords, correctWords_toDisplay, bonusDifference, pointBonus, elapsedSeconds);
    
    //compute the score
    pointCorrect = 3 * correctWord;
    pointWrong = 6 * incorrectWord;
    total = pointBonus + pointCorrect - pointWrong;
    
    //check if previous score was greater than the present score
    if(total>finalScore && total>0)
      finalScore = total;

    //display the score
    cout<<pointCorrect<<" points: "<<correctWord<<" spelled correctly x 3 points each"<<endl;
    if(incorrectWord>0)
       cout <<pointWrong<<" point penalty: "<<incorrectWord<<" spelled incorrectly x 6 points each"<<endl;
    
    cout <<"Score: "<<total<<endl;
}

//DISPLAY RANDOM WORDS FROM MISSPELLED WORDS AND DISPLAY THE SCORE
void optionTwo(vector <string> dictionary, int &finalScore, int &noOfLetters){
    int i = 0, elapsedSeconds = 0, pointBonus = 0, bonusDifference = 0, correctWord = 0, incorrectWord = 0, pointCorrect = 0, pointsPerWord, pointWrong = 0, total = 0;
    long unsigned int size = dictionary.size();
    string random_words[5], answer;
    vector <string> userInput;                      //intialise vectors and variables for score calculation, storing user input, and computation
    vector<string> incorrectWords;
    vector<string>correctWords_toDisplay;
    cout<<"Using full dictionary"<<endl;
    
    //a loop to generate 5 random words fro mthe dictionary
    while(i<5){
        int randNum = rand()%(size);
        if(dictionary.at(randNum).length() == noOfLetters){             //check for the length of the random words is equal to length of the characters to be printed
            random_words[i] = dictionary.at(randNum);
            cout << random_words[i] <<" ";
            i++;
        }
    }
    cout << endl;
    
    cout<<"Type in those words within goal of 15 seconds:"<<endl;
    time_t startTime = time( NULL);
    
    //a loop to take 5 user input for the rando words
    for(int i =0; i<5; ++i){
        cin>>answer;
        userInput.push_back(answer);
    }
    
    elapsedSeconds = difftime( time( NULL), startTime);
    
    //a loop to check for number of correct and incorrect words
    for(i = 0 ; i < 5 ; i++){
        for(long unsigned int j =0 ;j < size ; j++){
            if(random_words[i] == dictionary.at(j)){
                if(userInput.at(i) == dictionary.at(j)){
                    correctWord++;
                }
                else{
                    incorrectWords.push_back(userInput.at(i));
                    correctWords_toDisplay.push_back(dictionary.at(j));
                    incorrectWord++;
                }
            }
        }
    }
    
    //a function to display time taken for the moves and display incorrect words
    displayMispelledWordsANDtimeTaken(incorrectWord, incorrectWords, correctWords_toDisplay, bonusDifference, pointBonus, elapsedSeconds);
    
    //compute the score
    pointsPerWord = noOfLetters - 4;
    pointCorrect = pointsPerWord * correctWord;
    pointWrong = pointsPerWord * 2 * incorrectWord;
    total = pointBonus + pointCorrect - pointWrong;
    
    //check if previous score was greater
    if(total>finalScore && total>0)
        finalScore = total;
    
    //display the score
    cout<<pointCorrect<<" points: "<<correctWord<<" spelled correctly x "<<pointsPerWord<<" points each"<<endl;
    if(incorrectWord>0)
        cout <<pointWrong<<" point penalty: "<<incorrectWord<<" spelled incorrectly x "<<pointsPerWord*2<<" points each"<<endl;
    cout <<"Score: "<<total<<endl;
    
    //increment the number of characters after execution
    ++noOfLetters;
    
}

//DISPLAY A SET A WORDS FROM CERTAIN INDICES ACCORDING TO USER FROM DICTIONARY AND MISSPELLED WORDS
void optionThree(vector <string> dictionary, vector <string> misspelledWords, vector <string> misspelledWords_wrong, vector <string> misspelledWords_correct ){
    
    int start, end;         //intialise start, end and the user choice
    char choice;
    cout<<"Displaying word list entries."<<endl                 //display the menu options
        <<"Which words do you want to display?"<<endl
        <<"  A. Dictionary of all words"<<endl
        <<"  B. Wrongly spelled common misspelled words"<<endl
        <<"  C. Correctly spelled common misspelled words"<<endl
        <<"Your choice -->";
    cin>>choice;
    choice = toupper(choice);                           //change the choice to upper case
    
    //a switch statement to check the user choice
    switch(choice){
        case 'A': {
            cout<<"Enter the start and end indices between 0 and 263532: ";             //case A - to display words from the dictionary
            cin>>start>>end;
            for(int i=start; i<=end; ++i)
               cout<<i<<". "<<dictionary.at(i)<<endl;
            break;
        }
        case 'B': {
            cout<<"Enter the start and end indices between 0 and 113: ";            //case B - to display incorrect words from Misspelled words database
            cin>>start>>end;
            for(int i=start; i<=end; ++i)
               cout<<i<<". "<<misspelledWords_wrong.at(i)<<endl;
            break;
        }
        case 'C': {
            cout<<"Enter the start and end indices between 0 and 113: ";           //case C - to display correct words from Misspelled words database
            cin>>start>>end;
            for(unsigned long int i = start; i <= end; ++i)
               cout<<i<<". "<<misspelledWords_correct.at(i)<<endl;
            break;
        }
    }
}

//SEARCH FOR A WORD FROM THE DICTIONARY USING BINARY SEARCH
void optionFour(vector <string> dictionary){
    
    int moveNumber = 1, found=0;           //intialise move number and found value (0 or 1)
    unsigned long int high = dictionary.size()-1,  mid = 0, low = 0;            //intialise low mid high for binary search
    string someWord;
    cout<<"Enter the word to lookup:";
    cin>>someWord;                  //take user input for word to search in the dictionary
    cout<<endl;
    
    //a loop to binary search the word in the dictionary
    while(low<=high){
        mid = (low+high)/2;
        cout<<moveNumber<<". Comparing to: "<<dictionary.at(mid)<<endl;
        ++moveNumber;
        //if the word is found
        if(dictionary.at(mid) == someWord){
            cout<<someWord<<" was found."<<endl;
            found++;
            break;
        }
        //if the word is greater than the mid value of dictionary
        else if(someWord>dictionary.at(mid)){
            low = mid+1;
        }
        //if the word is less than the mid value of dictionary
        else if(someWord<dictionary.at(mid)){
            high = mid-1;
        }
    }
    //if word is not found
    if(found == 0)
        cout<<someWord<<" was NOT found."<<endl;
}

//CHANGE THE LENGTH OF THE WORDS USED FOR OPTION 2 ACCORDING TO THE USER
void optionFive(int &noOfLetters){
    cout<<"Enter new wordLength: ";
    //user input for number of characters to be displayed in each word in option 2
    cin>>noOfLetters;
}

//MAIN FUNCTION , WHERE THE PROGRAM EXECUTION STARTS
int main() {
    
    int choice=0, finalScore = 0, noOfLetters=5;            //initialise user choice, score at the end, characters for option 2,
    vector< string> dictionary;                             //intialise vector for dictionary
    vector< string> misspelledWords;                        //intialise vector for misspelled words
    vector< string> misspelledWords_wrong;                  //intialise vector for wrong misspelled words
    vector< string> misspelledWords_correct;                //intialise vector for right misspelled words
    readWordsIntoMisspelledWords( misspelledWords);         //function call to read misspelled words into vector
    readWordsIntoDictionary( dictionary);                   //function call to read dictionary words into vector
    split_misspelledWords(misspelledWords_wrong, misspelledWords_correct, misspelledWords);            //function call to split wrong ang right misspelled words
    srand(1);                                               // Seed the random numbert to 1
    
    cout<<"There are "<<dictionary.size()<<" words in the full dictionary."<<endl
        <<"There are "<<misspelledWords_wrong.size()<<" commonly misspelled words."<<endl;          //display number of dictionary and misspelled words
     
    while(choice!=6){                                                           //menu options for user to choose from
        cout<<"Select a menu option:"<<endl
            <<"   1. Spell commonly misspelled words (timed)"<<endl
            <<"   2. Type random words from full dictionary (timed)"<<endl
            <<"   3. Display some words from one of the lists"<<endl
            <<"   4. Use binary search to lookup a word in full dictionary"<<endl
            <<"   5. Set word length to use with full dictionary"<<endl
            <<"   6. Exit the program"<<endl
            <<"Your choice --> ";
            cin>>choice;
    
        switch(choice){                                     //A switch statement to check the user input
            case 1:
                //optionOne(misspelledWords_wrong, misspelledWords_correct, finalScore);                            //call option 1
                continue;
            case 2:
                optionTwo(dictionary, finalScore, noOfLetters);                                                 //call option 2
                continue;
            case 3:
                optionThree(dictionary, misspelledWords, misspelledWords_wrong ,misspelledWords_correct);    //call option 3
                continue;
            case 4:
                optionFour(dictionary);                                                                    //call option 4
                continue;
            case 5:
                optionFive(noOfLetters);                                                                 //call option 5
                continue;
            
        }
    }
    
    cout<<"Exiting program"<<endl;                                                  //exit the program after user enters option 6
    cout<<"Best score was "<<finalScore<<endl;
    exit(0);

    return 0;
}
