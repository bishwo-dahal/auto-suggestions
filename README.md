# How it works

`compare(a,b)`
Checks if these characters are same or not  (case insensitive)

If the word is found then just message is displayed and 
If the word is not found 
    * It removes all words whose length doesnot match with input text
    * Loops the count of input
        * Removes words whose current character does not matches
        * If the suggestions is empty , we increase the counter in for loop because currently is already calculated.
        * if the character at current exist then removing words whose current character doesnot matches character at all elements
        * If the suggestions is empty then assigining suggestions to previousSuggestions and breaking it.
    * At last just removing more items. If it's size is greater than 5, then it checks for first element
    * Just making the array exactly 5


