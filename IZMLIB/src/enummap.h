#ifndef IZM_ENUMMAP_H
#define IZM_ENUMMAP_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <initializer_list>

namespace izm
{

template<class T>
class EnumMap
{
public:
    EnumMap() {}
    EnumMap( std::initializer_list<std::pair<T, std::string>> list ) : m_data( list.begin(), list.end() ) {}

public:
    void registerElement( const T& element, const std::string& str )
    {
        if ( !isDefined( element ) )
        {
            m_data.insert( { element, str } );
        }
    }

    T parse( const std::string str ) const
    {
        T ret;
        bool found = searchElement( str, [&ret](const T& elem){ ret = elem; } );
        if ( !found )
        {
            throw std::invalid_argument( "cannot convert to element" );
        }
        return ret;
    }

    std::string toString( const T& element ) const
    {
        auto&& ret = std::string();
        if ( isDefined( element ) )
        {
            ret = m_data.at( element );
        }
        else
        {
            throw std::invalid_argument( "cannot convert to string" );
        }
        return ret;
    }

    std::vector<T> elements() const
    {
        auto&& ret = std::vector<T>();
        for ( auto&& item : m_data )
        {
            ret.push_back( item.first );
        }
        return ret;
    }

    std::vector<std::string> stringList() const
    {
        auto&& ret = std::vector<T>();
        for ( auto&& item : m_data )
        {
            ret.push_back( item.second );
        }
        return ret;
    }

    bool isDefined( const T& element ) const
    {
        return ( m_data.find( element ) != m_data.end() ) ? true : false;
    }

    bool isDefined( const std::string& str )
    {
        return searchElement( str, nullptr );
    }
private:
    bool searchElement( const std::string& str, std::function<void (const T&)> func ) const
    {
        bool found = false;
        for ( auto&& item : m_data )
        {
            if ( item.second == str )
            {
                found = true;
                if ( func != nullptr )
                {
                    func( item.first );
                }
                break;
            }
        }
        return found;
    }

private:
    std::map<T, std::string> m_data = {};
};

} // namespace izm

#endif // IZM_ENUMMAP_H
