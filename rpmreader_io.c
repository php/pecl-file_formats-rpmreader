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

/* This file contains the I/O functions used to get data from the RPM
 * files as well as tests associated with the RPM binary format.
 */

#ifdef PHP_WIN32
# include "win32/php_stdint.h"
#else
# ifndef _STDINT_H
#  include <stdint.h>
# endif
#endif

#ifndef _RPMREADER_IO_H
#include "rpmreader_io.h"
#endif

#ifndef _PHP_RPMREADER_H
#include "php_rpmreader.h"
#endif

#ifndef PHP_H
#include "php.h"
#endif

/* {{{ proto void _free_rpmreader(zend_rsrc_list_entry *rsrc)
   Will free an RPM file resource. */
void _free_rpmreader(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
}
/* }}} */

/* {{{ proto void _php_free_rpm_index(void **idx)
   Will free a variable of type rpmIndex that has been emalloc'd during execution. */
void _php_free_rpm_index(void **idx)
{
	/*
	rpmIndex *ri = (rpmIndex *) &(*idx);
	zend_printf("freeing %u ", ri);
	zend_printf("(%u) ", ri->tag);
	zend_printf("(%u) ", ri->datatype);
	zend_printf("(%u) ", ri->offset);
	zend_printf("(%u)<br>\n", ri->count);
	efree(ri);
	*/
}
/* }}} */

/* {{{ proto int _php_rpm_validity(php_stream *stream)
   Will read the first 4 bytes of the file and check to see if they are the magic number that identifies the file as an RPM file. */
int _php_rpm_validity(php_stream *stream TSRMLS_DC)
{
	/*Will return 0 on error, non-zero on success. */

	int c;
	/* rewind the file back to the beginning of the file */
	if (stream)
		php_stream_seek(stream, 0, SEEK_SET); /* rewind */
	else
		return 0;

	if (!php_stream_eof(stream))
		c = php_stream_getc(stream);
	else
		return 0;

	if (c == RPM_MGK_1) {
		if (!php_stream_eof(stream))
			c = php_stream_getc(stream);
		else
			return 0;

		if (c == RPM_MGK_2)	{
			if (!php_stream_eof(stream))
				c = php_stream_getc(stream);
			else
				return 0;

			if (c == RPM_MGK_3) {
				if (!php_stream_eof(stream))
					c = php_stream_getc(stream);
				else
					return 0;

				if (c == RPM_MGK_4)
					return 1;
			}
		}
	}
	return 0;
}
/* }}} */

/* {{{ proto int _php_rpm_seek_header(php_stream *stream)
   Will read from the file pointer until it reaches the first header magic number.  */
int _php_rpm_seek_header(php_stream *stream TSRMLS_DC)
{
	/* This function will return 0 on error, non-zero on success.  The
	 * return value, if not zero, will contain the number of bytes
	 * read from the file.  This is useful later on to use in
	 * calculations from the base of the file.  On successful exit,
	 * the file pointer passed to the function will point to the first
	 * byte of the header (by way of the php_stream_seek function).
	 */
	int found, c, bytecount;
	bytecount = 0;

	found = 0;
	while (!found) {
		if (php_stream_eof(stream) == 0) {
			c = php_stream_getc(stream);
			++bytecount;
		}
		else
			return 0;
		if (c == HDR_MGK_1) {
			if (php_stream_eof(stream) == 0) {
				c = php_stream_getc(stream);
				++bytecount;
			}
			else
				return 0;
			if (c == HDR_MGK_2) {
				if (php_stream_eof(stream) == 0) {
					c = php_stream_getc(stream);
					++bytecount;
				}
				else
					return 0;

				if (c == HDR_MGK_3) {
					found = 1;
					/* subtract the 3 bytes we have read into the
					 * header to test for the magic number. */
					bytecount -= 3;
					if (php_stream_seek(stream, -3, SEEK_CUR) < 0)
						return 0;
				}
			}
		}
	}

	if (found)
		return bytecount;
}
/* }}} */

/* {{{ proto int _php_rpm_find_signature(php_stream *stream)
   Will read from the file pointer until it reaches the first header magic number (the signature). */
int _php_rpm_find_signature(php_stream *stream TSRMLS_DC)
{
	/* This function makes use of the php_stream_seek function to
	 * rewind the file back to the beginning of the file.  The
	 * function will return 0 on error, non-zero on success.  The
	 * return value, if not zero, will contain the byte position value
	 * of the first byte of the signature header.  This is useful
	 * later on to use in calculations from the base of the file.  On
	 * successful exit, the file pointer passed to the function will
	 * point to the first byte of the signature header.
	 */

	int bytecount = 0;

	/* rewind the file back to the beginning of the file */
	if (stream)
		php_stream_seek(stream, 0, SEEK_SET); /* rewind */
	else
		return 0;

	bytecount = _php_rpm_seek_header(stream TSRMLS_CC);

	return bytecount;
}
/* }}} */

