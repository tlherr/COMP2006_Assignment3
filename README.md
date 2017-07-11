# Assignment 3

Assignment 3 is to create a number of smaller deliverables that can be used to create a card based game, for example Assignment 4.  The following are the required deliverables:

i.	Create the four suits (clubs, diamonds, hearts, and spades) as an enumerator
ii.	Create constants to represent the jack, queen, king, ace and assign them to 11-14 respectively (NB. In assignment 4 the ace is worth 1 however the intention with the above is to denote that 1 is not ace in terms of a physical card.  The above allows you to cycle 11-14, Jack-Ace within a loop.  The index of 14 is not a significant component).
iii.	Create a card class that:
 ..a.	Has member data of the card number and the suit
 ..b.	Has member functions consisting of a constructor (empty for the time being), setting a card value with a suit and value, and display function
iv.	The display function shall:
 ..a.	Display the suit of the card using the unicode text values.  This will vary from system to system but as an example will include ♠, ♥, ♦, ♣. If your compiler allows for this you can copy and paste this into your code.
 ..b.	Display the numerical value of the card from 2 to 10 or J, Q, K, or A for jack, queen, kind, and ace respectively (aligning with the enumerators)
 ..c.	An example: 3♠
v.	In your main function you will:
 ..a.	Create an array to hold the 52 cards of a standard North American playing deck
 ..b.	Allow the user to control the application with 4 options:
i.	To Create a deck:
    +Set each card in the deck, suit and numerical value, in order of A to K
    +Once the deck is created display every card in the ordered deck using the display function and the deck array, ex: A♠, 2♠, 3♠, 4♠, 5♠, 6♠, 7♠, 8♠, 9♠, 10♠, J♠, Q♠, K♠ << endl followed by the other suits in turn, one at a time.
ii.	To shuffle the deck:
    +Using the system time randomly seed the deck. You can do this by randomly selecting a card in the deck and swapping it with a temp class.  Repeat this at least 52 times to “shuffle” each card
    +Display every card in the shuffled deck similar to the above ordered representation. We will look to ensure no duplicates and that it is random.
    +Keep in mind the modulus operator can be used to help with this function and that you will need new include files for randomisation (see slides)
    +Keep in mind that for both i and ii no cards should ever be duplicated in the running deck
iii.	To cut the deck:
    +Have a random card from within the deck being displayed.
iv.	To exit the application

# Assignment 4

Cribbage is a 400 year old card game that allows for 2, 3, or 4 players. It uses a standard 52 card deck, so no jokers, and all suits are equal in status thus there is no need to develop a trump suit.  In the game of cribbage the ace is counted as a 1 and the jack, queen, and king is worth 10.  The following process highlights the process, rules, and developmental needs for the game of cribbage.  For the purpose of our application (non-networked and non-AI functioning as a learning game) we will just show all cards for the time being as being “face up” for error checking purposes etc.

## Pre-Game – Set Up:
-	Elicit user input as to how many players are playing the game (with valid options consisting of 2, 3, and 4 players only, with some error checking)
o	2 player will be the base model
o	Bonus – If you create the game with full flexibility of 2, 3, or 4 players based on the user selection
-	Ask each user for their name based on the number of expected players above
-	Seat the players around a “table” with their name and space to denote the cards as the game is in progress
-	Each user is to cut the deck (pull a random card, without replacement) after which the user that pulls the lowest card is designated the dealer.  If there is a tie for the lowest shuffle and repeat the cutting process.
-	Dealer shuffles the cards (normally the person next to the dealer cuts the deck but as the shuffling is randomised we will ignore this step)
-	Once the dealer is selected the cards are dealt, one at a time, starting to the left of the dealer and proceeding in a clockwise direction

