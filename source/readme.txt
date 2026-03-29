String Matching Project by Group 11

Our project mainly focuses on the efficiency of specific string-matching algorithms, where their number of comparisons and execution time are measured and compared.
The following guidelines assume that you have already installed a g++ compiler (version C++17 or later) in order to successfully compile our C++ project.

How to run our program:
Step 1: Unzip our compressed file and place it in your desired directory.
Step 2: Open Command Prompt and type in 'g++ <filepath>/source/*.cpp -std=c++17 -o crossword[.exe]'. If the compilation is successful, a .exe file will appear in your workplace directory.
Step 3: The usage is as follows: 

	crossword[.exe] -a [algorithm] -i [input_file] -o [output_file]

	Options:
		-a [algorithm]		Select algorithm: bf, rk, kmp, bm (respectively referred to as brute-force, Rabin-Karp, Knuth-Morris-Pratt, Boyer-Moore algorithms)
		-i [input_file]		Path to user-provided data file
		-o [output_file]		Path to the result output file

	Example:
		crossword.exe -a kmp -i <filepath>/source/tests/puzzle01.txt -o solution.txt

About the 'source' folder:
	The 'source' folder contains our source code (.cpp and .h) and a subfolder named 'tests' including our generated test cases (input only). These test files are categorized into 2 types of test cases:
	- Input files with prefix 'scenario1' — number of keywords is fixed to a small number, and grid sizes range from small (10 x 10) to large (500 x 500).
	- Input files with prefix 'scenario2' — grid size is fixed to a medium value (100 x 100), and number of keywords ranges from small (10) to large (100).

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

About output format:
	- For each keyword in the input order:
		+ if at least one occurrence is found, its coordinates will be shown, formatted as (r_start, c_start) -> (r_end, c_end), each separated by a semicolon ';'.
		+ if no occurrence is found, 'not found' text will be shown.
	- At the end of the output, a performance summary will be seen, which includes the name of the chosen algorithm, the number of comparisons and its execution time.