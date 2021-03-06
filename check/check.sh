#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    check.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <zboub@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 14:20:41 by mcanal            #+#    #+#              #
#    Updated: 2016/06/08 15:18:38 by mcanal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


VERBOSE=1
MAKE=0

if [ $0 == ./check/check.sh ]; then
	SH_DIR=.;
	CHECK_DIR=check;
else
	SH_DIR=..;
	CHECK_DIR=.;
fi;

if	[ "$MAKE" != 0 ]; then
	make -sC $SH_DIR zclean;
	make -sC $SH_DIR me_cry;
	make -sC $SH_DIR me_cry || exit;
	make -sC $SH_DIR sanitize;
	make -sC $SH_DIR sanitize || exit;
fi;

if [ -n "$1" ]; then
	TARGET=$CHECK_DIR/ctrl;
else
	TARGET=$CHECK_DIR/test;
fi;
echo -e " 
cd $SH_DIR; cd ..; cd -; cd; cd -
setenv toto=; env | grep toto
setenv toto=42; env | grep toto
setenv toto=42=23; env | grep toto
setenv to=to; setenv tototo=to; unsetenv toto
setenv | grep toto
env PATH=toto ls
env -i ls
\tls\t -a	\t 
ls; ls eglk
ls > 1; echo 'yo' >> 1; cat 1; rm 1
cat -e < auteur
cat << KTHX
hey youpla boum
tsoin tsoin
bye
KTHX
ls erlmgk . 2>&1 | cat -e
ls erlmgk . 1>&2 | cat -e
ls ezgge 2> toto; cat toto
ls ezgge 2>> toto; cat toto; rm toto
cat -e 0< auteur
" | $SH_DIR/21sh > $TARGET 2>&1;
echo "$SH_DIR/21sh; exit 42; exit 42" | env -i $SH_DIR/21sh >> $TARGET 2>&1;
echo $? >> $TARGET 2>&1;
if [ -n "$1" ]; then
	cat $TARGET;
	exit;
fi;

diff -y --suppress-common-lines $CHECK_DIR/test $CHECK_DIR/ctrl > $CHECK_DIR/diff;
if [ -s $CHECK_DIR/diff ]; then
	echo -e "\033[31;01mKO\033[0m";
	echo -e "\033[37;01mdiff:\033[0m"; cat $CHECK_DIR/diff;
	if [ "$VERBOSE" != 0 ]; then
		echo -e "\033[37;01m\ntest:\033[0m"; cat $CHECK_DIR/test;
		echo -e "\033[37;01m\ncontrol:\033[0m"; cat $CHECK_DIR/ctrl;
	fi
else
	echo -e "\033[32;01mOK\033[0m";
fi

rm -f $CHECK_DIR/test $CHECK_DIR/diff;
