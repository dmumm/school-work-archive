/* Dylan Mumm
 * dmumm
 * Lab 10
 * Nick Glyder, Section 004
 *
 * Victor Gamble
 * mlgambl
 * Lab 10
 * Nick Glyder, Section 005
 */

/* Driver for lab  files */

#include "Package.h"
#include "ThreeDay.h"
#include "OvernightPackage.h"
#include "Person.h"
using namespace std;

#include <iostream>
#include <iomanip>

/*You will need to write the implementation for the following functions.  */

void getSenderInfo(Person &);
void getRecipientInfo(Person &);
void calculateAndPrint(Package &, ThreeDay&, OvernightPackage&);
void getPackageInfo(double&, double&, double&, double&, double&);


int main()
{
   double weight, cost, fee1, fee2, flat;

   Person s;
   Person r;
   getSenderInfo(s);
   getRecipientInfo(r);
   getPackageInfo(weight, cost, fee1, fee2, flat);

   Package p1(s, r, weight, cost);
   ThreeDay p2(s, r, weight, cost, fee1);
   OvernightPackage p3(s, r, weight, cost, fee2, flat);

   calculateAndPrint(p1, p2, p3);

}
/*This function is used to request and receive information from the user
 *The information received from this function will be used to instantiate the
 *instances of Package, ThreeDay, and OvernightPackage in the main.  See
 *the sample output in the lab specification document for an example.*/

void getPackageInfo(double& w, double& cost, double& fee1, double& fee2,
                    double& flat)
{

  cout << "\nEnter the weight, in oz, of the package: ";
  cin >> w;

  cout << "Enter the cost per oz, in dollars, of the package: ";
  cin >> cost;

  cout << "Enter the additional fee per ounce of the 3-day package: ";
  cin >> fee1;

  cout << "Enter the additional fee per ounce of the overnight package: ";
  cin >> fee2;

  cout << "Enter the flat fee for the overnight package: ";
  cin >> flat;

}

/*This function is used to request and receive information from the user.
 *The information is used to set the values of a person that will be
 *passed to the instances of Package, ThreeDay, and OverrnightPackage.
 *It represents the "sender" of the Package class.*/

void getSenderInfo(Person& sender)
{
  string name, city, address, state;
  int zip;


  cout << "Enter the Sender's Name: ";
  getline(cin,name);
  sender.setName(name);

  cout << "Enter the Sender's Street address: ";
  getline(cin,address);
  sender.setAddress(address);

  cout << "Enter the Sender's City: ";
  getline(cin,city);
  sender.setCity(city);

  cout << "Enter the Sender's State: ";
  getline(cin,state);
  sender.setState(state);

  cout << "Enter the Sender's Zip Code: ";
  cin >> zip;
  sender.setZip(zip);

  cin.ignore();

}

/*Similar to the getSenderInfo function
 *This function is used to request and receive information from the user.
 *The information is used to set the values of a person that will be
 *passed to the instances of Package, ThreeDay, and OverrnightPackage.
 *It represents the "recipient" of the Package class.*/

void getRecipientInfo(Person& recipient)
{

  string name, city, address, state;
  int zip;

  cout << "\nEnter the Recipient's Name: ";
  getline(cin,name);
  recipient.setName(name);

  cout << "Enter the Recipient's Street Address: ";
  getline(cin,address);
  recipient.setAddress(address);

  cout << "Enter the Recipient's City: ";
  getline(cin,city);
  recipient.setCity(city);

  cout << "Enter the Recipient's State: ";
  getline(cin,state);
  recipient.setState(state);

  cout << "Enter the Recipient's Zip Code: ";
  cin >> zip;
  recipient.setZip(zip);

}

/*The above functions set the information for the sender and recipient
 *and was passed to the constructors of p1, p2, and p3.  In this
 *function you will use the instance of Package to get the sender
 *and recipient information then call printSenderInfo and
 *printRecipientInfo. */

void calculateAndPrint(Package& p1, ThreeDay& p2, OvernightPackage& p3)
{

  /*create an instance of Person and make it equal to the P1's sender
   *information.  Do the same with P1's recipient.  */


   Person sender = p1.getSender();
   Person recipient = p1.getRecipient();

  /*print the sender information*/

  sender.printSenderInfo();

  /*print the recipient information*/

  recipient.printSenderInfo();

  /*Since we are dealing with money make sure you set the precision to 2
   *and make sure sure trailing zeros are printed.*/

   cout << fixed << setprecision(2);

  /*Now you are to calculate and print the cost of the Package, ThreeDay,
   *and OvernightPackage  See the sample output.  */

   cout << "\nCost calculation for Package: $" << p1.calculateCost();
   cout << "\nCost calculation for ThreeDay: $" << p2.calculateCost();
   cout << "\nCost calculation for Overnight: $" << p3.calculateCost() << endl;




}
