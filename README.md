# Tideman
Tideman is a program that is created for CS50 Problem Set 3. The program is used to determine the winner in an election and it is created by using C. The users have to run the C file with extra command line arguments known as "[candidates ...]", in the format of "./tideman [candidates ...]". The users will then be prompted to enter the number of voters. Every voter gets to cast three votes for three different candidates. Then, the program will determine the winner in the tideman election.

# Information about Tideman 
Tideman voting method consists of three parts:
1) **Tally**: Once all of the voters have indicated all of their preferences, determine, for each pair of candidates, who the preferred candidate is and by what margin they are preferred.
2) **Sort**: Sort the pairs of candidates in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate.
3) **Lock**: Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair to the candidate graph, so long as locking in that pair does not create a cycle in the graph.

Once the graph is complete, the source of the graph (the one with no edges pointing towards it) is the winner!

# How to Run the Project
1) Download all the files.
2) Open the "tideman.c" file and run the project.
3) Run the command `./tideman [candidates...]`, where candidates ... are the name of candidates in the election. 

# Some Screenshots from the Program 
![cs50 pset 3 ss1](https://user-images.githubusercontent.com/95561298/179237447-00202646-fb69-4b54-a4b0-8bf8753de26d.png)

# Reference 
https://cs50.harvard.edu/x/2022/psets/3/tideman/