/* {{{ proto int _php_rpm_find_header(php_stream *stream)
   Will read from the file pointer until it reaches the second header magic number (the header). */
int _php_rpm_find_header(php_stream *stream TSRMLS_DC)
{
	/* This function makes use of the _php_rpm_find_signature function
	 * to skip to the first header in the file before trying to find
	 * the second header.  The function will return 0 on error,
	 * non-zero on success.  The return value, if not zero, will
	 * contain the number of bytes read from the file.  This is useful
	 * later on to use in calculations from the base of the file.  On
	 * successful exit, the file pointer passed to the function will
	 * point to the first byte of the signature header.
	 */

	int retval, bytecount = 0;
	char c[3];
	size_t size;

	/* Use the _php_rpm_find_signature function to get to the first
	 * header (signature) */
	bytecount = _php_rpm_find_signature(stream TSRMLS_CC);
	if (bytecount == 0)
		return 0;

	/* Skip past the previous header so that the _php_rpm_seek_header
	 * function will not mistakenly find the signature header again */
	size = php_stream_read(stream, c, 3);

	/* If we didn't read 3 bytes, then there was an error */
	if (size != 3)
		return 0;

	/* Increase the bytecount to account for the 3 bytes we just read to
	 * get past the first header magic number. */
	bytecount += 3;

	/* Use the _php_rpm_seek_header function to get to the next
	 * header */ 
	retval = _php_rpm_seek_header(stream TSRMLS_CC);
	if (retval == 0)
		return 0;

	/* Add the new bytecount to the original bytecount from above */
	bytecount += retval;

	return bytecount;
}
/* }}} */

/* {{{ proto int _php_rpm_fetch_header(php_stream *stream, rpmHeader **hdr)
   Will read the header for a header structure within an RPM file. */
int _php_rpm_fetch_header(php_stream *stream, rpmHeader **hdr TSRMLS_DC)
{
	/* This function assumes that the file pointer is pointing to the
	 * first byte of the header.  The function will read the 0x10(16)
	 * bytes of header data from the file pointer and return 0 on
	 * error, non-zero on success.  If the return value is non-zero,
	 * it will be the number of bytes read from the file by this
	 * function.  On success, the rpmHeader parameter will contain the
	 * data from the header.  Storage for the rpmHeader value will be
	 * allocated by this function.  On successful exit from this
	 * function, the file pointer will be pointing to the first byte
	 * of the first index in the header.
	 */

	int mgk[3], nbytes, byte, retcode, uint32_size;
	uint32_t fourbyte;
	rpmHeader *rh = NULL;
	off_t filePos;

	uint32_size = sizeof(uint32_t);
	nbytes = 0;

	if (!stream)
		return 0;

	filePos = php_stream_tell(stream);

	/* read 3 bytes to get past the magic number in the header */
	mgk[0] = php_stream_getc(stream);
	mgk[1] = php_stream_getc(stream);
	mgk[2] = php_stream_getc(stream);
	nbytes += 3;

	/* If the magic number for a header isn't correct, then the file
	 * pointer is in the wrong place or we somehow got here
	 * unexpectedly */ 
	if ( (mgk[0] != HDR_MGK_1) || (mgk[1] != HDR_MGK_2) || (mgk[2] != HDR_MGK_3) )
		return 0;

	/* allocate new space for the header structure */
	if ((rh = (rpmHeader *) emalloc(sizeof(rpmHeader))) == NULL)
		return 0;

	/* set the beginning byte count of the header */
	rh->begin_byte = filePos;

	/* get the version byte from the header and store it in the
	 * rpmHeader structure */
	byte = php_stream_getc(stream);
	++nbytes;
	rh->version = byte;

	/* skip the reserved bits */
	retcode = php_stream_read(stream, (char *) &fourbyte, uint32_size);
	nbytes += uint32_size;
	if (retcode != uint32_size) {
		efree(rh);
		return 0;
	}

	/* get the index count from the header and store it in the rpmHeader
	 * structure */
	retcode = php_stream_read(stream, (char *) &fourbyte, uint32_size);
	nbytes += uint32_size;
	if (retcode != uint32_size) {
		efree(rh);
		return 0;
	}

	/* data in RPM files is stored in network byte order, so ntohl */
	rh->num_indices = ntohl(fourbyte);

	/* get the size of the data store from the header and store it in
	 * the rpmHeader structure */
	retcode = php_stream_read(stream, (char *) &fourbyte, uint32_size);
	nbytes += uint32_size;
	if (retcode != uint32_size) {
		efree(rh);
		return 0;
	}

	/* data in RPM files is stored in network byte order, so ntohl */
	rh->store_size = ntohl(fourbyte);

	*hdr = rh;
	return nbytes;
}
/* }}} */

/* {{{ proto int _php_rpm_fetch_index(php_stream *stream, rpmIndex **idx)
   Will read an index entry within a header in an RPM file. */
