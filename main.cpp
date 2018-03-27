#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class CAR{    // class for train cars;

      public:
            CAR();                              // constructor
            int getWeight();             // returns the weight of the car in pounds
            void loadCar(int);           // loads a cargo with parameter weight
            CAR *nextCar;                // pointer to the next car on the train
      private:
            int cargoWeight;              // the weight of the trains cargo
 };
CAR::CAR(){
    cargoWeight = 75;
    nextCar = NULL;
    }

int CAR::getWeight(){
    return cargoWeight;
    }

void CAR::loadCar (int cargo){
    cargoWeight = cargo;
    }
class TRAIN                     // train class as a linked list of cars
{
    private:
        int trainWeight;
    public:
        TRAIN();                   //constructor
        int getWeight();           // returns the weight of the train
        void loadTrain();          // load train with initial cars
        void addCar_front(int);
        void addCar_end(int);      // THIS IS CODE YOU MUST WRITE//
        ~TRAIN();      // destructor THIS IS CODE YOU MUST WRITE
        const TRAIN& operator=(const TRAIN& RHS);
        TRAIN(const TRAIN& LHS);
        void displayTrainInfo();
        CAR *firstCar;
};
TRAIN::TRAIN()
{
    trainWeight = 0;
    firstCar = NULL;
}
int TRAIN::getWeight() // returns the train weight
{
    return trainWeight;
}
void TRAIN::loadTrain() // load train with initial cars
{
    addCar_front(0); // add first car
    addCar_front(10);
    addCar_front(20);
    addCar_front(30);
    addCar_front(40);
    addCar_front(50);
    addCar_front(60);
    addCar_end(60);
    addCar_end(30);
    addCar_end(40);
}
void TRAIN::addCar_end (int cWeight)    // add car to end
{
    CAR* current;
    if (firstCar == NULL) //train is empty
    {
       this->addCar_front(cWeight);
    }
    else // find the end first
    {
        for (current=firstCar; current->nextCar != NULL; current=current->nextCar); //iterates until current's next car = NULL
        current->nextCar = new CAR;
        current->nextCar->nextCar = NULL;
    }
    delete current;
}
void TRAIN::addCar_front (int cWeight)  // add first car to train
{
    CAR* hold = firstCar;
    firstCar = new CAR;
    firstCar->nextCar = hold;
    firstCar->loadCar(cWeight);
}
TRAIN::~TRAIN()
{
    for(int x = 0; x <= 10; x++) //for loop that iterates 11 times to delete train cars
    {
        CAR* hold = firstCar->nextCar; //"hold" pointer set equal to the second car
        delete firstCar; //first car is deleted
        firstCar = hold; //first car pointer is set equal to hold
        this->displayTrainInfo(); //train info is printed
        cout << "Destructor was called" << endl; //this line is output to ensure the destructor was called
    }
}
void TRAIN::displayTrainInfo()
{
         int cnt = 0;
         CAR* ptrCar;
         for (ptrCar = firstCar; ptrCar != NULL && ++cnt <11; ptrCar = ptrCar->nextCar)
                 cout << "+-------+  ";
                 cout << endl;
                 cnt = 0;
         for (ptrCar = firstCar; ptrCar != NULL && ++cnt < 11; ptrCar = ptrCar->nextCar)
                 cout << "|       |  ";
                 cout << endl; cnt = 0;
         for (ptrCar = firstCar; ptrCar != NULL && ++cnt < 11; ptrCar = ptrCar->nextCar)
         {
                 if ((*ptrCar).getWeight() < 10)
                          cout << "|   " << (*ptrCar).getWeight() << "   |->";  else    cout << "|   " <<
                                       (*ptrCar).getWeight() << "  |->";
          }
          cout << endl; cnt = 0;
          for (ptrCar = firstCar; ptrCar != NULL && ++cnt < 11; ptrCar = ptrCar->nextCar)
                  cout << "|       |  ";
          cout << endl;
          cnt = 0;
          for (ptrCar = firstCar; ptrCar != NULL && ++cnt < 11; ptrCar = ptrCar->nextCar)
                  cout << "+-------+  ";
          cout << endl;
 }

