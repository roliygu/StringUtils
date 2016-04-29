#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

namespace StringUtils{

    static inline bool isBlank(char a){
        if((a==' ')||(a=='\n')||(a=='\r')||(a=='\t')){
            return true;
        }
        return false;
    }

    /**
     * Checks if a string is whitespace or empty.
     * e.g.
     *      ""      => true
     *      " "     => true
     *      "\t\n"  => true
     *      " a"    => false
     */
    static inline bool isBlank(std::string str){
        if(str.empty()){
            return true;
        }
        for(auto i : str){
            if(isBlank(i)){
                return false;
            }
        }
        return true;
    }

    template <class T>
    static inline bool isNotBlank(T a){
        return !isBlank(a);
    }

    /**
     * convert a foundation type value to a string
     * e.g.
     *      1 to "1", 1.1 to "1.1"
     */
    template <class T>
    static inline std::string convert2str(T a){
        std::string res;
        std::stringstream ss;
        ss<<a;
        ss>>res;
        return res;
    }

    /**
     * convert a string to a other foundation type value
     */
    template <class T>
    static inline void convert2other(const std::string str, T &res){
        std::stringstream ss;
        ss<<str;
        ss>>res;
    }

    /**
     * count the number of subStr appearance in source string
     */
    static inline size_t countSubStr(const std::string source, const std::string subStr){
        int count=0;
        int res = source.find(subStr);
        while(res != std::string::npos){
            count++;
            res = source.find(subStr, ++res);
        }
        return count;
    }

    /**
     * filter blank strings
     */
    static inline std::vector<std::string> compact(const std::vector<std::string> &tokens){
        std::vector<std::string> compacted;

        for(auto i : tokens){
            if(!isBlank(i)){
                compacted.push_back(i);
            }
        }

        return compacted;
    }

    static inline std::vector<std::string> split(const std::string &str, const std::string &delim, const bool trim_empty = false){
        size_t pos, last_pos = 0, len;
        std::vector<std::string> tokens;

        while(true) {
            pos = str.find(delim, last_pos);
            if (pos == std::string::npos) {
                pos = str.size();
            }

            len = pos-last_pos;
            if ( !trim_empty || len != 0) {
                tokens.push_back(str.substr(last_pos, len));
            }

            if (pos == str.size()) {
                break;
            } else {
                last_pos = pos + delim.size();
            }
        }

        return tokens;
    }

    static inline std::string join(const std::vector<std::string> &tokens, const std::string &delim, const bool trim_empty = false){
        if(trim_empty) {
            return join(compact(tokens), delim, false);
        } else {
            std::stringstream ss;
            for(size_t i=0; i<tokens.size()-1; ++i) {
                ss << tokens[i] << delim;
            }
            ss << tokens[tokens.size()-1];

            return ss.str();
        }
    }

    static inline std::string trim(const std::string &str){

        size_t begin = 0, size = str.size();
        while((begin<size)&&isBlank(str[begin])){
            begin++;
        }
        if(begin==size){
            return "";
        }
        size_t end = size-1;
        while((end>begin)&&isBlank(str[end])){
            end--;
        }
        return str.substr(begin, end-begin+1);
    }

    static inline std::string repeat(const std::string &str, size_t times){
        std::stringstream ss;
        for(size_t i=0; i<times; ++i) {
            ss << str;
        }
        return ss.str();
    }

    static inline std::string replaceAll(const std::string &source, const std::string &target, const std::string &replacement){
        return join(split(source, target, false), replacement, false);
    }

    static inline std::string toUpper(const std::string &str){
        std::string s(str);
        std::transform(s.begin(), s.end(), s.begin(), toupper);
        return s;
    }

    static inline std::string toLower(const std::string &str){
        std::string s(str);
        std::transform(s.begin(), s.end(), s.begin(), tolower);
        return s;
    }

}

#endif