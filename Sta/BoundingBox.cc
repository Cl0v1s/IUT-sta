#include "BoundingBox.h"

using namespace std;

BoundingBox::BoundingBox(int x, int y, int width, int height)
{
    m_x = x;
    m_y =y;
    m_width= width;
    m_height = height;
    m_density = (m_width + m_height) /2;
}

bool BoundingBox::intersects(const BoundingBox &other)
{
    if(((int)m_x) + m_width >= other.getX() && ((int)m_x) <= other.getX()+other.getWidth() && ((int)m_y) + m_height >= other.getY() && ((int)m_y) <= other.getY()  + other.getHeight())
        return true;
    return false;
}

int BoundingBox::getX() const
{
    return m_x;
}

void BoundingBox::setX(const float x)
{
    m_x = x;
}

int BoundingBox::getY() const
{
    return m_y;
}

void BoundingBox::setY(const float y)
{
    m_y = y;
}

int BoundingBox::getWidth() const
{
    return m_width;
}

void BoundingBox::setWidth(const int width)
{
    m_width = width;
}

int BoundingBox::getHeight() const
{
    return m_height;
}

void BoundingBox::setHeight(const int height)
{
    m_height = height;
}

void BoundingBox::setDensity(const int x)
{
    m_density = x;
}

int BoundingBox::getDensity() const
{
    return m_density;
}

string BoundingBox::toString() const
{
    stringstream s;
    s << "x:" << m_x << " y:" << m_y << " width:" << m_width << " height:" << m_height;
    return s.str();
}

bool BoundingBox::inScreen() const
{
    if(m_x+m_width > 0 && m_x < WINDOW_WIDTH && m_y+m_height > 0 && m_y < WINDOW_HEIGHT)
        return true;
    else
        return false;
}
