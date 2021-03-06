#	@(#)Makefile.inc	8.1 (Berkeley) 5/31/93
# $FreeBSD: src/games/Makefile.inc,v 1.10.2.2 2002/02/18 16:02:39 ru Exp $
# $DragonFly: src/games/Makefile.inc,v 1.3 2006/10/08 16:22:34 pavalos Exp $

# These games write to /var/games/
.if defined(VARGAMES)
BINGRP=		games
BINMODE=	2555
.endif

# Handle libcrypto dependency
.if defined(GAMESCRYPTO)
LDADD+=		-lcrypto
DPADD+=		${LIBCRYPTO}
CFLAGS+=	-I${_SHLIBDIRPREFIX}/usr/include/priv
LDFLAGS+=       ${PRIVATELIB_LDFLAGS}
.endif

# Handle libncurses dependency
.if defined(GAMESCURSES)
DPADD+=		${LIBNCURSES}
LDADD+=		-lncurses
CFLAGS+=	-I${_SHLIBDIRPREFIX}/usr/include/ncurses
LDFLAGS+=	${PRIVATELIB_LDFLAGS}
.endif

PREFIX?=	/usr/local
BINDIR?=	${PREFIX}/bin
SHAREDIR=	${PREFIX}/share
MANDIR=		${PREFIX}/man/man
FILESDIR?=	${SHAREDIR}/games
WARNS?=		6

# cribbed from DragonflyBSD build system

NXCC?=		${CC}
NXCFLAGS?=	${CFLAGS:N-mtune*:N-mcpu*:N-march*}

.SUFFIXES: .nx .no

# .no == native object file, for helper code when cross building.
#
.c.no:
	${NXCC} ${_${.IMPSRC:T}_FLAGS} ${NXCFLAGS} -c ${.IMPSRC} -o ${.TARGET}

.y.no:
	${YACC} ${YFLAGS} ${.IMPSRC}
	${NXCC} ${NXCFLAGS} -c y.tab.c -o ${.TARGET}
	rm -f y.tab.c

.l.no:
	${LEX} ${LFLAGS} -o${.TARGET}.c ${.IMPSRC}
	${NXCC} ${NXCFLAGS} -c ${.TARGET}.c -o ${.TARGET}
	rm -f ${.TARGET}.c

.no.nx .c.nx:
	${NXCC} ${_${.IMPSRC:T}_FLAGS} ${NXCFLAGS} ${NXLDFLAGS} ${.IMPSRC} \
	    ${NXLDLIBS} -o ${.TARGET}
