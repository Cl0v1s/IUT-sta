#include "Menu.h"

using namespace std;


Menu::Menu(Scene* parent, int x, int y, int w, int h)
{
    m_parent = parent;
    m_selected = 0;
    m_x = x;
    m_y = y;
    m_width = w;
    m_height = h;
    active = true;
}

Menu::~Menu()
{

}

void Menu::addEntry(std::string option, void (*f)(Scene *))
{
        m_options.push_back(option);
        m_callbacks.push_back(f);
}

bool Menu::getActive() const
{
    return active;
}

void Menu::setActive(const bool v)
{
    active = v;
}

bool Menu::changeEntryName(std::string entry, std::string ne)
{
    bool f = false;
    unsigned int i = 0;
    while (i < m_options.size() && !f)
    {
        if(m_options[i] == entry)
        {
            m_options[i] = ne;
            f = true;
        }
        i++;
    }
    return f;
}

string Menu::toString() const
{
    stringstream s;
    for(vector<string>::const_iterator it = m_options.begin(); it != m_options.end(); it++)
    {
        unsigned int index = std::distance(m_options.begin(), it);
        if(index == m_selected)
            s << "> ";
        s << *it << endl;
    }
    return s.str();
}
void Menu::changeOption(int action)
{
    m_selected += action;
    if(m_selected < 0)
        m_selected = m_options.size() -1;
    if(m_selected >= m_options.size())
        m_selected = 0;
}

void Menu::select()
{
    void (*f)(Scene*) = m_callbacks.at(m_selected);
    if(f != NULL)
    {
        f(m_parent);
    }
}
