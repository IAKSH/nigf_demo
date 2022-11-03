#include "audio.hpp"

int nigf::Audio::getFileCursorMark(std::ifstream &fs, std::string mark)
{
    int len = mark.length();
    char buf[len + 1];
    buf[len] = '\0';
    int i = 0;
    while (!fs.eof())
    {
        fs.seekg(i++, std::ios::beg);
        fs.read(buf, sizeof(char) * len);
        if (mark.compare(buf) == 0)
            return i;
    }
    std::cerr << "[libwavaudio] ERROR: failed to locate mark (" << mark << ") in moveFileCursorToMark()\n";
    abort();
}

nigf::Audio::Audio(int id, const char *name)
    : ID(id), NAME(name)
{
}

nigf::Audio::Audio(int id, const char *name, const char *path)
    : ID(id), NAME(name)
{
    reload(path);
}

nigf::Audio::~Audio()
{
    if (pcm)
        free(pcm);
}

void nigf::Audio::reload(const char *path)
{
    int i;
    std::ifstream fs(path, std::ios::in | std::ios::binary);
    if (!fs)
    {
        std::cerr << "[ERROR] can't open file (" << path << ")\n";
        abort();
    }

    i = getFileCursorMark(fs, "data") - 1;
    fs.seekg(i + 4, std::ios::beg);
    fs.read((char *)&size, 4);
    fs.seekg(i + 8, std::ios::beg);
    pcm = new unsigned char[size];
    fs.read((char *)pcm, size);

    fs.close();
}

unsigned char *nigf::Audio::get_pcm()
{
    if (!pcm)
    {
        std::cerr << "[ERROR] trying to load pcm from an empty Audio\n";
        abort();
    }

    return pcm;
}

int nigf::Audio::get_size()
{
    if (!pcm)
    {
        std::cerr << "[ERROR] trying to get size from an empty Audio\n";
        abort();
    }

    return size;
}

const std::string_view nigf::Audio::get_name()
{
    return NAME;
}