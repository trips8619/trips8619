#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int main()
{

	cout << "\n Welcome to Number Guessing game!"
		<< endl;
	cout << "You have to guess a number between 1 and 10. "
			
		<< endl;

	while (true) {
		srand(time(0));
		int no = 1 + (rand() % 10);
		int variable;
			cout << "\nYou have 5 choices for finding the "
					"secret number between 1 and 10.";
			int choice = 5;
			for (int i = 1; i <= 5; i++) {
				cout << "\n\nEnter the number: ";
				cin >> variable;
				if (variable == no) {
					cout << "Correct, "
						<< variable
						<< " is the secret number" << endl
						<< "You win!"<<endl;
					break;
				}
				else {
					cout << "No, " << variable
						<< " is not the right number\n";
					if (variable > no) {
						cout << "The secret number is "
								"smaller than the number "
								"you have chosen"
							<< endl;
					}
					else {
						cout << "The secret number is "
								"greater than the number "
								"you have chosen"
							<< endl;
					}
					choice--;
					cout << choice << " choices left. "
						<< endl;
					if (choice == 0) {
						cout << "You couldn't find the "
								"secret number, it was "
							<< no
							<< ", You lose!!\n\n";
						cout << "Play the game again to "
								"win!!!\n\n";
					}
				}
			}
break;
	}
	return 0;
}
