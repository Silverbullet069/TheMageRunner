#ifndef TXTREADER_H
#define TXTREADER_H
#include <string>
#include <fstream>

//System
class TxtReader
{
    public:
        inline static TxtReader* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new TxtReader();
        }

        std::string ReadTileSet(std::string source, std::string attribute);

    private:
        TxtReader(){};
        static TxtReader* s_Instance;
};

#endif // TXTREADER_H
