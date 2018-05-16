#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
#define REOPEN_WRITE freopen("./keyword.lex", "w", stdout);

string words = "\
void int double bool string class interface null this extends implements for while if else return break new NewArray Print ReadInteger ReadLine \
+ - * / % < <= > >= = == != && || ! ; , . [] [ ] ( ) { }";


string types[] =  {"T_LessEqual", "T_GreaterEqual", "T_Equal", "T_NotEqual", "T_And", "T_Or", "T_NewArray"};
int main(){
    REOPEN_WRITE

    string keyword;
    stringstream ss(words);
    size_t type_index = 0;
    while(ss >> keyword){
        string t_keyword = keyword;
        keyword[0] = toupper(keyword[0]);
        if(isalpha(keyword[0])){
            string indent(15 - keyword.size(), ' ');
            printf("\"%s\"%s{return T_%s;}\n", t_keyword.c_str(), indent.c_str(), keyword.c_str());
        } else if(keyword.size() == 1){
            printf("\"%s\"    {return '%s';}\n", t_keyword.c_str(), keyword.c_str());
        }else{
            printf("\"%s\"   {return %s;}\n", t_keyword.c_str(), types[type_index++].c_str());
        }
    }
    return 0;
}
