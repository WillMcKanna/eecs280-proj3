#include "movie.hpp"
#include "inventory.hpp"
#include "finicky_database.hpp"

#include "singly_linked_list.hpp"
#include "doubly_linked_list.hpp"
#include "binary_search_tree.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{
	// check if we are passed a movie data file
	if( argc < 2 )
	{
		cout << "Usage: ./movies <movie_input_file>" << endl;

		return -1; // this is ok in very obvious cases
	}

	// these are for timekeeping
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto diff  = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	start = std::chrono::high_resolution_clock::now();
	// this is an untrustworthy database
	FinickyDatabase<Movie> finicky_database;
	finicky_database.populate( argv[1] );
	end = std::chrono::high_resolution_clock::now();
	diff  = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
	cerr
		<< "Populated the finicky database with "
		<< finicky_database.size()
		<< " items in "
		<< diff
		<< " seconds"
		<< endl
		;

	Movie movie; // this is a placeholder/iterator
// *****************************************************************************************************
	// step 1: get the following code to work to work.
	// this requires implementing a copy constructor and the operator= function for the Movie class.
	// while( finicky_database.readFirst(movie))
	// {
	// 	cout << movie << endl;
	// }
	// cout << "Finicky database contained " << finicky_database.size() << " movies." << endl;

	// // try 10 times to output the data a second time
	// for(int i = 0; i < 10; i ++)
	// {
	// 	cout << "Trying to output the movies again..." << endl;
	// 	while( finicky_database.readFirst(movie))
	// 	{
	// 		cout << movie << endl;
	// 	}
	// 	cout << "Done trying to output the movies again." << endl;
	// }
	// you can comment the code for step 1 above once you're done.
	// you will use similar functionality below
	// (leave the copy constructor and operator= for the Movie class)
// *****************************************************************************************************
	// step 1.5: get a bunch of info from stdin, describing what to do next in the test case
	string operation;
	string name;
	std::vector<std::string> operations;
	start = std::chrono::high_resolution_clock::now();
	while( std::getline(cin, operation, '\t' ) && std::getline(cin, name, '\n' ) )
	{
		operations.push_back( operation );
		operations.push_back( name );
	}
	end = std::chrono::high_resolution_clock::now();
	diff  = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
	cerr << "Received " << (operations.size()-2) / 2 << " operations in " << diff << " s" << endl;
	bool linked_list = false;
	
	//instantiate your inventory 
	Inventory* inventory;		// if not using templates


	// create objects for both single linked list and binary search tree
	SinglyLinkedList singleLinkedList;
	BinarySearchTree binarySearchTree;


// *****************************************************************************************************
	// step 2: instantiate an inventory as a linked list
	if( operations[0] == "type" && operations[1] == "linked_list" )
	{
		cerr << "Instantiating the inventory as a linked list!" << endl;

		linked_list = true;
	}
// // *****************************************************************************************************
	// step 3: instantiate an inventory as a binary tree
 	else if( operations[0] == "type" && operations[1] == "binary_tree" )
 	{
 		cerr << "Instantiating the inventory as a binary tree!" << endl;
 	}
 // *****************************************************************************************************
	// something is wrong here so we end
	else
	{
		cerr << "Malformed test file!" << endl;
		return -1;
	}

	
	
	
	// if linked list, assign dynamic type to linked list object, otherwise set inventory dynamic object type to binary search tree
	if (linked_list)
	{
		inventory = &singleLinkedList;
	}
	else
	{
		inventory = &binarySearchTree;		
	}

	// iterate through database and insert each movie into inventory
	for (size_t i = 0; i < finicky_database.size(); i++)
	{
		Movie tempMovie;
		
		finicky_database.read(tempMovie, i);
	
		inventory->insert(tempMovie);												// insert is virtual function, so will call dynamic type insert function
		
	}
	

// *****************************************************************************************************
	//step 3.5: populate your inventory from the finicky database

	// show the current state of the inventory
	
	//cerr << *inventory << endl;
	
// *****************************************************************************************************
	// step 4: implement a user list as a doubly linked list
	DoublyLinkedList user_list;
	
	// process each command in the test case according to the inventory interface
	// ** initiate timer **
	auto start_timer = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < operations.size() - 1; i++)
	{
		
		if (operations.at(i) == "insert")
		{
			// assigns string to next input of operations, which is title of movie, and checks if inventory has a movie object with that name
			std::string tempMovieStr = operations.at(i+1);
			const Movie* tempMoviePtr = inventory->contains(tempMovieStr);

			// can only insert into user list if movie title is in inventory, tempMoviePtr is null if not in inventory
			if (tempMoviePtr)
			{
				user_list.insert(*tempMoviePtr);
			}
			else {
				cerr << "Given movie is not in the inventory." << endl;
			}
		}
		
		if (operations.at(i) == "remove")
		{
			// assigns string to next inout, and finds the movie object that contains this title
			std::string tempMovieStr = operations.at(i+1);
			const Movie* tempMoviePtr = inventory->contains(tempMovieStr);
			
			// if not a nullptr, so exists in inventory, and removes it from user_lists
			if (tempMoviePtr)  {
				user_list.remove(*tempMoviePtr);
			}
			else
			{
				cerr << "Given movie is not in inventory." << endl;
			}
		}
		
		if (operations.at(i) == "swap") 
		{
			// find "|", this seperates the two movies in test cases
			std::string tempMovieStr = operations.at(i+1);
			int indexOfPipe = tempMovieStr.find("|");

			// assign each movie title to different strings
			std::string movie1Title = tempMovieStr.substr(0, indexOfPipe);
			std::string movie2Title = tempMovieStr.substr(indexOfPipe + 1);


			// assigns movie pointer depending on title string, nullptr is inventory doesn't contain the movie
			const Movie* tempMovie1Ptr = inventory->contains(movie1Title);
			const Movie* tempMovie2Ptr = inventory->contains(movie2Title);

			// makes sure both movies are in inventory, neither is nullptr, and swaps movie objects
			if (tempMovie1Ptr && tempMovie2Ptr) {
				user_list.swap(*tempMovie1Ptr, *tempMovie2Ptr);
			}
			else {
				cerr << "At least one of these movies is not in the inventory." << endl;
			}
		}
		
	}
	// ** terminate timer **
	auto end_timer = std::chrono::high_resolution_clock::now();
	
	// ** calculate diff
	auto diff_timer  = std::chrono::duration_cast<std::chrono::duration<double>>(end_timer - start_timer).count();

	// step 4.5: output the user list to stdout
	cerr << "Outputting user list." << endl;
	cerr << user_list << "\n" << "Completed all operations in " << diff_timer << " seconds." << endl;

	std::ofstream ofs;

	// write to different respective output files, can test diff against one another
	if (linked_list)
	{
		ofs.open("outputTestFile.txt");
	}
	else {
		ofs.open("outputTestFileBST.txt");
	}

	// stream user_list in and close file
	ofs << user_list << endl;
	ofs.close();

	cerr << "At the end of main!" << endl;


	
	return 0;
}
