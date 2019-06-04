#include <iostream>
#include <vector>
#include <map>

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
    STRING,
    INT,
    HEX,
    IP
};

std::ostream& operator << (std::ostream& os, const ArgumentType &at)
{
    switch(at)
    {
        case ArgumentType::STRING: os << "STRING"; break;
        case ArgumentType::INT: os << "INT"; break;
        case ArgumentType::HEX: os << "HEX"; break;
        case ArgumentType::IP: os << "IP"; break;
    }
    return os;
}

class Argument {
public:
    string desc;
    ArgumentType type;
    int kpi;
    Argument(string d , ArgumentType t , int k) : desc(d),type(t),kpi(k){}
    ~Argument() {}
};

using argV = vector<Argument>;
using apiM = map<string , argV >;
using moduleM = map<string , apiM >;

moduleM rootVariant = {       // initialize
    {       // moduleM map
        "A" ,      // string : module name
        {       // apiM map
            {   // first element of apiM map
                "func1" ,  // api function
                {   // argV vector
                    { "argname", ArgumentType::STRING , 5}, // argument 1
                    { "int", ArgumentType::INT , 10}, // argument 2
                    { "hexa", ArgumentType::HEX , 10}, // argument 2
                }
            },
        },
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
                cout << "\t\targV desc : " << itargV->desc << " => " << static_cast<int>(itargV->type) << " => " << itargV->kpi << '\n';
                cout << "\t\targV desc : " << itargV->desc << " => " << itargV->type << " => " << itargV->kpi << '\n';
            }
        }
    }
    cout << endl;

    return 0;
}

