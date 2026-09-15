# Math Quiz Game

A console-based math quiz game built with C++. The player can choose the number of questions, difficulty level, and type of arithmetic operation before starting the quiz.

## Features

* Choose the number of questions (1–10)
* Choose a difficulty level:

  * Easy
  * Medium
  * Hard
  * Mixed
* Choose an operation:

  * Addition
  * Subtraction
  * Multiplication
  * Division
  * Mixed
* Randomly generated questions
* Immediate answer evaluation
* Displays the correct answer when an answer is incorrect
* Tracks correct and incorrect answers
* Displays a final pass/fail result
* Option to play again

## How It Works

At the beginning of each game, the player selects the number of questions, difficulty level, and operation type.

The game then generates random questions based on the selected options. Each answer is evaluated immediately, and the player's score is updated.

At the end, the game displays the number of correct and incorrect answers along with the final result.

## Example

```text
How many questions do you want? 1 to 10: 5

What level do you want?
[1] Easy
[2] Medium
[3] Hard
[4] Mix

What operation do you want?
[1] Add
[2] Subtraction
[3] Multiplication
[4] Division
[5] Mix
```

The game then generates questions according to the selected settings and evaluates each answer.
