//
//  main.cpp
//  Cs 204 HW#1
//
//  Created by Mehmet Egehan Pala on 9.10.2023.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

bool searchForWord(const string& word, string currentWord, vector<vector<char>>& puzzle, int index, int i, int j, bool& foundMatch)
{
    // in this function word is the word to be searched
    // currentword is an empty string when we found the letters of the word one by one we are going to add them to compare whether the word is found
    // puzzle is our matrix
    // index is the current index of the word that we are searching for (initially it is 0)
    // i is the rows of the matrix
    // j is the collums og the matrx
    // foundMatch is the boolean value that shows us whether the word is found or not
    
    
    /*
    This is the base function, when the currentWord size becomes equal with the searched word size then it means we do not have to call the function again it is ended.
     */
    if (currentWord.size() == word.size())
    {
        foundMatch = true;
        return foundMatch;
    }
    
    /* This 4 coding line is for to check if our program exceeded the matrix's boundries and for to check whether the char in the matrix matchs with the setted index of the word if one of these are the case program returns the initial value of foundMatch which is 0 */
    
    if (i < 0 || j < 0 || i >= puzzle.size() || j >=  puzzle[0].size() || puzzle[i][j] != word[index] || foundMatch)
    {
        return foundMatch;
    }
    
    
    currentWord += word[index]; // we add the setted index of the word to currentWord
    
    /* This is where backtracking starts we set a temporarily character that becames the searched point in the matrix, then we make the searced point in the matrix as an empty space so that program could not return the previous point again at the end of the recursion we set the searched point in the puzzle to it's original value so that it does not change */
    char temp = puzzle[i][j];
    puzzle[i][j] = ' ';
    
    /* This part is the recursive part. We call the funtions recursively to check the values of the word around the search point*/
    searchForWord(word, currentWord, puzzle, index + 1, i + 1, j, foundMatch); // this is for to chech the right side of the point
    searchForWord(word, currentWord, puzzle, index + 1, i - 1, j, foundMatch); // this is for to chech the left side of the point
    searchForWord(word, currentWord, puzzle, index + 1, i, j + 1, foundMatch); // this is for to chech the upside of the point
    searchForWord(word, currentWord, puzzle, index + 1, i, j - 1, foundMatch); // this is for to chech the downside of the point
    
    puzzle[i][j] = temp; // as it mentioned before we set the searched point to it's original value
    
    
    return foundMatch;
    
}


vector<string> find_words_in_the_puzzle(vector<vector<char>> &puzzle, vector<string> &words)
{
    //we create a vector to store founded words in the puzzle
    vector<string> foundWords;
    
    //this is another bool value we have created for the word match if the word matches it becomes true
    bool foundMatch = false;
    
    // this for loop is for to move between the strings in the words vector to select one
    for (int k = 0; k < words.size(); k++)
    {
        string word = words[k]; //word becomes the values in the words vector
        for (int i = 0; i < puzzle.size(); i++) // this for loop is for to move between the rows of the matrix (i = row value)
        {
            for (int j = 0; j < puzzle[0].size(); j++)// this for loop is for to move between the collums of the matrix (j is the rows)
            {
                if (puzzle[i][j] == word[0]) //if a char in the matrix match with the first char in the word string continue
                {
                    searchForWord(word, {}, puzzle, 0, i, j, foundMatch); // calling the searching algorithm matrix
                }
                if (foundMatch)
                {
                    foundWords.push_back(word); //if foundMatch bool value becomes true then it means word is found so add it to the vector founWords
                    foundMatch = false;
                }
            }
        }
    }
    return foundWords;
}





