#include <iostream>
#include <vector>

using namespace std;

//Prototyping of classes
class StateContext;
class InitiateState;
class Transition;
class Pancake;

enum state { Out_Of_Mix, No_Credit, Has_Credit, Dispenses_Pancake, Display_Menu };
enum stateParameter { No_Of_Pancakes, Credit, Cost_Of_Pancake, Pancake_Option, Number_Of_Coatings };

class TransitionState
{
public:
	virtual void transition(void) {}
};

class Transition
{
public:
	virtual void insertMoney(int) {}
	virtual void displayMenu(void) {}
	virtual void makeSelection(int){}
	virtual void moneyRejected(void){}
	virtual void addMix(int){}
	virtual void dispense(void){}
};

//Sets up the classes that are chosen for the pancake and filling if filing is chosen
class Pancake
{
public:
	virtual int cost()
	{
		return 15;
	}

	virtual void prepare(int coatingCyclesIn)
	{
		bakeCoatings(coatingCyclesIn);
		warmPancake();
	}

	virtual void bakeCoatings(int coatingCyclesIn)
	{
		for (coatingCyclesIn; coatingCyclesIn > 0; coatingCyclesIn--) // Bakes one cycle for each layer of coating
		{
			cout << "Baking coating to pancake" << endl;
		}
	}
	virtual void warmPancake() // Sets the default target warming to 65 Celcius which is overloaded in each pancake subclass
	{
		cout << "Warming pancake to 65 Celsius" << endl;
	}

	virtual ~Pancake(void)
	{	}
};

class ChocolateFilling : public Pancake
{
	int cost()
	{
		return 40;
	}

	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}

};

