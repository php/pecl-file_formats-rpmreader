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

#ifndef _PHP_RPMREADER_H
#define _PHP_RPMREADER_H 1

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _RPMREADER_IO_H
#include "rpmreader_io.h"
#endif

#define PHP_RPMREADER_VERSION "0.4.0-dev"
#define PHP_RPMREADER_EXTNAME "rpmreader"

/* The RPM data types that are stored in headers */
#define RPM_TYPE_NULL         0
#define RPM_TYPE_CHAR         1
#define RPM_TYPE_INT8         2
#define RPM_TYPE_INT16        3
#define RPM_TYPE_INT32        4
#define RPM_TYPE_INT64        5
#define RPM_TYPE_STRING       6
#define RPM_TYPE_BIN          7
#define RPM_TYPE_STRING_ARRAY 8
#define RPM_TYPE_I18NSTRING   9

/* The Signature types.  We probably won't be doing anything with
 * signatures, but having the constants around may be useful */
#define RPM_SIG_SIZE 1000
#define RPM_SIG_MD5  1001
#define RPM_SIG_PGP  1002

/* 
 * These constants are the tags that we are going to support in the
 * RPM file.  There may be more tags, but these are the ones we
 * will be supporting.  Most of the tags that have been removed are
 * tags which have been deprecated, obsoleted, unused, or are very
 * internal with no real use to this module
 */
