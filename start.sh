#!/bin/bash

gcc main.c -o main
if [ $? -eq 0 ]; then
  HORA=$(date +"%H:%M:%S")
  echo "Compilacion exitosa a las: $HORA"
  ./main
fi
  

