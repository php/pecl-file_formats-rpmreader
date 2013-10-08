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

/* This file contains the "PHP" functions that will be visible in the
 * PHP module being created */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"

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

/* True global variables */
static int le_rpmreader;

static zend_function_entry rpmreader_functions[] = {
	PHP_FE(rpm_close, NULL)
	PHP_FE(rpm_get_tag, NULL)
	PHP_FE(rpm_is_valid, NULL)
	PHP_FE(rpm_open, NULL)
	PHP_FE(rpm_version, NULL)
	{NULL, NULL, NULL}
};

zend_module_entry rpmreader_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_RPMREADER_EXTNAME,
	rpmreader_functions,
	PHP_MINIT(rpmreader),
	PHP_MSHUTDOWN(rpmreader),
	NULL,
	NULL,
	PHP_MINFO(rpmreader),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_RPMREADER_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_RPMREADER
ZEND_GET_MODULE(rpmreader)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(rpmreader)
{
	/*REGISTER_INI_ENTRIES();*/

	le_rpmreader = zend_register_list_destructors_ex(_free_rpmreader, NULL, "RPM file object", module_number);

	REGISTER_LONG_CONSTANT("RPMREADER_NAME", RPM_TAG_NAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_MINIMUM", RPM_TAG_MINIMUM, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_VERSION", RPM_TAG_VERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_RELEASE", RPM_TAG_RELEASE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_EPOCH", RPM_TAG_EPOCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_SERIAL", RPM_TAG_SERIAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_SUMMARY", RPM_TAG_SUMMARY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_DESCRIPTION", RPM_TAG_DESCRIPTION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_BUILDTIME", RPM_TAG_BUILDTIME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_BUILDHOST", RPM_TAG_BUILDHOST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_INSTALLTIME", RPM_TAG_INSTALLTIME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_SIZE", RPM_TAG_SIZE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_DISTRIBUTION", RPM_TAG_DISTRIBUTION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_VENDOR", RPM_TAG_VENDOR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_GIF", RPM_TAG_GIF, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_XPM", RPM_TAG_XPM, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_LICENSE", RPM_TAG_LICENSE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_COPYRIGHT", RPM_TAG_COPYRIGHT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PACKAGER", RPM_TAG_PACKAGER, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_GROUP", RPM_TAG_GROUP, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_SOURCE", RPM_TAG_SOURCE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PATCH", RPM_TAG_PATCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_URL", RPM_TAG_URL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_OS", RPM_TAG_OS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_ARCH", RPM_TAG_ARCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PREIN", RPM_TAG_PREIN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_POSTIN", RPM_TAG_POSTIN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PREUN", RPM_TAG_PREUN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_POSTUN", RPM_TAG_POSTUN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_OLDFILENAMES", RPM_TAG_OLDFILENAMES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILESIZES", RPM_TAG_FILESIZES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILESTATES", RPM_TAG_FILESTATES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEMODES", RPM_TAG_FILEMODES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILERDEVS", RPM_TAG_FILERDEVS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEMTIMES", RPM_TAG_FILEMTIMES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEMD5S", RPM_TAG_FILEMD5S, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILELINKTOS", RPM_TAG_FILELINKTOS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEFLAGS", RPM_TAG_FILEFLAGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEUSERNAME", RPM_TAG_FILEUSERNAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEGROUPNAME", RPM_TAG_FILEGROUPNAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_ICON", RPM_TAG_ICON, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_SOURCERPM", RPM_TAG_SOURCERPM, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEVERIFYFLAGS", RPM_TAG_FILEVERIFYFLAGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_ARCHIVESIZE", RPM_TAG_ARCHIVESIZE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PROVIDENAME", RPM_TAG_PROVIDENAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PROVIDES", RPM_TAG_PROVIDES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_REQUIREFLAGS", RPM_TAG_REQUIREFLAGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_REQUIRENAME", RPM_TAG_REQUIRENAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_REQUIREVERSION", RPM_TAG_REQUIREVERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CONFLICTFLAGS", RPM_TAG_CONFLICTFLAGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CONFLICTNAME", RPM_TAG_CONFLICTNAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CONFLICTVERSION", RPM_TAG_CONFLICTVERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_EXCLUDEARCH", RPM_TAG_EXCLUDEARCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_EXCLUDEOS", RPM_TAG_EXCLUDEOS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_EXCLUSIVEARCH", RPM_TAG_EXCLUSIVEARCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_EXCLUSIVEOS", RPM_TAG_EXCLUSIVEOS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_RPMVERSION", RPM_TAG_RPMVERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_TRIGGERSCRIPTS", RPM_TAG_TRIGGERSCRIPTS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_TRIGGERNAME", RPM_TAG_TRIGGERNAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_TRIGGERVERSION", RPM_TAG_TRIGGERVERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_TRIGGERFLAGS", RPM_TAG_TRIGGERFLAGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_TRIGGERINDEX", RPM_TAG_TRIGGERINDEX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_VERIFYSCRIPT", RPM_TAG_VERIFYSCRIPT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CHANGELOGTIME", RPM_TAG_CHANGELOGTIME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CHANGELOGNAME", RPM_TAG_CHANGELOGNAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CHANGELOGTEXT", RPM_TAG_CHANGELOGTEXT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PREINPROG", RPM_TAG_PREINPROG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_POSTINPROG", RPM_TAG_POSTINPROG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PREUNPROG", RPM_TAG_PREUNPROG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_POSTUNPROG", RPM_TAG_POSTUNPROG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_BUILDARCHS", RPM_TAG_BUILDARCHS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_OBSOLETENAME", RPM_TAG_OBSOLETENAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_OBSOLETES", RPM_TAG_OBSOLETES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_VERIFYSCRIPTPROG", RPM_TAG_VERIFYSCRIPTPROG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_TRIGGERSCRIPTPROG", RPM_TAG_TRIGGERSCRIPTPROG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_COOKIE", RPM_TAG_COOKIE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEDEVICES", RPM_TAG_FILEDEVICES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEINODES", RPM_TAG_FILEINODES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILELANGS", RPM_TAG_FILELANGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PREFIXES", RPM_TAG_PREFIXES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_INSTPREFIXES", RPM_TAG_INSTPREFIXES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PROVIDEFLAGS", RPM_TAG_PROVIDEFLAGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PROVIDEVERSION", RPM_TAG_PROVIDEVERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_OBSOLETEFLAGS", RPM_TAG_OBSOLETEFLAGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_OBSOLETEVERSION", RPM_TAG_OBSOLETEVERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_DIRINDEXES", RPM_TAG_DIRINDEXES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_BASENAMES", RPM_TAG_BASENAMES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_DIRNAMES", RPM_TAG_DIRNAMES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_OPTFLAGS", RPM_TAG_OPTFLAGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_DISTURL", RPM_TAG_DISTURL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PAYLOADFORMAT", RPM_TAG_PAYLOADFORMAT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PAYLOADCOMPRESSOR", RPM_TAG_PAYLOADCOMPRESSOR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PAYLOADFLAGS", RPM_TAG_PAYLOADFLAGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_INSTALLCOLOR", RPM_TAG_INSTALLCOLOR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_INSTALLTID", RPM_TAG_INSTALLTID, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_REMOVETID", RPM_TAG_REMOVETID, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_RHNPLATFORM", RPM_TAG_RHNPLATFORM, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PLATFORM", RPM_TAG_PLATFORM, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PATCHESNAME", RPM_TAG_PATCHESNAME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PATCHESFLAGS", RPM_TAG_PATCHESFLAGS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_PATCHESVERSION", RPM_TAG_PATCHESVERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CACHECTIME", RPM_TAG_CACHECTIME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CACHEPKGPATH", RPM_TAG_CACHEPKGPATH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CACHEPKGSIZE", RPM_TAG_CACHEPKGSIZE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CACHEPKGMTIME", RPM_TAG_CACHEPKGMTIME, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILECOLORS", RPM_TAG_FILECOLORS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILECLASS", RPM_TAG_FILECLASS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_CLASSDICT", RPM_TAG_CLASSDICT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEDEPENDSX", RPM_TAG_FILEDEPENDSX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILEDEPENDSN", RPM_TAG_FILEDEPENDSN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_DEPENDSDICT", RPM_TAG_DEPENDSDICT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_SOURCEPKGID", RPM_TAG_SOURCEPKGID, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FILECONTEXTS", RPM_TAG_FILECONTEXTS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_FSCONTEXTS", RPM_TAG_FSCONTEXTS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_RECONTEXTS", RPM_TAG_RECONTEXTS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_POLICIES", RPM_TAG_POLICIES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("RPMREADER_MAXIMUM", RPM_TAG_MAXIMUM, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(rpmreader)
{
	/*UNREGISTER_INI_ENTRIES();*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION

 */
PHP_MINFO_FUNCTION(rpmreader)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "RPM files support", "enabled");
	php_info_print_table_row(2, "RPMreader version", PHP_RPMREADER_VERSION);
	php_info_print_table_row(2, "RPMreader revision", "$Revision$");
	php_info_print_table_end();
}

/* }}} */

/* {{{ proto resource rpm_open(string path)
   Opens an RPM file and returns a PHP resource for that file*/
PHP_FUNCTION(rpm_open)
{
	zval *fname;
	int retval;
	php_rpmreader_rsrc *rfr = NULL;
	rpmHeader *rh;
	zend_llist *idxl;
	void *store;
	
	if (ZEND_NUM_ARGS() != 1 || zend_parse_parameters(1 TSRMLS_CC, "z", &fname) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
	
	if (Z_TYPE_P(fname) == IS_STRING) {
		rfr = (php_rpmreader_rsrc *) emalloc(sizeof(php_rpmreader_rsrc));
		
    if (rfr == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to allocate memory for file pointer resource");
		RETURN_FALSE;
    }
	
    rfr->stream = php_stream_open_wrapper(Z_STRVAL_P(fname), "rb", REPORT_ERRORS|ENFORCE_SAFE_MODE|STREAM_MUST_SEEK, NULL);
	
    if (!rfr->stream) {
		efree(rfr);
		RETURN_FALSE;
    }
	
    if (!_php_rpm_validity(rfr->stream TSRMLS_CC)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "File is not an RPM file");
		php_stream_close(rfr->stream);
		efree(rfr);
		RETURN_FALSE;
    }
	
    if (!(retval = _php_rpm_find_header(rfr->stream TSRMLS_CC))) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "RPM Header not found in file");
		php_stream_close(rfr->stream);
		efree(rfr);
		RETURN_FALSE;
    }

    if (_php_rpm_fetch_header(rfr->stream, &rh TSRMLS_CC) < 0x10)	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Cannot read header section");
		php_stream_close(rfr->stream);
		efree(rfr);
		RETURN_FALSE;
    }

    rfr->rpmhdr = rh;

    idxl = NULL;
    retval = _php_rpm_import_indices(rfr->stream, rfr->rpmhdr, &idxl TSRMLS_CC);

    if (idxl == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Problem importing indices");
		php_stream_close(rfr->stream);
		efree(rfr);
		RETURN_FALSE;
    }

    rfr->idxlist = idxl;
	
    retval = _php_rpm_fetch_store(rfr->stream, rfr->rpmhdr, &store TSRMLS_CC);
    if (store == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Problem importing store");
		php_stream_close(rfr->stream);
		efree(rfr);
		RETURN_FALSE;
    }

    rfr->store = store;
	
    ZEND_REGISTER_RESOURCE(return_value, rfr, le_rpmreader);
	}
	else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unexpected parameter type");
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto bool rpm_is_valid(resource handle)
   Uses the _php_rpm_validity function to test the file's validity */
