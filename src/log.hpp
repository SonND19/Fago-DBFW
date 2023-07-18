//
// GreenSQL event logging API.
//
// Copyright (c) 2007 GreenSQL.NET <stremovsky@gmail.com>
// License: GPL v2 (http://www.gnu.org/licenses/gpl.html)
//

#ifndef GREEN_SQL_LOG_HPP
#define GREEN_SQL_LOG_HPP

#include <string>
#include "dbpermobj.hpp"
#include <cstring>
// #include "../lib/greensql_types.h"

enum ErrorType { CRIT, ERR, INFO, SQL_DEBUG, DEBUG, STORAGE, NET_DEBUG};


void log_alert(const char *use, const char *db, const char *query, DBBlockLevel block, ...);
bool log_init(std::string & file, int level);
bool LogInit(std::string & file, int level);
bool log_close();
void logevent(ErrorType type, const char * fmt, ...);
void loghex(ErrorType type, const unsigned char * data, int size);
// void log_event(const char * user, const char *query, const char *question, const char *block_reason, ...);
bool Log_init(std::string & file, int level);
void log_event(const char *fmt, ...);

// namespace greensql
// {
// SO_PUBLIC TextLog* TextLog_Init(const char* name, unsigned int maxBuf = 0, size_t maxFile = 0);
// SO_PUBLIC void TextLog_Term(TextLog*);

// SO_PUBLIC bool TextLog_Putc(TextLog* const, char);
// SO_PUBLIC bool TextLog_Quote(TextLog* const, const char*);
// SO_PUBLIC bool TextLog_Write(TextLog* const, const char*, int len);
// SO_PUBLIC bool TextLog_Print(TextLog* const, const char* format, ...) __attribute__((format (printf, 2, 3)));

// SO_PUBLIC bool TextLog_Flush(TextLog* const);
// SO_PUBLIC int TextLog_Avail(TextLog* const);
// SO_PUBLIC void TextLog_Reset(TextLog* const);
// }

// inline bool TextLog_NewLine(TextLog* const txt)
// {
//     return snort::TextLog_Putc(txt, '\n');
// }

// inline bool TextLog_Puts(TextLog* const txt, const char* str)
// {
//     return snort::TextLog_Write(txt, str, strlen(str));
// }

#endif

