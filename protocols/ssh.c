/*
 * Copyright (C) 2010 Tildeslash Ltd. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 *
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */

#include <config.h>

#include <ctype.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif

#include "protocol.h"

/**
 *  A simple 'SSH protocol version exchange' implemetation based on
 *  RFC (http://www.openssh.com/txt/draft-ietf-secsh-transport-14.txt)
 * 
 *  @author Igor Homyakov, <homyakov@altlinux.ru>
 *
 *  @file
 */
int check_ssh(Socket_T s) {

  char  buf[STRLEN];

  ASSERT(s);
    
  if(!socket_readln(s, buf, sizeof(buf))) {
    LogError("SSH: error receiving identification string -- %s\n", STRERROR);
    return FALSE;
  }
  
  if(! Util_startsWith(buf, "SSH-")) {
    LogError("SSH: protocol error %s\n", buf);
    return FALSE;
  }

  /* send identification string back to server */
  if(socket_write(s, buf, strlen(buf)) <= 0) {
    LogError("SSH: error sending identification string -- %s\n", STRERROR);
    return FALSE;
  }

  /* Read one extra line to prevent the "Read from socket failed" warning */
  socket_readln(s, buf, sizeof(buf));
   
  return TRUE;
  
}