const TRAIN& TRAIN::operator=(const TRAIN& RHS)
{
	this->~TRAIN();
	CAR * current = RHS.firstCar;
	CAR * currentLHS = new CAR;
	currentLHS->loadCar(current->getWeight());
	currentLHS->nextCar = NULL;
	this->firstCar = currentLHS;
	for (current = RHS.firstCar->nextCar; current != NULL; current = current->nextCar)
	{
		//currentLHS->nextCar = new CAR;
		//currentLHS->nextCar->loadCar(current->getWeight());
		//currentLHS->nextCar = NULL;
		this->addCar_end(current->getWeight());
	}
	return *this;
}
TRAIN::TRAIN(const TRAIN& LHS)
{
	firstCar = new CAR;
	CAR* currentLHS = LHS.firstCar;
	CAR* current = firstCar;
	firstCar->loadCar(LHS.firstCar->getWeight());
	current->nextCar = new CAR;
	currentLHS = currentLHS->nextCar;
	for (current = firstCar->nextCar; currentLHS->nextCar != NULL; currentLHS = currentLHS->nextCar)
	{
		current->loadCar(currentLHS->getWeight());
		current->nextCar = new CAR;
		current = current->nextCar;
	}
	current->loadCar(currentLHS->getWeight());
	current->nextCar = NULL;
}
int main()
{
    TRAIN MetroLiner;
    cout << "PROGRAM OUTPUT:" << endl;
    MetroLiner.loadTrain();
    MetroLiner.displayTrainInfo();
    return 0;
}

/*
PROGRAM OUTPUT:
+-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+
|       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |
|   60  |->|   50  |->|   40  |->|   30  |->|   20  |->|   10  |->|   0   |->|   75  |->|   75  |->|   75  |->
|       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |
+-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+
+-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+
|       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |
|   50  |->|   40  |->|   30  |->|   20  |->|   10  |->|   0   |->|   75  |->|   75  |->|   75  |->
|       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |
+-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+
Destructor was called
+-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+
|       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |
|   40  |->|   30  |->|   20  |->|   10  |->|   0   |->|   75  |->|   75  |->|   75  |->
|       |  |       |  |       |  |       |  |       |  |       |  |       |  |       |
+-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+
Destructor was called
+-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+
|       |  |       |  |       |  |       |  |       |  |       |  |       |
|   30  |->|   20  |->|   10  |->|   0   |->|   75  |->|   75  |->|   75  |->
|       |  |       |  |       |  |       |  |       |  |       |  |       |
+-------+  +-------+  +-------+  +-------+  +-------+  +-------+  +-------+
Destructor was called
+-------+  +-------+  +-------+  +-------+  +-------+  +-------+
|       |  |       |  |       |  |       |  |       |  |       |
|   20  |->|   10  |->|   0   |->|   75  |->|   75  |->|   75  |->
|       |  |       |  |       |  |       |  |       |  |       |
+-------+  +-------+  +-------+  +-------+  +-------+  +-------+
Destructor was called
+-------+  +-------+  +-------+  +-------+  +-------+
|       |  |       |  |       |  |       |  |       |
|   10  |->|   0   |->|   75  |->|   75  |->|   75  |->
|       |  |       |  |       |  |       |  |       |
+-------+  +-------+  +-------+  +-------+  +-------+
Destructor was called
+-------+  +-------+  +-------+  +-------+
|       |  |       |  |       |  |       |
|   0   |->|   75  |->|   75  |->|   75  |->
|       |  |       |  |       |  |       |
+-------+  +-------+  +-------+  +-------+
Destructor was called
+-------+  +-------+  +-------+
|       |  |       |  |       |
|   75  |->|   75  |->|   75  |->
|       |  |       |  |       |
+-------+  +-------+  +-------+
Destructor was called
+-------+  +-------+
|       |  |       |
|   75  |->|   75  |->
|       |  |       |
+-------+  +-------+
Destructor was called
+-------+
|       |
|   75  |->
|       |
+-------+
Destructor was called





Destructor was called
*/
