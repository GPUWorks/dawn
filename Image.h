#pragma once
#include <string>
#include <cstring>
#include <boost/shared_ptr.hpp>

#include "constants.h"
#include "Object.h"

namespace dawn
{
  class Buffer : public Object
  {
  public:
    Buffer(const void *data, size_t length)
    {
      m_data = new uint8_t[length];
      std::memcpy(m_data, data, length);
      m_length = length;
    }

    virtual ~Buffer()
    {
      delete [] m_data;
    }

    const uint8_t *raw() const
    {
      return m_data;
    }

  private:
    uint8_t *m_data;
    size_t m_length;
  };

  typedef boost::shared_ptr<Buffer> BufferPtr;

  class Image : public Object
  {
  public:
    virtual ~Image() { }

    virtual BufferPtr buffer() = 0;
    virtual unsigned int width() = 0;
    virtual unsigned int height() = 0;
    virtual CONSTANTS::PixelFormat format() = 0;
  };

  typedef boost::shared_ptr<Image> ImagePtr;
}