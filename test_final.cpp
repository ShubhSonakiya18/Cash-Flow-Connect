#include<iostream>
#include<string>
#include<iomanip>
#include<limits>
#include <stdexcept>
#include<fstream>
#include <sstream>
#include<queue>
#include <cctype>
using namespace std;

class Node{
public:
	//Data Entry
	string Name;
	string Aadhar;
	char Gender;
	string Type;
	int Acc_Number;
	int pin;
	int bala;
	//Node
	Node *right, *left;
	int height;
};
Node *temp, *temp1, *temp2, *tempcell = NULL;

void menu();
Node *root = NULL;
int admin_pswd = 18;
int staff_pswd = 28;
// Max Function
int max(int a, int b){
	if (a > b){ return a; }
	else{ return b; }
}
// Height Function
int height(Node* temp){
	if (temp == NULL){ return 0; }
	int lh = height(temp->left);
	int rh = height(temp->right);
	if (lh > rh){ return lh + 1; }
	else{ return rh + 1; }
}
// Left Rotation Function
Node *left_rotation(Node* temp2) {
	temp1 = temp2->right;
	temp2->right = temp1->left;
	temp1->left = temp2;

	temp2->height = max(height(temp2->left), height(temp2->right)) + 1;
	temp1->height = max(height(temp1->left), height(temp1->right)) + 1;
	return temp1;
}
// Right Rotation Function
Node *right_rotation(Node* temp2){
	temp1 = temp2->left;
	temp2->left = temp1->right; 
	temp1->right = temp2;

	temp2->height = max(height(temp2->left), height(temp2->right)) + 1;
	temp1->height = max(height(temp1->left), height(temp1->right)) + 1;

	return temp1;
}
// right left rotation
Node *right_left_rotation(Node* temp3)   {
	temp3->right = right_rotation(temp3->right);
	return left_rotation(temp3);
}
// Left right rotation
Node *left_right_rotation(Node *temp3)     {
	temp3->left = left_rotation(temp3->left);
	return right_rotation(temp3);
}
//Minimum Function{
Node *min(Node* temp)
{
	if (temp == NULL){ return 0; }
	if (temp->left == NULL)
	{
		return temp;
	}
	else
	{
		return (min(temp->left));
	}

}
// balance function
Node *balance(Node* temp)  {
	if (temp == NULL){ cout << "No rotation is found " << endl; }
	if (height(temp->left) - height(temp->right) > 1){
		if (height(temp->left->left) >= height(temp->left->right)){ temp = right_rotation(temp); }
		else{ temp = left_right_rotation(temp); }
	}
	else if (height(temp->right) - height(temp->left) > 1){
		if (height(temp->right->right) >= height(temp->right->left))
		{
			temp = left_rotation(temp);
		}
		else
		{
			temp = right_left_rotation(temp);
		}
	}
	temp->height = max(height(temp->left), height(temp->right)) + 1;
	return temp;
}



Node *insertion(Node* temp, string name, string cnc, char gen, string type, int account_no, int PIN, int bal){    ///////////////////////// insertion
	if (temp == NULL){
		temp = new Node();
		temp->Name = name;
		temp->Aadhar = cnc;
		temp->Gender = gen;
		temp->Type = type;
		temp->Acc_Number = account_no;
		temp->pin = PIN;
		temp->bala = bal;
		temp->left = NULL;
		temp->right = NULL;
		temp->height = 0;
	}

	if (account_no < temp->Acc_Number){
		temp->left = insertion(temp->left, name, cnc, gen, type, account_no, PIN, bal);
		if (height(temp->left) - height(temp->right) == 2){
			if (account_no < temp->left->Acc_Number){ temp = right_rotation(temp); }
			else{ temp = left_right_rotation(temp); }
		}
	}

	if (account_no > temp->Acc_Number){
		temp->right = insertion(temp->right, name, cnc, gen, type, account_no, PIN, bal);
		if (height(temp->right) - height(temp->left) == 2){
			if (account_no > temp->right->Acc_Number){ temp = left_rotation(temp); }
			else{ temp = right_left_rotation(temp); }
		}
	}

	temp->height = max(height(temp->left), height(temp->right)) + 1;
	return temp;
}

