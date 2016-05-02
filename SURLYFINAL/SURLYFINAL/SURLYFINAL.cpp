// SURLYFINAL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// SURLY2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<sstream>
#include<map>
#include<string>
#include<string.h>
#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
#include<deque>
#include<fstream>
#include<cstring>
#include<typeinfo>
#include<vector>
#include<iomanip>
#include<ctype.h>
#include <rapidxml/rapidxml.hpp>
#include "rapidxml/rapidxml_print.hpp"
using namespace rapidxml;
using namespace std;
using std::string;

int numTables = 0;
unsigned int iter = 0;
vector<string> tempTables;

//Attribute structure
class attribute
{
public:

	string name;
	string datatype;
	string length;

	attribute(string n, string d, string len);

};

attribute::attribute(string n, string d, string len) {
	name = n;
	datatype = d;
	length = len;
}
//tuple structure
class mytuple
{
public:
	vector<string> values;

	mytuple(vector<string> v) {
		values = v;
	}

};


//Relation structure
class Relation
{
public:
	string name;
	vector<attribute> dataAttributes;
	vector<mytuple> tuples;
	int tupleIndex;

	Relation(string n, vector<attribute> attributes)
	{
		name = n;
		dataAttributes = attributes;
		tupleIndex = 0;
	}

	void insertTuple(mytuple t)
	{
		tuples.push_back(t);
	}

	void printRelation()
	{
		// data initialiazation
		int columnWidths = dataAttributes.size();
		int tableWidth = 70;

		
		for (int i = 0; i < tableWidth; i++)
		{
			cout << "-";
		}
		cout << "\n";

		cout << name << "\n";

		// print a separator
		for (int i = 0; i < tableWidth; i++)
		{
			cout << "-";
		}
		cout << "\n";

		// print the column names
		for (unsigned int i = 0; i < dataAttributes.size(); i++)
		{
			cout << setw(15) << dataAttributes.at(i).name << "\t";
		}
		cout << "\n";

		// print a separator
		for (int i = 0; i < tableWidth; i++)
		{
			cout << "-";
		}
		cout << "\n";

		// stop if there are no tuples
		if (tuples.empty())
		{
			return;
		}

		for (unsigned int j = 0; j < tuples.size(); j++)
		{
			mytuple t = tuples.at(j);
			for (unsigned int i = 0; i < dataAttributes.size(); i++)
			{
				cout << setw(15) << t.values.at(i) << "\t";
			}
			cout << "\n";
		}

		// print the bottom border
		for (int i = 0; i < tableWidth; i++)
		{
			cout << "-";
		}
		cout << "\n";
	}
};



// Compare two string . Used for the select command
bool compareStrings(string a, string b, string op) {
	if (op.compare("=") == 0){

		if (a.compare(b) == 0)
			return true;
	}
	else if (op.compare("<") == 0){
		int a1 = atoi(a.c_str());
		int b1 = atoi(b.c_str());
		if (a1 < b1)
			return true;
	}

	else if (op.compare("<=") == 0){
		int a1 = atoi(a.c_str());
		int b1 = atoi(b.c_str());
		if (a1 <= b1)
			return true;
	}
	else if (op.compare(">") == 0){
		int a1 = atoi(a.c_str());
		int b1 = atoi(b.c_str());
		if (a1 > b1)
			return true;
	}
	else if (op.compare(">=") == 0){
		int a1 = atoi(a.c_str());
		int b1 = atoi(b.c_str());
		if (a1 >= b1)
			return true;
	}
	else
	{
		return false;
	}
}



//string manipulation functions. 
string ClearWhiteSpace(string str)
{

	char chars[] = " ";

	for (unsigned int i = 0; i < strlen(chars); ++i)
	{
		// you need include <algorithm> to use general algorithms like std::remove()
		str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
	}

	return str;
}

string ClearApos(string str)
{

	char chars[] = "'";

	for (unsigned int i = 0; i < strlen(chars); ++i)
	{
		// you need include <algorithm> to use general algorithms like std::remove()
		str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
	}

	return str;
}

string ClearString(string str)
{

	char chars[] = "();";

	for (unsigned int i = 0; i < strlen(chars); ++i)
	{
		// you need include <algorithm> to use general algorithms like std::remove()
		str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
	}

	return str;
}

