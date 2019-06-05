using namespace std;


enum class ArgumentType {
    None,
    String,
    Int,
    Hex,
    Ip,
};

class Argument {
public:
    string name;
    string desc;
    ArgumentType type;
    Argument(string n , string d, ArgumentType t) : name(n),desc(d),type(t){}
    ~Argument() {}
    bool operator< (const Argument& userObj) const
    {
        return userObj.name > this->name;
    }
};

using vectorArg = vector<Argument>;
using mapApi = map<Argument,vectorArg>;
using mapMod = map<Argument, mapApi >;
vector<string> vectorHistory;


string command = "sldd";

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
                {"wapi-api2" , "wifi-api2 is our first module" , ArgumentType::None }, // Argument
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