void default_insertion(){

	ifstream input_file("account.txt");
	string line;
	while (getline(input_file, line)) {
		
        string name_database="";
        int name_database_i;
			string aadhar_database="";
			int aadhar_database_i;
			char gender_database;
			int gender_database_i;
			string type_database="";
			int type_database_i;
			string AccNo_store="";
			int AccNo_database=0;
			int AccNo_database_i;
			string pin_store="";
			int pin_database=0;
			int pin_database_i;
			string amount_store="";
			int amount_database=0;
			int amount_database_i;
		for(int i=0;i<line.length();i++){
			if(line[i]=='@'){
				name_database_i=i;
			}
			else if(line[i]=='#'){
				aadhar_database_i=i;
			}
			else if(line[i]=='$'){
				gender_database_i=i;
			}
			else if(line[i]=='%'){
				type_database_i=i;
			}
			else if(line[i]=='^'){
				AccNo_database_i=i;
			}
			else if(line[i]=='&'){
				pin_database_i=i;
			}
			else if(line[i]=='*'){
				amount_database_i=i;
			}

		}
		for(int i=0;i<line.length();i++){
			if(i>=0 && i<name_database_i){
				name_database+=line[i];
			}
			else if(i>name_database_i && i<aadhar_database_i){
				aadhar_database+=line[i];
			}
			else if(i>aadhar_database_i && i<gender_database_i){
				gender_database=line[i];
			}
			else if(i>gender_database_i && i<type_database_i){
				type_database+=line[i];
			}
			else if(i>type_database_i && i<AccNo_database_i){
				AccNo_store+=line[i];
			}
			else if(i>AccNo_database_i && i<pin_database_i){
				pin_store+=line[i];
			}
			else if(i>pin_database_i && i<amount_database_i){
				amount_store+=line[i];
			}
			
		}
		try{
		AccNo_database=stoi(AccNo_store);
		pin_database=stoi(pin_store);
		amount_database=stoi(amount_store);
		}
		catch(const std::invalid_argument& e){
			std::cerr << "Invalid input: " << e.what() << std::endl;
		}
		catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
		root=insertion(root,name_database,aadhar_database,gender_database,type_database,AccNo_database,pin_database,amount_database);
    }

    input_file.close();

}

Node *deletion(Node* temp, int x) ///////////////////////// deletion
{
	if (temp == NULL){
		return temp;
	}
	else if (x < temp->Acc_Number){
		temp->left = deletion(temp->left, x);
	}
	else if (x > temp->Acc_Number){
		temp->right = deletion(temp->right, x);
	}
	else if (temp->left && temp->right){
		tempcell = min(temp->right);
		temp->Acc_Number = tempcell->Acc_Number;
		temp->right = deletion(temp->right, temp->Acc_Number);
	}
	else{
		tempcell = temp;
		if (temp->left == NULL){
			temp = temp->right;
		}
		else if (temp->right == NULL){
			temp = temp->left;
		}
		delete tempcell;
	}
	if (temp != NULL){
		temp = balance(temp);
	}

	return temp;

}

int findMax(Node* root)  ///////////////////////// find max
{
	if (root == NULL){ return 0; }
	int res = root->Acc_Number;
	int lres = findMax(root->left);
	int rres = findMax(root->right);
	if (lres > res){ res = lres; }
	if (rres > res)
		res = rres;
	return res;
}

bool search(Node* temp, int x)  ///////////////////////// search
{
	while (temp != NULL)
	{

		if (x > temp->Acc_Number)
			temp = temp->right;


		else if (x < temp->Acc_Number)
			temp = temp->left;
		else
			return true;
	}
	return false;

}

int CountOfAllNodes(Node* root){
    queue<Node*> qt;
    qt.push(root);
    qt.push(NULL);
    int count=0;
    while(!qt.empty()){
        Node* node=qt.front();
        qt.pop();
        if(node!=NULL){
            count++;
            if(node->left){
                qt.push(node->left);
                
            }
            if(node->right){
                qt.push(node->right);
                
            }
        }
        else{
            if(!qt.empty()){
                qt.push(NULL);
            }
        }
    }
    return count;
}
void write_BST_to_file(Node* root, ofstream &file){
	if(root==NULL){
	    return;
		
	}
	write_BST_to_file(root->left , file);
	file<<root->Name<<"@"<<root->Aadhar<<"#"<<root->Gender<<"$"<<root->Type<<"%"<<root->Acc_Number<<"^"<<root->pin<<"&"<<root->bala<<"*"<<endl;
	write_BST_to_file(root->right,file);
}

