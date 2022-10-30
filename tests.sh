#!/bin/bash

echo "--------------------------------------------------";
echo "TEST BASIC SEARCH";
echo "-------------------------";
echo "";
echo "./myfind testdir Findme.txt findme2.txt";
./myfind testdir Findme.txt findme2.txt
echo "";
echo "--------------------------------------------------";
echo "--------------------------------------------------";
echo "TEST RECURSIVE"
echo "-------------------------";
echo "";
echo "./myfind testdir -R Findme.txt findme2.txt notfound.txt";
./myfind testdir -R Findme.txt findme2.txt notfound.txt
echo "";
echo "--------------------------------------------------";
echo "--------------------------------------------------";
echo "TEST CASE SENSITIVE";
echo "-------------------------";
echo "";
echo "./myfind testdir findme.txt Findme.txt -i findme2.txt";
./myfind testdir findme.txt Findme.txt -i findme2.txt
echo "";
echo "--------------------------------------------------";
echo "--------------------------------------------------";
echo "TEST ERRORS";
echo "-------------------------";
echo "";
echo "./myfind";
./myfind
echo "";
echo "CASE 2:";
echo "-------------------------";
echo "";
echo "./myfind nodir findme.txt";
./myfind nodir findme.txt
echo "";
echo "CASE 3:";
echo "-------------------------";
echo "";
echo "./myfind /";
./myfind /