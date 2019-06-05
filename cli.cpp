#include <iostream>
#include <vector>
#include <map>

#include <termios.h>
#include <unistd.h>
#include <string.h>

using namespace std;


enum class ArgumentType {
    None,
    String,
    Int,
    Hex,
    Ip,
};

std::ostream& operator << (std::ostream& os, const ArgumentType &at)
{
    switch(at)
    {
        case ArgumentType::None: os << "None"; break;
        case ArgumentType::String: os << "String"; break;
        case ArgumentType::Int: os << "Int"; break;
        case ArgumentType::Hex: os << "Hex"; break;
        case ArgumentType::Ip: os << "Ip"; break;
    }
    return os;
}

class Argument {
public:
    string name;
    string desc;
    ArgumentType type;
    Argument(string n , string d, ArgumentType t) : name(n),desc(d),type(t){}
    ~Argument() {}
    bool operator< (const Argument& userObj) const
    {
        return userObj.name < this->name;
    }
};

using vectorArg = vector<Argument>;
using mapApi = map<Argument,vectorArg>;
using mapMod = map<Argument, mapApi >;


/*
vectorArg testarg = {
                    { "name-string", "description string for A" , ArgumentType::String}, // argument 1
                    { "name-int", "description integer for A" , ArgumentType::Int}, // argument 2
                    { "name-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 3
};

mapApi testapi = {
    { // mapApi map
        {"wifi" , "wifi is our first module" , ArgumentType::None }, // Argument
        {   // vector<Argument> = vectorArg
            { "name-string", "description string for A" , ArgumentType::String}, // argument 1
            { "name-int", "description integer for A" , ArgumentType::Int}, // argument 2
            { "name-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 3
        }
    },
};
*/

