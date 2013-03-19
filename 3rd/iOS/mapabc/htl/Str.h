//
// Str: A C++ String Class
//
// Copyright (c) 2006, Matthew Wachowski All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
// 
//     * Redistributions in binary form must reproduce the above copyright notice,
//       this list of conditions and the following disclaimer in the documentation
//       and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// $Id: Str.hpp,v 1.6 2007/05/05 03:59:14 mattwach Exp $

// Design Goals:
// 
// - Simple
//   - Easy to use, convention over configuration
//   - Lightweight, one file to include.
//   - Minimal dependencies.  Only a bit of the standard C library
//   - Tight integration with char* arrays, cast to a char* any time
//   - Support for [] and =
//   - Automatic memory management in the default case
//   - Simple data representation
// - Fast
//   - Length is tracked.  This optimizes string length, append, and
//     compare operations
//   - Ability to use stack, heap, or persistent memory for storage
// - Flexible
//   - Ability to gracefully handle buffer overruns when stack or
//     persistent memory is used
//   - Ability to optimize operations to increase performance or minimize space
//   - Ability to grow buffer size beyond the current string size

// Some switches
// 
// Uncomment this to avoid the use of throw/catch.  In many cases
// the return can be used
// 
//#define STR_NO_THROW
//
// Uncomment this to bypass safety checks for the sake of faster
// execution
//
// #define STR_NO_CHECKS
//
// Uncomment this line to remove support/dependence on C++ style IO
// streams
//
// #define STR_NO_STREAMS
//
// #define STR_HAVE_STREAMS
// Uncomment this to enable debug verbosity
//
// #define STR_DEBUG

// A quick way to define a stack string.  Use it if you don't mind
// the slightly higher level of obfuscation 

#include "htl_config.h"

#define STR(name,size) char __ ## name ## buff[size]; string name(__ ## name ## buff, sizeof(__ ## name ## buff))

#include <string.h>

#ifdef STR_HAVE_STREAMS
#include <iostream>
using namespace std;
#endif


#ifndef STR_THROW
#include <stdio.h>
#include <stdlib.h>
#define THROW_OUT(str) fprintf(stderr, "Str: %s\n", str); exit(1)
#else
#define THROW_OUT(str) throw str;
#endif

#ifndef CLASS_STR
#define CLASS_STR

__HTL_BEGIN_NAMESPACE

class string {

public:

    // Construct an empty string

	string() { size_and_flags = 0; m_pData = 0; }
    
    // Construct a string from a char based string

    string(const char* cstr);
    
    // Constructstringstring from another string

    string(const string& str);
    
    // Construct a heap-based string.
    
    string(unsigned long size, bool time_efficient);
    
    // Construct a string from the given memory
    
    string(char* buff, unsigned long buff_size, bool initialize=true,
        bool deallocate=false) {
        size_and_flags = 0;
        m_pData = 0;
        attach(buff, buff_size, initialize, deallocate);
    }
    
    // Destructor
    
    ~string();
    
    
    // Resize string buffer to make or free space, if string is
    // time efficient, then new_size will automatically be
    // raised to the next power of 2

    void resize(unsigned long new_size, bool allow_smaller=false);

    // Compact a string down to the lowest size required to hold its
    // current contents.  If time efficient is active, this will 
    // compact the string down to the nearest power of 2
    
    inline void compact() { resize(length() + 1, true); }
    
    // Make a string time or space efficient
    
    void setTimeEfficient(bool flag, bool fix_now=true);
    inline bool isTimeEfficient() const { return (size_and_flags & STR_TIME_EFFICIENT) != 0; }

    // Information
    
    inline unsigned long length() const { return size_and_flags & STR_SIZE_MASK; }
    inline unsigned long size() const {
        if (size_and_flags & STR_EXTRA_BUFFER) {
            unsigned char* tmp_data = reinterpret_cast<unsigned char*>(m_pData + length());
            return (tmp_data[0] << 24) |
                   (tmp_data[1] << 16) |
                   (tmp_data[2] <<  8) |
                    tmp_data[3];
        } else if (m_pData) {
            return length() + 1;
        } else {
            return 0;
        }
    }
    
    inline bool equals(const string& str) const {
        if (&str == this) { return true; }
        else if (length() == str.length()) { return equals(static_cast<const char*>(str)); }
        else { return false; }
    }
    bool equals(const char* cstr) const;
    
    inline bool startsWith(const string& str) const {
        if (&str == this) { return true; }
        else if (length() >= str.length()) { return startsWith(static_cast<const char*>(str)); }
        else { return false; }
    }
    bool startsWith(const char* cstr) const;
    
    inline bool endsWith(const char* cstr) const { return endsWithLen(cstr, strlen(cstr)); }
    inline bool endsWith(const string& str) const { return endsWithLen(static_cast<const char*>(str), str.length()); }
    
    // Manipulation

    inline void append(const char* cstr) { appendWithLength(cstr, strlen(cstr)); }
    inline void append(const string& str)   { appendWithLength(static_cast<const char*>(str), str.length()); }

