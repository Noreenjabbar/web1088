                                                    
                                                    
#include <iostream>
#include <stack>
#include <string>

class TextEditor {
private:
    std::string text;
    std::stack<std::string> undoStack;
    std::stack<std::string> redoStack;
    int cursor;

public:
    TextEditor() : cursor(0) {}

    void insertCharacter(char c) {
        undoStack.push(text);
        while (!redoStack.empty()) redoStack.pop();
        text.insert(cursor, 1, c);
        cursor++;
    }

    void deleteCharacter() {
        if (cursor > 0 && cursor <= text.length()) {
            
            undoStack.push(text);
            while (!redoStack.empty()) redoStack.pop();
            text.erase(cursor - 1, 1);
            cursor--;
        }
    }

    void undo() {
        if (!undoStack.empty()) {
            
            redoStack.push(text);
            text = undoStack.top();
            undoStack.pop();
            cursor = text.length();
        }
    }

    void redo() {
        if (!redoStack.empty()) {
           
            undoStack.push(text);
            text = redoStack.top();
            redoStack.pop();
		    cursor = text.length();
        }
    }

    void next() {
        if (cursor < text.length())
		 cursor++;
    }

    void previous() {
        if (cursor > 0)
		 cursor--;
    }

    void start() {
        cursor = 0;
    }

    void end() {
        cursor = text.length();
    }

    void curr_position(int pos) {
        if (pos >= 0 && pos <= text.length()) {
            cursor = pos;
        }
    }

    std::string getText() const {
        return text;
    }
};

int main() {
    TextEditor editor;
    editor.insertCharacter('H');
    editor.insertCharacter('e');
    editor.insertCharacter('l');
    editor.insertCharacter('l');
    editor.insertCharacter('o');

    std::cout << editor.getText() << std::endl; 

    editor.undo();
    std::cout << editor.getText() << std::endl; 

    editor.redo();
    std::cout << editor.getText() << std::endl; 

    editor.start();
    editor.insertCharacter('A');
    std::cout << editor.getText() << std::endl; 

    editor.end();
    editor.deleteCharacter();
    std::cout << editor.getText() << std::endl; 

    editor.curr_position(1);
    editor.insertCharacter('B');
    std::cout << editor.getText() << std::endl; 

    return 0;
}