mapMod rootmod = {       // mapMod
    {       // mapMod map <Argument,mapApi>
        {"wifi" , "wifi is our first module" , ArgumentType::None }, // Argument
        {   // mapApi
            { // mapApi map
                {"wifi-api1" , "wifi-api1 is our first module" , ArgumentType::None }, // Argument
                {   // vectorArg
                    { "name-string", "description string for A" , ArgumentType::String}, // argument 1
                    { "name-int", "description integer for A" , ArgumentType::Int}, // argument 2
                    { "name-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 3
                }
            },
            { // mapApi map
                {"api-api2" , "wifi-api2 is our first module" , ArgumentType::None }, // Argument
                {   // vectorArg
                    { "name-string", "description string for A" , ArgumentType::String}, // argument 1
                    { "name-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 2
                }
            },
            { // mapApi map
                {"wifi-api3" , "wifi-api3 is our first module" , ArgumentType::None }, // Argument
                {   // vectorArg
                }
            },
        }
    },
    {       // mapMod map <Argument,mapApi>
        {"dongle" , "dongle is our first module" , ArgumentType::None }, // Argument
        {   // mapApi
            { // mapApi map
                {"dongle-api" , "dongle-api is our first module" , ArgumentType::None }, // Argument
                {   // vectorArg
                    { "dongle-string", "description string for A" , ArgumentType::String}, // argument 1
                    { "dongle-int", "description integer for A" , ArgumentType::Int}, // argument 2
                    { "dongle-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 3
                    { "dongle-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 3
                    { "dongle-int", "description integer for A" , ArgumentType::Int}, // argument 5
                }
            },
        }
    },
};


Argument* 
getArgument(const int level , const string token,const mapMod* pmapMod,const mapApi* pmapApi,const vectorArg* pvectorArg)
{
}

bool
verifyTokenType(const string& s,const ArgumentType& t)
{
    bool ret = true;
    switch(t){
        case ArgumentType::None: 
            return true;
        case ArgumentType::String: 
            return true;
        case ArgumentType::Int: 
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
            for (itmapMod=rootmod.begin(); itmapMod!=rootmod.end(); ++itmapMod){
                if(itmapMod->first.name.substr(0,strToken[0].size()) == strToken[0]){
                    matchedCnt++;
                    matchedIndex = itmapMod;
                    cout << "found >1> mapMod first : " << itmapMod->first.name << " => " << itmapMod->first.desc << " => " << itmapMod->first.type << " token[" << strToken[0] << "]" << endl;
                }
                cout << ">1> mapMod first : " << itmapMod->first.name << " => " << itmapMod->first.desc << " => " << itmapMod->first.type << endl;
            }
            if(matchedCnt == 1){
                strToken[0] = matchedIndex->first.name;
                return true;
            }
            cout << endl << "recommand list:" << endl;
            for (itmapMod=rootmod.begin(); itmapMod!=rootmod.end(); ++itmapMod){
                if(itmapMod->first.name.substr(0,strToken[0].size()) == strToken[0]){
                    cout << "\t" << itmapMod->first.name << " <= description:" << itmapMod->first.desc << "[" << itmapMod->first.type << "]" << endl;
                }
            }
            if(matchedCnt > 0){ remained = strToken[0]; }
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
            for (itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
                if(itmapApi->first.name.substr(0,strToken[1].size()) == strToken[1]){
                    matchedCnt++;
                    matchedIndex = itmapApi;
                    cout << "found >1> mapApi first : " << itmapApi->first.name << " => " << itmapApi->first.desc << " => " << itmapApi->first.type << " token[" << strToken[1] << "]" << endl;
                }
                cout << ">1> mapApi first : " << itmapApi->first.name << " => " << itmapApi->first.desc << " => " << itmapApi->first.type << endl;
            }
            if(matchedCnt == 1){
                strToken[1] = matchedIndex->first.name;
                return true;
            }
            cout << endl << "recommand list:" << endl;
            for (itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
                if(itmapApi->first.name.substr(0,strToken[1].size()) == strToken[1]){
                    cout << "\t";
                    for(int i=0;i<1;i++){
                        cout << strToken[i] << " ";
                    }
                    cout << itmapApi->first.name << " <= description:" << itmapApi->first.desc << "[" << itmapApi->first.type << "]" << endl;
                }
            }
            if(matchedCnt > 0){ remained = strToken[1]; }
            return false; 
        }
    }
    if(strToken.size() >= 3){
        found = 0;
        if(itmapApi->second.size() < (strToken.size()-2)){
            cout << endl << "recommand list:" << endl;
            cout << "\t";
            for(int i=0;i<strToken.size()-1;i++){
                    cout << strToken[i] << " ";
            }
            cout << "<CR>" << endl;
            return false;
        }
        string remained;
        if(verifyTokenType(strToken[strToken.size()-1],itmapApi->second[strToken.size()-3].type)){
            return true;
        } else {
            cout << endl << "recommand list:" << endl;
            cout << "\t";
            for(int i=0;i<strToken.size()-1;i++){
                    cout << strToken[i] << " ";
            }
            cout << itmapApi->second[strToken.size()-3].name << "<type:" << itmapApi->second[strToken.size()-3].type << ">" << " <= description:" << itmapApi->second[strToken.size()-3].desc << endl;
            return false;
        }
        /*
        for(int i = 2;i<strToken.size() ; i++){
            cout << "[" << i << "] " << (itmapApi->second)[i-2].name << " => " << itmapApi->second[i-2].type << endl;
        }
        */
    }
            //for (vectorArg::iterator itvectorArg=itmapApi->second.begin(); itvectorArg!=itmapApi->second.end(); ++itvectorArg,++cnt){

    return true;
}

void
list()
{
    cout << endl << "::LIST::" << endl;
    for (mapMod::iterator itmapMod=rootmod.begin(); itmapMod!=rootmod.end(); ++itmapMod){
        cout << "Module Name : " << itmapMod->first.name << " <= description : " << itmapMod->first.desc << endl;
        for (mapApi::iterator itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
            cout << "> " << itmapMod->first.name << " " << itmapApi->first.name << " ";
            for (vectorArg::iterator itvectorArg=itmapApi->second.begin(); itvectorArg!=itmapApi->second.end(); ++itvectorArg){
                cout << itvectorArg->name << "<" << itvectorArg->type << "> ";
            }
            cout << endl;
            cout << "\tAPI description : " << itmapApi->first.desc << endl;
        }
    }
    cout << endl;
}
void
printPrompt(vector<string>& strToken)
{
    cout << endl << ">";
    mapMod::iterator itmapMod;
    if(strToken.size() >= 1){
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
        cout << strToken[1] << " ";
        for (itmapApi=itmapMod->second.begin(); itmapApi!=itmapMod->second.end(); ++itmapApi){
            if(itmapApi->first.name == strToken[1]){
                //found = 1;
                break;
            }
        }
    }
    if(strToken.size() >= 3){
        for(int i = 2;i<strToken.size() ; i++){
            cout << (itmapApi->second)[i-2].name << "<" << itmapApi->second[i-2].type << ">=" << strToken[i] << " ";
        }
    }
}

void 
loop(string& s)
{
    int level = 1;
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
    cout << ">";
    string remained;
    while (brkflag){
        fread(&c, 1, 1, stdin);
        if( (prevc == ' ') && (c == ' ') ){ continue; }
        switch(c){
            case '\n':
                brkflag = 0;
                break;
            case '\t':
                if(token.size() == 0){
                    token = " ";
                }
            case ' ':
                strToken.push_back(token);
                remained.clear();
                if(verifyLastArgument(strToken,remained)){
                    token.clear();
                    s.push_back(c);
                    cout << ' ';
                    printPrompt(strToken);
                } else {
                    strToken.pop_back();
                    s.clear();
                    cout << endl;
                    for(int i=0;i<strToken.size();i++){
                        s += strToken[i];
                        s += ' ';
                    }
                    token = remained;
                    s += remained;
                    cout << ">" << s;
                }
                break;
            case '\b':
                if(token.size() <= 0){ break; } 
                token.pop_back();
                s.pop_back();
                printf("\b");
                printf(" ");
                printf("\b");
                break;
            default :
                token.push_back(c);
                s.push_back(c);
                cout << c;
                //cout << "{" << c << "}";
        }
        prevc = c;
    }

    cout << endl << token << endl;
    if(token == "quit"){ cout << endl << "quit<cr>" << endl; }
    if(token == "list"){ list(); }
    if(token == "help"){ list(); }
    if(token == "history"){ cout << endl << "history<cr>" << endl; }

    return ;
}

int 
main()
{

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


    struct termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ECHO | ECHOE | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    while(1){
        string s;
        loop(s);
        cout << "\nCommand:" << s << endl;
    }
}
