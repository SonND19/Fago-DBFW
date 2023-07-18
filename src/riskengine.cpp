//
// GreenSQL risk engine API. This is GreenSQL core functions.
// These functions are intended to find SQL tautologies.
//
// Copyright (c) 2007 GreenSQL.NET <stremovsky@gmail.com>
// License: GPL v2 (http://www.gnu.org/licenses/gpl.html)
//

// THIS CODE IS NO LONGER IN USE.
#include "mysql/mysql_con.hpp"
#include "pgsql/pgsql_con.hpp"
// #include "dbpermobj.hpp" 
#include "riskengine.hpp"
#include "normalization.hpp"
#include "misc.hpp"
#include "log.hpp"
#include "parser/parser.hpp"
#include <regex>


bool check_or_token(std::string & query)
{
    std::regex pattern("\\bor\\b", std::regex_constants::icase);
    return std::regex_search(query, pattern);
}

bool check_union_token(std::string & query)
{
    std::regex pattern("\\bunion\\b", std::regex_constants::icase);
    return std::regex_search(query, pattern);
}

bool check_in_token(std::string & query)
{
    std::regex pattern("\\bin\\b", std::regex_constants::icase);
    return std::regex_search(query, pattern);
}

bool check_and_token(std::string & query)
{
    std::regex pattern("\\band\\b", std::regex_constants::icase);
    return std::regex_search(query, pattern);
}

bool check_not_token(std::string & query)
{
    std::regex pattern("\\bnot\\b", std::regex_constants::icase);
    return std::regex_search(query, pattern);
}

bool check_true_token(std::string & query)
{
    std::regex pattern("\\btrue\\b", std::regex_constants::icase);
    return std::regex_search(query, pattern);
}

bool check_comments(std::string & query)
{
    std::regex special_char("[\'\\_\\-\\+\\//\\=\\<\\>\\(\\)\\,\\.\\?\\:\\|\\[\\]\\{\\}\\@\\#\\$\\%\\&\\!\\^]");
    
    return std::regex_search(query, special_char);
}
bool check_token(std::string & query)
{
    str_lowercase(query);
    if(check_comments(query) == true)
    {
        return true;
    }
    if(check_or_token(query) == true)
    {
        return true;
    }
    if(check_union_token(query) == true)
    {
        return true;
    }
    if(check_sensitive_tables(query) == true)
    {
        return true;
    }
    if(check_and_token(query) == true)
    {
        return true;
    }
    if(check_in_token(query) == true)
    {
        return true;
    }
    if(check_not_token(query) == true)
    {
        return true;
    }
    return false;
}


 bool check_sensitive_tables(std::string & query)
{
    // we need parse query
    // SELECT xxx from tables where
    // SELECT xxx from t1 left join t2 on XXX and XXX left join
    // left/inner/right join
    // case is not important here - everything must go lowecase ??? 
    std::string list;
    size_t start;
    size_t end;
    str_lowercase(query);
    
    // convers word "join" to a comma
    start = 0;
    while ( (start = list.find(" join ",start)) != std::string::npos)
    {
        list.erase(start+1, 4);
	list[start] = ',';
    }
    
    start = 0;
    size_t temp = 0;
    std::string table;
    end = 0;
    while ( (end = list.find(",", end)) != std::string::npos)
    {
       if (list[start] == ' ')
	       start++;
       temp = list.find(" ", start);
       if (temp != std::string::npos && temp < end)
       {
          table = list.substr(start, temp - start); 
       } else if (temp != std::string::npos)
       {
          table = list.substr(start, end - start);
       } else {
	  table = list.substr(start, end - start);
       }
       if ( check_sensitive_table(table) == true)
           return true;   
       end++;
       start = end;
    }
    // get last table
    if ( start < list.size())
    {
       if (list[start] == ' ')
           start++;
       temp = list.find(" ", start);
       table = list.substr(start, temp-start);
       if ( check_sensitive_table(table) == true)
           return true;
    }
	   
    return false;
}

 bool check_sensitive_table(std::string & table)
{
    if (table.size() == 0)
        return false;
    return true;
}

bool check_white_space(const std::string& query) {
    size_t found = query.find_first_of(" ");
    
    return (found != std::string::npos);
}

bool check_command(const std::string &query)
{
    std::regex pattern("^(select|delete|update|insert|drop|truncate|create|grant|revoke)\\b");
    return std::regex_search(query, pattern);
}
bool check_grant(const std::string &query)
{
    std::regex pattern("\\bgrant\\b.*\\bon\\b.*\\bto\\b", std::regex_constants::icase);

    return std::regex_search(query, pattern);
    
}
bool check_revoke(const std::string &query)
{
    std::regex pattern("\\brevoke\\b.*\\bon\\b.*\\bfrom\\b", std::regex_constants::icase);

    return std::regex_search(query, pattern);
    
}