# TataTechnologyInterview
BolwlingGame

Game Rules

A bowling game consists of 10 frames.

Each frame, the player has two tries to knock down 10 pins with a bowling ball.

The score for the frame is the total of knocked down pins, plus bonuses for strikes and spared

A Spare is when a player knocks down all 10 pins in two tries
The bonus for this frame is the number of pins knocked down by the next roll

A Strike is when the player knocks down all 10 pins on his first try.
The bonus for this frame is the number of pins knocked down by the next two rolls.

In the 10 frame, a player is allowed to throw an extra ball if she he scores a Spare or a Strike.
No more than three throws are allowed for the 10" frame
No bonus sclats are granted for Strikes and Spares in 10" frame
If a player hits a Strike/Spare, 10 pins will be available again for the next

Sample execution:
./BollowingGame_Uniq 
Enter bowling scores for 10 frames.
Each roll must be a number between 0 and 10.
Frame 1, Trial 1: 2
Frame 1, Trial 2: 3
Frame 2, Trial 1: 4
Frame 2, Trial 2: 5
Frame 3, Trial 1: 4
Frame 3, Trial 2: 3
Frame 4, Trial 1: 4
Frame 4, Trial 2: 2
Frame 5, Trial 1: 5
Frame 5, Trial 2: 6
Invalid second roll. The total for the frame cannot exceed 10.
4
Frame 6, Trial 1: 3
Frame 6, Trial 2: 4
Frame 7, Trial 1: 3
Frame 7, Trial 2: 3
Frame 8, Trial 1: 4
Frame 8, Trial 2: 5
Frame 9, Trial 1: 3
Frame 9, Trial 2: 4
Frame 10, Trial 1: 10
Frame 10, Trial 2: 0
Frame 10, Trial 3: 9

Total Score: 84
