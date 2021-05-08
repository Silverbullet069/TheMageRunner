#include "TxtReader.h"

TxtReader* TxtReader::s_Instance = nullptr;

std::string TxtReader::ReadTileSet(std::string source, std::string attribute)
{
    std::ifstream fileIn(source);

    std::string allText;
    allText.assign((std::istreambuf_iterator<char>(fileIn) ),
                     (std::istreambuf_iterator<char>()    ));

    std::string properAttribute = attribute + "=\"";
    int index_first_found = allText.find(properAttribute);
    std::string str_after_found = allText.substr(index_first_found + properAttribute.size());
    int index_last_found = str_after_found.find("\"");
    std::string str_total_found = str_after_found.substr(0, index_last_found);

    fileIn.close();
    return str_total_found;
}

