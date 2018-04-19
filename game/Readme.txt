//problems
Possible Problems:
	FIXED?//The rebounding of the aliens may not work with more than 1 row(which i named column with out thinking)
	FIXED?//frame drops are present due to poor handling of object creation and collision checking
	deleting large numbers of enemies deletes enemies that haven't been touched???? it might just be slow frame changing
	FIXED?//I changed my iterators to work with delete (*iter) and nothing crased when erasing from list so....fingers crossed you won't have problems
	
	Lose and win screens are text in console...the player is just returned to the start menu
	A base class could have been used for bombs, player, missile, and aliens. I just didn't ever use it// maybe a sub type of projectile for missile and bomb as well
	could have made draws and destroys template functions so i don't have duplicate code, but i forgot templates existed even though i made a template class last week :(
	I do not using std or sf...ever...only in main...i was to lazy to delete it from main

//special
	random row and column of aliens are present in level2
	aliens speed up as they loose memebers
	capped bomb limit based on missile limit to balance game
	ship is just big enough to slip through a scatter shot to even out the odds for player
	Bombs are faster in level2
	shooting pattern changes with number of onscreen enemies