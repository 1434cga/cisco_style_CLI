

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
        {"mode" , "show the mode in Normal / Privileged " , ArgumentType::None , ModeType::Normal }, // Argument
        {   // mapApi
            { // mapApi map
            },
        }
    },
    {       // mapMod map <Argument,mapApi>
        {"version" , "version" , ArgumentType::None , ModeType::Normal }, // Argument
        {   // mapApi
            { // mapApi map
            },
        }
    },
    {       // mapMod map <Argument,mapApi>
        {"quit" , "quit program" , ArgumentType::None , ModeType::Normal }, // Argument
        {   // mapApi
            { // mapApi map
            },
        }
    },
    {       // mapMod map <Argument,mapApi>
        {"list" , "show all command lists" , ArgumentType::None , ModeType::Normal }, // Argument
        {   // mapApi
            { // mapApi map
            },
        }
    },
    {       // mapMod map <Argument,mapApi>
        {"help" , "show all command lists" , ArgumentType::None , ModeType::Normal }, // Argument
        {   // mapApi
            { // mapApi map
            },
        }
    },
    {       // mapMod map <Argument,mapApi>
        {"history" , "history" , ArgumentType::None , ModeType::Normal }, // Argument
        {   // mapApi
            { // mapApi map
            },
        }
    },
    {       // mapMod map <Argument,mapApi>
        {"testwifi" , "wifi is our first module" , ArgumentType::None , ModeType::Normal }, // Argument
        {   // mapApi
            { // mapApi map
                {"wifi-api1" , "wifi-api1 is our first module" , ArgumentType::None , ModeType::Normal }, // Argument
                {   // vectorArg
                    { "name-string", "description string for A" , ArgumentType::String, ModeType::Normal }, // argument 1
                    { "name-int", "description integer for A" , ArgumentType::Int, ModeType::Normal }, // argument 2
                    { "name-hexa", "description hexa for A" , ArgumentType::Hex, ModeType::Normal }, // argument 3
                }
            },
            { // mapApi map
                {"api-privileged" , "wifi-api2 is our first module" , ArgumentType::None , ModeType::Privileged }, // Argument
                {   // vectorArg
                    { "name-string", "description string for A" , ArgumentType::String, ModeType::Normal }, // argument 1
                    { "name-hexa", "description hexa for A" , ArgumentType::Hex, ModeType::Normal }, // argument 2
                }
            },
            { // mapApi map
                {"wapi-api2" , "wifi-api2 is our first module" , ArgumentType::None , ModeType::Privileged }, // Argument
                {   // vectorArg
                    { "name-string", "description string for A" , ArgumentType::String, ModeType::Normal }, // argument 1
                    { "name-hexa", "description hexa for A" , ArgumentType::Hex, ModeType::Normal }, // argument 2
                }
            },
            { // mapApi map
                {"wifi-api3" , "wifi-api3 is our first module" , ArgumentType::None , ModeType::Normal }, // Argument
                {   // vectorArg
                }
            },
            { // mapApi map
                {"wifi-api4" , "wifi-api4 is our first module" , ArgumentType::None , ModeType::Privileged }, // Argument
                {   // vectorArg
                }
            },
        }
    },
    {       // mapMod map <Argument,mapApi>
        {"testdongle" , "dongle is our first module" , ArgumentType::None , ModeType::Normal }, // Argument
        {   // mapApi
            { // mapApi map
                {"dongle-api" , "dongle-api is our first module" , ArgumentType::None , ModeType::Normal }, // Argument
                {   // vectorArg
                    { "dongle-string", "description string for A" , ArgumentType::String, ModeType::Normal }, // argument 1
                    { "dongle-int", "description integer for A" , ArgumentType::Int, ModeType::Normal }, // argument 2
                    { "dongle-hexa", "description hexa for A" , ArgumentType::Hex, ModeType::Normal }, // argument 3
                    { "dongle-hexa", "description hexa for A" , ArgumentType::Hex, ModeType::Normal }, // argument 3
                    { "dongle-int", "description integer for A" , ArgumentType::Int, ModeType::Normal }, // argument 5
                }
            },
        }
    },
};

