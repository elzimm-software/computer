# Igor's Computer

A basic interpreter that uses Simple Machine Language.

## Usage

The computer takes one argument at the command line.  That being the path to the desired `.sml` file containing the code to be executed.

## Memory Size

The memory size is limited to 200 elements.  As the operands are two digit words, programs cannot BRANCH to a line greater than 99 and elements more than 100 above the index of the HALT command cannot be indexed.  The BRANCH limitations can be avoided by use of the JUMP command family.  These commands move execution relative to themselves rather than to the program.  Therefore, in theory, there is no limit to the program length.

## Write

The WRITE_ASCII command family uses an ASCII table that has been adapted for the 2 digit operands.  It encompasses the most commonly used 98 characters and can be found in `reduced_ascii_table.csv`.

## Comments

Any non numeric character will be considered a comment.  Comments can be on separate lines* or following the operand.  They must not start with a digit or come before the op-code.

*Lines with no machine code do not contribute to the end position of BRANCH or JUMP commands.

## Op-Codes

| Operation        | Code | Description                                                  |
| ---------------- | ---- | ------------------------------------------------------------ |
| READ             | 10   | Read a word from the keyboard into a specific location in memory. |
| WRITE            | 11   | Write a word from a specific location in memory to the screen. |
| WRITE_ASCII_ADDR | 12   | Write a character based on the number at the address.        |
| WRITE_ASCII      | 13   | Write character defined by the operand.                      |
| LOAD             | 20   | Load a word from a specific location in memory into the accumulator. |
| STORE            | 21   | Store a word from the accumulator into a specific location in memory. |
| DIRECT_LOAD      | 22   | Load a given word to memory.                                 |
| MOVE             | 23   | Move the value of a given address to another address.        |
| ADD              | 30   | Add a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator). |
| SUBTRACT         | 31   | Subtract a word from a specific location in memory from the word in the accumulator (leave the result in the accumulator). |
| DIVIDE           | 32   | Divide the word in the accumulator by a word from a specific location in memory (leave the result in the accumulator). |
| MULTIPLY         | 33   | Multiply a word from a specific location in memory by the word in the accumulator (leave the result in the accumulator). |
| REMAINDER        | 34   | Take a remainder after the division of the word in the accumulator by a word from a specific location in memory (leave the result in the accumulator). |
| BRANCH           | 40   | Branch to a specific location in memory.                     |
| BRANCH_NEG       | 41   | Branch to a specific location in memory if the accumulator is negative. |
| BRANCH_ZERO      | 42   | Branch to a specific location in memory if the accumulator is zero. |
| JUMP             | 44   | Jump a given number of lines.                                |
| JUMP_NEG         | 45   | Jump a given number of lines if the accumulator is negative. |
| JUMP_ZERO        | 46   | Jump a given number of lines if the accumulator is zero.     |
| HALT             | 43   | Halt.                                                        |
