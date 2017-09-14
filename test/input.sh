
cd /tmp; pwd
cd ..; pwd
cd ..; cd -; pwd
cd; cd -; pwd;

setenv toto=; env | grep toto
setenv toto=42; env | grep toto
setenv toto=42=23; env | grep toto
setenv to=to; setenv tototo=to; unsetenv toto
setenv | grep toto

env PATH=toto ls
env -i ls

mkdir -pv /tmp/toto
cd /tmp/toto
touch tata titi
mkdir tutu

	ls	 -a
ls; ls eglk
ls > 1; echo 'yo' >> 1; cat 1; rm 1

echo bob > auteur 2>&1
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

cat << KTHX | cat -e
hey youpla boum
tsoin tsoin
bye
KTHX

rm tata titi auteur
 rmdir	tutu
cd ..
rmdir toto


foo
/bin/ls
/bin/ls -laF
/bin/ls -l -a -F
