#include "RenderText.h"


RenderText::RenderText(std::string label, std::string text, int x, int y, int size, bool centered)
{
    m_label = label;
    if(!m_font.LoadFromFile("assets/font.ttf"))
    {
        throw std::string("Unable to find font.");
    }
    m_string_text = text;
    m_text.SetText(text);
    m_text.SetFont(m_font);
    m_text.SetSize(size);
    m_x = x;
    m_y = y;
    m_size = size;
    m_centered = centered;
    if(centered)
        m_text.Move(x - m_text.GetRect().GetWidth()/2 , y);
    else
        m_text.Move(x, y);


}

void RenderText::draw(sf::RenderWindow *window)
{
    window->Draw(m_text);
}

std::string RenderText::getText() const
{
    return m_string_text;
}

void RenderText::setText(const std::string text)
{
        m_string_text = text;
        m_text.SetText(text);
        if(m_centered)
            m_text.Move(m_x - m_text.GetRect().GetWidth() /2 , m_y);
}

std::string RenderText::getLabel() const
{
    return m_label;
}
