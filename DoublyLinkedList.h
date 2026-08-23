#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include<string>
#include "Node.h"

#include<stack>
#include "Operation.h"

class DoublyLinkedList{
private:
    Node* head;
    Node* tail;
    Node* cursorLeft;
    Node* cursorRight;

    std::stack<Operation> undoStack;
    std::stack<Operation> redoStack;

    int cursorPosition;

    bool recordHistory;

    //helper functions
    void clearRedoStack();

    void recordOperation(OperationType type,char character,int position);

public:
    DoublyLinkedList();

    void insertAtCursor(char ch);

    void moveCursorLeft();

    void moveCursorRight();

    void backspace();

    void deleteCharacter();

    bool empty();

    int length();

    void clear();

    void newFile();

    void saveFile(const std::string &file_name);

    void openFile(const std::string &file_name);

    bool search(const std::string &word);

    bool replace(const std::string &oldWord,const std::string &newWord);

    int replaceAll(const std::string &oldWord,const std::string &newWord);

    //helper function
    int getCursorPosition();

    void undo();

    void redo();

    void display();

    ~DoublyLinkedList();
};

#endif