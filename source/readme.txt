String Matching Project by Group 11

Our project mainly focuses on the efficiency of specific string-matching algorithms, where their number of comparisons and execution time are measured and compared.
The following guidelines assume that you have already installed a g++ compiler (version C++17 or later) in order to successfully compile our C++ project.

How to run our program:
Step 1: Unzip our compressed file and place it in your desired directory.
Step 2: Open Command Prompt and type in 'g++ <filepath>/source/*.cpp -std=c++17 -o crossword[.exe]'. If the compilation is successful, a .exe file will appear in your workplace directory.
Step 3: The usage is as follows: 

	crossword[.exe] -a [algorithm] -i [input_file] -o [output_file]

	Options:
		-a [algorithm]		Select algorithm: bf, rk, kmp, bm, ust (respectively referred to as brute-force, Rabin-Karp, Knuth-Morris-Pratt, Boyer-Moore, Ukkonen-suffix-tree algorithms)
		-i [input_file]		Path to user-provided data file
		-o [output_file]	Path to the result output file

	Example:
		crossword.exe -a kmp -i <filepath>/source/tests/puzzle01.txt -o solution.txt

About the 'source' folder:
	The 'source' folder contains our source code (.cpp and .h) and a subfolder named 'tests' including our generated test cases (input only). 

About your own test case:
	Your input file must be formatted to follow the structure below (otherwise undefined behavior may occur):
	- The first line contains two integers R and C (1 ≤ R,C ≤ 1000) — the number of rows and columns in the puzzle grid.
	- The next R lines describe the grid. Each line contains C lowercase English characters, separated by a single space.
	- The next line contains an integer K (1 ≤ K ≤ 100) — the number of keywords to search.
	- The following K lines each contain a single string S — the keyword to find in the grid.
	Example: 
	4 3
	e x a
	m p l
	e l s
	e x p
	2
	ex
	xp

	Test cases are organized based on two factors:
		- Scenarios:
			+ Scenario 1: Fix number of keywords (K = 10), vary grid size (10×10, 100x100 500×500).
			+ Scenario 2: Fix grid size (100×100), vary number of keywords (K = 10, 50, 100).
		- Data Types:
			+ Random: grid is random, keywords may be NoMatch, SingleMatch, or MultipleMatch.
			+ Repetitive: grid contains repeated patterns, includes full match and near-match cases.
	File Naming:
		- Scenario1: <type>_<R>x<C>.txt
		- Scenario2: <type>_k<K>.txt
	where <type> ∈ {random, repetitive}
		  <R, C> ∈ {10, 100, 500}
		  <K> ∈ {10, 50, 100}

About output format:
	- For each keyword in the input order:
		+ if at least one occurrence is found, its coordinates will be shown, formatted as (r_start, c_start) -> (r_end, c_end), each separated by a semicolon ';'.
		+ if no occurrence is found, 'not found' text will be shown.
	- At the end of the output, a performance summary will be seen, which includes the name of the chosen algorithm, the number of comparisons and its execution time.
