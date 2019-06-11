#include <iostream>
#include <vector>
#include <map>

#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


using namespace std;




enum class ArgumentType {
    None,
    Sldd,
    String,
    Int,
    Uint,
    Hex,
    Ip,
};

std::ostream& operator << (std::ostream& os, const ArgumentType &at)
{
    switch(at)
    {
        case ArgumentType::None: os << "None"; break;
        case ArgumentType::Sldd: os << "Sldd"; break;
        case ArgumentType::String: os << "String"; break;
        case ArgumentType::Int: os << "Int"; break;
        case ArgumentType::Uint: os << "Uint"; break;
        case ArgumentType::Hex: os << "Hex"; break;
        case ArgumentType::Ip: os << "Ip"; break;
    }
    return os;
}

enum class ModeType {
    Normal,
    Privileged,
};

std::ostream& operator << (std::ostream& os, const ModeType &at)
{
    switch(at)
    {
        case ModeType::Normal: os << "Normal"; break;
        case ModeType::Privileged: os << "Privileged"; break;
    }
    return os;
}

class Argument {
public:
    string name;
    string desc;
    ArgumentType type;
    ModeType mode;
    Argument(string n , string d, ArgumentType t,ModeType m) : name(n),desc(d),type(t),mode(m){}
    Argument(){}
    ~Argument() {}
    bool operator< (const Argument& userObj) const
    {
        return userObj.name > this->name;
    }
};

#define PASSWORD "root"
#define VERSION  "1.0"
string command = "sldd";
ModeType mode = ModeType::Normal;

using vectorArg = vector<Argument>;
using mapApi = map<Argument,vectorArg>;
using mapMod = map<Argument, mapApi >;
vector<string> vectorHistory;


/*
 * define data structure for input
*/
#include "cli.h"


bool
verifyTokenType(const string& s,const ArgumentType& t)
{
    bool ret = true;
    if(s.size() == 0){ return false; }
    switch(t){
        case ArgumentType::None: 
            return true;
        case ArgumentType::Sldd: 
            return true;
        case ArgumentType::String: 
            return true;
        case ArgumentType::Int: 
            for(int i=0;i<s.size();i++){
                if( ('0' <= s[i]) && (s[i] <= '9') ){ continue; }
                if('-' == s[i]){ continue; }
                ret = false;
                break;
            }
            return ret;
        case ArgumentType::Uint: 
            for(int i=0;i<s.size();i++){
                if( ('0' <= s[i]) && (s[i] <= '9') ){ continue; }
                ret = false;
                break;
            }
            return ret;
        case ArgumentType::Hex: 
            for(int i=0;i<s.size();i++){
                if( ('0' <= s[i]) && (s[i] <= '9') ){ continue; }
                if( ('a' <= s[i]) && (s[i] <= 'f') ){ continue; }
                if( ('A' <= s[i]) && (s[i] <= 'F') ){ continue; }
                ret = false;
                break;
            }
            return ret;
        case ArgumentType::Ip: 
            for(int i=0;i<s.size();i++){
                if( ('0' <= s[i]) && (s[i] <= '9') ){ continue; }
                if('.' == s[i]){ continue; }
                ret = false;
                break;
            }
            return ret;
    }
    return false;
}

