# Mastermind
Efficient solution to the Mastermind game


---------THE GAME------------

This is a traditionally 2 player game, in which player 1 arranges 4 pegs in a particular sequence and player 2 has to guess it.
There are 6 different colors of pegs and the player 2 needs to guess the combination within 20 guesses. 
After each guess, player 1 will provide player 2 with feedback about how good/bad the guess was, using terms called "black hits" and "white hits".
A black hit refers to a peg that is the right color but in the wrong position. A white hit refers to a peg that is the right color and right position. 

For example, if player 1's configuration is RRGG and player 2 guesses GRBY, that player 2's guess would have one black hit (G; right color, wrong position) and one white hit (R; right color and position). 

Player 2 then uses this information to construct his next guess, and so on until he gets the solution, or until he has used up all of his 20 guesses. 


--------THE PROGRAM---------

The program automates this entire process. First, it generates a random code of n integers, each of which can take m possible values (these can even be ludicrous numbers like 500). The user supplies the program n and m. 

The program then attempts to guess the code using Knuth's algorithm, described here: https://math.stackexchange.com/questions/1192961/knuths-mastermind-algorithm.

For the [n,m] = [4,6] case, it averages 4.2 guesses before it gets the right solution. 
When [n,m] are bigger numbers (order 100), it uses a more standard guessing approach that takes many attempts (>1000) but achieves the solution within 5 seconds. 

Usage: ./mm-6 n m (n,m supplied by user)

e.g: ./mm-6 4 6 would generate a random sequence of 4 integers, each with 6 possible values (the same setup as the actual game, where you have 4 pegs of 6 colors). 
