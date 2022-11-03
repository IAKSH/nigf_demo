#pragma once

#include <AL/al.h>
#include <AL/alc.h>

namespace nie
{
    class AudioPlayer
    {
    private:
        ALCdevice *device = nullptr;
        ALCcontext *context = nullptr;
        ALuint buffer;
        ALuint audioSource;
        ALfloat audioSourcePos[3];
        ALfloat audioSourceVel[3];

        void initializeOpenAL();
        void closeOpenAL();

    public:
        AudioPlayer();
        ~AudioPlayer();

        void play(unsigned char *pcm,int size, bool loopable, float posX, float posY, float posZ, float velX, float velY, float velZ);
        void stop();
    };
}