#!/bin/bash

files=`ls | grep -v Auto`

for file in $files; do
  # name
  echo -n "$(echo "$file" | grep -oE "^[a-z]+") "
  # sid
  echo "$(echo "$file" | grep -oE "[0-9]{12}")"