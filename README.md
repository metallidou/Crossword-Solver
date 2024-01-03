# Crossword-Solver
This is the finished **crossword solving program** I made as a University project, in the course 'Introduction to Porgramming'.<br />
https://cgi.di.uoa.gr/~ip/iphw2223_4.pdf

### - How does it work?
The program reads a crossword grid file and a dictionary file from stdin, and attempts to find first possible solution (if it exists).

### Grid:
The crossword grid is analyzed and its information is stored in two structures:<br />
- ***VisualGrid*** holds basic information about the grid's graphical features (ex. width, height, black boxes).<br />
- ***DataGrid*** holds data about more technical features (ex. number of words it can fit, gap coordinates, gap intersections).<br />
It is quite useful, as it is provides needed information throughout the whole solving procedure.<br />

### Hash Table:
- The ***HashTable*** is used to store the whole dictionary and offers a more efficient word search than a simple linear search.<br />
It sorts words according to length and letters at certain positions.

## Solving Procedure
In order to have a solution, all grid gaps need to be filled (both approaches follow a combination of static and dynamic variable ordering).<br />
### 1. Order Of Filling Gaps:
Gap filling order is determined using two different approaches:<br /><br />
**Approach 1:** Gaps with less word possibilities are filled first.<br />
**Approach 2:** Gaps with a greater number of intersections are filled first<br /><br />
I have concluded that the first approach works best, for most cases, although the second approach is more efficient at times
> approach 1 for Crossword5.txt, MoreWords.txt less efficient than approach 2<br />
> approach 1 for Extra40.txt, Words.txt more efficient than approach 2<br />

The order of filling the gaps is decided during solving.<br />
**Flags** signify the filling priority of each gap.

### 2. Constrained Word Search:
While filling the gaps with words, other gaps become constrained, as they can only be filled with words with letters on certaint positions.<br />
This is the reason a data structure for efficient word search is needed.
#### Hash Table for Word Search
The Hash Table structure can be used for accessing words of a **specific length** and all words with a **letter** on a specific **position** at a time.<br /> 
This data structure in combination with a partial linear search, for additional constraints, offers a more efficient search method.<br />

### 3. Forward Checking:
Before placing a word in a gap, as a potential solution, **it needs to be checked in advance**.<br /><br />
Basically, it needs to be made sure that the current word choice won't make up additional constraints that correspond to non-existing words.<br />
This speeds up the solving procedure, as it **prevents unnecessary backtracking operations**.<br />

### 4. Backtracking:
A ***Backtracking Operation*** is performed when a word with constraints cannot be found to fill a gap.<br /><br />
In this case, a previously placed word has resulted in a dead end, so it needs to be replaced.<br />
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
