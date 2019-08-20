#include <windows.h>
#include <conio.h>
#include <vector>

#include <iostream>
#include <string>
#include <sstream>

/*
 * Alternative to C++11 std::to_string.
 * More info: http://www.rootdirectory.de/wiki/SSTR()
 */
#define SSTR(x) dynamic_cast< std::ostringstream & >( \
    ( std::ostringstream() << std::dec << x ) ).str()

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

template<typename T>
struct Node {
    T value;
    Node* prev;
    Node* next;

    Node() : value(NULL), prev(NULL), next(NULL) {
    }

    Node(T _value) : value(_value), prev(NULL), next(NULL) {
    }

    Node(T _value, Node* _prev) : value(_value), prev(_prev), next(NULL) {
    }

    Node(T _value, Node* _prev, Node* _next) : value(_value), prev(_prev),
        next(_next) {
    }
};

template<typename T>
class List {
public:
    List(void) {
        head = tail = NULL;
    }

    List(const T& node) {
        head = tail = node;
    }

    ~List(void) {
        clear();
    }

    /* Insert value to end of list */
    void add(const T& value) {
        if (head != NULL) {
            tail->next = new Node<T>(value, tail);
            tail = tail->next;
        } else {
            head = tail = new Node<T>(value);
        }
    }

    void remove(Node<T>* node) {
        if (node == NULL) return;
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
        delete (node);
    }

    /* Insert value to start of list */
    void insert(const T& value) {
        if (head) {
            insert(value, head);
        } else {
            add(value);
        }
    }

    /* Insert value after @prev node */
    void insert(const T& value, Node<T>* prev) {
        if (prev && prev->next) {
            Node<T>* tmp = prev->next;
            prev->next = new Node<T>(value, prev, prev->next);
            tmp->prev = prev->next;
        } else {
            insert(value);
        }
    }

    /* Insert value before @next node */
    void insertBefore(const T& value, Node<T>* next) {
        if (next && next->prev) {
            insert(value, next->prev);
        } else {
            insert(value, tail);
        }
    }

    /* Empty list with all values */
    void clear(void) {
        Node<T>* tmp = NULL;

        while (head) {
            tmp = head;
            head = head->next;
            delete (tmp);
        }
    }

    /* Find node by value */
    Node<T>* find(const T& value) {
        Node<T>* pv = head;

        while (pv) {
            if (pv->value == value) {
                return pv;
            }

            pv = pv->next;
        }

        return NULL;
    }

    void print(void) {
        Node<T>* pv = head;
        std::cout << "Print:" << std::endl;

        while (pv) {
            std::cout << pv->value << std::endl;
            pv = pv->next;
        }
    }

    Node<T>* next(Node<T>* node) {
        return node->next;
    }

    Node<T>* prev(Node<T>* node) {
        return node->prev;
    }

    Node<T>* first(void) {
        return head;
    }

    Node<T>* last(void) {
        return tail;
    }


protected:
    Node<T>* head;
    Node<T>* tail;
};


/**
 * Dictionary
 */
struct DictionaryNode {
    unsigned int count;
    std::string eng;
    std::string ukr;

    DictionaryNode() : eng(""), ukr(""), count(0) {
    }

    DictionaryNode(const std::string& _eng) : eng(_eng), ukr(""), count(0) {
    }

    DictionaryNode(const std::string& _eng, const std::string& _ukr) : eng(_eng),
        ukr(_ukr),
        count(0) {
    }
};


class Dictionary : public List<DictionaryNode> {
public:
    void add(const std::string& eng) {
        const DictionaryNode val = DictionaryNode(eng);
        List<DictionaryNode>::add(val);
    }

    void add(const std::string& eng, const std::string& ukr) {
        const DictionaryNode val = DictionaryNode(eng, ukr);
        List<DictionaryNode>::add(val);
    }

    Node<DictionaryNode>* next(Node<DictionaryNode>* node) {
        Node<DictionaryNode>* next = List::next(node);

        if (next) {
            next->value.count++;
            return next;
        }

        return NULL;
    }