## Pre-Game – Dealing:
-	The number of cards dealt will depend on the number of players however prior to the start of play each player will hold 4 cards in their hand.
An extra “hand” consisting of 4 cards is created called the “crib” by the players prior to in-game play.  The following table covers the permutations of the dealing process based on the number of players
|# of Players	|# Cards Dealt to Players	|# Cards Dealt to Directly to Crib|	# Cards Discarded by each Player to Crib
2 | 6 | 0 | 2
3 | 5 | 1 | 1
4 | 5 | 0 | 1

-	You should error check to confirm that before the game starts that each player has 4 cards and the crib has 4 cards
-	Normally the users place their cards in the crib in a random manner however for this purpose you can poll each user in a linear manner to determine this (ie. following the dealer around the table)
-	The player to the left of the dealer cuts the remaining deck and the next card is placed face up for all participants to see on the side.  If it is a Jack the dealer gets 2 points.  As we can’t really cut the deck we can take a random position from the remaining deck and show this card instead.
-	Once this is complete the game can start.  You will have:
o	Each player has 4 cards
o	The crib has 4 cards
o	There will be 1 card face up


## The Game – Pegging:

-	Normally score is kept in Cribbage on a board with pegs hence regular play is sometimes referred to as pegging (see previous pg).  For our purposes we can have a list of the players name with their associated score beside it.  The first player to reach 121 wins the match.
-	The play starts to the left of the dealer and continues in the clockwise position:
o	Players will only play one card at a time.  (Examples follow this text)
o	You can use position rather than card name to “play” it .. ie. play card 1 rather than A♠
o	If a player can play a card (numerically) they must play a card
o	Each player will play their cards face up in a pile in front of themselves
o	When playing you normally state the running sum as you play. For example if player 1 places a 3 and player 2 places a 5 they would state “eight” out loud.  In our program we can display a running total by the cut card for the current round in progress.
o	Face cards are worth 10, aces 1, the remaining are their face value.  The play must not exceed 31 so if a player cannot play they must pass (or say go while playing).
Bonus – If the software automatically determines if they cannot play. Otherwise have the software accept “G” for go or something equivalent to move to the next player.
o	The last person to play, whether or not the sum is at 31, finishes the round.  It starts with the next person to their left with the running total being 0 at the start.
-	Points are obtained in play by the following and counted as the play occurs:
o	If the running total is 31 the player who reached 31 gets 2 points
o	If the running total is 15 the player who reached 15 gets 2 points
o	Whoever finishes the round last gets 1 point if 31 is not obtained in the running total (called for the go)
o	Runs of 3, if they are in order or not, is 3 points for the person who completed the run. For example if player 1 plays a 3, player 2 plays a 5, and player 3 plays a 4 then player 3 will get 3 points.  If player 4 then plays a 5 then they get 4 points.  The number of runs continues with the allocated points until no further play is possible.
o	Pairs are worth 2 points. If 3 cards are played in sequence of the same type a total of 6 points are awarded (3 permutations of the pair can be made), 12 points are awarded for 4 of the same card type being played in order.

## Post Game Counting:
-	Starting to the left of the dealer each player scores their hands. The player is the last to score (this is very important when the game is close in score at the end)
-	The counting rules are similar for in hand as during play. The player uses their 4 cards in their hand plus the card that was cut at the start of the match for the following:
o	Count of 15 = 2 points (each combination)
o	Runs of 4, 5, or 5 = 1 point for each card (regardless of suit, includes the cut card as an option)
o	Pairs = 2 points per pair (each combination)
o	Flush = 4 points (all cards in hand same suit); 5 points if the cut card is the same suit; One additional point the player has the jack which matches the suit of the cut
-	The dealer scores last and also scores the crib in the same manner (effectively scoring 2 hands)

## Post Game Process:
-	Each player scores their hand, if anyone reaches 121 the game ends at this point regardless of where in terms of the progress counting is
-	Shuffle the deck and the person to the left of the current dealer deals the next hand following the same process (you do not cut to deal once the match has started)
-	Bonus – If you implement AI to control all hands but one (human) interface.