    // cut will reduce a string in place where copyRange will copy a range of the
    // provided str argument to this string
    
    void cut(unsigned long start_idx, unsigned long end_idx);
    void copyRange(const string& str, unsigned long start_idx, unsigned long end_idx);

    // insert is used to insert strings into the current string
    
    inline void insert(const char* cstr, unsigned long idx) { insertWithLength(cstr, idx, strlen(cstr)); }
    inline void insert(const string& str, unsigned long idx)   { insertWithLength(static_cast<const char*>(str), idx, str.length()); }
    inline void replaceRange(unsigned long start_idx, unsigned long end_idx, const char* cstr) {
        replaceRangeWithLen(start_idx, end_idx, cstr, strlen(cstr));
    }
    inline void replaceRange(unsigned long start_idx, unsigned long end_idx, const string& str) {
        replaceRangeWithLen(start_idx, end_idx, static_cast<const char*>(str), str.length());
    }

    // format is used to place formatted input into this string

    void format(const char* templ, ...);
    
    // rstrip will strip whitespace from the right of a string,
    // lstrip will strip whitespace from the left of a string
    // strip will strip whitespace from both sides of a string
    //
    // A string that represents valid whitespace characters
    // can be passed to these methods. The default whitespace set
    // includes spaces, tabs, new lines, and line feeds

    inline void  strip(const char* whitespace_set=0) { stripPrivate(whitespace_set, true,  true); }
    inline void lstrip(const char* whitespace_set=0) { stripPrivate(whitespace_set, true,  false); }
    inline void rstrip(const char* whitespace_set=0) { stripPrivate(whitespace_set, false, true); }

    // Token operations split the string into individual units

    unsigned int countTokens(unsigned long start_idx=0, const char* white_space_set=0) const;
    long copyToken(const string& str, long start_idx=0, const char* white_space_set=0);

    // getAllTokens is a convenience function that returns an array of Str[] objects, each object pointing
    // to a different token.  The array of Str[] objects and the buffer data they use is referenced
    // in the memory that is returned.  This means that a single free() can be used to deallocate
    // all of the strings and their associated string buffers.  Although convenient, this free()
    // foregoes the ability to run the Str destructors.  For this reason, the Str array returned is
    // constant and no modifiers can be called on individual elements
    //
    // If there are no tokens in the string, this function returns NULL and sets token_count=0

    string* getAllTokens(unsigned int& token_count, const char* white_space_set=0) const;
    
    // Find / Replace / Count substrings

    long findNext(const char* str, unsigned long start_position=0) const;
    unsigned long count(const char* str, unsigned long start_position=0) const;
    unsigned long replace(const char* old_str, const char* new_str, unsigned long start_position=0,
                          bool replace_all=true);

    int find(char c, int start = 0) const;
    // Simple functions to change case
    
    void upper();
    void lower();
    
    bool IsEmpty( ) const;
    
    const string& operator+=( const string& str );
    
	const string& operator+=(char* lpsz );
	const string& operator+=(const char ch );
	
    inline bool operator==(const string& str) const {
        if (&str == this) { return true; }
        else if (length() == str.length()) { return equals(static_cast<const char*>(str)); }
        else { return false; }
    }
    bool operator==(const char* cstr) const;
    
	char at( int iIndex ) const;
	//const string& operator+=( const unsigned short* lpsz );
	
    // Copy operations
    
    string &operator=(const char* cstr);
    string &operator=(const string& str);
    
    
    friend string operator+( const string& string1,const string& string2 );
    
    inline char getChar(int idx) const {
        return m_pData[idx];
    }

    
    inline void setChar(int idx, char c) {
    	m_pData[idx] = c;
    }



    // conversion to and from char*
    
    operator const char* () const { return m_pData; }

    const char* c_str() const { return m_pData; }
    const char* data() const { return m_pData; }  
    
    // detach the char* data from a string and return it to the caller
    
    // At this point the char* data can be manipulated and reattached if
    // needed.  The buff_size and allocated parameter are string
    // attributes that are required to cleanly reattach the string
    //
    // A note on allocated, even if the string was constructed with static
    // buffer data it is possible that it has to reallocate its buffer.
    // It is therefore important to used the allocated parameter and
    // not depend on how the string was initially created when handling
    // memory management.  If allocated is true then someone eventually needs
    // to free() the buffer data.  One easy way to accomplish this is to
    // simply reattach the string
    
    char* detach(unsigned long& buff_size, bool& allocated);
    
