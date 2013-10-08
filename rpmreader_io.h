/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2004 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Andrew Teixeira <ateixeira@gmail.com>                       |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef _RPMREADER_IO_H
#define _RPMREADER_IO_H 1

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifdef PHP_WIN32
# include "win32/php_stdint.h"
#else
# ifndef _STDINT_H
#  include <stdint.h>
# endif
#endif

#ifndef PHP_H
#include "php.h"
#endif

/* define the magic numbers that identify a file as an RPM file */
#define RPM_MGK_1 0xed
#define RPM_MGK_2 0xab
#define RPM_MGK_3 0xee
#define RPM_MGK_4 0xdb

/* define the magic numbers for headers within RPM files */
#define HDR_MGK_1 0x8e
#define HDR_MGK_2 0xad
#define HDR_MGK_3 0xe8

/*
 * This macro will calculate the location of the beginning byte of
 * the header store given the number of indices and the offset.  The
 * offset is usually the offset of the header structure of the header
 * from the beginning of the file.
 * The store is found by multiplying the number of indices by the
 * size of an index entry (0x10 or 16) and then adding to that the
 * position of the first index in the header.  Since we are passed
 * the position of the header of the header, then we add 1 to the
 * number of indices since this will account for the fact that we
 * are 0x10 bytes short since the header is 0x10 bytes before the
 * first index entry.
 * We then add the offset to this which is the offset in the file
 * where the header began.
 */
#define STORE_BEGIN_BYTE(indices,offset) ( (((indices) + 1) * 0x10) + (offset) )

typedef struct _rpmHeader {
	long begin_byte;
	int version;
	uint32_t num_indices;
	uint32_t store_size;
} rpmHeader;

typedef struct _rpmIndex {
	uint32_t tag;
	uint32_t datatype;
	uint32_t offset;
	uint32_t count;
} rpmIndex;

typedef struct _rpmIndexNode {
	rpmIndex *idx;
	struct _rpmIndexNode *next;
} rpmIndexNode;

typedef struct _rpmIndexList {
	rpmIndexNode *head;
	rpmIndexNode *tail;
} rpmIndexList;

void _free_rpmreader(zend_rsrc_list_entry *rsrc TSRMLS_DC);
void _php_free_rpm_index(void **idx);
int _php_rpm_validity(php_stream *stream TSRMLS_DC);
int _php_rpm_seek_header(php_stream *stream TSRMLS_DC);
int _php_rpm_find_signature(php_stream *stream TSRMLS_DC);
int _php_rpm_find_header(php_stream *stream TSRMLS_DC);
int _php_rpm_fetch_header(php_stream *stream, rpmHeader **hdr TSRMLS_DC);
int _php_rpm_fetch_index(php_stream *stream, rpmIndex **idx TSRMLS_DC);
int _php_rpm_fetch_store(php_stream *stream, rpmHeader *hdr, void **store TSRMLS_DC);
int _php_rpm_import_indices (php_stream *stream, rpmHeader *hdr,
			     zend_llist **l TSRMLS_DC);

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
