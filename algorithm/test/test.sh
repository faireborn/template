#/bin/bash

expected="$($1 <$2)"
echo $3
[ "${expected}" == "$(<$3)" ] || exit 1