int print_data(Node* temp, int x) ///////////////////////// Print Function
{
	while (temp != NULL)
	{
		// pass right subtree as new tree
		if (x> temp->Acc_Number)
			{temp = temp->right;}

		// pass left subtree as new tree
		else if (x < temp->Acc_Number)
			{temp = temp->left;}
		else{
			cout << "        ####################################################################################################################################" << endl;
			cout << " " << endl;
			cout << "          " << "ACC_Number" << "                 " << "NAME" << "                   " << "Aadhar" << "                     " << "GENDER" << "            " << "Type" << "          " << "Balance" << endl;
			cout << " " << endl;
			cout << "        ####################################################################################################################################" << endl;
			cout << " " << endl;
			cout << "             ";
			cout << temp->Acc_Number;
			cout << "            ";
			cout << setw(18) << temp->Name;
			cout << "           ";
			string adh_no=temp->Aadhar;
            for(int i=0;i<9;i=i+4){
                for(int j=i;j<=i+3;j++){
                     cout<<adh_no[j];
        }
        if(i!=8){
        cout<<"-";}
    }
			cout << "                ";
			cout << static_cast<char>(toupper(temp->Gender));
			cout << "                ";
			// cout << temp->Type;
            for (char &c : temp->Type) {
                c = toupper(c);
            }

            cout << temp->Type;
			cout << "             ";
			cout << temp->bala << endl;
			return true;
		}
	}
	return false;
}

void print_for_admin(Node* temp)   ////////////////////////// print For order function
{

	if (temp->left != NULL){ print_for_admin(temp->left); }
	cout << "             ";
	cout<<temp->Acc_Number;
	cout << "            ";
	cout << setw(18) << temp->Name;
	cout << "           ";
	
    string adh_no=temp->Aadhar;
    for(int i=0;i<9;i=i+4){
        for(int j=i;j<=i+3;j++){
            cout<<adh_no[j];
        }
        if(i!=8){
        cout<<"-";}
    }
	cout << "                ";
    cout << static_cast<char>(toupper(temp->Gender));
	cout << "                ";
	// cout << temp->Type;
     for (char &c : temp->Type) {
                c = toupper(c);
            }

            cout << temp->Type;
	cout << "         ";
	cout << temp->bala << endl;
	if (temp->right != NULL){ print_for_admin(temp->right); }

}



int deposit(Node* temp, int acc_num, int PIN, int bal)   ///////////////////////// deposit Balance
{

	while (temp != NULL){
		if (acc_num> temp->Acc_Number){ temp = temp->right; }
		else if (acc_num < temp->Acc_Number){ temp = temp->left; }
		else{
			if (temp->pin == PIN){ temp->bala = temp->bala + bal; }
			else if (temp->pin != PIN){ return -1; }
			return 1;
		}
	}
	return 0;

}

int with_draw(Node* temp, int acc_num, int PIN, int bal)   /////////////////////////  with_draw balance
{
	while (temp != NULL){
		if (acc_num> temp->Acc_Number){ temp = temp->right; }
		else if (acc_num < temp->Acc_Number){ temp = temp->left; }
		else{
			if (temp->pin == PIN){
				if ((temp->bala < bal)){ return -1; }
				else { temp->bala = temp->bala - bal; }
			}
			else if (temp->pin != PIN){ return -2; }
			return 1;
		}
	}
	return 0;

}

bool is_integer(string Aadhar) {
  if (Aadhar.length() == 0) {
    return false;
  }

  for (char c : Aadhar) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}

int change_info(Node* temp, string name, string Aadhar, char gender, string type, int acc_num, int PIN)   ///////////////////////// Change Info
{

	while (temp != NULL){
		if (acc_num> temp->Acc_Number){ temp = temp->right; }
		else if (acc_num < temp->Acc_Number){ temp = temp->left; }
		else{
			if (temp->Acc_Number == acc_num){
				temp->Name = name;
				temp->Aadhar = Aadhar;
				temp->Gender = gender;
				temp->pin = PIN;
				temp->Type = type;
			}

			return 1;
		}
	}
	return 0;

}

int check_acc_pin(Node* temp, int acc_num, int PIN)   
{
	while (temp != NULL){
		if (acc_num> temp->Acc_Number){ temp = temp->right; }
		else if (acc_num < temp->Acc_Number){ temp = temp->left; }
		else{
			if (temp->pin == PIN){ return 1; }
			else if (temp->pin != PIN){ return -1; }
		}
	}

	return 0;

}




