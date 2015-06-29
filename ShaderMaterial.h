#pragma once
#include <map>
#include "IMaterial.h"
#include "Image.h"
#include "types.h"

namespace dawn
{
    class ShaderMaterial : public IMaterial
    {
    public:
        ShaderMaterial(std::string path) : m_path(path) { }

        CONSTANTS::MaterialType type() const { return CONSTANTS::ShaderMaterial; }

        std::string path() const { return m_path; }
        void path(std::string path) { markDirty(m_path != path); m_path = path; } // TODO Should it exist?

        UniformMap uniforms() const { return m_uniforms; }

        // TODO make read const
        uniform_t uniform(std::string key) { return m_uniforms[key]; }
        void uniform(std::string key, uniform_t value) { markDirty(); m_uniforms[key] = value; }

        virtual bool isDirty(bool recursive = false) const {
            if (IMaterial::isDirty(recursive)) {
                return true;
            } else if (recursive) {
                for (UniformMap::const_iterator itr = m_uniforms.begin(); itr != m_uniforms.end(); itr++) {
                    uniform_t u = itr->second;

                    if (u.type() == typeid(Object *) && boost::any_cast<Object *>(u)->isDirty(recursive)) {
                        return true;
                    }
                }
            }

            return false;
        }

        virtual void clean() {
            IMaterial::clean();

            for (UniformMap::const_iterator itr = m_uniforms.begin(); itr != m_uniforms.end(); itr++) {
                uniform_t u = itr->second;

                if (u.type() == typeid(Object *)) {
                    boost::any_cast<Object *>(u)->clean();
                }
            }
        }

    private:
        std::string m_path;
        UniformMap m_uniforms;
    };
}