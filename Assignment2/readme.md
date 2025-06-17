Assignment 2 Readme

Similar to Assignment 1, development was done using Clion. I began by copying the original code from Assignment 1 and then editing as needed.
Before making the changes in the requirements, I fixed the issue I was havingaround alpha numeric characters. 
This was fixed by adding the following code to the clean up helper function:
```
    if (!isalpha(word[0])) {
        std::string result = word;
        // Remove only trailing punctuation
        while (!result.empty() && !isalnum(result.back()) && result.back() != '\'') {
            result.pop_back();
        }
        return result;
    }
 ```
  This new function uses a copy function of the word then looks to either remove trailing punctuation (ie. the case of !!! or ,)
as well as looking at the first character to see if it is an alpha character.

Following this, the requirements outlined in the assignment were implemented. This includes the following:
- Token replaced with std::string
- IntList replaced with std::vector<int>
- DLList replaced with std::list<IndexedToken>

These changes are done to follow the RAII principle. There is also automatic using STL containers and removal of raw pointers in favor of iterators.
```
cmake ..
make
./COMP5421_Assignment1
```




