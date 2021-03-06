/*.SH.*/

/*
 *  Headerfile for module et_con
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  et_con.cpp on Thursday February 15 2001  13:12:35
 */

#ifndef __et_con__
#define __et_con__


#include "tom/et_tomate.hpp"
#include "tom/et_conser.hpp"

class cTomConServer : public cTomConsole {
   char buffer[1024];
   cConServer con_ser;
public:
   cTomConServer(cString name = NULL) :
      con_ser(name) {}
   virtual ~cTomConServer() {}

   virtual int io_putch(int ch) {
      buffer[0] = ch; buffer[1] = '\0';
      return con_ser.cputs(buffer);
   }
   virtual int io_getch() { return EOF; /*???*/ }
   virtual int io_vprintf(const char *fmt, va_list arg) {
      // Sicherheitsloch: was ist, wenn hier buffer nicht ausreicht ???
      vsprintf( buffer, fmt, arg );
      return con_ser.cputs( buffer );
   }
   virtual int io_kbhit() { return 0; }
   virtual int io_cputs(const char *str) {
      return con_ser.cputs( str );
   }
   virtual char* io_cgets(char *buf) {
      return con_ser.cgets( buf );
   }
};


#endif

/*.EH.*/
