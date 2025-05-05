1. Running the program:
    Compile with "make rtb"
    Run with "./rtb [input filename]"
    The input file should be a .txt file with the name of each player on a different line. Scores will also be written to this file after the game concludes, and need not be removed for the program to run again with the same players.
2. Program description:
    This program simulates the card game ride the bus, in which players take turns trying to guess the answers to four different questions about the next card they receive. The questions are red or black, higher or lower, inside or outside, and suit. Input is provided by pressing the number key associated with your desired choice, as stated when each question is asked. After each run-through of all questions to all players, play can be concluded or continued. Play automatically concludes once the whole deck has been cycled through.
3. Untaught element:
    The technique I used that wasn't explicitly taught in class was using color codes to color only certain parts of lines, as a means of visually highlighting the cards drawn. Note that this code may be platform specific and might not work as expected outside of a Linux terminal environment.