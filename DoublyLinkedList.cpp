#include<iostream>
#include<fstream>
#include<string>
#include "DoublyLinkedList.h"
using namespace std;

//O(1)
DoublyLinkedList::DoublyLinkedList(){
    head=tail=nullptr;

    cursorLeft=cursorRight=nullptr;

    cursorPosition=0;

    recordHistory=true;
}

//O(1)
void DoublyLinkedList::insertAtCursor(char ch){
    Node* newNode=new Node(ch);

    recordOperation(OperationType::INSERT,ch,cursorPosition);

    cursorPosition++;
    
    //Linked List is empty
    if(head==nullptr){
        head=tail=newNode;

        cursorLeft=newNode;
        cursorRight=nullptr;

        return;
    }

    //Cursor is at the beginning
    if(cursorLeft==nullptr){
        newNode->next=head;
        head->prev=newNode;
        head=newNode;

        cursorLeft=newNode;
        cursorRight=newNode->next;

        return;
    }

    //Cursor is at the end
    if(cursorRight==nullptr){
        cursorLeft->next=newNode;
        newNode->prev=cursorLeft;
        tail=newNode;

        cursorLeft=newNode;
        cursorRight=nullptr;

        return;
    }

    //cursor is in the middle
    newNode->next=cursorRight;
    newNode->prev=cursorLeft;

    cursorLeft->next=newNode;
    cursorRight->prev=newNode;

    cursorLeft=newNode;
}

//O(1)
void DoublyLinkedList::moveCursorLeft(){
    if(cursorLeft==nullptr){
        return;
    }

    cursorRight=cursorLeft;
    cursorLeft=cursorLeft->prev;

    cursorPosition--;
}

//O(1)
void DoublyLinkedList::moveCursorRight(){
    if(cursorRight==nullptr){
        return;
    }

    cursorLeft=cursorRight;
    cursorRight=cursorRight->next;

    cursorPosition++;
}

//O(1)
void DoublyLinkedList::backspace(){
    Node* deleteNode=cursorLeft;
    //case1 : nothing to delete
    if(cursorLeft==nullptr){
        return;
    }

    cursorPosition--;

    recordOperation(OperationType::BACKSPACE,cursorLeft->data,cursorPosition);

    //case2 : single node
    if(head==tail){
        delete deleteNode;

        head=tail=nullptr;
        cursorLeft=cursorRight=nullptr;

        return;
    }

    //case3 : delete the first node
    if(deleteNode==head){
        head=head->next;
        head->prev=nullptr;

        delete deleteNode;

        cursorLeft=nullptr;
        cursorRight=head;//optional

        return;
    }

    //case4 : delete the last node
    if(deleteNode==tail){
        tail=tail->prev;
        tail->next=nullptr;

        delete deleteNode;

        cursorLeft=tail;
        cursorRight=nullptr;//optional

        return;
    }

    //case5 : delete a middle node
    Node* prevNode=deleteNode->prev;
    Node* nextNode=deleteNode->next;

    prevNode->next=nextNode;
    nextNode->prev=prevNode;

    delete deleteNode;

    cursorLeft=prevNode;
    cursorRight=nextNode;//optional
}

//O(1)
void DoublyLinkedList::deleteCharacter(){
    Node* deleteNode=cursorRight;
    //case1 : nothing to delete
    if(cursorRight==nullptr){
        return;
    }

    recordOperation(OperationType::DELETE_CHARACTER,cursorRight->data,cursorPosition);

    //case2 : single node
    if(head==tail){
        delete deleteNode;

        head=tail=nullptr;
        cursorLeft=cursorRight=nullptr;

        return;
    }

    //case3 : delete the first node
    if(deleteNode==head){
        head=head->next;
        head->prev=nullptr;

        delete deleteNode;

        cursorLeft=nullptr;//optional
        cursorRight=head;

        return;
    }

    //case4 : delete the last node
    if(deleteNode==tail){
        tail=tail->prev;
        tail->next=nullptr;

        delete deleteNode;

        cursorLeft=tail;//optional
        cursorRight=nullptr;

        return;
    }

    //case5 : delete a middle node
    Node* prevNode=deleteNode->prev;
    Node* nextNode=deleteNode->next;

    prevNode->next=nextNode;
    nextNode->prev=prevNode;

    delete deleteNode;

    cursorLeft=prevNode;//optional
    cursorRight=nextNode;
}

//O(n)
void DoublyLinkedList::display(){
    Node* temp=head;
    if(cursorLeft==nullptr){
        cout<<"|";
    }

    while(temp!=nullptr){
        cout<<temp->data;
        if(temp==cursorLeft){  
            cout<<"|";
        }
        temp=temp->next;
    }
    cout<<endl;
}

//O(1)
bool DoublyLinkedList::empty(){
    return head==nullptr;
}

//O(n)
int DoublyLinkedList::length(){
    Node* current=head;
    int count=0;

    while(current!=nullptr){
        count++;
        current=current->next;
    }

    return count;
}

//O(n)
void DoublyLinkedList::clear(){
    Node* current=head;
    while(current!=nullptr){
        Node* nextNode=current->next;
        delete current;
        current=nextNode;
    }

    head=tail=nullptr;
    cursorLeft=cursorRight=nullptr;

    cursorPosition=0;
}

//create a new file - O(n)
void DoublyLinkedList::newFile(){
    clear();
}

