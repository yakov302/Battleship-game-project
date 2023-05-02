#pragma once

#include <SFML/Graphics.hpp>

namespace battle_ship
{

class Text
{
public:
    Text(std::string font_path, std::string text, sf::Color color, int size = 30, int x = 0, int y = 0)
    : m_font()
    , m_text(text, m_font, size)
    {
        m_font.loadFromFile(font_path);
        m_text.setPosition(x, y);
        m_text.setFillColor(color);
    };

    void set_text(std::string text)
    {
        m_text.setString(text);
    };

    void set_position(int x, int y)
    {
        m_text.setPosition(x, y);
    };

    void set_style(sf::Text::Style& style)
    {
        m_text.setStyle(style);
    };

    void set_font(std::string& font_path)
    {
        m_font.loadFromFile(font_path);
    };

    void set_fill_color(sf::Color color)
    {
        m_text.setFillColor(color);
    };

    void set_outline_color(sf::Color& color)
    {
        m_text.setOutlineColor(color);
    };

    void set_outline_thickness(float thickness)
    {
        m_text.setOutlineThickness(thickness);
    };

    void draw(sf::RenderWindow& window) const
    {
        window.draw(m_text);
    }

private:
    sf::Font m_font;
    sf::Text m_text;
};


}// battle_ship namespace