    std::string toString(const DictionaryNode& node) {
        return "English: " + ((node.eng.length()) ? node.eng : "<undefined>") +
            "\nUkraine: " +
            ((node.ukr.length()) ? node.ukr : "<undefined>") +
            "\nCall count: " + SSTR(node.count) + '\n';
    }

    void print() {
        Node<DictionaryNode>* pv = head;
        std::cout << "DICT:" << std::endl;

        while (pv) {
            std::cout << toString(pv->value) << std::endl;
            pv = next(pv);
        }

        remove(tail);
    }

    void sort() {
        Node<DictionaryNode>* pv = head;

        if (!pv) {
            return;
        }

        while (pv != tail) {
            if (pv->value.count < pv->next->value.count) {
                DictionaryNode value = pv->value;
                remove(pv);
                List<DictionaryNode>::add(value);
            }
        }
    }

};


void printMainMenu();


struct Console {
    static COORD position;

    Console() {
    }

    Console(const std::string& value, short x = -1, short y = -1,
        int color = 7) {
        this->cursor(
            (x >= 0) ? x : position.X,
            (y >= 0) ? y : position.Y,
            color);
        *this << value;
    }

    template<typename T>
    Console& operator<<(const T& x) {
        SetConsoleCursorPosition(handle, position);
        position.Y++;

        std::cout << x << std::endl;

        return *this;
    }

    static void cursor(short x, short y, int color = 7) {
        position.X = x;
        position.Y = y;

        SetConsoleTextAttribute(handle, color);
    }
};

COORD Console::position = { 0, 0 };
Console console;


class CMenu {
public:

    CMenu(unsigned short _type, short x, short y) : type(_type) {
        COORD _startPos = { x, y };

        this->startPos = _startPos;
        this->selectedIndex = 0;
    }

    void print() {
        Console::cursor(startPos.X, startPos.Y);

        switch (type) {
        case 0:
            printVertical();
            break;
        case 1:
            printGorizontal();
            break;
        default:
            throw "Unsupported type.";
        }

        Console("");
    }

    void _printVertical() {
        for (std::vector<std::string>::size_type i = 0; i < items.size(); i++) {
            toConsole(items[i], 0, i, (selectedIndex == i) ? 112 : 7);
        }
    }


protected:
    COORD startPos;
    unsigned short type;
    unsigned int itemLength;
    unsigned int selectedIndex;
    std::vector <std::string> items;

    virtual bool run() {
        return true;
    }

private:

    void moveLeft() {
        if (selectedIndex > 0) {
            toConsole(items[selectedIndex], (itemLength + 1) * selectedIndex,
                0);
            selectedIndex--;
        }
    }

    void moveRight() {
        if (selectedIndex < items.size() - 1) {
            toConsole(items[selectedIndex], (itemLength + 1) * selectedIndex,
                0);
            selectedIndex++;
        }
    }

    void moveUp() {
        if (selectedIndex > 0) {
            toConsole(items[selectedIndex], 0, selectedIndex);
            selectedIndex--;

            if (items[selectedIndex] == "") {
                moveUp();
            }
        }
    }

    void moveDown() {
        if (selectedIndex < items.size() - 1) {
            toConsole(items[selectedIndex], 0, selectedIndex);
            selectedIndex++;

            if (items[selectedIndex] == "") {
                moveDown();
            }
        }
    }

    void printGorizontal() {
        unsigned int x = 0;

        for (std::vector<std::string>::size_type i = 0; i < items.size(); i++) {
            toConsole(items[i], x, 0);
            x += itemLength + 1;
        }

        while (true) {
            toConsole(items[selectedIndex], (itemLength + 1) * selectedIndex, 0, 112);

            // 72 UP, 75 LEFT, 77 RIGHT, 80 DOWN 27 ESC
            switch (_getch()) {
            case 75:
                moveLeft();
                break;
            case 77:
                moveRight();
                break;
            case 13:
                if (!run()) return;
                break;
            }
        }
    }

    void toConsole(const std::string& value, short x = 0, short y = 0, unsigned int color = 7) {
        Console(value, startPos.X + x, startPos.Y + y, color);
    }

