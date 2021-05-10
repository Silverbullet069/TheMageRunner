#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    //Bien' nay` quan? ly' du~ lieu^ cua? file XML
    //Hay noi' cach' khac' la` convert toan` bo^. file XML thanh` 1 LindedList

    xml.LoadFile(source); //Load file co' duong` dan~ la` source

    if(xml.Error()) //Trong truong` hop. khong^ load duoc file
    {
        std::cerr<<"Failed to load : " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    //RootElement() tra? ve` Node root chua' du~ lieu^. cua Element dau` tien^
    //Trong root se~ co' 3 truong` du~ lieu^. can` su? dung.r

    int rowcount = 0; //Tong? so' hang` trong 1 TileLayer
    int colcount = 0; //Tong? so' cot. trong 1 TileLayer
    int tilesize = 0; //Kich' thuoc' cua? 1 tile

    root->Attribute("width", &colcount); //Gan'
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);
    /** NOTE : Cac' du~ lieu^. nay` se~ can` thiet' de? khoi? tao. 1 TileLayer **/


    TileSetsList tilesets; // Khai bao' Vector cac' TileSet

    //Loop qua tat' ca? cac' Node ke^? tu` Node root tro? di
    for(TiXmlElement* e = root->FirstChildElement() ; e != nullptr ; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset")) //Tim` duoc. Node "tileset"
        {
            //push TileSet da~ qua xu' ly' = ham` ParseTileSet vao` trong TileSetsList
            tilesets.push_back(ParseTileSet(e));
        }
    }

    TileMap* gamemap = new TileMap(); // Khai bao' 1 GameMap, GameMap  bao gom` nhieu` Layer

    //Loop qua tat' ca? cac' Node ke^? tu` Node root tro? di
    for(TiXmlElement* e = root->FirstChildElement() ; e != nullptr ; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("layer")) //Tim` duoc. Node "layer"
        {
            //Tao. TileLayer da~ qua xu? ly' = ham` ParseTileLayer, dung` du~ lieu^. trong Node root
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            //push TileLayer vao` trong list Layer ben trong GameMap
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    //Gan' GameMap moi' khoi tao. vao` trong map, id trong ham` Load
    m_MapDict[id] = gamemap;

    return true;
}

TileSet MapParser::ParseTileSet(TiXmlElement* xmlTileSet)
{
    //Xu ly du~ lieu^. cho TileSet

    /** xmlTileSet dang duoc. tro? toi' node "tileset" **/

    TileSet tileset; //Khai bao' 1 Tileset trung gian

    tileset.Name = xmlTileSet->Attribute("name");

    xmlTileSet->Attribute("firstgid", &tileset.FirstID);

    xmlTileSet->Attribute("tilecount", &tileset.TileCount);

    tileset.LastID = tileset.FirstID + tileset.TileCount - 1; //-1 vi` FirstID la` one-based

    xmlTileSet->Attribute("columns", &tileset.ColCount);

    tileset.RowCount = tileset.TileCount / tileset.ColCount;
    //Hieu? TileCount la dien tich', ColCount la` chieu` dai/rong

    xmlTileSet->Attribute("tilewidth", &tileset.TileSize);

    /** LUU Y : trong Node "tileset" khong^ co' du~ lieu^. ten^ file img (Source) \
    nen^ phai? tro? toi' Node tiep' theo la` node "image" **/
    TiXmlElement* image = xmlTileSet->FirstChildElement();
    tileset.Source = image->Attribute("source");

    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlTileLayer, TileSetsList tileSets,
                                     int tileSize, int rowCount, int colCount)
{
    TiXmlElement* data;  //Khai bao' 1 Node trung gian

    //Loop qua tat' ca? cac' node ke? tu` node xmlTileLayer (ta da biet' do' la` node "layer")
    for(TiXmlElement* e = xmlTileLayer->FirstChildElement(); e != nullptr ; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("data")) //Tim` duoc. Node "data"
        {
            data = e; //Gan' node data = node e
            break;
        }
    }
    /** LUU Y : LAYER NAO`, DATA NAY^', TILEMAP DO' **/

    //Xu? ly' du~ lieu^ cho TileLayer
    std::string matrix(data->GetText()); //Ham` GetText() tra? ve` du~ lieu^. trong node "data"
    std::istringstream iss(matrix); //Khai bao' luong` nhap. du~ lieu^. stringstream
    std::string id; //Id cua? tung` tile trong TileLayer

    TileMatrix tilematrix(rowCount, std::vector<int>(colCount, 0));
    //Khoi? tao. 1 bien' tilemap (la` 1 vector 2 chieu`)

    for(int row = 0 ; row < rowCount ; ++row)
    {
        for(int col = 0 ; col < colCount ; ++col)
        {
            getline(iss, id, ','); //Tung` so^' cua? du~ lieu^. trong node "data" duoc nhap^. vao` ID
            //Do cac' so^' trong du~ lieu^ cach' nhau = dau phay, nen ta tao. flag bo? qua.

            std::stringstream convertor (id);
            convertor >> tilematrix[row][col];
            //convert string => int

            if(!iss.good())
            {
                break;
            }
        }
    }

    return (new TileLayer(tileSize, rowCount, colCount, tilematrix, tileSets));
}

void MapParser::Clean()
{
    std::map<std::string, TileMap*>::iterator it;
    for(it = m_MapDict.begin() ; it != m_MapDict.end() ; ++it)
    {
        it->second = nullptr;
    }
    m_MapDict.clear();
}