////////////////////////////////////////////////////
vector<string> tokens;
attribute emptyAttribute("", "", "");
vector<attribute> emptyVectAt;
Relation emptyRelation("", emptyVectAt);
vector<string> s;
mytuple emptyTuple(s);
vector<mytuple> emptyTuples;
/////////////////////////////////////////////////////


//Database class
class Database
{
public:


	vector<string> queryVector;
	vector<Relation> Relations;

	void readFile()//read input file
	{


		string line, word[30];
		ifstream file("input1.txt");
		while (getline(file, line, '\n'))
		{

			queryVector.push_back(line);
			// cout << line  << "\n";
		}


	}

	//insert a relation
	void insertRelation(Relation relation)
	{
		Relations.push_back(relation);

	}

	//Find a Relation
	int findRelation(string name)
	{
		// return a value of -1 to indicate that the relation was not found
		int index = -1;

		for (unsigned int i = 0; i < Relations.size(); ++i)
		{
			if ((Relations.at(i).name).compare(name) == 0)
			{
				index = i;
			}
		}
		return index;
	}

	//Get a Relation
	Relation* getRelation(string name)
	{
		for (unsigned int i = 0; i < Relations.size(); ++i)
		{
			Relation relation = Relations.at(i);
			if (relation.name.compare(name) == 0)
			{
				return &Relations.at(i);
			}
		}
		// relation not found
		return &emptyRelation;
	}

	//Destroy a relation
	void destroyRelation(string name)
	{
		int index = findRelation(name);
		Relations.at(index).tuples.clear();
		Relations.erase(Relations.begin() + index);
	}


	//delete a Relation
	void deleteRelationTuples(string name)
	{
		int index = findRelation(name);
		Relations.at(index).tuples.clear();
	}


	void printDB()
	{
		for (unsigned int i = 0; i < Relations.size(); i++)
			Relations.at(i).printRelation();
	}

	void printRelation(string name)
	{
		int index = findRelation(name);
		if (index == -1)
		{
			cout << "Relation not found: " << name;
		}
		else
		{
			Relations.at(index).printRelation();
		}
	}






}DB;



bool isWordCharacter(char c) {
	if (isalpha(c) || isdigit(c) || (c == '_')){
		return true;
	}
	else{
		return false;
	}
}

bool isBreakCharacter(char c) {
	if ((c == '"') || (c == '\'') || (c == '(') || (c == ')') || (c == '*') || (c == ',') || (c == '/') || (c == ';') || (c == '<') || (c == '=') || (c == '>') || (c == '~')){
		return true;
	}
	else{
		return false;
	}

}

bool isStandaloneBreakCharacter(char c) {

	if ((c == '"') || (c == '(') || (c == ')') || (c == '*') || (c == ',') || (c == ';'))
	{
		return true;
	}
	else{
		return false;
	}
}

vector<string> tokenize(string input) {
	vector<string> tokens;
	string token = "";

	bool insideWord = false;
	bool insideBreak = false;
	bool insideComment = false;
	bool insideString = false;

	for (unsigned int i = 0; i < input.length(); i++) {
		char c = input.at(i);

		if (insideWord) {
			if (!isWordCharacter(c) && c != ':') {
				tokens.push_back(token);
				token = "";
				insideWord = false;
			}
		}
		else if (insideBreak) {
			if (!isBreakCharacter(c)) {
				tokens.push_back(token);
				token = "";
				insideBreak = false;
			}
		}
		else if (insideComment) {
			token += c;
			if ((c == '/') && (input.at(i - 1) == '*')) {
				tokens.push_back(token);
				token = "";
				insideComment = false;
			}
			continue;
		}
		else if (insideString) {
			if (c != '\'') {
				token += c;
			}
			else {
				tokens.push_back(token);
				token = "";
				insideString = false;
			}
			continue;
		}

		if (c != ' ') {
			if (c != '\'') {
				token += c;
			}

			if (isWordCharacter(c)) {
				insideWord = true;
			}
			else if (isBreakCharacter(c)) {
				if (isStandaloneBreakCharacter(c)) {
					tokens.push_back(token);
					token = "";
				}
				else if ((c == '/') && (input.at(i + 1) == '*')) {
					insideComment = true;
				}
				else if (c == '\'') {
					insideString = true;
				}
				else {
					insideBreak = true;
				}
			}
		}
	}

	for (unsigned int i = 0; i< tokens.size(); i++)
	{
		tokens.at(i) = ClearWhiteSpace(tokens.at(i));
		tokens.at(i).erase(std::remove(tokens.at(i).begin(), tokens.at(i).end(), '\n'), tokens.at(i).end());
		if (tokens.at(i).empty())
		{
			tokens.erase(tokens.begin() + i);
		}
	}

	return tokens;
}

