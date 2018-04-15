//problems
Possible Problems:
	The rebounding of the aliens may not work with more than 1 row(which i named column with out thinking)
	A base class could have been used for bombs, player, missile, and aliens. I just didn't ever use it
	could have made draws and destroys template functions so i don't have duplicate code, but i forgot templates existed even though i made a template class last week :(
	frame drops are present due to poor handling of object creation and collision checking
	I do not using std or sf...ever...only in main...i was to lazy to delete it from main

//special
	random row and column of aliens are present in level2
	aliens speed up as they loose memebers
	capped bomb limit based on missile limit to balance game
	ship is just big enough to slip through a scatter shot to even out the odds for player