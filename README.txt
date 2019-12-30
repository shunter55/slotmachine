Algorithm:
	This algorithm creates a Board with a winning value in a given range. The ranges I used were 0, 1-25, and 26-1000.
	The code for the algorithm can be found in Board.cpp::valueInRange.

	1) Pick random lines
		a) In my case I am picking a random 1-4 lines that will be considered winning lines.
	2) Pick random symbols
		a) Pick random [number of lines] (this is the result of step 1) symbols.
		b) This can be extended here to have different weights for different symbols. This means that lower valued symbols will be chosen more often so the payout is less.
	3) Put symbol on winning line.
		a) Determine the number of occurances for each of the randomly picked Symbols from step 2, that will produce a value within the given range.
			* If the range is impossible to make with the given symbol, redo step 3.
			* Note: this works nicely for a bet of 25 since only the 26-1000 range can't be made by all symbols. The Symbol picking algorithm can be extended to be smarter (not use repeats).
		b) Randomly pick one of those occurances.
		c) Put the Symbol [number of occurance] times along the chosen line.
		d) Repeat for the rest of the lines.
			* Note: Other lines may make the 1st lines lose, but that doesn't matter because it is guarenteed that at least the last line will be a winning line in the correct range.
	4) Fill in the rest of the board with Symbols that arn't in the 1st row.
		a) Really only the 2nd line needs to have Symbols that are not in the 1st row.
		b) This is also how you make a losing board for the range 0-0.

Unit Testing:
	I made the simplest test, where it just runs when the application launches. It asserts that with an epsilon of 2% the generated boards will meet the WCP and GWCP criteria.

	The assertions will crash the app if it fails. So far for me it has always been within 2%, but I use a random seed for every run (Default can be used by removing ln. 29 in BoardTest.cpp).

	Unit testing can be disabled by setting SHOULD_TEST in SlotMachineScene.cpp to false.

	1) Generate 100,000 boards
	2) Score the boards
	3) Assert - with Epsilon of 2%
		a) totalWins = WCP
		b) smallWins = WCP - GWCP
		c) bigWins = GWCP

Notes:
	* I only tested on iOS through xCode.
	* Console output will show the Score of the board immediately without waiting for animations to play.
	* Unit Test console output prints notable numbers.
	* Focus was on getting all features implemented with reasonable end user experience. Obviously in production level code I would take more time to make maintainable code vs. just getting it out fast.