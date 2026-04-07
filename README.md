# Text Editor — Linked List, Stack & Queue

A C project developed as part of the Data Structures and Algorithms course. It implements a simple text editor that loads text from a file, supports word insertion and deletion, and provides undo/redo functionality using stacks.

## Overview

Words are loaded from a text file into a singly linked list. Every insert or delete operation is recorded in an undo stack, allowing the user to reverse changes. Undone operations are pushed to a redo stack so they can be reapplied. The edited text can be saved to an output file.

## Data Structures

- **Linked List** — stores the words of the loaded text in order
- **Undo Stack** — records each insert/delete operation so it can be reversed
- **Redo Stack** — holds undone operations so they can be reapplied
- **Queue** — used internally during text processing

## Menu Options

1. Load the input file
2. Print the loaded text
3. Insert a word into the text
4. Remove a word from the text
5. Undo the last operation
6. Redo the last undone operation
7. Print the contents of the undo and redo stacks
8. Save the updated text to an output file
9. Exit

## How to Compile and Run

```bash
gcc project2.c -o project2
./project2
```

Make sure `input.txt` is in the same directory as the executable.