string
findCommonString(const vector<string>& matchedString,const int minSize)
{
    string ret;
    for(int i=0;i<minSize;i++){
        int flag = 0;
        for(int idx=0;idx<matchedString.size();idx++){
            if(matchedString[0][i]  != matchedString[idx][i]){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            ret.push_back(matchedString[0][i]);
        } else {
            break;
        }
    }
    //;; cout << "findCommon:"<<ret<<" ";
    return ret;
}

bool
verifyLastArgument(vector<string>& strToken,string& remained)
{
    int found = 0;
    if(strToken.size() <= 0){
        return false;
    } 

    mapMod::iterator itmapMod;
    if(strToken.size() >= 1){
        found = 0;
        for (itmapMod=rootmod.begin(); itmapMod!=rootmod.end(); ++itmapMod){
            if(itmapMod->first.name == strToken[0]){
                found = 1;
                //cout << "found >> mapMod first : " << itmapMod->first.name << " => " << itmapMod->first.desc << " => " << itmapMod->first.type << endl;
                break;
            }
            //cout << ">> mapMod first : " << itmapMod->first.name << " => " << itmapMod->first.desc << " => " << itmapMod->first.type << endl;
        }
        if(found == 0){ 
            int matchedCnt=0;
            mapMod::iterator matchedIndex;
            vector<string> matchedString;
            int matchedMinSize=BUFSIZ;
            for (itmapMod=rootmod.begin(); itmapMod!=rootmod.end(); ++itmapMod){
                if(itmapMod->first.name.substr(0,strToken[0].size()) == strToken[0]){
                    matchedCnt++;
                    matchedIndex = itmapMod;
                    matchedString.push_back(itmapMod->first.name);
                    if(matchedMinSize > itmapMod->first.name.size()){ 
                        matchedMinSize = itmapMod->first.name.size();
                    }
                    //cout << "found >1> mapMod first : " << itmapMod->first.name << " => " << itmapMod->first.desc << " => " << itmapMod->first.type << " token[" << strToken[0] << "]" << endl;
                }
                //cout << ">1> mapMod first : " << itmapMod->first.name << " => " << itmapMod->first.desc << " => " << itmapMod->first.type << endl;
            }
            if(matchedCnt == 1){
                strToken[0] = matchedIndex->first.name;
                return true;
            }
            cout << endl << "recommend list:" << endl;
            for (itmapMod=rootmod.begin(); itmapMod!=rootmod.end(); ++itmapMod){
                if(itmapMod->first.name.substr(0,strToken[0].size()) == strToken[0]){
                    cout << "\t" << itmapMod->first.name << " <= description:" << itmapMod->first.desc << "[" << itmapMod->first.type << "]" << endl;
                }
            }
            if(matchedCnt > 0){ 
                //;; cout << "matchedCount:" << matchedCnt << " ";
                strToken[0] = findCommonString(matchedString,matchedMinSize);
                remained = strToken[0]; 
            }
            return false; 
        }
    }
    mapApi::iterator itmapApi;
    if(strToken.size() >= 2){
        found = 0;
        for (itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
            if(itmapApi->first.name == strToken[1]){
                found = 1;
                //cout << "found >> mapApi first : " << itmapApi->first.name << " => " << itmapApi->first.desc << " => " << itmapApi->first.type << endl;
                break;
            }
            //cout << "\t>>mapApi first : " << itmapApi->first.name << " => " << itmapApi->first.desc << " => " << itmapApi->first.type << endl;
        }
        if(found == 0){ 
            int matchedCnt=0;
            mapApi::iterator matchedIndex;
            vector<string> matchedString;
            int matchedMinSize=BUFSIZ;
            for (itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
                if(itmapApi->first.mode <= mode){       // check mode for api only
                    if(itmapApi->first.name.substr(0,strToken[1].size()) == strToken[1]){
                        matchedCnt++;
                        matchedIndex = itmapApi;
                        matchedString.push_back(itmapApi->first.name);
                        if(matchedMinSize > itmapApi->first.name.size()){ 
                            matchedMinSize = itmapApi->first.name.size();
                        }
                        //cout << "found >1> mapApi first : " << itmapApi->first.name << " => " << itmapApi->first.desc << " => " << itmapApi->first.type << " token[" << strToken[1] << "]" << endl;
                    }
                }
                //cout << ">1> mapApi first : " << itmapApi->first.name << " => " << itmapApi->first.desc << " => " << itmapApi->first.type << endl;
            }
            if(matchedCnt == 1){
                strToken[1] = matchedIndex->first.name;
                return true;
            }
            if(itmapMod->second.size() == 0){
                cout << endl << "recommend : <CR>" << endl;
            } else {
                if(matchedCnt == 0){
                }
                cout << endl << "recommend LIST:" << endl;
            }
            for (itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
                if(itmapApi->first.mode <= mode){       // check mode for api only
                    if(itmapApi->first.name.substr(0,strToken[1].size()) == strToken[1]){
                        cout << "\t";
                        cout << strToken[0] << " ";
                        cout << itmapApi->first.name << " <= description:" << itmapApi->first.desc << "[" << itmapApi->first.type << "]" << endl;
                        cout << "\t\tex>";
                        cout << strToken[0] << " ";     // module name
                        cout << itmapApi->first.name << " "; // api name
                        for (vectorArg::iterator itvectorArg=itmapApi->second.begin(); itvectorArg!=itmapApi->second.end(); ++itvectorArg){
                            cout << itvectorArg->name << "<" << itvectorArg->type << "> ";
                        }
                        cout << "<CR>" << endl;
                    }
                }
            }
            if(matchedCnt > 0){ // matchedCnt >= 2
                //;; cout << "matchedCount:" << matchedCnt << " ";
                strToken[1] = findCommonString(matchedString,matchedMinSize);
                remained = strToken[1]; 
            }
            return false; 
        }
    }
    if(strToken.size() >= 3){
        found = 0;
        if(itmapApi->second.size() < (strToken.size()-2)){
            cout << endl << "recommend argument : <CR>" << endl;
            cout << "\tE1> ";
            for(int i=0;i<strToken.size()-1;i++){
                    cout << strToken[i] << " ";
            }
            cout << "<CR>" << endl;
            return false;
        }
        if(verifyTokenType(strToken[strToken.size()-1],itmapApi->second[strToken.size()-3].type)){
            return true;
        } else {
            cout << endl << "recommend argument type : ";
            cout << itmapApi->second[strToken.size()-3].type << "   <= description:" << itmapApi->second[strToken.size()-3].desc << endl;
            cout << "\tE2> ";
            for(int i=0;i<strToken.size()-1;i++){
                    cout << strToken[i] << " ";
            }
            for (int i=strToken.size()-3;i<itmapApi->second.size();i++){
                cout << itmapApi->second[i].name << "<type:" << itmapApi->second[i].type << "> ";
            }
            cout << "<CR>" << endl;
            return false;
        }
    }

    return true;
}

void
show_history()
{
    /*
     * sldd>  means that this is right command to send the command to sldd.
     * >  means that this is proper command. but it is not sldd command.  This is internal commands.
     * ! means wrong command.
     */
    cout << endl << "::HISTORY::" << endl;
    for(int i=0;i<vectorHistory.size();i++){
        cout << " [" << i << "] " << vectorHistory[i] << endl;
    }
    cout << endl;
}

void
show_version()
{
    cout << endl << "version " << VERSION << endl;
}

void
show_mode()
{
    cout << endl << "mode is " << mode << endl;
}

void
show_list()
{
    cout << endl << "::LIST::" << endl;
    for (mapMod::iterator itmapMod=rootmod.begin(); itmapMod!=rootmod.end(); ++itmapMod){
        cout << "- " << itmapMod->first.name << " <= description : " << itmapMod->first.desc << endl;
        for (mapApi::iterator itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
            if(itmapApi->first.mode <= mode){
                cout << "\tAPI : " << itmapMod->first.name << " " << itmapApi->first.name << " ";
                for (vectorArg::iterator itvectorArg=itmapApi->second.begin(); itvectorArg!=itmapApi->second.end(); ++itvectorArg){
                    cout << itvectorArg->name << "<" << itvectorArg->type << "> ";
                }
                cout << endl;
                cout << "\t\t\tAPI description : " << itmapApi->first.desc << endl;
            }
        }
    }
    cout << endl;
}

void
printPrompt(vector<string>& strToken,const string remained)
{
    ////;; cout << endl;

    string prompt;
    int hasArgFlag = 0;

    prompt +=  "[" + to_string(strToken.size()) + ":" + to_string((strToken.size() >= 1 ? strToken[strToken.size()-1].size():0)) + "]" + "P>";
    cout << prompt;

    mapMod::iterator itmapMod;
    if(strToken.size() >= 1){
        prompt += strToken[0] + " ";
        cout << strToken[0] << " ";
        for (itmapMod=rootmod.begin(); itmapMod!=rootmod.end(); ++itmapMod){
            if(itmapMod->first.name == strToken[0]){
                //found = 1;
                break;
            }
        }
    }
    mapApi::iterator itmapApi;
    if(strToken.size() >= 2){
        prompt += strToken[1] + " ";
        cout << strToken[1] << " ";
        for (itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
            if(itmapApi->first.name == strToken[1]){
                //found = 1;
                break;
            }
        }
    }
    if(strToken.size() >= 3){
        hasArgFlag = 1;
        for(int i = 2;i<strToken.size() ; i++){
            cout << (itmapApi->second)[i-2].name << "<" << itmapApi->second[i-2].type << ">=" << strToken[i] << " ";
        }
        cout << endl;
        cout << prompt;
        for(int i = 2;i<strToken.size() ; i++){
            cout << strToken[i] << " ";
        }
    }
    cout << remained;

    return ;
}

int
getArgCount(vector<string>& strToken , ArgumentType& at)
{
    int ret = 0;
    mapMod::iterator itmapMod;
    if(strToken.size() == 0){
        return 0;
    }
    if(strToken.size() >= 1){
        for (itmapMod=rootmod.begin(); itmapMod!=rootmod.end(); ++itmapMod){
            if(itmapMod->first.name == strToken[0]){
                at = itmapMod->first.type;
                ret++;
                break;
            }
        }

        if(strToken.size() >= 2){
            mapApi::iterator itmapApi;
            for (itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
                if(itmapApi->first.name == strToken[1]){
                    ret++;
                    break;
                }
            }
            if(strToken.size() >= 3){
                for (vectorArg::iterator itvectorArg=itmapApi->second.begin(); itvectorArg!=itmapApi->second.end(); ++itvectorArg){
                    ret++;
                }
            } else {
                if(itmapApi->second.size() != 0) return -1;
            }
        } else {    // strToken.size() == 1
            //cout << itmapMod->second.size() << endl;
            if(itmapMod->second.size() != 0) return -1;
        }
    }

    //;; cout << "[r"<<ret<<",t"<<strToken.size()<<"]" << endl;;
    return ret;
}

int 
loop(string& s,int& isCompleteSldd)
{
    int level = 1;
    static int cnt = 0;
    mapMod* pmapMod = &rootmod; // level  == 1
    mapApi* pmapApi = NULL; // level  == 2
    vectorArg* pvectorArg = NULL;   // level  is more than 2
    char c=0,prevc=0;
    string token;
    vector<string> strToken;

    //for(int i = 0;i<BUFSIZ;i++){ str[i] = 0; token[i]=0; }
    s.clear();
    token.clear();

    int brkflag=1;
    cout << cnt++ << ">";
    string remained;
    while (brkflag){
        fread(&c, 1, 1, stdin);
        //if( (prevc == ' ') && (c == ' ') ){ continue; }
        prevc = c;
        switch(c){
            case '\n':
                brkflag = 0;
                if(token.size() > 0){
                    strToken.push_back(token);
                }
                break;
            case '\t':
            case ' ':
                strToken.push_back(token);
                remained.clear();
                if(verifyLastArgument(strToken,remained)){
                    token.clear();
                    cout << ' ';
                    ;;;; cout << endl;
                    printPrompt(strToken,remained);
                } else {
                    strToken.pop_back();
                    s.clear();
                    ////;; cout << endl;
                    for(int i=0;i<strToken.size();i++){
                        s += strToken[i];
                        s += ' ';
                    }
                    token = remained;
                    s += remained;
                    //;;; cout << endl << "[" << strToken.size() << ":" << strToken[strToken.size()-1].size() << "]R>";
                    printPrompt(strToken,remained);
                }
                break;
            case '~':
            case '\b':
                if(token.size() <= 0){ 
                    if(strToken.size() <= 0){  break; }
                    token = strToken.back();
                    strToken.pop_back();
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    break; 
                } 
                token.pop_back();
                printf("\b");
                printf(" ");
                printf("\b");
                break;
            default :
                token.push_back(c);
                cout << c;
                //cout << "{" << c << "}";
                break;
        }
    }

    //cout << endl << token << endl;
    s.clear();
    for(int i=0;i<strToken.size();i++){
        s += strToken[i];
        s += ' ';
    }
    string hs;
    ArgumentType at = ArgumentType::None ;
    if( (strToken.size() >= 1) && (getArgCount(strToken,at) == strToken.size()) ){
        //hs = "> " + s + ":r" + to_string(getArgCount(strToken,at)) + ":t" + to_string(strToken.size());
        //cout << hs << endl;
        if(at == ArgumentType::Sldd){
            hs = "sldd> " + s;
            isCompleteSldd = 1;
        } else {
            hs = "> " + s;
        }
    } else {
        //hs = "! " + s + ":r" + to_string(getArgCount(strToken,at)) + ":t" + to_string(strToken.size());
        //cout << hs << endl;
        hs = "! " + s;
    }

    if(strToken.size() >= 1){
        if(strToken[0] == "quit"){ cout << endl << "quit<cr>" << endl; return 0; }
        if(strToken[0] == "list"){ show_list(); }
        if(strToken[0] == "help"){ show_list(); }
        if(strToken[0] == "version"){ show_version(); }
        if(strToken[0] == "history"){ show_history(); }
        if(strToken[0] == "mode"){ show_mode(); }
    }

    vectorHistory.push_back(hs);


    return 1;
}


int 
main(int argc,char *argv[])
{
    if(argc > 1){
        //printf("%d %s\n",argc,argv[1]);
        if( (strlen(PASSWORD) == strlen(argv[1])) &&
            (strncmp(PASSWORD,argv[1],strlen(PASSWORD)) == 0) ){
            mode = ModeType::Privileged;
        }
    }

    cout << "MODE : " << mode << endl;

    /*
    for (mapMod::iterator itmapMod=rootmod.begin(); itmapMod!=rootmod.end(); ++itmapMod){
        cout << "mapMod first : " << itmapMod->first.name << " => " << itmapMod->first.desc << " => " << itmapMod->first.type << endl;
        for (mapApi::iterator itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
            cout << "\tmapApi first : " << itmapApi->first.name << " => " << itmapApi->first.desc << " => " << itmapApi->first.type << endl;
            int cnt = 1;
            for (vectorArg::iterator itvectorArg=itmapApi->second.begin(); itvectorArg!=itmapApi->second.end(); ++itvectorArg,++cnt){
                cout << "\t\tArg[" << cnt << "] vectorArg desc : " << itvectorArg->name << " => " << itvectorArg->type << " => " << itvectorArg->desc << endl;
            }
        }
    }
    cout << endl;
    */


    struct termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ECHO | ECHOE | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    int ct=1;
    while(ct){
        string s;
        int isCompleteSldd = 0;
        ct = loop(s,isCompleteSldd);
        cout << endl << endl;
        if(isCompleteSldd){
            //cout <<"Command:" << command << " [" << s << "]" << endl << endl;
            cout <<"Command:" << command << " " << s << endl << endl;

            char temp[BUFSIZ];
            snprintf(temp,BUFSIZ,"%s %s",command.c_str(),s.c_str());
            system(temp);
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}
