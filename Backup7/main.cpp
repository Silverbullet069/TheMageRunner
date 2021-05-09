
#include "Engine.h"
#include "Timer.h"

//Entity-Component-System Design
//Xay^ dung. doi' tuong. thong^ qua cac' thanh` phan`(component)
//thay vi ke' thua` tu` 1 doi' tuong' goc^' (base object)
//De dang` them^ 1 thuc. the (entiry) phuc tap. moi'
//De dang` mo? rong 1 thuc. the? bang cach' them^ thanh` phan^`
//De dang` sua loi~, bao` tri` va nang^ cap^'

//Su? dung. data-driven architecture, tat^' ca? cac' file anh? va` font se~ duoc. quan? ly' bang` nhung~ file XML

int main(int argc, char** argv)
{
    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning())
    {
        Timer::GetInstance()->Start();
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->SetFPS(FAKE_FPS);
    }

    Engine::GetInstance()->Clean();


    return 0;
}
