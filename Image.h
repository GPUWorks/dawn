#pragma once
#include "Pixmap.h"

namespace dawn
{
    class Image : public Pixmap
    {
    public:
        Image(const std::string &path) : m_path(path) { }
        virtual ~Image() { }

        std::string path() const { return m_path; }
        virtual void path(const std::string &path) { markDirty(m_path != path); m_path = path; }

    protected:
        std::string m_path;
    };
}
