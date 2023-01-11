#include <iostream>
#include <string>

using namespace std;

class Sheet{
private:
    string name;
    double val[3][3] = {0};
    bool access = true;
public:
    Sheet(string name):name(name){};
    ~Sheet();
    string getName();
    void printVal();
    void setVal(int r, int c, string v);
    void setAccess(string set_access);
    string getAccess();
};

string Sheet::getName(){return name;}

void Sheet::printVal(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout << val[i][j] << ",";
        }
        cout << endl;
    }
}

void Sheet::setVal(int r, int c, string v){

    if(access == false){cout << "This sheet is not accessible." << endl;}
    else{
        for(int i=0; i<v.length(); i++){
            if(v[i] == '+'){
                val[r][c] = stod(v.substr(0, i)) + stod(v.substr(i+1, v.length()-1));
                break;
            }
            else if(v[i] == '-'){
                val[r][c] = stod(v.substr(0, i)) - stod(v.substr(i+1, v.length()-1));
                break;
            }
            else if(v[i] == '*'){
                val[r][c] = stod(v.substr(0, i)) * stod(v.substr(i+1, v.length()-1));
                break;
            }
            else if(v[i] == '/'){
                val[r][c] = stod(v.substr(0, i)) / stod(v.substr(i+1, v.length()-1));
                break;
            }
            val[r][c] = stod(v);
        }
    }
}

void Sheet::setAccess(string set_access){
    if(set_access == "ReadOnly"){access = false;}
    else{access = true;}
}

string Sheet::getAccess(){
    if(access == true){return "Editable";}
    else{return "ReadOnly";}
}

class User{
private:
    string name;
    Sheet* list[10];
    int count = 0;
public:
    User(string name):name(name){};
    ~User(){};
    string getName();
    void addSheet(string name);
    Sheet* findSheet(string name);
    int getCount();
    void shareSheet(Sheet* sheet);
};

string User::getName(){return name;}


void User::addSheet(string name){
    list[count] = new Sheet(name);
    count++;
}

Sheet* User::findSheet(string name){
    for(int i = 0; i < this->count; ++i)
        if(this->list[i]->getName() == name)
            return this->list[i];
    return nullptr;
}

int User::getCount(){
    return this->count;
}

void User::shareSheet(Sheet* sheet){
    list[count] = sheet;
    count++;
}

class Users{
private:
    User* list[10];
    int count;
public:
    Users();
    ~Users();
    void addUser(string name);
    User* findUser(string name);
    int getCount();
};

Users::Users(){
    this->count = 0;
}

Users::~Users(){
}

void Users::addUser(string name){
    list[count] = new User(name);
    count++;
}

User* Users::findUser(string name){
    for(int i = 0; i < this->count; ++i)
        if(this->list[i]->getName() == name)
            return this->list[i];
    return nullptr;
}

int Users::getCount(){return this->count;}


int main()
{
    Users users;
    int a;
    while(!cin.eof()){
        string user_name, sheet_name, user2_name, access;
        cout<<"---------------Menu---------------\n"
            <<"1. Create a user\n"
            <<"2. Create a sheet\n"
            <<"3. Check a sheet\n"
            <<"4. Change a value in a sheet\n"
            <<"5. Change a sheet's access right.\n"
            <<"6. Collaborate with an other user\n"
            <<"----------------------------------\n";
        cin >> a;
        switch(a){
            case 1:
            {
                cin >> user_name;
                users.addUser(user_name);
                cout << "Create a user named \"" + users.findUser(user_name)->getName() + "\".\n" << endl;
                break;
            }
            case 2:
            {
                cin >> user_name >> sheet_name;
                users.findUser(user_name)->addSheet(sheet_name);
                cout << "Create a sheet named \"" + users.findUser(user_name)->findSheet(sheet_name)->getName() + "\" for \"" + users.findUser(user_name)->getName() + "\".\n" << endl;
                break;
            }
            case 3:
            {
                cin >> user_name >> sheet_name;
                users.findUser(user_name)->findSheet(sheet_name)->printVal();
                cout << endl;
                break;
            }
            case 4:
            {
                int row, col;
                string value;
                cin >> user_name >> sheet_name;
                users.findUser(user_name)->findSheet(sheet_name)->printVal();
                cin >> row >> col >> value;
                users.findUser(user_name)->findSheet(sheet_name)->setVal(row, col, value);
                users.findUser(user_name)->findSheet(sheet_name)->printVal();
                break;
            }
            case 5:
            {
                cin >> user_name >> sheet_name >> access;
                users.findUser(user_name)->findSheet(sheet_name)->setAccess(access);
                break;
            }
            case 6:
            {
                cin >> user_name >> sheet_name >> user2_name;
                users.findUser(user2_name)->shareSheet(users.findUser(user_name)->findSheet(sheet_name));
                cout << "Share \"" << user_name << "\'s \"" << sheet_name << "\" with \"" << user2_name << "\"." << endl;
                break;
            }
            default:{break;}
        }
    }
    return 0;
}
