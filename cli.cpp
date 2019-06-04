#include <iostream>
#include <vector>
#include <map>

#include <termios.h>
#include <unistd.h>

using namespace std;


/*
map<string ,    // modulename 
    map<string,  // api function name 
        vector<pair<string,int>>     // argument name , argument type
    >
>;
*/
using argumentVector = vector<pair<string,int>>;
using apiMap = map<string , argumentVector >;
using moduleMap = map<string , apiMap >;

moduleMap rootMap = {       // initialize
    {       // moduleMap map
        "A" ,      // string : module name
        {       // apiMap map
            {   // first element of apiMap map
                "func1" ,  // api function
                {   // argumentVector vector
                    { "argname", 1 }, // argument 1
                    { "arg100", 2 }, // argument 2
                }
            },
        },
    },
};

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

using argV = vector<Argument>;
using apiM = map<string , argV >;
using moduleM = map<string , apiM >;

/*
map<string ,    // modulename 
    map<string,  // api function name 
        vector<class <string,string,enum>>     // argument name , argument type
    >
>;
*/
moduleM rootVariant = {       // initialize
    {       // moduleM map
        "A" ,      // string : module name
        {       // apiM map
            {   // first element of apiM map
                "func1" ,  // api function
                {   // argV vector
                    { "name-string", "description string for A" , ArgumentType::String}, // argument 1
                    { "name-int", "description integer for A" , ArgumentType::Int}, // argument 2
                    { "name-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 3
                }
            },
        },
    },
};

struct Comparator {
public:
    bool operator()(const Argument& c1, const Argument& c2){
        return c1.name < c2.name ;
    }
};

struct AAA {
public:
    string name;
    string desc;
    ArgumentType type;
    AAA(string n , string d, ArgumentType t) : name(n),desc(d),type(t){}
    ~AAA() {}
    bool operator< (const AAA& userObj) const
    {
        return userObj.name < this->name;
    }
};

using testArg = vector<AAA>;
using testApi = map<AAA,testArg>;
using testMod = map<AAA, testApi >;


testArg testarg = {
                    { "name-string", "description string for A" , ArgumentType::String}, // argument 1
                    { "name-int", "description integer for A" , ArgumentType::Int}, // argument 2
                    { "name-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 3
};

testApi testapi = {
    { // testApi map
        {"wifi" , "wifi is our first module" , ArgumentType::None }, // AAA
        {   // vector<AAA> = testArg
            { "name-string", "description string for A" , ArgumentType::String}, // argument 1
            { "name-int", "description integer for A" , ArgumentType::Int}, // argument 2
            { "name-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 3
        }
    },
};

testMod testmod = {       // testMod
    {       // testMod map <AAA,testApi>
        {"wifi" , "wifi is our first module" , ArgumentType::None }, // AAA
        {   // testApi
            { // testApi map
                {"wifi-api1" , "wifi-api1 is our first module" , ArgumentType::None }, // AAA
                {   // testArg
                    { "name-string", "description string for A" , ArgumentType::String}, // argument 1
                    { "name-int", "description integer for A" , ArgumentType::Int}, // argument 2
                    { "name-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 3
                }
            },
            { // testApi map
                {"wifi-api2" , "wifi-api2 is our first module" , ArgumentType::None }, // AAA
                {   // testArg
                    { "name-string", "description string for A" , ArgumentType::String}, // argument 1
                    { "name-hexa", "description hexa for A" , ArgumentType::Hex}, // argument 2
                }
            },
            { // testApi map
                {"wifi-api3" , "wifi-api3 is our first module" , ArgumentType::None }, // AAA
                {   // testArg
                }
            },
        }
    },
    {       // testMod map <AAA,testApi>
        {"dongle" , "dongle is our first module" , ArgumentType::None }, // AAA
        {   // testApi
            { // testApi map
                {"dongle-api" , "dongle-api is our first module" , ArgumentType::None }, // AAA
                {   // testArg
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

int 
main()
{
    for (moduleMap::iterator itmoduleMap=rootMap.begin(); itmoduleMap!=rootMap.end(); ++itmoduleMap){
        cout << "moduleMap first : " << itmoduleMap->first << " => " << '\n';
        for (apiMap::iterator itapiMap=itmoduleMap->second.begin(); itapiMap!=itmoduleMap->second.end(); ++itapiMap){
            cout << "\tapiMap first : " << itapiMap->first << " => " << '\n';
            for (argumentVector::iterator itargumentVector=itapiMap->second.begin(); itargumentVector!=itapiMap->second.end(); ++itargumentVector){
                cout << "\t\targumentVector first : " << itargumentVector->first << " => " << itargumentVector->second << '\n';
            }
        }
    }
    cout << endl;

    for (moduleM::iterator itmoduleM=rootVariant.begin(); itmoduleM!=rootVariant.end(); ++itmoduleM){
        cout << "moduleM first : " << itmoduleM->first << " => " << '\n';
        for (apiM::iterator itapiM=itmoduleM->second.begin(); itapiM!=itmoduleM->second.end(); ++itapiM){
            cout << "\tapiM first : " << itapiM->first << " => " << '\n';
            for (argV::iterator itargV=itapiM->second.begin(); itargV!=itapiM->second.end(); ++itargV){
                // cout << "\t\targV desc : " << itargV->name << " => " << static_cast<int>(itargV->type) << " => " << itargV->desc << '\n';
                cout << "\t\targV desc : " << itargV->name << " => " << itargV->type << " => " << itargV->desc << '\n';
            }
        }
    }
    cout << endl;

    for (testMod::iterator ittestMod=testmod.begin(); ittestMod!=testmod.end(); ++ittestMod){
        cout << "testMod first : " << ittestMod->first.name << " => " << ittestMod->first.desc << " => " << ittestMod->first.type << endl;
        for (testApi::iterator ittestApi=ittestMod->second.begin(); ittestApi!=ittestMod->second.end(); ++ittestApi){
            cout << "\ttestApi first : " << ittestApi->first.name << " => " << ittestApi->first.desc << " => " << ittestApi->first.type << endl;
            int cnt = 1;
            for (testArg::iterator ittestArg=ittestApi->second.begin(); ittestArg!=ittestApi->second.end(); ++ittestArg,++cnt){
                cout << "\t\tArg[" << cnt << "] testArg desc : " << ittestArg->name << " => " << ittestArg->type << " => " << ittestArg->desc << endl;
            }
        }
    }
    cout << endl;







    struct termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ECHO | ECHOE | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    char c;
    while (fread(&c, 1, 1, stdin)){
        switch(c){
            case '\t':
                std::cout << "tab"  << std::endl;
                break;
            case '\b':
                printf("\b");
                printf(" ");
                printf("\b");
                // std::cout << "backspace" << std::endl;
                break;
            default :
                cout << c;
        }
    }

    return 0;
}

