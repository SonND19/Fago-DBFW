//
// GreenSQL risk engine API.
//
// Copyright (c) 2007 GreenSQL.NET <stremovsky@gmail.com>
// License: GPL v2 (http://www.gnu.org/licenses/gpl.html)
//

#ifndef GREENSQL_RISKENGINE_HPP
#define GREENSQL_RISKENGINE_HPP


#include <string>
#include "connection.hpp"
#include "dbpermobj.hpp"
 bool check_comments(std::string & query);
 bool check_sensitive_tables(std::string & query);
 bool check_sensitive_table(std::string & table);
 bool check_or_token(std::string & query);
 bool check_union_token(std::string & query);

 bool check_token(std::string & query);
 bool check_and_token(std::string & query);
 bool check_not_token(std::string & query);
 bool check_in_token(std::string & query);
// unsigned int calc_risk(std::string & query, std::string & pattern, 
// 		std::string &reason);
bool check_comments(std::string & query);
bool check_true_token(std::string & query);
bool check_white_space(const std::string& query);
bool check_command(const std::string &query);
bool check_revoke(const std::string &query);
bool check_grant(const std::string &query);
#endif