PHP_FUNCTION(rpm_is_valid)
{
	php_stream *stream;
	zval *fname;
	int result;

	if (ZEND_NUM_ARGS() != 1 || zend_parse_parameters(1 TSRMLS_CC, "z", &fname) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
	
	if (Z_TYPE_P(fname) == IS_STRING) {
		stream = php_stream_open_wrapper(Z_STRVAL_P(fname), "rb", REPORT_ERRORS|ENFORCE_SAFE_MODE|STREAM_MUST_SEEK, NULL);
		
		if (!stream) {
			RETURN_FALSE;
		}
		
		result = _php_rpm_validity(stream TSRMLS_CC);
		
		php_stream_close(stream);
		
		if (result)	{
			RETURN_TRUE;
		}
		else {
			RETURN_FALSE;
		}
	}
	else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unexpected parameter type");
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto mixed rpm_get_tag(resource handle, int tagnum)

   Uses the open RPM resource and the tag the user is looking for (using the RPM_TAG_xxx defines in rpmreader.h) and will search through the list for the tag. */
PHP_FUNCTION(rpm_get_tag)
{
	zval *arg1;
	php_rpmreader_rsrc *rfr;
	int found = 0;
	uint32_t count, rpmtag, intvalue;
	void *storeptr = NULL;
	rpmIndex *idx;

	if (ZEND_NUM_ARGS() != 2 || zend_parse_parameters(2 TSRMLS_CC, "zl", &arg1, &rpmtag) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	ZEND_FETCH_RESOURCE(rfr, php_rpmreader_rsrc *, &arg1, -1, "RPM file object", le_rpmreader);

	if (rfr == NULL) {
		RETURN_FALSE;
	}

	if (rfr->idxlist == NULL) {
		RETURN_FALSE;
	}

	if ( (rpmtag < RPM_TAG_MINIMUM) || (rpmtag > RPM_TAG_MAXIMUM) ) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "RPM Tag number is out of range");
		RETURN_FALSE;
	}

	idx = zend_llist_get_first(rfr->idxlist);

	if (idx == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Cannot retrieve index list");
		RETURN_FALSE;
	}

	while (idx != NULL) {
		if (idx == NULL)
			break;

		if (idx->tag == rpmtag) {
			found = 1;
			break;
		}      
		
		idx = zend_llist_get_next(rfr->idxlist);
	}
	
	if (found == 0) {
		RETURN_FALSE;
	}

	if (idx == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Cannot retrieve index");
		RETURN_FALSE;
	}

	count = idx->count;
	storeptr = rfr->store;
	(char *)storeptr += idx->offset;

	switch (idx->datatype) {
	case RPM_TYPE_NULL:
		RETURN_NULL();
		break;
	case RPM_TYPE_CHAR:
		if (count == 1) {
			RETURN_STRING((char *) storeptr, 1);
		}
		else {
			array_init(return_value);
			while (count > 0)	{
				add_next_index_string(return_value, (char *) storeptr, 1);
				(char *)storeptr += sizeof(char);
				count--;
			}
		}
		break;
	case RPM_TYPE_INT8:
		if (count == 1) {
			intvalue = ntohl(*((uint8_t *) storeptr));
			RETURN_LONG((unsigned) intvalue);
		}
		else {
			array_init(return_value);
			while (count > 0) {
				intvalue = ntohl(*((uint8_t *) storeptr));
				add_next_index_long(return_value, (unsigned) intvalue);
				(char *)storeptr += sizeof(uint8_t);
				count--;
			}
		}
		break;
	case RPM_TYPE_INT16:
		if (count == 1) {
			intvalue = ntohl(*((uint16_t *) storeptr));
			RETURN_LONG((unsigned) intvalue);
		}
		else {
			array_init(return_value);
			while (count > 0)	{
				intvalue = ntohl(*((uint16_t *) storeptr));
				add_next_index_long(return_value, (unsigned) intvalue);
				(char *)storeptr += sizeof(uint16_t);
				count--;
			}
		}
		break;
	case RPM_TYPE_INT32:
		if (count == 1) {
			intvalue = ntohl(*((uint32_t *) storeptr));
			RETURN_LONG((unsigned) intvalue);
		}
		else {
			array_init(return_value);
			while (count > 0)	{
				intvalue = ntohl(*((uint32_t *) storeptr));
				add_next_index_long(return_value, (unsigned) intvalue);
				(char *)storeptr += sizeof(uint32_t);
				count--;
			}
		}
		break;
	case RPM_TYPE_STRING_ARRAY:
		if (count == 1) {
			RETURN_STRING((char *) storeptr, 1);
		}
		else {
			array_init(return_value);
			while (count > 0) {
				add_next_index_string(return_value, (char *) storeptr, 1);
				storeptr = strchr((char *) storeptr, 0);
				((char *)storeptr)++;
				count--;
			}
		}
		break;
	case RPM_TYPE_STRING:
	case RPM_TYPE_BIN:
	case RPM_TYPE_I18NSTRING:
		RETURN_STRING((char *) storeptr, 1);
		break;
	default:
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid datatype in RPM tag");
		RETURN_FALSE;
	}
}

/* }}} */

/* {{{ proto bool rpm_close(resource handle)
   Closes the open RPM file and frees all the data used during the execution of the program. */
PHP_FUNCTION(rpm_close)
{
	zval *arg;
	php_rpmreader_rsrc *rfr;
	
	if (ZEND_NUM_ARGS() != 1 || zend_parse_parameters(1 TSRMLS_CC, "z", &arg) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
	
	ZEND_FETCH_RESOURCE(rfr, php_rpmreader_rsrc *, &arg, -1, "RPM file object", le_rpmreader);
	
	if (rfr->stream)
		php_stream_close(rfr->stream);
	if (rfr->rpmhdr)
		efree(rfr->rpmhdr);
	if (rfr->idxlist) {
		zend_llist_clean(rfr->idxlist);
	}
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string rpm_version()
   Returns a string representing the current version of rpmreader */
PHP_FUNCTION(rpm_version)
{
	RETURN_STRING(PHP_RPMREADER_VERSION, 1);
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
