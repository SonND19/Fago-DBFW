//
// GreenSQL event logging functions.
//
// Copyright (c) 2007 GreenSQL.NET <stremovsky@gmail.com>
// License: GPL v2 (http://www.gnu.org/licenses/gpl.html)
//
#include <iostream>
#include "log.hpp"
#include <time.h>
#include <string.h>
//#include <syslog.h>
#include "config.hpp"
#include <stdarg.h> //for va_list 
#include <stdio.h>  //for STDOUT
#include <ctype.h> // for isascii

// for fstat
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <cstdarg>
#include <mutex>

static bool log_reload();
static void printline(const unsigned char * data, int max);
static FILE * log_file = stdout;
// static FILE * file_log = stdout;
static FILE *file_alert = stdout;
static FILE *file_event = stdout;
static int log_level = 3;
static char month_str[][4] = { {"Jan"}, {"Feb"}, {"Mar"}, {"Apr"}, {"May"}, {"Jun"}, {"Jul"}, {"Aug"}, {"Sep"}, {"Oct"}, {"Nov"}, {"Dec"}, {NULL} };


bool log_init(std::string & file, int level)
{
    log_level = level;
    FILE * fp = fopen(file.c_str(), "a+");

    if (fp == NULL)
    {
      return false;
    }
    log_file = fp;
    return true;
}

bool log_close()
{
    if (log_file != stdout)
    {
        fclose(log_file);
    }
    else if (file_alert != stdout)
    {
      fclose(file_alert);
    }
    else if (file_event != stdout)
    {
      fclose(file_event);
    }
    log_file = stdout;
    file_alert = stdout;
    file_event = stdout;

    return true;
}

static bool log_reload()
{
    GreenSQLConfig * cfg = GreenSQLConfig::getInstance();
    struct stat f_stat;
  
    if (log_file != stdout) 
    {
      // check if file was deleted 
      if ( fstat(fileno(log_file), &f_stat) == 0 )
      {
        // check number of har links, 0 - deleted
        if (f_stat.st_nlink != 0)
          return true; 
      }
    } 
    else if (file_alert != stdout)
    {
      if ( fstat(fileno(file_alert), &f_stat) == 0 )
      {
        // check number of har links, 0 - deleted
        if (f_stat.st_nlink != 0)
          return true; 
      }
    }
    else if (file_event != stdout)
    {
      if ( fstat(fileno(file_event), &f_stat) == 0 )
      {
        // check number of har links, 0 - deleted
        if (f_stat.st_nlink != 0)
          return true; 
      }
    }
    
    // log file was not found. reload it
    log_close();
    LogInit(cfg->file_alert, cfg->log_level);
    log_init(cfg->log_file, cfg->log_level);
    Log_init(cfg->file_event, cfg->log_level);
    return true; 
}

/*
 * This is a log variadic function
 *
 */
void logevent(ErrorType type, const char * fmt, ...)
{
    va_list ap;
    const char * error;
    struct tm *now;
    time_t tval;
    if (log_level < (int) type)
    {
      va_end(ap);
      return;
    }

    va_start(ap, fmt);
    tval = time(NULL);
    now = localtime(&tval);
        
    switch (type)
    {
      case CRIT:
        error = "CRIT      ";
        break;
      case ERR:
        error = "ERROR       ";
        break;
      case INFO:
        error = "INFO      ";
        break;
      case DEBUG:
        error = "DEBUG     ";
        break;
      case NET_DEBUG:
        error = "NET_DEBUG ";
        break;
      case SQL_DEBUG:
        error = "SQL_DEBUG ";

         break;
      case STORAGE:
        error = "STORAGE   ";
        break;
      default:
        error = "UNKNOWN   ";

        break;
    }
    
    log_reload();
    fprintf(log_file,"[%02d/%s/%02d %d:%02d:%02d] %s",now->tm_mday, month_str[now->tm_mon], now->tm_year+1900, now->tm_hour, now->tm_min, now->tm_sec, error );


    vfprintf(log_file, fmt, ap );
    va_end(ap);
    fflush(log_file);
}


