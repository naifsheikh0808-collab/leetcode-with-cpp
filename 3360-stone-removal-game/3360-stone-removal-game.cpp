
class Solution {
public:
    bool canAliceWin(int n) {
        int stones = 10;        // Alice must remove exactly 10 stones on her first turn
        bool aliceTurn = true;  // Alice plays first, so initially it's Alice's turn

        while (n >= stones) {   // Check if the current player has enough stones to make a move
            n = n - stones;     // Remove the required stones from the pile (e.g., 12 - 10 = 2)
            stones--;           // Next player must remove 1 fewer stone than the previous player

            aliceTurn = !aliceTurn; // Switch turns: Alice -> Bob or Bob -> Alice
        }

        return !aliceTurn;      // If it's Bob's turn, Bob cannot move and Alice wins
    }
};

/*
note:
1. aliceTurn = true means Alice is going to play.
2. aliceTurn = false means Bob is going to play.
3. When the loop stops, the current player cannot make a move.
4. Therefore, !aliceTurn tells us whether Alice wins.

*/

