#pragma once

#include <unordered_map>

template <typename Res>
class Resource_Manager
{
    public:
        Resource_Manager(std::string&& path, std::string&& extension)
        :   m_path      (std::move(path))
        ,   m_extension (std::move(extension))
        {}

        const Res& get(const std::string& name)
        {
            std::string full = m_path + name + m_extension;

            if (m_resourceMap.find(full))
            {
                ///@TODO Throw error on fail?
                add(name);
            }
            return qGet(full);
        }

        const Res& qGet(const std::string& name)
        {
            ///@TODO Maybe change to use operator []?
            return m_resourceMap.at(name);
        }

        void add(const std::string& name)
        {
            Res res;
            res.loadFromFile(name);
            m_resourceMap.insert(std::make_pair(name, res));
        }

    private:
        std::string m_path;
        std::string m_extension;

        std::unordered_map<std::string, Res> m_resourceMap;
};