void loghex(ErrorType type, const unsigned char * data, int size)
{
    const char * error;
    struct tm *now;
    time_t tval;

    if (size == 0)
        return;
    if (log_level < (int) type)
        return;

    tval = time(NULL);
    now = localtime(&tval);
 
    switch (type)
    {
      case CRIT:
        error = "CRIT      ";
        break;
      case ERR:
        error = "ERROR     ";
        break;
      case INFO:
        error = "INFO      ";
        break;
      case DEBUG:
        error = "DEBUG     ";
        break;
      case NET_DEBUG:
        error = "NET_DEBUG ";
        break;
      case SQL_DEBUG:
        error = "SQL_DEBUG ";
        break;
      case STORAGE:
        error = "STORAGE   ";
        break;
      default:
        error = "UNKNOWN   ";
        break;
    }

    int lines = size / 16;
    int i = 0;
    
    log_reload();

    for (i = 0; i < lines; i++)
    { std::cout << "log_hex1\n";
      /*fprintf(log_file, error);*/
      fprintf(log_file,"[%02d/%s/%02d %d:%02d:%02d] %s", now->tm_mday, month_str[now->tm_mon], now->tm_year+1900,now->tm_hour, now->tm_min, now->tm_sec, error );
      printline(data+i*16, 16);
    }
    // ord(size%16)
    int ord = (((unsigned char)(size<<4)) >>4);
    if ( ord > 0)
    { std::cout << "log_hex2\n";
      /*fprintf(log_file, error);*/
      fprintf(log_file,"[%02d/%s/%02d %d:%02d:%02d] %s", now->tm_mday, month_str[now->tm_mon], now->tm_year+1900, now->tm_hour, now->tm_min, now->tm_sec, error );
      printline(data+i*16, ord);
    }
    fflush(log_file);
    std::cout << "log_hex3\n";
}

static void printline(const unsigned char * data, int max)
{

    int j = 0;
    char temp[256];
    memset(temp, ' ', sizeof(temp));
    temp[sizeof(temp)-1] = 0;
    unsigned char b;

    for(j = 0; j < max; j++)
    {
      b = data[j];
      if (isalnum(b) || b == ' ' || ispunct(b))
        temp[j] = data[j];
      else
        temp[j] = '.';
    }
    
    // print hex
    temp[18] = '|';

    for (j = 0; j < max; j++)
    {
      b = (data[j]>>4);
      b += ( b > 9) ? 'A'-10 : '0';
      temp[20+j*3] = b;

      b = ((unsigned char)(data[j]<<4)) >>4;
      b += ( b > 9) ? 'A'-10 : '0';
      temp[20+j*3+1] = b;
   }
   temp[20+j*3] = '\n';
   temp[20+j*3+1] = 0;

   fprintf(log_file, "%s", temp);

}

bool LogInit(std::string & file, int level)
{
    log_level = level;
    FILE * fp = fopen(file.c_str(), "a+");

    if (fp == NULL)
    {
      return false;
    }
    file_alert = fp;
    return true;
}

bool Log_init(std::string & file, int level)
{
    log_level = level;
    FILE * fp = fopen(file.c_str(), "a+");

    if (fp == NULL)
    {
      return false;
    }
    file_event = fp;
    return true;
}

void log_alert(const char *use, const char *db, const char *query, DBBlockLevel block, ...)
{
    struct tm *now;
    time_t tval;
    const char * block_level;

    switch (block)
    {
    case WARN:
      block_level = "WARN    ";
      break;
    case BLOCKED:
      block_level = "BLOCKED   ";
      break;
    case HIGH_RISK:
      block_level = "HIGH_RISK    ";
      break;
    case LOW:
      block_level = "LOW    ";
      break;
    case SQL_ERROR:
      block_level = "SQL_ERROR    ";
      break;
    default:
      block_level = "UNKNOWN   ";
      break;
    }

    tval = time(NULL);
    now = localtime(&tval);
    log_reload();

    fprintf(file_alert,"[%02d/%s/%02d %d:%02d:%02d] User: %s [**] Database: %s [**] Query: %s [**] Level_alert: %s\n",
    now->tm_mday, month_str[now->tm_mon], now->tm_year+1900, now->tm_hour, now->tm_min, now->tm_sec, use, db, query, block_level);

    fflush(file_alert);
}

// void log_event(const char * user, const char *query, const char *question, const char *block_reason, ...)
// {
//   struct tm *now;
//   time_t tval;
//   tval = time(NULL);
//   now = localtime(&tval);
//   log_reload();

//   fprintf(file_event,"[%02d/%s/%02d %d:%02d:%02d] ,USER: %s [**] QUERY: %s [**] QUESTION: %s [**] Block_reason: %s",
//           now->tm_mday, month_str[now->tm_mon], now->tm_year+1900, now->tm_hour, now->tm_min, now->tm_sec, user, query, question, block_reason);
    
//   fflush(file_event);
// }

