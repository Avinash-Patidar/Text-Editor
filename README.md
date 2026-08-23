# Console-Based Text Editor

A console-based text editor developed using C++ & Data Structures and Algorithms (DSA).

The project demonstrates how fundamental data structures can be combined to build a practical application.

---

## Features

- Insert text at cursor
- Move cursor left and right
- Backspace
- Delete character
- Display text with cursor
- Create a new file
- Open an existing file
- Save data in a text file
- Search text
- Replace text
- Replace all occurrences
- Undo operations
- Redo operations
- Check text length
- Check whether the editor is empty
- Display current text
- Multi-line text support
- Header/Source File Organization
- Menu-driven interface

---

## Technologies Used

- C++
- Data Structures and Algorithms(Doubly Linked List,Stack)
- Object-Oriented Programming System(OOPs)
- Dynamic Memory Allocation
- Pointers
- File Handling
- String Processing
- Standard Template Library(STL)

---

## Data Structures Used

### 1. Doubly Linked List - Text Storage & Cursor Management

The text is stored using a custom Doubly Linked List.

Each node contains :
- Character data
- Pointer to previous node
- Pointer to next node

The Doubly Linked List allows the editor to efficiently manage characters around the cursor.

### 2. Stack - Undo & Redo History

Two Stacks are used for Undo and Redo operations :
- Undo Stack
- Redo Stack

Each Stack stores an `Operation` object representing an editing operation.

---

## Project Architecture

`Node.h` represents individual characters.

`DoublyLinkedList.h` and `DoublyLinkedList.cpp` contains the main text-editor logic.

`Operation.h` and `OperationType.h` stores information required for Undo and Redo.

`main.cpp` is responsible for user interface.

Multi-file C++ & DSA Project Structure :

main.cpp
|
|
+----------DoublyLinkedList
           |
           |
           +----------Node
           |
           |
           +----------Operation
                      |
                      |
                      +----------OperationType

---

## Future Enhancements

Possible future improvements include :

- Undo/Redo will support replace operations
- Replace words of different lengths
- Copy/Cut and Paste
- Find next occurrence
- Syntax highlighting(Highlight C++ Keywords)

- Keyboard shortcuts
  For Example :
  - Ctrl + S -> Save
  - Ctrl + Z -> Undo
  - Ctrl + Shift + Z or Ctrl + Y -> Redo

- Display
  - Character count
  - Word count
  - Line count
  - Cursor Position   
  For Example :
   - Characters : 120
   - Words : 25
   - Lines : 7
   - Cursor : Line 3,Column 15

---

## Split Into Phases

`Phase1` : Core Text Editor Engine

- Node class
- DoublyLinkedList class

- Insert a character --> insertAtCursor()
- Cursor movement(move cursor left/right) --> moveCursorLeft() and moveCursorRight()
- Display text --> display()
- Constructor and Destructor

Use a Doubly Linked List to store characters.

`Phase2` : Editing Operations

- Backspace --> backspace()
- Delete --> deleteCharacter()
- Clear all text --> clear()
- Utility functions --> empty() and length()

`Phase3` : File Handling

- New file --> newFile()
- Open file --> openFile()
- Save file --> saveFile()
- Save as --> (Future Enhancement)

Use File Handling for store and retrieve text.

`Phase4` : Search & Replace

- Search --> search()
- Replace --> replace()
- Replace all --> replaceAll()

Use String Processing.

`Phase5` : Undo & Redo

- Undo last Operation --> undo()
- Redo undone operation --> redo()
- Helper functions --> getCursorPosition(),clearRedoStack() and recordOperation()

Use two Stacks.

`Phase6` : Final Professional Version

- Menu-driven interface
- Better user interaction
- Better error handling and input validation
- Final Testing
- Documentation/README

---