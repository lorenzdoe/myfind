#!/bin/bash

echo "--------------------------------------------------";
echo "TEST BASIC SEARCH RELATEIV PATH";
echo "-------------------------";
echo "call: ./myfind ./testdir Findme.txt findme2.txt";
echo
./myfind testdir Findme.txt findme2.txt
echo 
read -p "Press any key to resume ..." null
echo "--------------------------------------------------";
echo "--------------------------------------------------";
echo "TEST BASIC SEARCH ABSOLUTE PATH";
echo "-------------------------";
echo "call: ./myfind /home/lorenz/uni/3_sem/verts/myfind Findme.txt findme2.txt";
echo
./myfind testdir Findme.txt findme2.txt
echo 
read -p "Press any key to resume ..." null
echo "--------------------------------------------------";
echo "--------------------------------------------------";
echo "TEST RECURSIVE"
echo "-------------------------";
echo "call: ./myfind testdir -R Findme.txt findme2.txt notfound.txt";
echo 
./myfind testdir -R Findme.txt findme2.txt notfound.txt
echo 
read -p "Press any key to resume ..." null
echo "--------------------------------------------------";
echo "--------------------------------------------------";
echo "TEST CASE SENSITIVE";
echo "-------------------------";
echo "call: ./myfind testdir findme.txt Findme.txt -i findme2.txt";
echo 
./myfind testdir findme.txt Findme.txt -i findme2.txt
echo 
read -p "Press any key to resume ..." null
echo "--------------------------------------------------";
echo "--------------------------------------------------";
echo "TEST CASE SENSITIVE AND RECURSIVE";
echo "-------------------------";
echo "call: ./myfind testdir findme.txt Findme.txt -i findme2.txt -R";
echo 
./myfind testdir findme.txt Findme.txt -i findme2.txt -R
echo 
read -p "Press any key to resume ..." null
echo "--------------------------------------------------";
echo "--------------------------------------------------";
echo "TEST ERRORS";
echo "-------------------------";
echo "call without params" 
echo
echo "call: ./myfind";
./myfind
echo 
echo "-------------------------";
echo "call with invalid directory"
echo 
echo "./myfind nodir findme.txt";
./myfind nodir findme.txt
echo 
echo "-------------------------";
echo "call only with directory" 
echo
echo "./myfind /";
./myfind /