int _php_rpm_fetch_index(php_stream *stream, rpmIndex **idx TSRMLS_DC)
{
	/* This function assumes that the file pointer is pointing to the
	 * first byte of an index.  The function will read the 0x10(16)
	 * bytes of index data from the file pointer and return 0 on
	 * error, non-zero on success.  If the return value is non-zero,
	 * it will be the number of bytes read from the file by this
	 * function.  On success, the rpmIndex parameter will contain the
	 * data from the index.  Storage for the rpmIndex value will be
	 * allocated by this function.  On successful exit from this
	 * function, the file pointer will be pointing to the first byte
	 * of the first index in the header.
	 */

	int nbytes, bytesread, uint32_size;
	uint32_t fourbyte;
	rpmIndex *ri = NULL;

	uint32_size = sizeof(uint32_t);
	nbytes = 0;

	if (!stream)
		return 0;

	/* allocate new space for the index structure */
	if ((ri = (rpmIndex *) emalloc(sizeof(rpmIndex))) == NULL)
		return 0;

	/* get the 4-byte tag from the index and store it in the rpmIndex
	 * structure */
	bytesread = php_stream_read(stream, (char *) &fourbyte, uint32_size);
	nbytes += bytesread;
	if (bytesread != uint32_size) {
		efree(ri);
		return 0;
	}

	ri->tag = ntohl(fourbyte);

	/* get the 4-byte data type from the index and store it in the
	 * rpmIndex structure */
	bytesread = php_stream_read(stream, (char *) &fourbyte, uint32_size);
	nbytes += bytesread;
	if (bytesread != uint32_size) {
		efree(ri);
		return 0;
	}

	/* data in RPM files is stored in network byte order, so ntohl */
	ri->datatype = ntohl(fourbyte);

	/* get the 4-byte offset from the index and store it in the rpmIndex
	 * structure */ 
	bytesread = php_stream_read(stream, (char *) &fourbyte, uint32_size);
	nbytes += bytesread;
	if (bytesread != uint32_size) {
		efree(ri);
		return 0;
	}

	/* data in RPM files is stored in network byte order, so ntohl */
	ri->offset = ntohl(fourbyte);

	/* get the 4-byte count from the index and store it in the rpmIndex
	 * structure */ 
	bytesread = php_stream_read(stream, (char *) &fourbyte, uint32_size);
	nbytes += bytesread;
	if (bytesread != uint32_size) {
		efree(ri);
		return 0;
	}

	/* data in RPM files is stored in network byte order, so ntohl */
	ri->count = ntohl(fourbyte);

	*idx = ri;
	return nbytes;
}
/* }}} */

/* {{{ proto int _php_rpm_fetch_store(php_stream *stream, rpmHeader *rh, void **store)
   Will read the entire data store within a header in an RPM file. */
int _php_rpm_fetch_store(php_stream *stream, rpmHeader *rh,
						 void **store TSRMLS_DC)
{
	/* This function assumes that the file pointer is pointing
	 * to the first byte of the store.  If the return value is
	 * non-zero, it will be the number of bytes read from the file by
	 * this function.  On success, the void parameter will contain the
	 * data from the store.  Storage for the void value will be
	 * allocated by this function.  On successful exit from this
	 * function, the file pointer will be pointing to the first byte
	 * of the archive.
	 */
	int nbytes;
	void *buffer;

	nbytes = 0;

	if (!stream)
		return 0;

	if (rh == NULL)
		return 0;

	/* allocate new space for the index structure */
	if ((buffer = (void *) emalloc(rh->store_size)) == NULL)
		return 0;

	nbytes = php_stream_read(stream, (char *) buffer, rh->store_size);
	if (nbytes < rh->store_size) {
		efree(buffer);
		buffer = NULL;
		return 0;
	}

	*store = buffer;

	return nbytes;
}
/* }}} */

/* {{{ proto int _php_rpm_import_indices(php_stream *stream, rpmHeader *hdr, zend_llist **idxlist)
   Will import all the index entries in the Header into a linked list so that we don't have to keep referencing the file to get the information. */
int _php_rpm_import_indices(php_stream *stream, rpmHeader *hdr,
							zend_llist **idxlist TSRMLS_DC)
{
	/* The function will return 0 on error, non-zero on success.  If
	 * successful, the number of indices processed will be returned.
	 */
	int i, nbytes;
	rpmIndex *idx;
	zend_llist *idxl = NULL;
	
	if (!stream)
		return 0;
	
	if (hdr == NULL)
		return 0;

	if (idxl == NULL) {
		idxl = (zend_llist *) emalloc(sizeof(zend_llist));
		zend_llist_init(idxl, sizeof(rpmIndex), (void(*)(void *)) _php_free_rpm_index, 0);
	}

	for (i = 0; i < hdr->num_indices; i++) {
		nbytes = _php_rpm_fetch_index(stream, &idx TSRMLS_CC);
		if (nbytes == 0x10) {
			zend_llist_add_element(idxl, (void *) idx);
		}
		else {
			zend_printf("bytes wrong<br>\n");
		}
	}

	*idxlist = idxl;

	return i;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
