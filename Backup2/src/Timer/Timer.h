#ifndef TIMER_H
#define TIMER_H

const int FAKE_FPS = 60;

class Timer
{
    public:
        inline static Timer* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Timer();
        }

        void Start();
        void Paused();
        void Unpaused();
        void Stop();

        //Set thu? cong^ FPS
        void SetFPS(const int& fake_fps);

        //Get tgian giua~ 2 event
        int GetTicks();

    private:
        Timer() {}
        static Timer* s_Instance;

        int m_StartTime;
        int m_PausedTime;

        bool m_IsStarted;
        bool m_IsPaused;

};

#endif // TIMER_H