#define RPM_TAG_NAME                     1000
#define RPM_TAG_MINIMUM                  RPM_TAG_NAME
#define RPM_TAG_VERSION                  1001
#define RPM_TAG_RELEASE                  1002
#define RPM_TAG_EPOCH                    1003
#define RPM_TAG_SERIAL                   RPM_TAG_EPOCH
#define RPM_TAG_SUMMARY                  1004
#define RPM_TAG_DESCRIPTION              1005
#define RPM_TAG_BUILDTIME                1006
#define RPM_TAG_BUILDHOST                1007
#define RPM_TAG_INSTALLTIME              1008
#define RPM_TAG_SIZE                     1009
#define RPM_TAG_DISTRIBUTION             1010
#define RPM_TAG_VENDOR                   1011
#define RPM_TAG_GIF                      1012
#define RPM_TAG_XPM                      1013
#define RPM_TAG_LICENSE                  1014
#define RPM_TAG_COPYRIGHT                RPM_TAG_LICENSE
#define RPM_TAG_PACKAGER                 1015
#define RPM_TAG_GROUP                    1016
/*#define RPMTAG_CHANGELOG                 1017*/ /* RPM internal-not used */
#define RPM_TAG_SOURCE                   1018
#define RPM_TAG_PATCH                    1019
#define RPM_TAG_URL                      1020
#define RPM_TAG_OS                       1021
#define RPM_TAG_ARCH                     1022
#define RPM_TAG_PREIN                    1023
#define RPM_TAG_POSTIN                   1024
#define RPM_TAG_PREUN                    1025
#define RPM_TAG_POSTUN                   1026
#define RPM_TAG_OLDFILENAMES             1027
#define RPM_TAG_FILESIZES                1028
#define RPM_TAG_FILESTATES               1029
#define RPM_TAG_FILEMODES                1030
/*#define RPM_TAG_FILEUIDS                 1031*/ /*RPM internal-not used*/
/*#define RPM_TAG_FILEGIDS                 1032*/ /*RPM internal-not used*/
#define RPM_TAG_FILERDEVS                1033
#define RPM_TAG_FILEMTIMES               1034
#define RPM_TAG_FILEMD5S                 1035
#define RPM_TAG_FILELINKTOS              1036
#define RPM_TAG_FILEFLAGS                1037
/*#define RPM_TAG_ROOT                     1038*/ /*RPM internal-not used*/
#define RPM_TAG_FILEUSERNAME             1039
#define RPM_TAG_FILEGROUPNAME            1040
/*#define RPMTAG_EXCLUDE                   1041*/ /*RPM internal-not used*/
/*#define RPMTAG_EXCLUSIVE                 1042*/ /*RPM internal-not used*/
#define RPM_TAG_ICON                     1043
#define RPM_TAG_SOURCERPM                1044
#define RPM_TAG_FILEVERIFYFLAGS          1045
#define RPM_TAG_ARCHIVESIZE              1046
#define RPM_TAG_PROVIDENAME              1047
#define RPM_TAG_PROVIDES                 RPM_TAG_PROVIDENAME
#define RPM_TAG_REQUIREFLAGS             1048
#define RPM_TAG_REQUIRENAME              1049
#define RPM_TAG_REQUIREVERSION           1050
/*#define RPM_TAG_NOSOURCE                 1051*/ /*RPM internal-not used*/
/*#define RPM_TAG_NOPATCH                  1052*/ /*RPM internal-not used*/
#define RPM_TAG_CONFLICTFLAGS            1053
#define RPM_TAG_CONFLICTNAME             1054
#define RPM_TAG_CONFLICTVERSION          1055
/*#define RPMTAG_DEFAULTPREFIX             1056*/ /*RPM internal-not used*/
/*#define RPM_TAG_BUILDROOT                1057*/ /*RPM internal-not used*/
/*#define RPMTAG_INSTALLPREFIX             1058*/ /*RPM internal-not used*/
#define RPM_TAG_EXCLUDEARCH              1059
#define RPM_TAG_EXCLUDEOS                1060
#define RPM_TAG_EXCLUSIVEARCH            1061
#define RPM_TAG_EXCLUSIVEOS              1062
/*#define RPM_TAG_AUTOREQPROV              1063*/ /*RPM internal-not used*/
#define RPM_TAG_RPMVERSION               1064
#define RPM_TAG_TRIGGERSCRIPTS           1065
#define RPM_TAG_TRIGGERNAME              1066
#define RPM_TAG_TRIGGERVERSION           1067
#define RPM_TAG_TRIGGERFLAGS             1068
#define RPM_TAG_TRIGGERINDEX             1069
#define RPM_TAG_VERIFYSCRIPT             1079
#define RPM_TAG_CHANGELOGTIME            1080
#define RPM_TAG_CHANGELOGNAME            1081
#define RPM_TAG_CHANGELOGTEXT            1082
/*#define RPMTAG_BROKENMD5                 1083*/ /*RPM internal-not used*/
/*#define RPM_TAG_PREREQ                   1084*/ /*RPM internal-not used*/
#define RPM_TAG_PREINPROG                1085
#define RPM_TAG_POSTINPROG               1086
#define RPM_TAG_PREUNPROG                1087
#define RPM_TAG_POSTUNPROG               1088
#define RPM_TAG_BUILDARCHS               1089
#define RPM_TAG_OBSOLETENAME             1090
#define RPM_TAG_OBSOLETES                RPM_TAG_OBSOLETENAME
#define RPM_TAG_VERIFYSCRIPTPROG         1091
#define RPM_TAG_TRIGGERSCRIPTPROG        1092
/*#define RPM_TAG_DOCDIR                   1093*/ /*RPM internal-not used*/
#define RPM_TAG_COOKIE                   1094
#define RPM_TAG_FILEDEVICES              1095
#define RPM_TAG_FILEINODES               1096
#define RPM_TAG_FILELANGS                1097
#define RPM_TAG_PREFIXES                 1098
#define RPM_TAG_INSTPREFIXES             1099
/*#define RPM_TAG_TRIGGERIN                1100*/ /*RPM internal-not used*/
/*#define RPM_TAG_TRIGGERUN                1101*/ /*RPM internal-not used*/
/*#define RPM_TAG_TRIGGERPOSTUN            1102*/ /*RPM internal-not used*/
/*#define RPM_TAG_AUTOREQ                  1103*/ /*RPM internal-not used*/
/*#define RPM_TAG_AUTOPROV                 1104*/ /*RPM internal-not used*/
/*#define RPM_TAG_SOURCEPACKAGE            1106*/ /*RPM internal-not used*/
/*#define RPM_TAG_BUILDPREREQ              1108*/ /*RPM internal-not used*/
/*#define RPM_TAG_BUILDREQUIRES            1109*/ /*RPM internal-not used*/
/*#define RPM_TAG_BUILDCONFLICTS           1110*/ /*RPM internal-not used*/
/*#define RPMTAG_BUILDMACROS               1111*/ /*RPM internal-not used*/
#define RPM_TAG_PROVIDEFLAGS             1112
#define RPM_TAG_PROVIDEVERSION           1113
#define RPM_TAG_OBSOLETEFLAGS            1114
#define RPM_TAG_OBSOLETEVERSION          1115
#define RPM_TAG_DIRINDEXES               1116
#define RPM_TAG_BASENAMES                1117
#define RPM_TAG_DIRNAMES                 1118
/*#define RPM_TAG_ORIGDIRINDEXES           1119*/ /*RPM internal-not used*/
/*#define RPM_TAG_ORIGBASENAMES            1120*/ /*RPM internal-not used*/
/*#define RPM_TAG_ORIGDIRNAMES             1121*/ /*RPM internal-not used*/
#define RPM_TAG_OPTFLAGS                 1122
#define RPM_TAG_DISTURL                  1123
#define RPM_TAG_PAYLOADFORMAT            1124
#define RPM_TAG_PAYLOADCOMPRESSOR        1125
#define RPM_TAG_PAYLOADFLAGS             1126
#define RPM_TAG_INSTALLCOLOR             1127
#define RPM_TAG_INSTALLTID               1128
#define RPM_TAG_REMOVETID                1129
/*#define RPMTAG_SHA1RHN                   1130*/ /*RPM internal-not used*/
#define RPM_TAG_RHNPLATFORM              1131
#define RPM_TAG_PLATFORM                 1132
#define RPM_TAG_PATCHESNAME              1133
#define RPM_TAG_PATCHESFLAGS             1134
#define RPM_TAG_PATCHESVERSION           1135
#define RPM_TAG_CACHECTIME               1136
#define RPM_TAG_CACHEPKGPATH             1137
#define RPM_TAG_CACHEPKGSIZE             1138
#define RPM_TAG_CACHEPKGMTIME            1139
#define RPM_TAG_FILECOLORS               1140
#define RPM_TAG_FILECLASS                1141
#define RPM_TAG_CLASSDICT                1142
#define RPM_TAG_FILEDEPENDSX             1143
#define RPM_TAG_FILEDEPENDSN             1144
#define RPM_TAG_DEPENDSDICT              1145
#define RPM_TAG_SOURCEPKGID              1146
#define RPM_TAG_FILECONTEXTS             1147
#define RPM_TAG_FSCONTEXTS               1148
#define RPM_TAG_RECONTEXTS               1149
#define RPM_TAG_POLICIES                 1150
#define RPM_TAG_MAXIMUM                  RPM_TAG_POLICIES

PHP_MINFO_FUNCTION(rpmreader);
PHP_MINIT_FUNCTION(rpmreader);
PHP_MSHUTDOWN_FUNCTION(rpmreader);

PHP_FUNCTION(rpm_close);
PHP_FUNCTION(rpm_get_tag);
PHP_FUNCTION(rpm_is_valid);
PHP_FUNCTION(rpm_open);
PHP_FUNCTION(rpm_version);

extern zend_module_entry rpmreader_module_entry;
#define phpext_rpmreader_ptr &rpmreader_module_entry

typedef struct _php_rpmreader_rsrc {
	php_stream *stream;
	rpmHeader *rpmhdr;
	zend_llist *idxlist;
	void *store;
} php_rpmreader_rsrc;

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