int main() {
    // Get the input file name
    string inputFileName;
    
    // we create a bool value to use it on whether the file is open or not
    bool file_open = false;
    
    do
    {
        // Get the file name input
        cout << "Enter the name of the file: ";
        cin >> inputFileName;
        
        // Open the input file
        ifstream inputFile(inputFileName);
        
        
        // If the file could not be opened, give an error.
        if (!inputFile.is_open()) 
        {
            cout << "Could not open the file " << inputFileName << endl;

            // Continue the loop to ask for another file name.
            continue;
        }

        // If the file was opened successfully, set the file_open flag to true and break out of the loop.
        file_open = true;
        break;
        
    } while (!file_open);

    //when the file name corrected open the file
    ifstream inputFile(inputFileName);
    
    vector<string> lines;
    string line;
    
    // Read the lines and store it in a vector
    while (getline(inputFile, line))
    {
        lines.push_back(line);
    }
    
    inputFile.close();
    
    

    
    
    // finds the number between the puzzle and the words in the file in order to split the puzzle and words
    string index_solution;
    
    unsigned long second_ = inputFileName.rfind('_'); //this is the index of the second "_" in the file name
    
    index_solution = inputFileName.substr(7, second_ - 7);// 7th index is the starting point od the matrix size (e.g. 7 means 7x7 matrix)
    
    
    // until_index is the index of the number between the matrix puzzle and the solution words
    int until_index {stoi(index_solution) + 1};
 
    
    
    vector <string> new_lines;
    //storing the matrix puzzle into the new_lines vector
    for (int i = 1 ; i < until_index ; i++)
    {
        
        new_lines.push_back(lines[i]);
    }
    
    vector<vector<char>> puzzle;
    
    vector<string> words;
    
    
    // stores the chars in the file into the double vector (making matrix)
    for (int i = 0 ; i < until_index ; i++)
    {
        vector<char> row;
        
        for (int j = 0 ; j < new_lines[i].size() ; j++ )
        {
            row.push_back(new_lines[i][j]);
        }
        if (!row.empty())
        {
            puzzle.push_back(row);
        }
    }
    
    
    //checking whether the matrix is empty or not
    if (puzzle.empty()){
        
        return 1;
    }
    
    
    
    // checks if the matrix is n x n or not
    for (int i = 0; i < puzzle.size(); i++)
    {
        if (puzzle.size() != puzzle[i].size()){ // if the puzzles row size is not matching with the puzzle's collum sizes gives error
            
            cout<< "Error: Input file is not in correct format!"<< endl;
            return 1;
        }
    }
    
    
    // checking whether the matrix is made of uppercase chars or not
    for (int i = 0; i < puzzle.size(); i++)
    {
        for (int j = 0; j < puzzle[0].size(); j++)
        {
            //if the characters in the matrix is not in between the ASCII value of the A and Z it gives error
            if (puzzle[i][j] < 'A' || puzzle[i][j] > 'Z')
            {
                cout << "Error: Input file is not in correct format!" << endl;
                return 1;
            }
        }
    }
   
    
    // splitting the solution words from the file to a vector
    for (int i = (until_index + 1) ; i < lines.size() ; i++)
    {
        if (!lines[i].empty())
        {
            words.push_back(lines[i]);
        }
    }
    
    // if the words vector is empty it returns 1 and program ends
    if (words.empty()){
        return 1;
    }
    
    
    // this is the function we are calling for the search and we are storing the founded words in a vector
    vector<string> foundWords = find_words_in_the_puzzle(puzzle, words);
    
    // this counts the words founded in the puzzle
    int count = 0;
    for (int i = 0; i < foundWords.size(); i++)
    {
        if (foundWords[i] != foundWords[i - 1]) // if the word founded 2 or more times we don't want to include it
        {
            count += 1;
        }
    }
    
    cout << count << " Words are Found: " ;
    
    string output = "";
    
    // this program prints out the words that are found in the puzzle
    for (int i = 0; i < foundWords.size(); i++)
    {
        if (foundWords[i] != foundWords[i - 1])//again we do not want the words that has been founded 2 or more times
        {
            output += foundWords[i] + " ";
        
        }
    }
    cout << output << endl;
    return 0;
                
}
