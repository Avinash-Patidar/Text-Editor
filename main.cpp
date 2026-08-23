#include<iostream>
#include<string>
#include<limits>
#include<cstdio>
#include<stack>
#include "DoublyLinkedList.h"
using namespace std;

void displayMenu(DoublyLinkedList &obj){
    cout<<endl;
    cout<<"================================================================================================================="<<endl;
    cout<<"                                                     C++ TEXT EDITOR"<<endl;
    cout<<"================================================================================================================="<<endl;

    cout<<endl<<"Current Text :"<<endl;
    obj.display();
    cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;

    cout<<"1. Insert Text"<<endl;
    cout<<"2. Backspace"<<endl;
    cout<<"3. Delete Character"<<endl;
    cout<<"4. Move Cursor Left"<<endl;
    cout<<"5. Move Cursor Right"<<endl;
    cout<<"6. Display Text"<<endl;
    cout<<"7. New File"<<endl;
    cout<<"8. Open File"<<endl;
    cout<<"9. Save File"<<endl;
    cout<<"10. Search"<<endl;
    cout<<"11. Replace"<<endl;
    cout<<"12. Replace All"<<endl;
    cout<<"13. Undo"<<endl;
    cout<<"14. Redo"<<endl;
    cout<<"15. Check Length"<<endl;
    cout<<"16. Check Empty"<<endl;
    cout<<"17. Exit"<<endl;

    cout<<"===================================================="<<endl;
}

//insert multiple lines of text
void insertText(DoublyLinkedList &obj){
    string text;
    bool isFirstLine=true;

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    cout<<"Enter Text :"<<" Hint : (Type END on a separate line to finish) :"<<endl;

    while(true){
        getline(cin,text);

        if(text=="END"){
            break;
        }

        if(isFirstLine==false){
            obj.insertAtCursor('\n');
        }

        for(char ch : text){
            obj.insertAtCursor(ch);
        }
        isFirstLine=false;
    }
}

int main(){
    DoublyLinkedList obj;

    int choice;
    while(true){
        displayMenu(obj);

        cout<<"Enter your choice :";
        // cin>>choice;
        if(!(cin>>choice)){
            cin.clear();
            cin.ignore(10000,'\n');

            cout<<"invalid Input. "<<"Please Enter A Number."<<endl;

            continue;
        }
        if(cin.peek()!='\n'){
            cin.ignore(10000,'\n');

            cout<<"invalid Input. "<<"Please Enter A Number."<<endl;

            continue;
        }

        switch(choice){
            case 1:{
                insertText(obj);
                break;
            }

            case 2:{
                obj.backspace();
                break;
            }

            case 3:{
                obj.deleteCharacter();
                break;
            }

            case 4:{
                obj.moveCursorLeft();
                break;
            }

            case 5:{
                obj.moveCursorRight();
                break;
            }

            case 6:{
                obj.display();
                break;
            }

            case 7:{
                obj.newFile();
                cout<<"New File Created."<<endl;
                break;
            }

            case 8:{
                string filename;
                cout<<"Enter File Name :";
                cin>>filename;

                obj.openFile(filename);
                break;
            }

            case 9:{
                string filename;
                cout<<"Enter File Name :";
                cin>>filename;

                obj.saveFile(filename);
                break;
            }

            case 10:{
                string word;
                cout<<"Enter Word To Search :";
                cin>>word;

                bool result=obj.search(word);
                if(result){
                    cout<<"Word found."<<endl;
                }else{
                    cout<<"Word Doesn't Found."<<endl;
                }
                break;
            }

            case 11:{
                string oldWord;
                string newWord;
                cout<<"Enter Word To Replace :";
                cin>>oldWord;

                cout<<"Enter New Word :";
                cin>>newWord;

                bool result=obj.replace(oldWord,newWord);
                if(result){
                    cout<<"First Occurrence Replaced."<<endl;
                }else{
                    cout<<"No Replacement."<<endl;
                }
                break;
            }

            case 12:{
                string oldWord;
                string newWord;
                cout<<"Enter Word To Replace :";
                cin>>oldWord;

                cout<<"Enter New Word :";
                cin>>newWord;

                int count=obj.replaceAll(oldWord,newWord);
                if(count){
                    cout<<"All Occurrence Replaced."<<endl;
                }else{
                    cout<<"No Replacement."<<endl;
                }
                break;
            }

            case 13:{
                obj.undo();
                break;
            }

            case 14:
                obj.redo();
                break;

            case 15:{
                int length=obj.length();
                cout<<"Text Length :"<<length<<endl;
                break;
            }

            case 16:{
                bool result=obj.empty();
                if(result){
                    cout<<"Editor Is Empty."<<endl;
                }else{
                    cout<<"Editor Isn't Empty."<<endl;
                }
                break;
            }

            case 17:{
                cout<<"Exiting text Editor..."<<endl;
                return 0;
            }

            default:{
                cout<<"Invalid Choice. "<<"Please Try Again."<<endl;
                break;
            }
        }
    }
    return 0;
}