//save the text into a file - O(n)
void DoublyLinkedList::saveFile(const string &file_name){
    ofstream file(file_name,ios::out);

    if(!file.is_open()){
        cout<<"Error : Unable to open the file for writing."<<endl;
        return;
    }

    Node* current=head;
    while(current!=nullptr){
        file<<current->data;
        current=current->next;
    }

    file.close();
    cout<<"File Saved Successfully."<<endl;
}

//open a file and load its contents into the editor - O(n)
void DoublyLinkedList::openFile(const string &file_name){
    ifstream file(file_name,ios::in);

    if(!file.is_open()){
        cout<<"Error : Unable to open the file."<<endl;
        return;
    }
    
    //remove existing text from the editor
    clear();

    char ch;
    while(file.get(ch)){
        insertAtCursor(ch);
    }

    file.close();
    cout<<"File Opened Successfully."<<endl;
}

//search a word in the editor --> time - O(m*n) & space - O(1)
bool DoublyLinkedList::search(const string &word){
    if(word.empty()){
        return false;
    }

    Node* current=head;
    while(current!=nullptr){
        Node* temp=current;
        int idx=0;
        while(temp!=nullptr&&idx<word.size()&&temp->data==word[idx]){
            temp=temp->next;
            idx++;
        }

        if(idx==word.size()){
            return true;
        }

        current=current->next;
    }
    return false;
}

//replace the first occurrence of a word --> time - O(m*n) & space - O(1)
bool DoublyLinkedList::replace(const string &oldWord,const string &newWord){
    if(oldWord.empty()||newWord.empty()||oldWord.size()!=newWord.size()){
        return false;
    }

    Node* current=head;
    while(current!=nullptr){
        Node* temp=current;
        int idx=0;
        while(temp!=nullptr&&idx<oldWord.size()&&temp->data==oldWord[idx]){
            temp=temp->next;
            idx++;
        }

        if(idx==oldWord.size()){
            temp=current;
            //replacement - O(n)
            for(int i=0;i<newWord.size();i++){
                temp->data=newWord[i];
                temp=temp->next;
            }
            return true;
        }

        current=current->next;
    }
    return false;
}

//replace all occurrences of a word --> time - O(m*n) & space - O(1)
int DoublyLinkedList::replaceAll(const string &oldWord,const string &newWord){
    if(oldWord.empty()||newWord.empty()||oldWord.size()!=newWord.size()){
        return 0;
    }

    int count=0;
    Node* current=head;
    while(current!=nullptr){
        Node* temp=current;
        int idx=0;
        while(temp!=nullptr&&idx<oldWord.size()&&temp->data==oldWord[idx]){
            temp=temp->next;
            idx++;
        }

        if(idx==oldWord.size()){
            temp=current;
            //each replacement - O(n)
            for(int i=0;i<newWord.size();i++){
                temp->data=newWord[i];
                temp=temp->next;
            }
            count++;
            
            //continue searching after the replaced word
            current=temp;
        }else{
            current=current->next;
        }
    }
    return count;
}

//helper functions
//O(n)
void DoublyLinkedList::clearRedoStack(){
    while(!redoStack.empty()){
        redoStack.pop();
    }
}

//O(1)
int DoublyLinkedList::getCursorPosition(){
    return cursorPosition;
}

//O(n)
void DoublyLinkedList::recordOperation(OperationType type,char character,int position){
    if(recordHistory==true){
        Operation obj(type,character,position);
        undoStack.push(obj);

        clearRedoStack();
    }
}

//undo the last operation - (time depends on cursor movement)
void DoublyLinkedList::undo(){
    if(undoStack.empty()){
        return;
    }

    Operation obj=undoStack.top();
    undoStack.pop();

    //move cursor to the recorded position
    while(cursorPosition>obj.position){
        moveCursorLeft();
    }
    while(cursorPosition<obj.position){
        moveCursorRight();
    }

    //prevent recording during undo
    recordHistory=false;

    switch(obj.type){
        case OperationType::INSERT:
            deleteCharacter();
            break;

        case OperationType::BACKSPACE:
            insertAtCursor(obj.character);
            break;

        case OperationType::DELETE_CHARACTER:
            insertAtCursor(obj.character);
            moveCursorLeft();
            break;
    }

    recordHistory=true;

    //save operation for redo
    redoStack.push(obj);
}

//redo the last undone operation - (time depends on cursor movement)
void DoublyLinkedList::redo(){
    if(redoStack.empty()){
        return;
    }

    Operation obj=redoStack.top();
    redoStack.pop();

    // //move cursor to the recorded position
    //because undo() already place the cursor at the required position
    // while(cursorPosition>obj.position){
    //     moveCursorLeft();
    // }
    // while(cursorPosition<obj.position){
    //     moveCursorRight();
    // }

    //prevent recording during redo
    recordHistory=false;

    switch(obj.type){
        case OperationType::INSERT:
            insertAtCursor(obj.character);
            break;

        case OperationType::BACKSPACE:
            backspace();
            break;

        case OperationType::DELETE_CHARACTER:
            deleteCharacter();
            break;
    }

    recordHistory=true;

    //put the operation back into the undoStack
    undoStack.push(obj);
}

//prevents memory leaks - O(n)
DoublyLinkedList::~DoublyLinkedList(){
    Node* current=head;
    while(current!=nullptr){
        Node* nextNode=current->next;
        delete current;

        current=nextNode;
    }

    head=tail=nullptr;
    cursorLeft=cursorRight=nullptr;
}