void log_event(const char *fmt, ...)
{
  va_list ap;
  struct tm *now;
  time_t tval;

    va_start(ap, fmt);
    tval = time(NULL);
    now = localtime(&tval);
  log_reload();

  fprintf(file_event,"[%02d/%s/%02d %d:%02d:%02d]" ,
        now->tm_mday, month_str[now->tm_mon], now->tm_year+1900, now->tm_hour, now->tm_min, now->tm_sec);
  vfprintf(file_event, fmt, ap );
  va_end(ap);
  fflush(file_event);
}


// FILE* OpenAlertFile(const char* filearg)
// {
//     FILE* file;

//     if ( !filearg )
//         filearg = "alert.txt";

//     // std::string name;
//     // const char* filename = get_instance_file(name, filearg);

//     if ((file = fopen(filename, "a")) == nullptr)
//     {
//         // FatalError("OpenAlertFile() => fopen() alert file %s: %s\n",
//         //     filename, get_error(errno));
//     }
//     else
//         setvbuf(file, (char*)nullptr, _IOLBF, (size_t)0);

//     return file;
// }

// int RollAlertFile(const char* filearg)
// {
//     char newname[STD_BUF+1];
//     time_t now = time(nullptr);

//     if ( !filearg )
//         filearg = "alert.txt";

//     std::string name;
//     // get_instance_file(name, filearg);
//     const char* oldname = name.c_str();

//     Snprintf(newname, sizeof(newname)-1, "%s.%lu", oldname, (unsigned long)now);


//     if ( rename(oldname, newname) )
//     {
//         // FatalError("RollAlertFile() => rename(%s, %s) = %s\n",
//         //     oldname, newname, get_error(errno));
//         return errno;
        
//     }
//     return errno;
// }
// int Snprintf(char *buf, size_t buf_size, const char *format, ...)
// {
//     va_list ap;
//     int ret;

//     if (buf == nullptr || buf_size == 0 || format == nullptr)
//         return SNORT_SNPRINTF_ERROR;

//     /* zero first byte in case an error occurs with
//      * vsnprintf, so buffer is null terminated with
//      * zero length */
//     buf[0] = '\0';
//     buf[buf_size - 1] = '\0';

//     va_start(ap, format);

//     ret = vsnprintf(buf, buf_size, format, ap);

//     va_end(ap);

//     if (ret < 0)
//         return SNPRINTF_ERROR;

//     if (buf[buf_size - 1] != '\0' || (size_t)ret >= buf_size)
//     {
//         /* result was truncated */
//         buf[buf_size - 1] = '\0';
//         return SNPRINTF_TRUNCATION;
//     }

//     return SNPRINTF_SUCCESS;
// // }
// static FILE* TextLog_Open(const char* name)
// {
//     if ( name && !strcasecmp(name, "stdout") )
//     {
// #ifdef USE_STDLOG
//         FILE* stdlog = fdopen(STDLOG_FILENO, "w");
//         return stdlog ? stdlog : stdout;
// #else
//         return stdout;
// #endif
//     }
//     return LogInit(name);
//     // return OpenAlertFile(name);
// }

// static void TextLog_Close(FILE* file)
// {
//     if ( !file )
//         return;
//     if ( file != stdout )
//         fclose(file);
// }

// static size_t TextLog_Size(FILE* file)
// {
//     struct stat sbuf;
//     int fd = fileno(file);
//     int err = fstat(fd, &sbuf);
//     return err ? 0 : sbuf.st_size;
// }


// namespace greensql
// {
// inline void* greensql_alloc(size_t sz)
// {return new uint8[sz];}

// inline void+ greensql_alloc(size_t num, size_t sz)
// {return greensql_alloc(num * sz);}

// inline void greensql_free(void* p)
// {delete[] (uint8_t*)p;}

// int TextLog_Avail(TextLog* const txt)
// { return txt->maxBuf - txt->pos - 1;}

// void TextLog_Reset(TextLog* const txt)
// {
//     txt->pos = 0;
//     txt->buf[txt->pos] = '\0';
// }

// /*-------------------------------------------------------------------
//  * TextLog_Init: constructor
//  *-------------------------------------------------------------------
//  */
// TextLog* TextLog_Init(
//     const char* name, unsigned int maxBuf, size_t maxFile)
// {
//     TextLog* txt;

//     if ( maxBuf < MIN_BUF )
//         maxBuf = MIN_BUF;

//     txt = (TextLog*)snort_alloc(sizeof(TextLog)+maxBuf);

//     txt->name = name ? snort_strdup(name) : nullptr;
//     txt->file = TextLog_Open(txt->name);
//     txt->size = TextLog_Size(txt->file);
//     txt->last = time(nullptr);
//     txt->maxFile = maxFile;

//     txt->maxBuf = maxBuf;
//     TextLog_Reset(txt);

//     return txt;
// }

