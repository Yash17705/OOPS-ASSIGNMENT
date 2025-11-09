Problem: Quiz Bowl
Your high school quiz bowl team has been losing its edge and needs to find a method to improve. Knowing that you are a savvy programmer, your coach asks you to write a program that the team members can use to hone their skills. Quiz Bowl questions come in three varieties:

1) True/False
2) Multiple Choice (variable number of choices)
3) Short Answer (all answers are a single word)

You will write an abstract class Question, that "keeps track of" information common to all three types of questions. All questions will have a String that stores the question as well as a point value. You will then write three classes: QuestionTF, QuestionMC, and QuestionSA, all of which inherit from Question.

Your program will be a training program for a single individual. Initially, your program will ask the user to enter their first and last name, followed by the name of the file storing the questions and answers for his/her training session. (The format of this file is discussed on the following page of this program description.) Then, your program should ask the user how many questions they would like for practice. (Your program should prompt the user with the maximum allowed, based on how many questions were in the input file they entered.) Make sure you gracefully handle a situation where the user doesn't enter a valid value or token. Then, your program should prompt the user with the number of random questions from this database that they requested. (Do NOT ask duplicate questions!) The user will have two options:

1) Answer the question
2) Skip the question

If the user skips the question, they neither gain nor lose points.

If the user answers the question correctly, they gain the number points at which the question is valued. If they answer incorrectly, they lose the same number of points.

When answering, to indicate that the user wants to skip the question, they MUST answer "SKIP" (It is guaranteed that no question will have as its correct answer, "SKIP".)

You must also create a class called Player, that keeps track of the user playing the game. This class should store the first and last name of the player, as well as the number of points the player has. The player initially starts with 0 points.

Finally, you should create a class QuizBowl that contains the main method that gets run. This class may also contain any instance variables and methods you deem necessary. (For example, this class could contain a Player object and an ArrayList of Question objects. In the main of this class, a QuizBowl object would be instantiated.)

Question File Format
The first line of a question database file will contain a single integer n, the number of questions in the file. The following n sets of data contain information about each question.

The first line in each set of data will contain a string that indicates the type of question followed by a positive integer indicating the point value of the question. The string is guaranteed to be one of the three following: "TF", "MC", or "SA".

The second line in each set of data will contain a string that is the question. This string will definitely contain spaces  you must read in the whole line in order to read in the whole question.

If the question is a true/false question, then the third line of the data set will contain either contain the string "true" or the string "false", depending on the answer to the question.

If the question is a short answer question, then the third line of the data set will contain a single string without spaces indicating the answer to the question.

If the question is a multiple choice question, then the third line of the data set will contain a single positive integer, k, less than 10, indicating the number of choices for the question.

The following k lines will contain each of the possible answers. These answers could have spaces in them  you have to read in the whole line. (These lines will correspond to choices A, B, C, etc.)

The last line of a multiple choice question will contain a string storing the correct answer. This string will be a capital letter corresponding to the correct answer choice. (Since there are at most 9 choices, this will always be either "A", "B", "C", "D", "E", "F", "G", "H", or "I".)


Sample Input File (sample.txt)
3
TF 5
There exist birds that can not fly. (true/false)
true
MC 10
Who was the president of the USA in 1991?
6
Richard Nixon
Gerald Ford
Jimmy Carter
Ronald Reagan
George Bush Sr.
Bill Clinton
E
SA 20
What city hosted the 2004 Summer Olympics?
Athens

Sample Program Run (User's answers in bold.)
What is your first name?
Arup
What is your last name?
Guha
What file stores your questions?
sample.txt
How many questions would you like (out of 3)?
5
Sorry, that is too many.
How many questions would you like (out of 3)?
Two
Sorry, that is not valid.
How many questions would you like (out of 3)?
3

Points: 10
Question: Who was the president of the USA in 1991? 
A) Richard Nixon
B) Gerald Ford
C) Jimmy Carter
D) Ronald Reagan
E) George Bush Sr.
F) Bill Clinton
E

Correct! You get 10 points.

Points: 20
Question: What city hosted the 2004 Summer Olympics?
LosAngeles

Incorrect, the answer was Athens. You lose 20 points.

Points: 5
Question: There exist birds that can not fly. (true/false)
SKIP

You have elected to skip that question.

Arup Guha, your game is over!
You final score is -10 points. 
Better luck next time!

Requirements
1) Your program must utilize the classes specified above: Question, QuestionTF, QuestionMC, QuestionSA, Player, and QuizBowl.

2) Your program must error check the response to the number of questions the user wants, checking for both the type of information entered as well as whether or not the value is valid.

3) Your program must ask the proper number of questions randomly from the database.

4) Your program must keep score and prompt the user with how many points they earned or lost after each question, as well as what their total score is at the end of the game.