void create_Acc()
{
	//Declared Variables
	string full_name;
	string Aadhar;
	string Acc_type;
	char g;
	int acc_no;
	int pin;
	long long Balance;
	int load = 0;
	int a = 1;
	//END Declared Variables
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "" << endl;
	cout << "                                                 Create User Account" << endl;
	cout << " " << endl;
	cout << "                                            Enter Customer's Full Name : "; 
	cin.ignore();
	getline(cin,full_name);
	cout << " " << endl;

	cout << "                                            Enter Aadhar (12 Digit Number) : ";
	cin >> Aadhar;
	cout << " " << endl;


	while (!is_integer(Aadhar)) {
  cout << "Invalid Aadhar number. Please enter an integer Aadhar number: ";
  cin >> Aadhar;
}
	while(Aadhar.length()!=12){
		cout<<"                                            Enter a valid Aadhar"<<endl;
		cout << "                                            Enter Aadhar (12 Digit Number) : ";
		cin >> Aadhar;
		cout << " " << endl;		
	}
	cout << "                                            Enter Gender  (M/F) : ";
	cin >> g;
	cout << " " << endl;
	while(g!='M' && g!='F' && g!='m' && g!='f'){
		cout<<"                                            Enter a valid gender! (M/F)"<<endl;
		cout << "                                            Enter Gender  (M/F) : ";
		cin>>g;
		cout << " " << endl;
	}
	cout << "                                            Enter Account Type (C/S) : "; 
	cin >> Acc_type;
	cout << " " << endl;
	while(Acc_type!="C" && Acc_type!="S" && Acc_type!="c" && Acc_type!="s"){
		cout<<"                                            Enter a valid account! (C/S)"<<endl;
		cout << "                                            Enter Account Type (C/S) : "; 
		cin >> Acc_type;
		cout << " " << endl;
	}
	load = findMax(root);
	acc_no = load + 1;
	cout << "                                            Your Account Number is : " << acc_no << endl;
	cout << " " << endl;
	string pin_str;
    int length;

    // while (true) {
    //     cout << "                                            Enter a 4-digit integer pin: ";
    //     if (cin >> pin) {
    //         pin_str = to_string(pin);
    //         length = pin_str.length();
    //         if (length == 4) {
    //             break;
    //         }
    //     }
    //     cout << "Enter a valid 4-digit pin!" << endl;
    //     cin.clear();
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // }
	 while (true) {
  cout << "                                            Enter a 4-digit integer pin : ";
  cin >> pin;

  if (pin >= 0000 && pin <= 9999) {
    break;
  } else {
    cout << "Enter a valid 4-digit pin!" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}
	cout << "                                            Enter Balance (Min:500) : ";
	cin >> Balance;
	if (Balance >= 500)
	{
		root = insertion(root, full_name, Aadhar, g, Acc_type, acc_no, pin, Balance); //insertion(root)
		
	}
	else{
		cout << "                                            Minimum Balance is 500Rs. " << endl;
		cout << "                                            Enter Balance (Min:500) : ";
		cin >> Balance;
		if (Balance >= 500)
		{
			root = insertion(root, full_name, Aadhar, g, Acc_type, acc_no, pin, Balance); //insertion(root)
			
		}
	}
	
    // update(root);

}


void admin_panel()
{
	//Declared Variables
	int b;
	int admin_delete_cin;
	int admin_search_cin;
	int result_admin_1;
	int result_admin_2;
	int result_admin_3;
	int result_admin_4;
	int admin_return;

	int acc_1;
	int pin_1;
	string cnc_1;
	char gen_1;
	string acc_type_1;
	string new_cnc_1;
	int new_pin_1;
	string new_acc_1;
	int admin_logs_cin;
	//END Declared Variables

	system("cls");
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       *************ADMIN|||PANEL*************" << endl;
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       *  Press 1 To Search Account          *" << endl;
	cout << "                                                       *  Press 2 To Show List of All Acc    *" << endl;
	cout << "                                                       *  Press 3 To Edit Information        *" << endl;
	cout << "                                                       *  Press 4 To Go Back to Main Menu    *" << endl;
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       Enter an Option : ";
	cin >> b;

	if (b == 1){
		system("cls");
		cout << "                                         Enter the Account Number to Search : ";
		cin >> admin_search_cin;
		result_admin_2 = search(root, admin_search_cin);
		if (result_admin_2 == 1){
			cout << " " << endl;
			cout << "                                         User Found..!!" << endl;
			cout << " " << endl;
			print_data(root, admin_search_cin);
			cout << " " << endl;
		}
		else if (result_admin_2 == 0){
			cout << " " << endl;
			cout << " " << endl;
			cout << "                                         User not found..!! :(" << endl;
			cout << " " << endl;
			cout << " " << endl;
		}
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "                                                Press 7 to return to ADMIN PANEL ...!!! ";
		cin >> admin_return;
		if (admin_return == 7){ admin_panel(); }
		else{ cout << "                                         Invalid Output !!" << endl; menu(); }
	}

	else if (b == 2){
		system("cls");
		cout << "        ####################################################################################################################################" << endl;
		cout << " " << endl;
		cout << "          " << "ACC_Number" << "                 " << "NAME" << "                   " << "Aadhar" << "                     " << "GENDER" << "            " << "Type" << "          "<< "BALANCE" << endl;
		cout << " " << endl;
		cout << "        ####################################################################################################################################" << endl;
		cout << " " << endl;
		print_for_admin(root);
		cout << " " << endl;
		cout << " " << endl;
		cout << "                                                Press 7 to return to ADMIN PANEL ...!!! ";
		cin >> admin_return;
		if (admin_return == 7){ admin_panel(); }
		else{ cout << "                                         Invalid Output !!" << endl; menu(); }
	}
	else if (b == 3){
		system("cls");
		cout << "                                            Change Informaion of Account " << endl;
		cout << "                                            Enter User_Account Number : ";
		cin >> acc_1;
		cout << "                                            Enter User_Account PIN number : ";
		cin >> pin_1;
		result_admin_3 = check_acc_pin(root, acc_1, pin_1);
		if (result_admin_3 == 1){
			cout << "                                            Change Informaion of Account " << endl;
			cout << "\n" << endl;
			cin.ignore();
			cout << "                                            Enter New Name / previous Name : ";
			getline(cin, new_acc_1);
			cout << "                                            Enter New Aadhar / Previous Aadhar : ";
			cin>>new_cnc_1;

			while (!is_integer(new_cnc_1)) {
           cout << "Invalid Aadhar number. Please enter an integer Aadhar number: ";
          cin >> new_cnc_1;
}
			while(new_cnc_1.length()!=12){
			cout<<"                                            Enter a valid Aadhar"<<endl;
			cout << "                                            Enter Aadhar (12 Digit Number) : ";
			cin >> new_cnc_1;		
	}
			cout << "                                            Enter Gender : ";
			cin >> gen_1;
    		while(gen_1!='M' && gen_1!='F' && gen_1!='m' && gen_1!='f'){
				cout<<"                                            Enter a valid gender! (M/F)"<<endl;
				cout << "                                            Enter Gender  (M/F) : ";
				cin>>gen_1;
		
	}			
			cout << "                                            Enter Account Type C/S : ";
			cin >> acc_type_1;
			while(acc_type_1!="C" && acc_type_1!="S" && acc_type_1!="c" && acc_type_1!="s"){
		cout<<"                                            Enter a valid account! (C/S)"<<endl;
		cout << "                                            Enter Account Type (C/S) : "; 
		cin >> acc_type_1;
		
	}
	string pin_str;
    int length;

    while (true) {
        cout << "                                            Enter New PIN / Previous PIN :";
        if (cin >> new_pin_1) {
            pin_str = to_string(new_pin_1);
            length = pin_str.length();
            if (length == 4) {
                break;
            }
        }
        cout << "                                            Enter a valid 4-digit pin!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
			change_info(root, new_acc_1, new_cnc_1, gen_1, acc_type_1, acc_1, new_pin_1);
			ofstream output_file_change_info("temp_change_info.txt");
		if(output_file_change_info.is_open()){
			write_BST_to_file(root,output_file_change_info);
			output_file_change_info.close();
		}
		remove("account.txt");
        rename("temp_change_info.txt", "account.txt");

			cout << "                                            Account information is Sucessfully Changed" << endl;
		}
		else if (result_admin_3 == -1){ cout << "                                            PIN is Incorrect...!!!" << endl; }
		else if (result_admin_3 == 0){ cout << "                                            Account is not Present...!!!" << endl; }
		else{ cout << "                                            Account is not Present...!!!" << endl; }

		cout << " " << endl;
		cout << " " << endl;
		cout << "                                             Press 7 to return to ADMIN PANEL ...!!! ";
		cin >> admin_return;
		if (admin_return == 7){ admin_panel(); }
		else{ cout << "                                         Invalid Output !!" << endl; menu(); }
	}
	else if (b == 4){ menu(); }
	else{
		system("cls");
		admin_panel();
	}
}

void staff_panel(){
	//Variable Used
    int admin_delete_cin;
	int admin_search_cin;
    int admin_return;
	int staff_acc_no;
	int staff_pin_no;
	int staff_amount_to_dep;
	int staff_acc_no_1;
	int staff_pin_no_1;
	int staff_amount_to_wdraw_1;
	int account_logs_cin;
	int c;
	int staff_return;
	int lol_staff_1;
	int lol_staff_2;
	int account_info_cin;
	int result_staff_1;
	int result_staff_2;
	int result_staff_3;
	int result_staff_4;
    int result_admin_1;
	//End Variable Declaration

	system("cls");
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       *************STAFF|||PANEL*************" << endl;
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       *  Press 1 to Create a new Accout     *" <<endl;
    cout << "                                                       *  Press 2 to Delete a Account        *" <<endl;
    cout << "                                                       *  Press 3 To Check Account Info      *" << endl;
	cout << "                                                       *  Press 4 To Deposit Cash            *" << endl;
	cout << "                                                       *  Press 5 To With_Draw Cash          *" << endl;
	cout << "                                                       *  Press 6 To Go Back to Main Menu    *" << endl;
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       Enter an Option : ";
	cin >> c;

    	if (c == 1){
		system("cls");
		create_Acc();
		ofstream output_file("account.txt");
		if(output_file.is_open()){
			write_BST_to_file(root,output_file);
			output_file.close();
		}
		cout << " " << endl;
		cout << " " << endl;
		cout << "                                                           Press 7 to return to STAFF PANEL ...!!! ";
		cin >> staff_return;
		if (staff_return == 7){ staff_panel(); }
		else{ menu(); }
	}
	else if (c == 2){
		system("cls");
		cout << "                                         Enter the Account Number to Delete :";
		cin >> admin_delete_cin;
		result_admin_1 = search(root, admin_delete_cin);
		cout << result_admin_1 << endl;
		if (result_admin_1 == 1){
			cout << "                                         Account number Found....!!!" << endl;
			cout << " " << endl;
			deletion(root, admin_delete_cin);
			ofstream output_file_delete_acc("temp_delete_acc.txt");
		if(output_file_delete_acc.is_open()){
			write_BST_to_file(root,output_file_delete_acc);
			output_file_delete_acc.close();
		}
		remove("account.txt");
        rename("temp_delete_acc.txt", "account.txt");
			cout << " " << endl;
			cout << "                                         Account is Deleted....!!!" << endl;
		}
		else{
			cout << " " << endl;
			cout << "                                         Account not found ....!!!" << endl;
			cout << " " << endl;
		}
		cout << " " << endl;
		cout << "                                         Press  7 to return to STAFF PANEL..!! ";
		cin >> staff_return;
		if (staff_return == 7){ staff_panel(); }
		else{ cout << "                                         Invalid Output !!" << endl; menu(); }
	}
	if (c == 3){
		system("cls");
		cout << "                                         Enter the Account Number to Check info : ";
		cin >> account_info_cin;
		result_staff_1 = search(root, account_info_cin);
		if (result_staff_1 == 1){
			cout << " " << endl;
			cout << "                                         User Found..!!" << endl;
			cout << " " << endl;
			print_data(root, account_info_cin);
			cout << " " << endl;
		}
		else if (result_staff_1 == 0){
			cout << "                                         User not found..!! :(" << endl;
			cout << " " << endl;
			cout << " " << endl;
		}

		cout << " " << endl;
		cout << "                                         Press  7 to return to STAFF PANEL..!! ";
		cin >> staff_return;
		if (staff_return == 7){ staff_panel(); }
		else{ cout << "                                         Invalid Output !!" << endl; menu(); }
	}
	else if (c == 4){
		system("cls");
		cout << "                                         Enter Account : ";
		cin >> staff_acc_no;
		cout << "                                         Enter Account PIN : ";
		cin >> staff_pin_no;
		cout << "                                         Enter The Amount Deposit : ";
		cin >> staff_amount_to_dep;
		cout << " " << endl;
		cout << "                                                   Status ""BEFORE"" Deposit Amount in ACCOUNT" << endl;
		cout << " " << endl;
		print_data(root, staff_acc_no);
		cout << " " << endl;
		cout << " " << endl;
		result_staff_2 = deposit(root, staff_acc_no, staff_pin_no, staff_amount_to_dep);
		if (result_staff_2 == 1){
			ofstream output_file_deposit("temp_deposit.txt");
		if(output_file_deposit.is_open()){
			write_BST_to_file(root,output_file_deposit);
			output_file_deposit.close();
		}
		remove("account.txt");
        rename("temp_deposit.txt", "account.txt");
			cout << "                                                   Status ""AFTER"" Deposit Amount in ACCOUNT" << endl;
			cout << " " << endl;
			print_data(root, staff_acc_no);

			cout << " " << endl;
			cout << " " << endl;

			cout << "                                         Amount " << staff_amount_to_dep << " has been Deposited in Account Number  " << staff_acc_no << endl;
		}
		else if (result_staff_2 == 0){ cout << "                                                     Account not Found....Amount is not Deposit in your Account...!" << endl; }
		else if (result_staff_2 == -1){ cout << "                                                     PIN is Incorrect" << endl; }
		cout << " " << endl;
		cout << " " << endl;
		cout << "                                         Press  7 to return to STAFF PANEL...!!! ";
		cin >> staff_return;
		if (staff_return == 7){ staff_panel(); }
		else{ cout << "                                         Invalid Output !!" << endl; menu(); }
	}
	else if (c == 5){
		cout << "with draw cash" << endl;
		system("cls");
		cout << "                                         Enter Account Number : ";
		cin >> staff_acc_no_1;
		cout << "                                         Enter Account PIN : ";
		cin >> staff_pin_no_1;
		cout << "                                         Enter The Amount WithDraw : ";
		cin >> staff_amount_to_wdraw_1;
		cout << " " << endl;
		cout << "                                                   Status ""BEFORE"" WITHDRAW Amount from ACCOUNT" << endl;
		cout << " " << endl;
		print_data(root, staff_acc_no_1);
		cout << " " << endl;
		cout << " " << endl;
		result_staff_3 = with_draw(root, staff_acc_no_1, staff_pin_no_1, staff_amount_to_wdraw_1);
		if (result_staff_3 == 1){
			ofstream output_file_withdraw("temp_withdraw.txt");
		if(output_file_withdraw.is_open()){
			write_BST_to_file(root,output_file_withdraw);
			output_file_withdraw.close();
		}
		remove("account.txt");
        rename("temp_withdraw.txt", "account.txt");
			cout << "                                                   Status ""AFTER"" WITHDRAW Amount from ACCOUNT" << endl;
			cout << " " << endl;
			print_data(root, staff_acc_no_1);
			cout << " " << endl;
			cout << " " << endl;
			cout << "                                         Amount " << staff_amount_to_wdraw_1 << " has been Withdraw in Account Number  " << staff_acc_no_1 << endl;
		}
		else if (result_staff_3 == 0){ cout << "                                                     Account not Found....Amount is not With Drawn from User Account...!" << endl; }
		else if (result_staff_3 == -1){ cout << "                                                     Account Balance is Insufficient " << endl; }
		else if (result_staff_3 == -2){ cout << "                                                     PIN is InCorrect..!! " << endl; }
		cout << " " << endl;
		cout << " " << endl;
		cout << "                                                      Press  7 to return to STAFF PANEL...!!! ";
		cin >> staff_return;
		 if (staff_return == 7){ staff_panel(); }
		else{ cout << "                                         Invalid Output !!" << endl; menu(); }
	}

	else if (c == 6){
		system("cls"); menu();
	}
	else{ staff_panel(); }
}

void Bank_panel()
{
	// declare variable
	int d;
	int Bank_acc_no_1;
	int Bank_pin_no_1;
	int Bank_amount_to_wdraw_1;
	int result_Bank_3;
	int Bank_return;

	system("cls");
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       *******************BANK*****************" << endl;
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       *  Press 1 To  Cash            *" << endl;
	cout << "                                                       *  Press 2 To Go Back to Main Menu    *" << endl;
	cout << "                                                       ***************************************" << endl;
	cout << "                                                       Enter an Option : ";
	cin >> d;
	if (d == 1){
		system("cls");
		cout << "                                         Enter Account Number : ";
		cin >> Bank_acc_no_1;
		cout << "                                         Enter Account PIN : ";
		cin >> Bank_pin_no_1;
		cout << "                                         Enter The Amount WithDraw : ";
		cin >> Bank_amount_to_wdraw_1;
		cout << " " << endl;
		cout << "                                                   Status ""BEFORE"" WITHDRAW Amount from ACCOUNT" << endl;
		cout << " " << endl;
		print_data(root, Bank_acc_no_1);
		cout << " " << endl;
		cout << " " << endl;
		result_Bank_3 = with_draw(root, Bank_acc_no_1, Bank_pin_no_1, Bank_amount_to_wdraw_1);
		if (result_Bank_3 == 1){
			ofstream output_file_atm("temp_atm.txt");
		if(output_file_atm.is_open()){
			write_BST_to_file(root,output_file_atm);
			output_file_atm.close();
		}
		remove("account.txt");
        rename("temp_atm.txt", "account.txt");
			cout << "                                                   Status ""AFTER"" WITHDRAW Amount from ACCOUNT" << endl;
			cout << " " << endl;
			print_data(root, Bank_acc_no_1);
			cout << " " << endl;
			cout << " " << endl;
			cout << "                                         Amount " << Bank_amount_to_wdraw_1 << " has been Withdraw in Account Number  " << Bank_acc_no_1 << endl;
		}
		else if (result_Bank_3 == 0){ cout << "                                                     Account not Found....Amount is not With Drawn from User Account...!" << endl; }
		else if (result_Bank_3 == -1){ cout << "                                                     Account Balance is Insufficient " << endl; }
		else if (result_Bank_3 == -2){ cout << "                                                     PIN is InCorrect..!! " << endl; }
		cout << " " << endl;
		cout << " " << endl;
		cout << "                                         Press  5 to return to Bank PANEL...!!! ";
		cin >> Bank_return;
		if (Bank_return == 5){ Bank_panel(); }
		else{ cout << "                                         Invalid Output !!" << endl; menu(); }
	}

	else if (d == 2){
		system("cls"); menu();
	}
	else{ Bank_panel(); }
}

void menu()
{
	
	int a;
	int b;
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	system("cls");
	cout << "\n";
	cout << "\n" << endl;
	cout << "                                                            Welcome to FinX! " << endl;
	cout << "                                                       ********************************" << endl;
	cout << "                                                       **********LOGIN||PANEL**********" << endl;
	cout << "                                                       ********************************" << endl;
	cout << "                                                       *  Press 1 For ADMIN Login     *" << endl;
	cout << "                                                       *  Press 2 For STAFF Login     *" << endl;
	cout << "                                                       *  Press 3 For ATM Service     *" << endl;
	cout << "                                                       *  Press 4 To  Exit            *" << endl;
	cout << "                                                       ********************************" << endl;
	cout << "                                                       ********************************" << endl;
	cout << "\n" << endl;
	cout << "                                                       Enter Your Choice : ";
	cin >> a;
	if (a == 1){
		system("cls");
		cout << "\n";
		cout << "\n";
		cout << "\n";
		cout << "\n";
		cout << "                                                       Enter Pin : ";
		cin >> b;
		if (b == admin_pswd){ admin_panel(); }
		else{
			cout << "                                                       Enter Pin : ";
			cin >> b;
			if (b == admin_pswd){ admin_panel(); }
			else { cout << "                                         Invalid Output !!" << endl; exit(0); }
		}
	}
	else if (a == 2){
		system("cls");
		cout << "\n";
		cout << "\n";
		cout << "\n";
		cout << "\n";
		// cout << "                                                       Enter Pin : ";
		// cin >> b;
		// if (b == staff_pswd){ staff_panel(); }
		// else{
			cout << "                                                       Enter Pin : ";
			cin >> b;
			if (b == staff_pswd){ staff_panel(); }
			else { cout << "                                         Invalid Output !!" << endl; exit(0); }
		// }
	}
	else if (a == 3){ Bank_panel(); }
	else if (a == 4){ exit(0); }
	else { menu(); }
}


int main()
{

	// root = insertion(root, "Rahul Dewangan", "123412341234", 'M', "C", 32001, 1234, 500);    //already registered 
	// root = insertion(root, "Dhruv Arora", "123412341234", 'M', "S", 32002, 5678, 589);
    // root = insertion(root, "Pushti Maheshwari", "123123123123", 'F', "S", 32003, 1111, 600);
    default_insertion();
	menu();
	system("pause");
	return 0;

}