class FudgeFilling : public Pancake
{
	int cost()
	{
		return 40;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

class ChocolateFudgeFilling : public Pancake
{
	int cost()
	{
		return 65;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

class VanillaCreamFilling : public Pancake
{
	int cost()
	{
		return 65;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

class WildBerryFilling : public Pancake
{
	int cost()
	{
		return 45;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

class BlueberryFilling : public Pancake
{
	int cost()
	{
		return 50;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

class CherryFilling : public Pancake
{
	int cost()
	{
		return 30;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

class RaspberryFilling : public Pancake
{
	int cost()
	{
		return 30;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

class StrawberryFilling : public Pancake
{
	int cost()
	{
		return 50;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

class PeanutButterFilling : public Pancake
{
	int cost()
	{
		return 30;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

class CookiesAndCreamFilling : public Pancake
{
	int cost()
	{
		return 40;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

class CookieDoughFilling : public Pancake
{
	int cost()
	{
		return 40;
	}
	void warmPancake()
	{
		cout << "Warming pancake to 70 Celsius" << endl;
	}
};

//Sets up the coating classes with different costs
class Coating : public Pancake
{
public:
	Pancake* pancake;
	void addCoatingToPancake(Pancake* customerPancake)
	{
		pancake = customerPancake;
	}

	~Coating(void)
	{
		delete pancake;
	}
};

class Frosted : public Coating
{
	int cost()
	{
		return(20 + pancake->cost());
	}
};

class Wildlicious : public Coating
{
	int cost()
	{
		return(30 + pancake->cost());
	}
};

class Chocolate : public Coating
{
	int cost()
	{
		return(40 + pancake->cost());
	}
};

class Smarties : public Coating
{
	int cost()
	{
		return(50 + pancake->cost());
	}
};

class HundredsAndThousands : public Coating
{
	int cost()
	{
		return(10 + pancake->cost());
	}
};

class JellyBeans : public Coating
{
	int cost()
	{
		return(50 + pancake->cost());
	}
};

class WildBerry : public Coating
{
	int cost()
	{
		return(30 + pancake->cost());
	}
};

class BrownSugar : public Coating
{
	int cost()
	{
		return(20 + pancake->cost());
	}
};

class ChocolateChip : public Coating
{
	int cost()
	{
		return(40 + pancake->cost());
	}
};

class State : public Transition, public TransitionState
{
protected:
	StateContext* currentContext;

public:
	State(StateContext* Context){
		currentContext = Context;
	}
};


class StateContext
{
protected:
	State* currentState;
	vector<State*> availableStates;
	vector<int> stateParameters;

public:
	~StateContext()
	{
		for (int i = 0; i < availableStates.size(); i++){
			delete availableStates[i];
		}
	}

	void setState(state newState){
		this->currentState = availableStates[newState];
		this->currentState->transition(); //Call the transition function of the new state
	}

	void setStateParam(stateParameter SP, int value){
		this->stateParameters[SP] = value;
	}

	int getStateParam(stateParameter SP){
		return this->stateParameters[SP];
	}
};

class DisplayMenu : public State
{
public:
	DisplayMenu(StateContext* Context) : State(Context) {}

	void transition(void)
	{
		int option;
		bool display = true;
		while (display)
		{
			//system("cls"); // Clears screen to improve readability of output.
			cout << "Current credit: " << this->currentContext->getStateParam(Credit) << endl;
			cout << "Please select a filling for your pancake:" << endl;
			cout << "[1] Insert more money" << endl;
			cout << "[2] Reject money and cancel order" << endl;
			cout << "[3] Chocolate fudge filling 65p" << endl;
			cout << "[4] Vanilla cream filling 65p" << endl;
			cout << "[5] Wild Berry filling 45p" << endl;
			cout << "[6] Blueberry filling 50p" << endl;
			cout << "[7] Cherry filling 30p" << endl;
			cout << "[8] Raspberry filling 30p" << endl;
			cout << "[9] Strawberry filling 50p" << endl;
			cout << "[10] Peanutbutter filling 30p" << endl;
			cout << "[11] Cookies and cream filling 40p" << endl;
			cout << "[12] Cookie dough filling 40p" << endl;
			cout << "[13] Chocolate filling 40p" << endl;
			cout << "[14] Fudge filling 40p" << endl;
			cout << "[15] No filling 25p" << endl;

			cin >> option;

			this->currentContext->setStateParam(Pancake_Option, option); //Sets Pancake_Option to allow the transitions to call the corrct functions

			if (option == 1 || option == 2)
			{
				this->currentContext->setState(Has_Credit);
			}
			else
			{
				makeSelection();
			}
		}
	}

	void insertMoney(int money) {

	}
	void makeSelection(void)
	{
		this->currentContext->setState(Has_Credit);
	}
	void moneyRejected(void){}
	void addMix(int){}
	void dispense(void){}
};


class OutOfMix : public State
{
public:
	OutOfMix(StateContext* Context) : State(Context){}

	void transition()
	{
		int addedMix = 0;
		cout << "Welcome to the Sweet Pancake vending machine!" << endl;
		cout << "Made by Pancake Vending Ltd" << endl;
		cout << "This machine handles money in the form of pence" << endl;
		cout << "Please add mix!" << endl;
		cin >> addedMix;
		addMix(addedMix);
	}

	void insertMoney(int money){
		cout << "Error! No Mix left! Ejecting money!" << endl;
	}

	void makeSelection(int option){
		cout << "Error! No Mix left! No Selection Made!" << endl;
	}

	void moneyRejected(void){
		cout << "Ejecting!" << endl; //new transition added
	}

	void addMix(int number){
		this->currentContext->setStateParam(No_Of_Pancakes, number);
		cout << "Added mix for: " << number << " Pancake/s" << endl;
		this->currentContext->setState(No_Credit);
	}

	void dispense(void){
		cout << "Error! No Mix left! Nothing to Dispense!" << endl;
	}

};

class NoCredit : public State
{
public:
	NoCredit(StateContext* Context) : State(Context){}

	void transition(){
		if (this->currentContext->getStateParam(Credit) == 0)
		{
			//system("cls"); // Clears screen to improve readability of output.
			int insertedMoney;
			cout << "Please insert credit: " << endl;
			cin >> insertedMoney;
			insertMoney(insertedMoney);
		}
	}

	void insertMoney(int money){
		cout << "You inserted: " << money << "p";
		money = money + this->currentContext->getStateParam(Credit);
		this->currentContext->setStateParam(Credit, money);
		cout << " Total: " << money << "p" << endl;
		this->currentContext->setState(Has_Credit);
	}

	void makeSelection(int option){
		cout << "Error! No Money!" << endl;
	}

	void moneyRejected(void){
		cout << "Error! No Money!" << endl;
	}

	void addMix(int number){
		cout << "Error! Already Got Mix!" << endl;
	}

	void dispense(void){
		cout << "Error! No Money!" << endl;
	}
};

void printCost(Pancake* pancakeSold)
{
	cout << "Current cost " << pancakeSold->cost() << "p" << endl;
}

class HasCredit : public State
{
public:
	HasCredit(StateContext* Context) : State(Context){}

	void transition(void){
		int option = this->currentContext->getStateParam(Pancake_Option);
		if (option == 0)
		{
			this->currentContext->setState(Display_Menu);
		}
		else if (option == 1)
		{
			this->currentContext->setStateParam(Pancake_Option, 0); // Allows the menu to be called again
			//system("cls"); // Clears screen to improve readability of output.
			int insertedMoney;
			cout << "Please insert credit: " << endl;
			cin >> insertedMoney;
			insertMoney(insertedMoney);
		}
		else if (option == 2)
		{
			moneyRejected();
		}

		else
		{
			//system("cls"); // Clears screen to improve readability of output.
			cout << "Please select coating/s select 0 to finish:" << endl;
			cout << "[1] Frosted coating 20p" << endl;
			cout << "[2] Wildilicious coating 30p" << endl;
			cout << "[3] Chocolate coating 40p" << endl;
			cout << "[4] Smarties coating 50p" << endl;
			cout << "[5] Hundereds and Thousands coating 10p" << endl;
			cout << "[6] Jelly Beans coating 50p" << endl;
			cout << "[7] Wild Berry coating 30p" << endl;
			cout << "[8] Brown Sugar coating 20p" << endl;
			cout << "[9] Chocolate chip coating 40p" << endl;
			makeSelection(option);
		}
	}

	void insertMoney(int money){
		cout << "You inserted: " << money << "p";
		money = money + this->currentContext->getStateParam(Credit);
		this->currentContext->setStateParam(Credit, money);
		cout << " Total: " << money << "p" << endl;
		this->currentContext->setState(Has_Credit);
	}

	void makeSelection(int option){
		switch (option)
		{
		case 15:
		{
			cout << "No filling selected" << endl;
			Pancake* selectedFilling = new Pancake;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		case 13:
		{
			cout << "Chocolate filling selected" << endl;
			Pancake* selectedFilling = new ChocolateFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		case 14:
		{
			cout << "Fudge filling selected" << endl;
			Pancake* selectedFilling = new FudgeFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		case 3:
		{
			cout << "Chocolate Fudge filling selected" << endl;
			Pancake* selectedFilling = new ChocolateFudgeFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		case 4:
		{
			cout << "Vanilla Cream filling selected" << endl;
			Pancake* selectedFilling = new VanillaCreamFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		case 5:
		{
			cout << "Wild Berry filling selected" << endl;
			Pancake* selectedFilling = new WildBerryFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		case 6:
		{
			cout << "Blueberry filling selected" << endl;
			Pancake* selectedFilling = new BlueberryFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		case 7:
		{
			cout << "Cherry filling selected" << endl;
			Pancake* selectedFilling = new CherryFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			break;
		}
		case 8:
		{
			cout << "Raspberry filling selected" << endl;
			Pancake* selectedFilling = new RaspberryFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		case 9:
		{
			cout << "Strawberry filling selected" << endl;
			Pancake* selectedFilling = new StrawberryFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			break;
		}
		case 10:
		{
			cout << "Peanut Butter filling selected" << endl;
			Pancake* selectedFilling = new PeanutButterFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		case 11:
		{
			cout << "Cookies and Cream filling selected" << endl;
			Pancake* selectedFilling = new CookiesAndCreamFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		case 12:
		{
			cout << "Cookie Dough filling selected" << endl;
			Pancake* selectedFilling = new CookieDoughFilling;
			printCost(selectedFilling);
			SelectCoating(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			break;
		}
		default:
		{
			cout << "Error try again." << endl;		//If anything other than the valid inputs are input makeSelection is called again with a new option.
			cin >> option;
			makeSelection(option);
			break;
		}

		}
		this->currentContext->setState(Dispenses_Pancake);
	}

	//Select coating is called with the pancake that is made in make selection. SelectCoating is recursive to allow multiple coatings to be added.
	void SelectCoating(Pancake* selectedFilling){

		int coatingOption = 0;
		cin >> coatingOption;

		switch (coatingOption)
		{
		case 1:
		{
			cout << "Frosted coating selected" << endl;
			Coating* selectedCoating = new Frosted;
			selectedCoating->addCoatingToPancake(selectedFilling);
			selectedFilling = selectedCoating;
			printCost(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			this->currentContext->setStateParam(Number_Of_Coatings, this->currentContext->getStateParam(Number_Of_Coatings) + 1);
			SelectCoating(selectedFilling);
			break;
		}
		case 2:
		{
			cout << "Wildlicious coating selected" << endl;
			Coating* selectedCoating = new Wildlicious;
			selectedCoating->addCoatingToPancake(selectedFilling);
			selectedFilling = selectedCoating;
			printCost(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			this->currentContext->setStateParam(Number_Of_Coatings, this->currentContext->getStateParam(Number_Of_Coatings) + 1);
			SelectCoating(selectedFilling);
			break;
		}
		case 3:
		{
			cout << "Chocolate coating selected" << endl;
			Coating* selectedCoating = new Chocolate;
			selectedCoating->addCoatingToPancake(selectedFilling);
			selectedFilling = selectedCoating;
			printCost(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			this->currentContext->setStateParam(Number_Of_Coatings, this->currentContext->getStateParam(Number_Of_Coatings) + 1);
			SelectCoating(selectedFilling);
			break;
		}
		case 4:
		{
			cout << "Smarties coating selected" << endl;
			Coating* selectedCoating = new Smarties;
			selectedCoating->addCoatingToPancake(selectedFilling);
			selectedFilling = selectedCoating;
			printCost(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			this->currentContext->setStateParam(Number_Of_Coatings, this->currentContext->getStateParam(Number_Of_Coatings) + 1);
			SelectCoating(selectedFilling);
			break;
		}
		case 5:
		{
			cout << "Hundreds and Thousands coating selected" << endl;
			Coating* selectedCoating = new HundredsAndThousands;
			selectedCoating->addCoatingToPancake(selectedFilling);
			selectedFilling = selectedCoating;
			printCost(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			this->currentContext->setStateParam(Number_Of_Coatings, this->currentContext->getStateParam(Number_Of_Coatings) + 1);
			SelectCoating(selectedFilling);
			break;
		}
		case 6:
		{
			cout << "Jelly Beans coating selected" << endl;
			Coating* selectedCoating = new JellyBeans;
			selectedCoating->addCoatingToPancake(selectedFilling);
			selectedFilling = selectedCoating;
			printCost(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			this->currentContext->setStateParam(Number_Of_Coatings, this->currentContext->getStateParam(Number_Of_Coatings) + 1);
			SelectCoating(selectedFilling);
			break;
		}
		case 7:
		{
			cout << "Wild Berry coating selected" << endl;
			Coating* selectedCoating = new WildBerry;
			selectedCoating->addCoatingToPancake(selectedFilling);
			selectedFilling = selectedCoating;
			printCost(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			this->currentContext->setStateParam(Number_Of_Coatings, this->currentContext->getStateParam(Number_Of_Coatings) + 1);
			SelectCoating(selectedFilling);
			break;
		}
		case 8:
		{
			cout << "Brown Sugar coating selected" << endl;
			Coating* selectedCoating = new BrownSugar;
			selectedCoating->addCoatingToPancake(selectedFilling);
			selectedFilling = selectedCoating;
			printCost(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			this->currentContext->setStateParam(Number_Of_Coatings, this->currentContext->getStateParam(Number_Of_Coatings) + 1);
			SelectCoating(selectedFilling);
			break;
		}
		case 9:
		{
			cout << "ChocolateChip coating selected" << endl;
			Coating* selectedCoating = new ChocolateChip;
			selectedCoating->addCoatingToPancake(selectedFilling);
			selectedFilling = selectedCoating;
			printCost(selectedFilling);
			this->currentContext->setStateParam(Cost_Of_Pancake, selectedFilling->cost());
			this->currentContext->setStateParam(Number_Of_Coatings, this->currentContext->getStateParam(Number_Of_Coatings) + 1);
			SelectCoating(selectedFilling);
			break;
		}
		case 0:
		{
			cout << "Selection ended." << endl;
			this->currentContext->setState(Dispenses_Pancake);
			break;
		}
		default:
		{
			cout << "Error try again." << endl;		//If anything other than the valid inputs are input makeSelection is called again with a new option.
			SelectCoating(selectedFilling);
			break;
		}
		}
	}

	void moneyRejected(void){
		cout << "Money Rejected!" << endl;
		this->currentContext->setStateParam(Credit, 0);
		this->currentContext->setState(No_Credit);
	}

	void addMix(int number){
		cout << "Error! Already Got Chocolate!" << endl;
	}

	void dispense(void){
		cout << "Error! No Selection Made!" << endl;
	}
};

class DispensesPancake : public State
{
public:
	DispensesPancake(StateContext* Context) : State(Context){}

	void transition(void){
		if (this->currentContext->getStateParam(No_Of_Pancakes) >= 1)
		{
			dispense();
		}
		else
		{
			cout << "No mix available!" << endl;
			this->currentContext->setState(Out_Of_Mix);
		}
	}

	void insertMoney(int money){
		cout << "Error! Busy Dispensing!" << endl;
	}

	void makeSelection(int option){
		cout << "Error! Busy Dispensing!" << endl;
	}

	void moneyRejected(void){
		cout << "Error! Busy Dispensing!" << endl;
	}

	void addMix(int number){
		cout << "Error! Busy Dispensing!" << endl;
	}

	void dispense(){
		//system("cls");
		if (this->currentContext->getStateParam(Credit) >= (this->currentContext->getStateParam(Cost_Of_Pancake))){
			if (this->currentContext->getStateParam(Pancake_Option) == 0) // Workaround to heat the filling of pancake for plain or a pancake with filling
			{
				Pancake* finishedPancake = new Pancake;
				finishedPancake->prepare(this->currentContext->getStateParam(Number_Of_Coatings));
			}
			else
			{
				Pancake* finishedPancake = new ChocolateFilling;
				finishedPancake->prepare(this->currentContext->getStateParam(Number_Of_Coatings));
			}
			this->currentContext->setStateParam(Credit, this->currentContext->getStateParam(Credit) - this->currentContext->getStateParam(Cost_Of_Pancake));
			this->currentContext->setStateParam(No_Of_Pancakes, this->currentContext->getStateParam(No_Of_Pancakes) - 1);
			this->currentContext->setStateParam(Pancake_Option, 0); //Once the pancake is dispenced the pancake option is set back to 0
			this->currentContext->setStateParam(Number_Of_Coatings, 0); //Resets the number of coatings back to 0

			if (rand() % 10 == 0)
			{
				cout << "YOU HAVE WON A FREE PANCAKE!!" << endl;
				if (this->currentContext->getStateParam(No_Of_Pancakes) >= 1)
				{
					cout << "This pancake will be a plain pancake." << endl;
					Pancake* finishedPancake = new Pancake;
					this->currentContext->setStateParam(No_Of_Pancakes, this->currentContext->getStateParam(No_Of_Pancakes) - 1);
					finishedPancake->prepare(this->currentContext->getStateParam(Number_Of_Coatings));
				}
				else
				{
					cout << "Sadly there is no pancake mix left." << endl;
				}
			}
			int option;
			cout << "Press 1 to make another pancake 2 to reject money" << endl;
			cin >> option;
			if (option == 2)
			{
				this->currentContext->setStateParam(Pancake_Option, 2);
			}
		}
		else{
			cout << "Error! Not enough money" << endl;
		}

		if (this->currentContext->getStateParam(Credit) > 0){
			this->currentContext->setState(Has_Credit);
		}
		else{
			this->currentContext->setState(No_Credit);
		}

		if (this->currentContext->getStateParam(No_Of_Pancakes) == 0){
			this->currentContext->setState(Out_Of_Mix);
		}
	}
};

class Pancake_Dispenser : public StateContext, Transition
{
public:
	Pancake_Dispenser(){
		this->availableStates.push_back(new OutOfMix(this));
		this->availableStates.push_back(new NoCredit(this));
		this->availableStates.push_back(new HasCredit(this));
		this->availableStates.push_back(new DispensesPancake(this));
		this->availableStates.push_back(new DisplayMenu(this));
		this->stateParameters.push_back(1); // Amount of pancakes able to be made with current mix in machine
		this->stateParameters.push_back(0); // Available Credit inserted
		this->stateParameters.push_back(20);// Cost of Pancake
		this->stateParameters.push_back(0); // Pancake option chosen in display menu
		this->stateParameters.push_back(0); // Number of coatings added to increase baking time

		this->setState(Out_Of_Mix); //The default state the pancake vending machine should be in when it is set up
	}

	void insertMoney(int money){
		this->currentState->insertMoney(money);
	}

	void displayMenu(void){
		this->currentState->displayMenu();
	}

	void makeSelection(int option){
		this->currentState->makeSelection(option);
	}

	void moneyRejected(void){
		this->currentState->moneyRejected();
	}

	void addMix(int number){
		this->currentState->addMix(number);
	}

	void dispense(void){
		this->currentState->dispense();
	}
};

void main(void)
{
	Pancake_Dispenser* myDispenser = new Pancake_Dispenser();
	delete myDispenser;
}