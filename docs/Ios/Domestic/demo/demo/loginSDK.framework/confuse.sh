#!/usr/bin/env bash

S0="${BASH_SOURCE[0]}"
DIRNAME="$(dirname "$S0")";
DIR="$(cd "$DIRNAME" && pwd)";

TABLENAME=symbols
SYMBOL_DB_FILE="symbols"
STRING_SYMBOL_FILE="$DIR/func.list"
HEAD_FILE="$DIR/loginSDK/wfnjiOpenMix.h"
export LC_CTYPE=C

#维护数据库方便日后作排重
#createTable()
#{
#echo "create table $TABLENAME(src text, des text);" | sqlite3 $SYMBOL_DB_FILE
#}
#
#insertValue()
#{
#echo "insert into $TABLENAME values('$1' ,'$2');" | sqlite3 $SYMBOL_DB_FILE
#}
#
#query()
#{
#echo "select * from $TABLENAME where src='$1';" | sqlite3 $SYMBOL_DB_FILE
#}

ramdomString()
{
openssl rand -base64 64 | tr -cd 'a-zA-Z' |head -c 20
}

rm -f $SYMBOL_DB_FILE
rm -f $HEAD_FILE
#createTable

touch $HEAD_FILE
echo '#ifndef wfnjiOpenMix_h
#define wfnjiOpenMix_h' >> $HEAD_FILE
echo "//confuse string at `date`" >> $HEAD_FILE
cat "$STRING_SYMBOL_FILE" | while read -ra line; do
if [[ ! -z "$line" ]]; then
ramdom=`ramdomString`
echo $line $ramdom
#insertValue $line $ramdom
echo "#define $line $ramdom" >> $HEAD_FILE
fi
done
echo "#endif" >> $HEAD_FILE


#sqlite3 $SYMBOL_DB_FILE .dump

