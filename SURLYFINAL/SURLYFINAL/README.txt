What Is This?
-------------

This project is a working algorithm of Database major implementations such as CREATE TABLE, INSERT, PRINT, DELETE, DESTROY, SELECT, PROJECT, JOIN, and IMPORT, EXPORT. The code uses many directories and libraries including iostream, sstream, map, string, string.h, stdio.h, algorithm, stdlib.h, deque, fstream, cstring, typeinfo, vector, dirent.h, iomanip, ctype.h and rapidXML. 

How To Use It
--------------

1. Specify a .txt file that would have the database statements on it and run the code 

2. Read the code. 

3. The code is written with a lot of comments line to make the code readable and easily understandable.

4. To do the Import and Export operations, a .xml file is required. The xml file path must be clearly represented. 

Syntax For Using The code:
--------------------------
To create a table specify the table name and attributes in the following format:

RELATION <table name> (<attribute1 name> <attribute1 type> <attribute1_max>, …..,<attributen name> <attributen type> <attributen_max>);

To Insert tuples:
INSERT <table name>  <value1, . . . . valuen>;

To delete a table:
DELETE <table_name>;

TO print :
PRINT <table_names>;

To do select operation:
SELECT <table name> WHERE <conditions>;

To create a temporary table for the output of select or join operation 
<temporary_table_name> = <Select/Join Query>;

To Import/Export a table:
EXPORT/IMPORT <table_name>;

How To Install The Modules
--------------------------

1. Most of the Libraries are predefined but some libraries need to be downloaded, they can be downloaded from github  


Now you can read the code and its comments and see the result, experiment with
it