void relationCommand(Database* database, vector<string> t) {


	string relationName = t.at(iter);
	iter++;

	// get the attributes for the columns
	vector<attribute> attributes;
	string token;
	while (true) {


		token = t.at(iter);
		iter++;

		// skip opening parenthesis and stop at closing parenthesis
		if (token.compare("(") == 0){
			continue;
		}
		else if (token.compare(")") == 0) {
			break;
		}
		else if (token.compare(",") == 0) {
			continue;
		}

		string name = token;

		string type = t.at(iter);
		iter++;

		string len = t.at(iter);
		iter++;

		attribute atr(name, type, len);
		attributes.push_back(atr);
		//cout << name <<  " " << type << " " << len << "\n";

	}

	// create and insert the new relation into the database

	Relation rel(relationName, attributes);
	(*database).insertRelation(rel);

	//(*database).printDB();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void insertCommand(Database* database, vector<string> t) {
	string temp;
	string relationName = t.at(iter);
	iter++;

	vector<string> values;
	string token;
	while (true) {
		token = t.at(iter);
		iter++;
		// stop at a semicolon
		if (token.compare(";") == 0) {
			break;
		}

		values.push_back(token);
	}

	// make sure the relation exists
	Relation* relation = DB.getRelation(relationName);
	mytuple Tuple(values);



	(*relation).insertTuple(Tuple);
	// cout <<  (*DB.getRelation(relationName)).tuples.at(0).values.at(0) << "\n";
	//	cout << (*database).Relations.at(0).tuples.at(0).values.at(0);
	// cout << "Insert: Insertion successful" << "\n";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void deleteCommand(Database* database, vector<string> t) {
	string relationName = t.at(iter);
	iter++;

	// delete all tuples from the relation
	(*database).deleteRelationTuples(relationName);

	cout << "Deleted tuples from relation: " << relationName << "\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void destroyCommand(Database* database, vector<string> t) {
	string relationName = t.at(iter);
	iter++;

	// delete the relation
	(*database).destroyRelation(relationName);

	cout << "Destroyed relation: " << relationName << "\n";
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printCommand(Database* database, vector<string> t) {
	vector<string> relationNames;

	string token;
	while (true) {
		token = tokens.at(iter);
		iter++;
		// stop at a semicolon
		if (token.compare(";") == 0) {
			break;
		}
		else if (token.compare(",") == 0) {
			continue;
		}

		relationNames.push_back(token);
	}

	// print the relations
	for (unsigned int i = 0; i < relationNames.size(); i++) {
		string relationName = relationNames.at(i);
		cout << "Printing relation: " << relationName << "\n";
		(*database).printRelation(relationName);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void joinCommand(Database* database, vector<string> t) {
	//Get temp name if it exist 
	string tempRelationName;
	if (t.at(iter - 2).compare("=") == 0) {
		tempRelationName = t.at(iter - 3);
		tempTables.push_back(tempRelationName);
	}
	// get all the necessary arguments
	string relationName1 = t.at(iter); cout << relationName1 << "\n";
	iter += 2;  // ,
	string relationName2 = t.at(iter);
	iter += 2;  // OVER
	string attributeName1 = t.at(iter);
	iter += 2;  // =
	string attributeName2 = t.at(iter);
	iter++;

	Relation* relation1 = (*database).getRelation(relationName1);
	Relation* relation2 = (*database).getRelation(relationName2);

	if (relation1 == &emptyRelation) {
		cout << "Join: Relation does not exist: " << relationName1 << "\n";
		return;
	}
	else if (relation2 == &emptyRelation) {
		cout << "Join: Relation does not exist: " << relationName2 << "\n";
		return;
	}

	int attributeIndex1 = -1;
	int attributeIndex2 = -1;

	for (unsigned int i = 0; i < (*relation1).dataAttributes.size(); i++) {
		if ((*relation1).dataAttributes.at(i).name.compare(attributeName1) == 0) {
			attributeIndex1 = i;
			break;
		}
	}

	for (unsigned int i = 0; i < (*relation2).dataAttributes.size(); i++) {
		if ((*relation2).dataAttributes.at(i).name.compare(attributeName2) == 0) {
			attributeIndex2 = i;
			break;
		}
	}

	// attribute does not exist
	if (attributeIndex1 == -1) {
		cout << "Select: Attribute does not exist: " << attributeName1 << "\n";
		return;
	}
	else if (attributeIndex2 == -1) {
		cout << "Select: Attribute does not exist: " << attributeName2 << "\n";
		return;
	}

	attribute attribute1 = (*relation1).dataAttributes.at(attributeIndex1);
	attribute attribute2 = (*relation2).dataAttributes.at(attributeIndex2);



	// merge the attribute lists for the temporary relation
	vector<attribute> tempAttributes;
	tempAttributes = (*relation1).dataAttributes;
	for (unsigned int i = 0; i < (*relation2).dataAttributes.size(); i++) {
		attribute att = (*relation2).dataAttributes.at(i);
		if (att.name.compare(attributeName2) != 0) {
			tempAttributes.push_back(att);
		}
	}

	if (tempRelationName.empty()){
		tempRelationName = relationName1 + " + " + relationName2;
		tempTables.push_back(tempRelationName);
	}

	// create and insert the temporary relation
	Relation tempRelation(tempRelationName, tempAttributes);

	// find all tuples where the attributes match and insert them into the temporary relation
	for (unsigned int i = 0; i < (*relation1).tuples.size(); i++) {
		mytuple tuple1 = (*relation1).tuples.at(i);
		for (unsigned int j = 0; j < (*relation2).tuples.size(); j++) {
			mytuple tuple2 = (*relation2).tuples.at(j);
			string element1 = tuple1.values.at(attributeIndex1);
			string element2 = tuple2.values.at(attributeIndex2);

			if (element1.compare(element2) == 0) {
				// create a new list for the new tuple
				vector<string> newValues;

				// include all elements from the first tuple
				newValues = tuple1.values;

				// include all elements from the second tuple except the one in the redundant column
				for (unsigned int i = 0; i < (*relation2).dataAttributes.size(); i++) {
					if (i != attributeIndex2) {
						newValues.push_back(tuple2.values.at(i));
					}
				}

				// insert the new tuple into the temporary relation
				mytuple Tuple(newValues);
				tempRelation.insertTuple(Tuple);
			}
		}
	}

	(*database).insertRelation(tempRelation);

	// print the temporary relation
	(*database).printRelation(tempRelationName);

	// delete the temporary relation unless the NODELETE option was given

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Get temp name if it exist
void projectCommand(Database* database, vector<string> t) {
	//Get tempRelationName if if exist
	string tempRelationName;
	if (t.at(iter - 2).compare("=") == 0) {
		tempRelationName = t.at(iter - 3);
		tempTables.push_back(tempRelationName);
	}
	string relationName = t.at(iter);
	iter += 2;  // OVER

	// get the list of attributes to be projected
	vector<string> attribList;


	while (t.at(iter).compare(";") != 0) {
		attribList.push_back(t.at(iter));
		iter++;

	}

	Relation* relation = (*database).getRelation(relationName);
	if (relation == &emptyRelation) {
		cout << "Project: Relation does not exist: " << relationName << "\n";
		return;
	}

	// get the indexes of all the desired attributes
	vector<int> attribIndexes;
	for (unsigned int i = 0; i < (*relation).dataAttributes.size(); i++) {
		if (std::find(attribList.begin(), attribList.end(), (*relation).dataAttributes.at(i).name) != attribList.end()) {
			attribIndexes.push_back(i);
		}
	}

	// set the attributes for the temporary relation
	vector<attribute> tempAttributes;
	for (unsigned int i = 0; i < (*relation).dataAttributes.size(); i++) {
		if (std::find(attribIndexes.begin(), attribIndexes.end(), i) != attribIndexes.end()) {
			tempAttributes.push_back((*relation).dataAttributes.at(i));
		}
	}

	// create and insert the temporary relation
	if (tempRelationName.empty()){
		tempRelationName = "PROJECT(" + relationName + ")";
		tempTables.push_back(tempRelationName);
	}
	Relation tempRelation(tempRelationName, tempAttributes);

	// insert the tuples into the temporary relation
	for (unsigned int j = 0; j < (*relation).dataAttributes.size(); j++) {
		mytuple Tuple = (*relation).tuples.at(j);
		vector<string> newValues;

		for (unsigned int i = 0; i < (*relation).dataAttributes.size(); i++) {
			if (std::find(attribIndexes.begin(), attribIndexes.end(), i) != attribIndexes.end()) {
				newValues.push_back(Tuple.values.at(i));
			}
		}

		mytuple Tp(newValues);
		tempRelation.insertTuple(Tp);
	}
	(*database).insertRelation(tempRelation);

	// print the temporary relation
	(*database).printRelation(tempRelationName);


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void selectCommand(Database* database, vector<string> t) {
	//Get tempRelationName if if exist
	string tempRelationName;
	if (t.at(iter - 2).compare("=") == 0) {
		tempRelationName = t.at(iter - 3);
		tempTables.push_back(tempRelationName);
	}
	// get all the necessary arguments
	string relationName = t.at(iter);
	iter += 2;  // WHERE
	string columnName = t.at(iter);
	iter++;
	string op = t.at(iter);
	iter++;
	string val = t.at(iter);
	string andOp;
	string columnName1;
	iter++;
	string op1;
	iter++;
	string val1;
	if (t.at(iter+1).compare("and") == 0)
	{
		iter++;
		andOp = t.at(iter);
		iter++;
		columnName1 = t.at(iter);
		iter++;
		op1 = t.at(iter);
		iter++;
		val1 = t.at(iter);

	}

	// see if the relation exists
	Relation* relation = (*database).getRelation(relationName);
	if (relation == &emptyRelation) {
		cout << "Select: Relation does not exist: " << relationName << "\n";
		return;
	}

	// find the column with the given name
	int columnIndex = -1;
	for (unsigned int i = 0; i < (*relation).dataAttributes.size(); i++) {
		if ((*relation).dataAttributes.at(i).name.compare(columnName) == 0) {
			columnIndex = i;
			break;
		}
	}

	// column not found
	if (columnIndex == -1) {
		cout << "Select: Column does not exist: " << columnName << "\n";
		return;
	}


	// create a temporary relation to store the selected tuples
	if (tempRelationName.empty()){
		tempRelationName = "TEMP";
		tempTables.push_back(tempRelationName);
	}
	Relation temp(tempRelationName, (*relation).dataAttributes);

	// check the tuples for matches
	for (unsigned int i = 0; i < (*relation).tuples.size(); i++) {
		mytuple tuple = (*relation).tuples.at(i);
		string value = tuple.values.at(columnIndex);

		bool result = false;

		result = compareStrings(value, val, op);

		if (result) {
			temp.insertTuple(tuple);
		}
	}

	(*database).insertRelation(temp);
	// print the selection
	(*database).printRelation(tempRelationName);



}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void exportCommand(Database* database, vector<string> t) {
	string token;

	xml_document<> doc;
	xml_node<> *root_node = doc.allocate_node(node_declaration);
	root_node->append_attribute(doc.allocate_attribute("version", "1.0"));
	root_node->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(root_node);

	token = t.at(iter); 
	string relationName;
	while (t.at(iter).compare(";") != 0) {
		relationName = t.at(iter); cout << t.at(iter) << endl;
		iter++;
		if (t.at(iter).compare(",") == 0){
			iter++;
		}

		Relation* relation = (*database).getRelation(relationName);

		// root elements
		xml_node<> *child = doc.allocate_node(node_element, "RELATION");
		child->append_attribute(doc.allocate_attribute("name", (*relation).name.c_str()));
		doc.append_node(child);

	

		if (relation == &emptyRelation) {
			cout << "Export: Relation does not exist: " << relationName << endl;
			return;
		}
		for (unsigned int i = 0; i < (*relation).dataAttributes.size(); i++) {
			attribute* attr = &(*relation).dataAttributes.at(i);
			xml_node<> *Element = doc.allocate_node(node_element, "ATTRIBUTE");
			Element->append_attribute(doc.allocate_attribute("name", (*attr).name.c_str()));
			Element->append_attribute(doc.allocate_attribute("type", (*attr).datatype.c_str()));
			Element->append_attribute(doc.allocate_attribute("length", (*attr).length.c_str()));
			child->append_node(Element);
		}

		for (unsigned int i = 0; i < (*relation).tuples.size(); i++) {
			mytuple* Tuple = &(*relation).tuples.at(i); //cout << Tuple.values.at(i) << endl;
			xml_node<> *tupleElement = doc.allocate_node(node_element, "TUPLE");
			child->append_node(tupleElement);

			for (unsigned int j = 0; j < (*relation).dataAttributes.size(); j++) {
				xml_node<> *valueElement = doc.allocate_node(node_element, "VALUES");
				valueElement->append_attribute(doc.allocate_attribute("name", (*relation).dataAttributes.at(j).name.c_str()));
				valueElement->append_attribute(doc.allocate_attribute("value", (*Tuple).values.at(j).c_str()));
				tupleElement->append_node(valueElement);
			}
		}

		string xml_as_string;

		// write the content to an XML file
		ofstream xmlFile;
		xmlFile.open("XmlFILE.xml");
		xmlFile << doc;
		xmlFile.close();
		xmlFile.clear();


		//cout << "Export: Relation exported to xmlFile" << endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////
void importCommand(){
	xml_document<> doc;
	ifstream file("xmlFILE.xml");

	stringstream buffer;
	buffer << file.rdbuf();
	string content(buffer.str());
	cout << content << endl;
	doc.parse<0>(&content[0]);
}

int main(){

	string input;
	string tempValue;
	DB.readFile();
	vector<string> commands;
	commands.push_back("RELATION");
	commands.push_back("INSERT");
	commands.push_back("DELETE");
	commands.push_back("DESTROY");
	commands.push_back("PRINT");
	commands.push_back("JOIN");
	commands.push_back("SELECT");
	commands.push_back("PROJECT");
	commands.push_back("EXPORT");
	commands.push_back("IMPORT");
	//cout << commands.at(5) << "\n";
	for (unsigned int i = 0; i< DB.queryVector.size(); i++)
	{
		input += DB.queryVector.at(i);
		input += "\n";
		//cout << DB.queryVector.at(i) << "\n";

	}

	//tokenize the input string and put it into a vector
	tokens = (tokenize(input));
	int tokensSize = tokens.size();

	/*
	for(int i = 0; i< tokens.size();i++)
	{
	cout << tokens.at(i) << "*" << "\n";
	}

	*/
	//Run Th queries
	string token;
	while (iter < tokens.size()) {
		token = tokens.at(iter);
		iter++;

		// check if the token is a command

		if (std::find(commands.begin(), commands.end(), token) != commands.end()) {
			// do something based on what the command is

			if (token.compare("RELATION") == 0){
				relationCommand(&DB, tokens);
				iter++;
			}

			else if (token.compare("INSERT") == 0){
				insertCommand(&DB, tokens);
			}

			else if (token.compare("DELETE") == 0){
				deleteCommand(&DB, tokens);
			}

			else if (token.compare("DESTROY") == 0){
				destroyCommand(&DB, tokens);
			}

			else if (token.compare("PRINT") == 0){
				printCommand(&DB, tokens);
				//cout << tokens.at(iter);
			}
			else if (token.compare("JOIN") == 0)
			{
				joinCommand(&DB, tokens);
			}
			else if (token.compare("PROJECT") == 0){
				projectCommand(&DB, tokens);
			}


			else if (token.compare("SELECT") == 0){
				selectCommand(&DB, tokens);
			}

			else if (token.compare("EXPORT") == 0){
				exportCommand(&DB, tokens);
			}
			else if (token.compare("IMPORT") == 0){
				importCommand();
			}
			else
				cout << "Command not implemented: " << token << endl;

		}
	}

	//Destroy temporary tables
	for (unsigned int i = 0; i < tempTables.size(); i++)
	{
		DB.destroyRelation(tempTables.at(i));
		//cout << tempTables.at(i) << endl;
	}

	 DB.printDB();
	system("PAUSE");
	return 0;
}