// /*-------------------------------------------------------------------
//  * TextLog_Term: destructor
//  *-------------------------------------------------------------------
//  */
// void TextLog_Term(TextLog* const txt)
// {
//     if ( !txt )
//         return;

//     TextLog_Flush(txt);
//     TextLog_Close(txt->file);

//     if ( txt->name )
//         snort_free(txt->name);
//     snort_free(txt);
// }

// /*-------------------------------------------------------------------
//  * TextLog_Flush: start writing to new file
//  * but don't roll over stdout or any sooner
//  * than resolution of filename discriminator
//  *-------------------------------------------------------------------
//  */
// static void TextLog_Roll(TextLog* const txt)
// {
//     if ( txt->file == stdout )
//         return;
//     if ( txt->last >= time(nullptr) )
//         return;

//     TextLog_Close(txt->file);
//     RollAlertFile(txt->name);
//     txt->file = TextLog_Open(txt->name);

//     txt->last = time(nullptr);
//     txt->size = 0;
// }

// /*-------------------------------------------------------------------
//  * TextLog_Flush: write buffered stream to file
//  *-------------------------------------------------------------------
//  */
// bool TextLog_Flush(TextLog* const txt)
// {
//     int ok;

//     if ( !txt->pos )
//         return false;

//     if ( txt->maxFile and txt->size + txt->pos > txt->maxFile )
//         TextLog_Roll(txt);

//     ok = fwrite(txt->buf, txt->pos, 1, txt->file);

//     if ( ok == 1 )
//     {
//         txt->size += txt->pos;
//         TextLog_Reset(txt);
//         return true;
//     }
//     return false;
// }

// /*-------------------------------------------------------------------
//  * TextLog_Putc: append char to buffer
//  *-------------------------------------------------------------------
//  */
// bool TextLog_Putc(TextLog* const txt, char c)
// {
//     if ( TextLog_Avail(txt) < 1 )
//     {
//         TextLog_Flush(txt);
//     }
//     txt->buf[txt->pos++] = c;
//     txt->buf[txt->pos] = '\0';

//     return true;
// }

// /*-------------------------------------------------------------------
//  * TextLog_Write: append string to buffer
//  *-------------------------------------------------------------------
//  */
// bool TextLog_Write(TextLog* const txt, const char* str, int len)
// {
//     do
//     {
//         int avail = TextLog_Avail(txt);
//         int n = snprintf(txt->buf+txt->pos, avail, "%.*s", len, str);
//         if ( n < avail and n < len )
//             return false;

//         // actual bytes written:
//         // 1) if avail is a limit, auto-appended '\0' should be truncated
//         // 2) avail could be zero from the start, keep it as 0
//         int l = std::min(n, avail > 0 ? avail - 1 : 0);
//         txt->pos += l;
//         str += l;
//         len -= l;

//         if ( n >= avail )
//             TextLog_Flush(txt);
//     }
//     while ( len > 0 );

//     return true;
// }

// /*-------------------------------------------------------------------
//  * TextLog_Printf: append formatted string to buffer
//  *-------------------------------------------------------------------
//  */
// bool TextLog_Print(TextLog* const txt, const char* fmt, ...)
// {
//     int avail = TextLog_Avail(txt);
//     int len;
//     va_list ap;

//     va_start(ap, fmt);
//     len = vsnprintf(txt->buf+txt->pos, avail, fmt, ap);
//     va_end(ap);

//     if ( len >= avail )
//     {
//         TextLog_Flush(txt);
//         avail = TextLog_Avail(txt);

//         va_start(ap, fmt);
//         len = vsnprintf(txt->buf+txt->pos, avail, fmt, ap);
//         va_end(ap);
//     }
//     if ( len >= avail )
//     {
//         txt->pos = txt->maxBuf - 1;
//         txt->buf[txt->pos] = '\0';
//         return false;
//     }
//     else if ( len < 0 )
//     {
//         return false;
//     }

//     txt->pos += len;

//     return true;
// }

// /*-------------------------------------------------------------------
//  * TextLog_Quote: write string escaping quotes
//  *-------------------------------------------------------------------
//  */
// bool TextLog_Quote(TextLog* const txt, const char* qs)
// {
//     TextLog_Putc(txt, '"');

//     do
//     {
//         int len = strlen(qs);
//         int pre = strcspn(qs, "\"\\");

//         TextLog_Write(txt, qs, pre);
//         qs += pre;

//         if ( pre < len )
//         {
//             TextLog_Putc(txt, '\\');
//             TextLog_Putc(txt, *qs++);
//         }
//     }
//     while ( *qs );

//     TextLog_Putc(txt, '"');

//     return true;
// }
// }