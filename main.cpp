/**
* @author Leon Kleyn
  @author Sahil Hirani
  @author David Iordan
  @author Robert Goss
* @cal448
* @date 12 February 2017
* @brief main file for cal448 that calls and runs executive class
* @file main.cpp **/

#include "Executive.h"

/**
*	Creates an instance of the Executive class and runs the program
*	@pre None
*	@post None
*	@param None
*	@return None
*/
int main() 
{
	Executive exec; //creates an executive object
	exec.run(); //calls run
	
	return(0);
}
