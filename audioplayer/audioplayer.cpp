#include "audioplayer.hpp"

#include <iostream>

nie::AudioPlayer::AudioPlayer()
{
    initializeOpenAL();
    alGenSources(1, &audioSource);
}

nie::AudioPlayer::~AudioPlayer()
{
    closeOpenAL();
}

void nie::AudioPlayer::initializeOpenAL()
{
    device = alcOpenDevice(nullptr); // open defeault device
    if(!device)
    {
        std::cerr << "[ERROR] failed to open defeault audio device\n";
        abort();
    }

    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);
}

void nie::AudioPlayer::closeOpenAL()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void nie::AudioPlayer::play(unsigned char *pcm, int size, bool loopable, float posX, float posY, float posZ, float velX, float velY, float velZ)
{
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, pcm, size, 44100);

    audioSourcePos[0] = posX;
    audioSourcePos[1] = posY;
    audioSourcePos[2] = posZ;

    audioSourceVel[0] = velX;
    audioSourceVel[1] = velY;
    audioSourceVel[2] = velZ;

    alSourcei(audioSource, AL_BUFFER, buffer);
    alSourcef(audioSource, AL_PITCH, 1.0f);
    alSourcef(audioSource, AL_GAIN, 1.0f);
    alSourcefv(audioSource, AL_POSITION, audioSourcePos);
    alSourcefv(audioSource, AL_VELOCITY, audioSourceVel);
    alSourcei(audioSource, AL_LOOPING, static_cast<ALboolean>(loopable));

    alSourcePlay(audioSource);

    alDeleteBuffers(1, &buffer);
}

void nie::AudioPlayer::stop()
{
    alSourceStop(audioSource);
}