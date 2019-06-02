# Codeforces Status Parser

The code of this repository contains a parser that help us to convert the html web page status from Codeforces to a JSON file.

This JSON file has the format required to be used in [Saris by Club Algoritmia ESCOM](https://github.com/galloska/SarisByClubAlgoritmiaESCOM).

The purpose of this tool is to use it in codeforces private contest (mashups).

For other contest we can use [Codeforces API](https://codeforces.com/api/help).

### Installation

To run this tool first you need to get the repository. You can either download the source code in your computer or run the following command:

`git clone https://github.com/galloska/Codeforces-Status-Parser.git`

### How to run this program?

To run this program you need to have installed C++11 in your computer and run the following command in the root of this directory:

`g++ generateLogs.cpp -std=c++11`

Once the file is compiled run:

`./a.out numberOfFileStatus startDateOfContest`

where **numberOfFileStatus** is the total number of html files that conform the status file from the Codeforces contest and **startDateOfContest** is the date when the contest started. This is to get the correct time when each submission was made.

This is an example of how to run the second command:

`./a.out 7 "Jun/01/2019 19:35"`

**Important Note**: this tool will only work if the *logs* folder exists, and the file status are in the folder *status* numbered from 1 to *numberOfFileStatus* in any order. This means status must be named as *1.html, 2.html, ..., numberOfFileStatus.html*.

### Requirements

The requirements of this tool in order to run properly are the following:

* You need to have in your computers installed C++11.
* Folder *status* and *logs* must exists.
* Status files must be named from *1.html, 2.html, ..., to numberOfFileStatus.html*.

You can check the JSON format in the [Saris by Club Algoritmia ESCOM](https://github.com/galloska/SarisByClubAlgoritmiaESCOM) Github page.
