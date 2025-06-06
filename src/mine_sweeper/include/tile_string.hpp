#pragma once

#include <cstdint>
#include <array>
#include <iostream>

#include "mine_sweeper_constants.hpp"
#include "mine_sweeper_tile.hpp"

// #define MSWP_COMPACT_TILESTRING 1

namespace mswp
{

#pragma pack(push, 1)

/**
 * @brief Enum that stores two tile visual representation
 * 
 */
enum class TileChar : uint8_t 
{
    VISIBLE_0 = 0u,
    VISIBLE_1 = 1u,
    VISIBLE_2 = 2u,
    VISIBLE_3 = 3u,
    VISIBLE_4 = 4u,
    VISIBLE_5 = 5u,
    VISIBLE_6 = 6u,
    VISIBLE_7 = 7u,
    VISIBLE_8 = 8u,
    VISIBLE_BOMB = 9u,
    HIDDEN = 10u,
    FLAGGED = 11u,
};

#pragma pack(pop)

// Typedefs used inorder to make it easier to change sizes safely.

typedef uint16_t TileStringSize;
typedef uint8_t TileStringWidth;
typedef TileStringSize TileStringIndex;
typedef std::array<TileChar, MSWP_MAX_TILES> TileChars;
typedef std::initializer_list<Tile> TileStringInitList;

/**
 * @brief Converts a tile object into a TileChar
 * 
 * @param tile 
 * @return TileChar::TileChar
 */
inline TileChar tileToTileChar(Tile tile)
{
    if (tile.state & Tile::VISIBLE)
    {
        if (tile.state & Tile::BOMB)
        {
            return TileChar::VISIBLE_BOMB;
        }
        return static_cast<TileChar>(tile.adjBombs);
    }
    if (tile.state & Tile::FLAGGED)
    {
        return TileChar::FLAGGED;
    }
    return TileChar::HIDDEN;
}

/**
 * @brief Converts TileChar into char
 * 
 * @param tileChar 
 * @return char 
 */
inline char tileCharToChar(TileChar tileChar)
{
    switch (tileChar)
    {
    case TileChar::VISIBLE_0:
        return ' ';
    case TileChar::VISIBLE_1:
        return '1';
    case TileChar::VISIBLE_2:
        return '2';
    case TileChar::VISIBLE_3:
        return '3';
    case TileChar::VISIBLE_4:
        return '4';
    case TileChar::VISIBLE_5:
        return '5';
    case TileChar::VISIBLE_6:
        return '6';
    case TileChar::VISIBLE_7:
        return '7';
    case TileChar::VISIBLE_8:
        return '8';

    case TileChar::FLAGGED:
        return '@';
    case TileChar::VISIBLE_BOMB:
        return 'X';

    case TileChar::HIDDEN:
        return '#';
    }
    throw std::runtime_error("INVALID CHARACTER");
}

class TileString
{
public:
    /**
     * @brief Construct a new Tile String object
     * 
     */
    TileString();
    /**
     * @brief Construct a new Tile String object
     * 
     * @param size length of tile string
     * @param width width of the tile string
     */
    TileString(TileStringSize size, TileStringWidth width);
    /**
     * @brief Construct a new Tile String object
     * 
     * @param width width of the tile string
     * @param tiles init list of tiles
     */
    TileString(TileStringWidth width, TileStringInitList&& tiles);
    /**
     * @brief Construct a new Tile String object
     * 
     * @param width width of tile string
     * @param tiles init list of tiles
     */
    TileString(TileStringWidth width, const TileStringInitList& tiles);
    /**
     * @brief Gets reference value at index i
     * 
     * @param i index
     * @return TileChar&
     */
    TileChar& operator[](TileStringIndex i);
    /**
     * @brief Gets value at index i
     * 
     * @param i index
     * @return TileChar 
     */
    TileChar operator[](TileStringIndex i) const;

    /**
     * @brief Compares to init list
     * 
     * @param tiles 
     * @return true 
     * @return false 
     */
    bool operator==(TileStringInitList&& tiles) const;
    /**
     * @brief Compares to other TileString
     * 
     * @param tileChars 
     * @return true 
     * @return false 
     */
    bool operator==(const TileString& tileChars) const;

    /**
     * @brief Sets TileString
     * 
     * @param tiles 
     */
    void operator=(TileStringInitList&& tiles);
    /**
     * @brief Fills tile string with value
     * 
     * @param tileChar
     */
    void fill(TileChar tileChar);

    /**
     * @brief Gets size
     * 
     * @return TileStringSize 
     */
    TileStringSize size() const;
    /**
     * @brief Gets width
     * 
     * @return TileStringWidth 
     */
    TileStringWidth width() const;
    /**
     * @brief Gets TileChars
     * 
     * @return const TileChars& 
     */
    const TileChars& tileChars() const;

    /**
     * @brief Fills self with hidden
     * 
     */
    void reset();

    /**
     * @brief Gets iterator at start
     * 
     * @return TileChar* 
     */
    TileChars::iterator begin();
    /**
     * @brief Gets iterator at end
     * 
     * @return TileChar* 
     */
    TileChars::iterator end();
    /**
     * @brief Gets iterator at start
     * 
     * @return const TileChar* 
     */
    TileChars::const_iterator begin() const;
    /**
     * @brief Gets iterator at end
     * 
     * @return const TileChar* 
     */
    TileChars::const_iterator end() const;
private:
    /**
     * @brief Array of TileChars
     * 
     */
    TileChars m_TileChars;
    /**
     * @brief Space used in TileChars
     * 
     */
    const TileStringSize m_Size;
    /**
     * @brief Width of strings
     * 
     */
    const TileStringWidth m_Width;
};

/**
 * @brief Prints TileString
 * 
 * @param out 
 * @param tileString 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream &out, const TileString& tileString);
/**
 * @brief Prints Tile
 * 
 * @param out 
 * @param tile 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream &out, const Tile& tile);

} // mswp end