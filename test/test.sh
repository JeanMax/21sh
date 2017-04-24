#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <zboub@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/08 15:00:49 by mcanal            #+#    #+#              #
#    Updated: 2017/04/24 18:11:28 by mc               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

if [ $0 == ./test/test.sh ]; then
	SH_DIR=.;
	CHECK_DIR=test;
else
	SH_DIR=..;
	CHECK_DIR=.;
fi;

make -sC $SH_DIR sanitize || exit
touch $CHECK_DIR/ctrl.zob $CHECK_DIR/test.zob $CHECK_DIR/diff.zob

echo $1 | bash > $CHECK_DIR/ctrl.zob 2>&1
echo $1 | $SH_DIR/21sh > $CHECK_DIR/test.zob 2>&1
diff -y --suppress-common-lines $CHECK_DIR/test.zob $CHECK_DIR/ctrl.zob > $CHECK_DIR/diff.zob

if [ -s $CHECK_DIR/diff.zob ]; then
	echo -e "\033[31;01mKO\033[0m"
	echo -e "\033[37;01mctrl:\033[0m"
	cat $CHECK_DIR/ctrl.zob
	echo -e "\033[37;01m\ntest:\033[0m"
	cat $CHECK_DIR/test.zob
	echo -e "\033[37;01m\ndiff:\033[0m"
	cat $CHECK_DIR/diff.zob
else
	echo -e "\033[32;01mOK\033[0m"
fi

rm -f $CHECK_DIR/ctrl.zob $CHECK_DIR/test.zob $CHECK_DIR/diff.zob
