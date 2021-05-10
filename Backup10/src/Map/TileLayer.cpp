#include "TileLayer.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMatrix tileMatrix, TileSetsList tileSets) :
m_TileSize(tileSize), m_ColCount(colCount), m_RowCount(rowCount), m_Tilematrix(tileMatrix), m_Tilesets(tileSets)
{
    //Load tat' ca? anh? cua? Tileset
    for(unsigned int i = 0 ; i < m_Tilesets.size() ; ++i)
    {
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "resource/maps/" + m_Tilesets[i].Source);
    }
}

void TileLayer::Render()
{
    //Ham` nay` se~ Render tat' ca? cac' o^ tile trong 1 TileLayer
    for(unsigned int row_index = 0 ; row_index < m_RowCount ; ++row_index)
    {
        for(unsigned int col_index = 0 ; col_index < m_ColCount ; ++col_index)
        {
            int tileID = m_Tilematrix[row_index][col_index];
            //Lay' tileID trong TileMatrix

            if(tileID == 0)
            {
                continue;
            }
            else
            {
                int ts_index = 0; //Set dang lam` viec^. voi' TileSet duoi' cung`

                if(m_Tilesets.size() > 1) //Neu' co' tu` 2 TileSet tro? len^ trong 1 TileLayer
                {
                    //Loop qua tat' ca? cac' TileSet trong TileSetsList
                    //Luu y: chay. tu` k = 1, tuc' la` xet' tu` TileSet phia' tren^ TileSet duoi' cung`
                    for (unsigned int k = 1 ; k < m_Tilesets.size() ; ++k)
                    {
                        //Luu y: Dau' bang`
                        if(tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID)
                        {
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            ts_index = k;
                            break;
                        }
        /** GIAI THICH :
            Doi' voi' truong` hop. co' nhieu` TileSet trong TileLayer, se~ xay? ra tinh` huong' su? dung. nhieu`
            TileSet trong 1 TileLayer, nhu vay^. co' the? TileID nay` nam` trong mien` quan? ly' cua? TileSet nay`,
            co' TileID lai. nam` trong mien` quan? ly' cua? TileSet kia, ma` viec^. in an^' lai. xu? ly' chung
            tat^' ca? cac' TileID theo one-based indexing (tuc' la` firstID phai? bat' dau` = 1), tai. sao khong^ phai?
            zero-based indexing vi` tileID = 0 quy dinh. nhung~ o^ tile rong~ (khong in gi` o? do' ca?)
            viec^. su? dung. cong^ thuc' kia  se~  quy het' tat' ca? cac' TileID cua? cac' TileSet con` lai.
            ve` one-based indexing. **/

                    }
                }


                /**LUU Y : ColCount la` one-based, tileID cung~ la` one-based
                //Nhung tileRow va tileCol la` zero-based **/

                TileSet ts = m_Tilesets[ts_index];
                int tileRow = tileID/ts.ColCount;
                int tileCol = tileID - tileRow*ts.ColCount - 1;

                //Neu' tile nay` nam` o` cot^. cuoi' cung` trong TileSet
                if(tileID % ts.ColCount == 0)
                {
                    //Theo cong^ thuc' ben^ tren^ thi` row cua? tile nay` se~ tang len^ 1
                    //Nhung thuc. te' la` row cua? tile nay` van~ giu nguyen^
                    tileRow--;
                    //col tile se~ la` tong? so' Col - 1 (col cuoi' cung` nhung theo zero-based)
                    tileCol = ts.ColCount - 1;
                }

            TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, col_index * ts.TileSize,
                                                    row_index * ts.TileSize, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::Update()
{
    //
}