    // Attach  C-style strings or buffer to this
    // string.
    // 
    // If initialize is true, then the given buffer is 
    // initialized to a empty string.  If set to false, then
    // it is assumed that a valid string is contained in buff
    // .  Also, if set to false, buff_size will be set to the
    // maximum of its given value and the length of the string
    // in buff.  This allows buff_size=0 to be passed in the case
    // where the buff_size == the length of the string in buff (i.e.
    // a time-saver)
    //
    // If deallocate is set to false, then the caller is responsible
    // for management of buff storage.  This is desirable when using
    // stacked-based or global data.  If deallocate is set to true, it
    // is assumed that malloc() was used to allocate the buffer data.
    // When set to true, free() will be called on this buffer when
    // the string is destructed.
    //
    // If this function is called on a normal string, the strings
    // older buffer is discarded appropriately.  If this function
    // is called on a detaced string, there is no buffer to discard
    // the function simply attached the new buffer

    void attach(char* buff, unsigned long buff_size, bool initialize=true,
                bool deallocate=false);

#ifdef STR_HAVE_STREAMS
    // C++ Stream I/O functions
    
    friend ostream &operator<<(ostream &stream, string& str);
    friend istream &operator>>(istream &stream, string& str); 
#endif
    
    //------------------------------------------------------------------------
    //
    // Here ends the public interface
    //
    //------------------------------------------------------------------------
    

#ifndef SWIG
private:
#endif

    // flags
    
    enum flags {
        STR_ALLOCATED      = 0x80000000,  // Set if the destructor needs to free memory
        STR_EXTRA_BUFFER   = 0x40000000,  // Set if the string has extra buffer space beyond its length  
        STR_TIME_EFFICIENT = 0x20000000,  // Keep string buffer size at a 2^n power for time efficiency 
        STR_SIZE_MASK      = 0x1FFFFFFF,  // mask to extract length
    };
    
    unsigned long size_and_flags;
public:
    char* m_pData;
    
    // Helper functions

    void appendWithLength(const char* cstr, unsigned long cstr_len);
    void insertWithLength(const char* cstr, unsigned long idx, unsigned long cstr_len);
    bool endsWithLen(const char* cstr, unsigned long cstr_len) const;
    void stripPrivate(const char* whitespace_set, bool strip_left, bool strip_right);
    unsigned long calcSubStrChksumAndLength(const char* substr, unsigned long& substr_len) const;
    long findNextWithChecksum(const char* substr, unsigned long start_position, 
                              unsigned long substr_chksum, unsigned long substr_len) const;
    void replaceRangeWithLen(unsigned long start_idx, unsigned long end_idx, const char* cstr, 
                             unsigned long cstr_len);
    
    inline void markExtraBuffer(unsigned long size) {
        unsigned long offset = length();
        if (size > (offset + sizeof(unsigned long))) {
            size_and_flags |= STR_EXTRA_BUFFER;
            unsigned char* tmp_data = reinterpret_cast<unsigned char*>(m_pData + offset);
            tmp_data[0] =  size >> 24;
            tmp_data[1] = (size >> 16) & 0xFF;
            tmp_data[2] = (size >>  8) & 0xFF;
            tmp_data[3] =  size        & 0xFF;
        } else {
            size_and_flags &= ~STR_EXTRA_BUFFER;
        }
    }

    inline unsigned long findNextPower(unsigned long size) {
        unsigned long next_power = 1;
        // Allow for extra buffer field space
        size += 4;
        while (next_power < size) { next_power = next_power << 1; }
        return next_power;
    }

    // to scan forward, pass str=the start of the string, str_len=the search range,
    // and direction=1
    //
    // to scan in reverse pass str=the last chat in the string, str_len=0-the length,
    // and direction=-1

    inline void setupBitMaskArray(unsigned long* bit_mask_array, const char* whitespace_set) const {

        if (!whitespace_set) { 

            unsigned long default_bit_mask_array[] = 
                         { 0x00002600, 0x00000001,
                           0x00000000, 0x00000000,
                           0x00000000, 0x00000000,
                           0x00000000, 0x00000000 };

            memcpy(bit_mask_array, default_bit_mask_array, 8 * sizeof(unsigned long) );
        } else {
            memset(bit_mask_array, 0, 8*sizeof(unsigned long));
            // setup bits in bit_mask_array
            const char* ws_iter = whitespace_set;
            unsigned char w;
            for (; (w = (unsigned char)(*ws_iter)); ++ws_iter) {
                bit_mask_array[w >> 5] |= (1 << (w & 0x1F));
            }
        }
        
    }

    inline void invertBitMaskArray(unsigned long* inv_bma, unsigned long* bma) const {
        
        int i=0;
        for (; i<8; ++i) {
            inv_bma[i] = ~bma[i];
        }
        
    }
    
    inline const char* scanWhiteSpace(const char* str, long str_len,
                                      long direction, 
                                      const unsigned long* bit_mask_array) const {
        const char* ret = 0;
        
        unsigned char c;
        for (; (str_len != 0); str += direction, str_len -= direction) {
            c = (unsigned char)(*str);
            // test the appropriate bit in bit_mask_array.  If the
            // bit is clear then this character is not in the whitespace
            // set
            if (((1 << (c & 0x1F)) & bit_mask_array[c >> 5]) == 0) {
                ret = str;
                break;
            }
        }

        return ret;
        
    }

};

__HTL_END_NAMESPACE

#endif