    void printVertical() {
        _printVertical();
        while (true) {
            toConsole(items[selectedIndex], 0, selectedIndex, 112);

            switch (_getch()) {
            case 72:
                moveUp();
                break;
            case 80:
                moveDown();
                break;
            case 13:
                if (!run()) {
                    return;
                }
                _printVertical();
                break;
            }
        }
    }
};


std::string wFill(std::string str, unsigned int width = 80) {
    unsigned int len = str.length();

    if (len > width) {
        return str;
    }

    return str + std::string(width - str.length(), ' ');
}


class Prompt : public CMenu {
public:
    Prompt(const std::string& msg) : CMenu(1, 33, 10) {
        int msgLen = msg.length();
        short msgPadding = (msgLen > 60) ? 0 : 40 - (short)(msgLen / 2);

        Console(msg, msgPadding, 8);
        items.push_back("[ Yes ]");
        items.push_back("[ No  ]");

        this->itemLength = items[0].length();
        selectedIndex = 1;
    }

    bool print() {
        CMenu::print();
        return selectedIndex == 0;
    }

protected:
    bool run() {
        return false;
    }
};

Dictionary dict;

class CCDictForm : public CMenu {
public:
    CCDictForm() : CMenu(0, 0, 0) {
        items.push_back(wFill("English:"));
        items.push_back(wFill("Ukraine:"));
        items.push_back(wFill("Initial value:"));
        items.push_back("[ Save   ]");
        items.push_back("[ Cancel ]");
    }

protected:
    bool run() {
        std::string eng_str;
        std::string ukr_str;

        switch (selectedIndex) {
        case 0:
            std::getline(std::cin, eng_str);
            return true;
        case 1:
            std::getline(std::cin, ukr_str);
            return true;
        case 2:
            break;
        case 3:
            dict.add(eng_str, ukr_str);

            Console::cursor(0, 0);
            system("cls");

            return false;
        case 4:
            Console::cursor(0, 0);
            system("cls");

            return false;
        }

        return true;
    }
};

class CreateDictForm : public CMenu {
public:
    CreateDictForm() : CMenu(0, 0, 10) {
        items.push_back(wFill("[ ... ]  Back to main menu."));
        items.push_back(wFill("[  <  ]  Prev value."));
        items.push_back(wFill("[  >  ]  Next value."));
        items.push_back(wFill("[ ADD ]  Append to end of dictionary."));
        items.push_back(wFill("[ INS ]  Insert after this."));
        items.push_back(wFill("[ DEL ]  Delete value from dictionary."));
        items.push_back(wFill("[ <<< ]  Skip to first element of dictionary."));
        this->dictItem = dict.first();
        printDictItem();
    }

protected:
    Node<DictionaryNode>* dictItem;

    void addToDict() {
        CCDictForm* f = new CCDictForm();
        f->print();
        dictItem = dict.last();
    }

    bool run() {
        Console("", 0, 0);
        system("cls");

        switch (selectedIndex) {
        case 0:
            return false;
        case 1:
            if (dictItem && dictItem->prev) {
                dictItem = dict.prev(dictItem);
            } else {
                console << "There are no previous values anymore.";
            }

            printDictItem();
            break;
        case 2:
            if (dictItem && dictItem->next) {
                dictItem = dict.next(dictItem);
            } else {
                console << "The are no next values anymore.";
            }

            printDictItem();
            break;
        case 3:
            addToDict();
            printDictItem();
            break;
        case 4:
            if (dictItem) {
                dict.remove(dictItem->prev);
                dictItem = dict.first();
            }
        case 5:
            dictItem = dict.first();
            break;
        }

        return true;
    }

    void printDictItem() {
        if (dictItem) {
            DictionaryNode node = dictItem->value;
            console <<
                ("English: " + ((node.eng.length()) ? node.eng : "<undefined>"))
                << ("Ukraine: " + ((node.ukr.length()) ? node.ukr : "<undefined>"))
                << "Call count: " + SSTR(node.count);
        } else {
            console << "Dictionary is empty.";
        }
    }
};


