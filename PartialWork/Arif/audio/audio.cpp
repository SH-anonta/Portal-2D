#include<windows.h>
#include<mmsystem.h>
//using namespace std;
int main()
{
    while(true)
    {
        PlaySound(TEXT("shoot.wav"), NULL, SND_FILENAME);
       // system("PAUSE");


        if (GetAsyncKeyState( VK_LBUTTON ))
        {
            PlaySound(TEXT("shoot.wav"), NULL, SND_FILENAME);
        }
    }

}

