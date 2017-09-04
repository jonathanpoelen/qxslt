#!/bin/bash

if [ $# -lt 1 ] || [ $# -gt 2 ] ; then
  echo "$0 file.xml [file.xsl]" >&2
  exit 1
fi

xml="$1"
xsl="$2"
[ $# -eq 1 ] && xsl="${1/\.xml/\.xsl}"

if [ ! -f "$xsl" ] ; then
  echo "$xsl: not found"
  exit 2
fi

tmp="${TMPDIR:-/tmp}"
tmpfile="$tmp/$$.xsl"

sed s'#xmlns="http://www.w3.org/1999/xhtml"##g;s#<html\s\+xml:lang="fr">#<html>#' "$xsl" > "$tmpfile"

./build/qxslt "$(readlink -f "$xml")" "$tmpfile"