class MainMenu : public CMenu {
public:
    MainMenu() : CMenu(0, 0, 0) {
        items.push_back("[ Home         ]");
        items.push_back("[ Dictionary   ]");
        items.push_back("[ Sort         ]");
        items.push_back("[ Conclusion   ]");
        items.push_back("");
        items.push_back("[ About        ]");
        items.push_back("[ Exit         ]");
        this->itemLength = items[1].length();
        run();
    }

protected:
    void dictController() {
        Dictionary dict;
        CreateDictForm* form = new CreateDictForm();
        form->print();
    }

    void homeController() {
        Console::cursor(itemLength + 2, 0);
        console << "Welcome." << ""
            << "Use the arrows to navigate the menu items"
            << "Press Enter to confirm your choice.";
        Console::cursor(itemLength + 12, 6);
        console
            << "             [^]"
            << "             Up"
            << ""
            << "Left [<]  [ENTER]  [>] Right"
            << "           Select"
            << ""
            << "             [\31]"
            << "             Down";
    }

    void aboutController() {
        Console::cursor(itemLength + 2, 0);
        console << "About application" << ""
            << "@author Serhii Zarutskiy"
            << "@version 1.0.0" << ""
            << "Task:"
            << "* The English - Ukrainian dictionary is constructed as a linear"
            << "* dictionary list. Each component contains an English word,"
            << "* the corresponding Ukrainian word and counter access to this"
            << "* component. Originally a tree is formed according to the English"
            << "* alphabet. In the process dictionary operation every time you"
            << "* access components is added to the hit counter."
            << ""
            << "* Make a program that:"
            << "* - provides initial dictionary maintenance with"
            << "*   specific values of hit counters;"
            << "* - forms a new dictionary representation as a binary"
            << "*   trees according to the following algorithm:"
            << "*   à) the old dictionary is looking for a component of"
            << "*      the greatest value of the hit counter;"
            << "*   á) the component found is recorded in the new"
            << "*      dictionary and removed from the old one;"
            << "*   â) go to a) step to exhaustion of the original"
            << "*      dictionary;"
            << "* - Print dictionary conclusion with some stats."
            << "* The program should provide dialogue through"
            << "* menu and error input control & validation.";
    }

    void sortController() {
        dict.sort();
    }

    void resController() {
        int eng_count = 0, ukr_count = 0, view_count = 0;
        Node<DictionaryNode>* pv = dict.first();

        while (pv) {
            view_count += pv->value.count;
            eng_count++;

            if (pv->value.ukr.length() > 0) {
                ukr_count++;
            }

            pv = pv->next;
        }

        Console("Conclusion", 19, 0);
        console << "" << "The total number of words in the dictionary: " + SSTR(eng_count)
            << "Number of Ukrainian words: " + SSTR(ukr_count)
            << "The total number of word views: " + SSTR(view_count);
    }

    void selectItem(unsigned int index = 0, bool togle = false) {
        unsigned int prev = selectedIndex;
        selectedIndex = index;

        if (index == 0) {
            run();
        }

        if (togle) {
            selectedIndex = prev;
        }
    }

    bool run() {
        Console("");
        system("cls");

        switch (selectedIndex) {
        case 0:
            homeController();
            break;
        case 1:
            dictController();
            selectItem(0, true);
            break;
        case 2:
            sortController();
            break;
        case 3:
            resController();
            break;
        case 4:
            break;
        case 5:
            aboutController();
            break;
        case 6:
            Prompt * isExit = new Prompt("Close application?");
            if (isExit->print()) {
                return false;
            }

            selectItem(0, 0);
        }

        return true;
    }

};

MainMenu* mainMenu;

void printMainMenu() {
    mainMenu->_printVertical();
}

void initStdHndl() {
    HANDLE hConsoleOutput;
    CONSOLE_CURSOR_INFO structCursorInfo;

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
}

int main() {
    initStdHndl();

    mainMenu = new MainMenu();
    mainMenu->print();

    return 0;
}
