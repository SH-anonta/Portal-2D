#ifndef AUDIO_H
#define AUDIO_H

class AudioFacade{
public:

    static void playShootingSound(){
        PlaySound(TEXT("audio_resources/shoot.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_NOSTOP);
    }
};

#endif
