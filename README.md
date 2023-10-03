# Crossword-Solver
This is the finished **crossword solving program** I made as a University project.

### How does it work?
This reads a crossword grid file and a dictionary file and attempts to find first possible solution (if it exists).

### Grid:
The crossword grid is analyzed and its information is stored in two structures:<br />
- ***VisualGrid*** holds basic information about the grid's graphical features (ex. width, height, black boxes).<br />
- ***DataGrid*** holds data about more technical features (ex. number of words it can fit, gap coordinates, intersections).<br />
It is quite useful, as it is used throughout the whole search for a solution<br />

### Hash Table:
- The ***HashTable*** is used to store the whole dictionary and offers a more efficient word search than a simple linear search.<br />
It sorts words according to length and letters at certain positions.

## Solving Procedure
In order to have a solution all grid gaps need to be filled.<br />
### Order Of Filling Gaps:
Gap filling order has two different approaches:<br /><br />
**Approach 1:** Gaps with less word choices are filled first.<br />
**Approach 2:** Gaps with a greater number of intersections are filled first<br /><br />
I have concluded that the first approach works best, for most cases, although the second approach is more efficient at times
> approach 1 for Crossword5.txt, MoreWords.txt less efficient than approach 2<br />
> approach 1 for Extra40.txt, Words.txt more efficient than approach 2<br />

The order of filling the gaps is decided during solving.<br />
**Flags** signify the filling priority of each gap.

### Constrained Word Search:
While filling the gaps with words, other gaps become constrained, as they can only be filled with words with letters on certaint positions.<br />
This is the reason a data structure for efficient word search is needed.
#### Hash Table for Word Search
The Hash Table structure can be used for accessing words of a **specific length** and all words with a **letter** on a specific **position** at a time.<br /> 
This data structure in combination with a partial linear search, for additional constraints, offers a more efficient search method.<br />

### Check:
Before placing a word in a gap, as a potential solution, **its validity needs to be checked**.<br /><br />
This means that the word needs to be checked, so that it won't create non valid constraints for other words to be placed.<br />
This speeds up the solving procedure, as it **minimizes unnecessary backtracking operations**.<br />

### Backtracking:
A ***Backtracking Operation*** is performed when a word with constraints cannot be found to fill a gap.<br /><br />
This means that a previously placed word has resulted in a dead end, so it needs to be replaced with another one.<br />
It is assumed that the "problematic" word is the **last placed word**.<br />

## How to run program?
To compile program:
```
make
```
To run program:
```
./crossw Others/crosswords/'CrosswordFile' Others/dictionaries/'DictionaryFile'
```
