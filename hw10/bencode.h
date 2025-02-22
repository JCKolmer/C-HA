#pragma once

#include <optional>
#include <string_view>
#include <cstring>
#include <iostream>

namespace bencode {
// TODO: Implement int parsing for the bencode fromat
// Bencode encoded integers have the format `i<number>e`. Your function should return the number.
// The function returns a `std::optional<std::string_view>` to indicate success or failure.
// In the case of success, the optional should have the value of the integer number,
// which might be negative.
//
// We assume that the passed string_view contains only one encoding, and the last character
// of a valid encoding is 'e'. Therefore, you do not need to handle cases like 'i4ei42e'.
//
// Example of a valid encoding: "i42e", which should be parsed to the integer 42.
// Example of a valid encoding: "i-42e", which should be parsed to the integer -42.
//
// Edges cases you might need to look out for:
// - String not starting with 'i', or ending with 'e'
// - Handle empty string
// - Handle if a non-digit number is between 'i' and 'e'
consteval std::optional<int> parse_int(std::string_view str) {
    int n = str.size();
    int result = 0;
    bool minus = false;
    if(str.at(0) != 'i')
    {
        return {};
    }
    if(str.at(str.size()-1)!='e')
    {
        return {};
    }
    if(str.size() < 0)
    {
        return {};
    }
    
    str.remove_suffix(1);
    str.remove_prefix(1);
        if(str.size()==0)
        {
            return {};
        }
        if(str.at(0) == '-')
        {
            minus = true;
            str.remove_prefix(1);
        }
        for(int i=0; i < str.size(); i++)
        {
            int num = str.at(i);
            num = num - 48;
            if((num < 0) || (num > 9))
            {
                return {};
            }
           result = result * 10 + num;
        }
        if(minus)
        {
            result = -result;
        }
        return result;
}

// TODO: Implement byte string parsing for the bencode fromat
// Bencode byte strings have the format <length>:<string>, where `length` is a number.
// The colon ':' separates the length and the actual string.
// The function returns a `std::optional<std::string_view>` to indicate success or failure.
// In the case of success, the optional should have the value of the string.
// For failure, the optional should be empty.
//
// Example of a valid byte string: "5:hello", where the length is 5, and the string is "hello".
//
// You may assume that all characters in the byte string are ASCII characters.
//
// We do not check for all edge cases, important edgecases your implementation should handle:
// - The byte string doesn't start with a number
// - The byte string doesn't have a colon
// - It is fine for the length to be shorter than the string, just return the string according to the length
// - It is NOT valid for the string to be shorter than the specified length
// - The string may contain colons
consteval std::optional<std::string_view> parse_byte_string(std::string_view str) {
    int n = str.size();
     if(n <= 0)
    {
        return {};
    }
    int num = 0;
    int j=0;
    for(j=0;j<n;j++)
    {
        int ziffer = str.at(j) - '0';
        if((ziffer < 0) || (ziffer > 9))
            {
                if(str.at(j) == ':')
                {
                    break;
                }
                return {};
            }
        num = num * 10 + ziffer;
    }
    if(num > n-2)
    {
        return {};
    }
    return str.substr(j+1,num);
}
} // namespace bencode
