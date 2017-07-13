#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>

using namespace std;

enum typeOfError {CORRECT, DELETION, INSERTION, SUBSTITUTION, TRANSPOSITION, ERROR};

//prototypes
void findErrors(string correct_word,string user_word,typeOfError &errorType);
void isSubstitution(string correct_word,string user_word,typeOfError &errorType);
void isTransposition(string correct_word,string user_word,typeOfError &errorType);
void isDeletion(string correct_word,string user_word,typeOfError &errorType);
void isInsertion(string correct_word,string user_word,typeOfError &errorType);
void displayErrors(typeOfError errorType,int &insCounter,int &delCounter,int &subsCounter,int &transCounter,int &errorCounter,int &correctCounter);

int main(){
	ifstream fin("Input.txt");
	if(!fin){
		cout<<"Input file not opening\n";
		//system("pause");
		exit(0);
	}
	
	//variables
	string correct_word="",user_word="";
	typeOfError errorType=ERROR;
	char spaceFinder=' ';
	int delCounter=0,insCounter=0,transCounter=0,subsCounter,correctCounter=0,errorCounter=0;
				
	cout<<"Word correction by:mission-possible"<<endl;
	
	while(!fin.eof()){
		fin>>correct_word;
		cout<<"*****starting new line*******"<<endl<<endl;
		fin.get(spaceFinder);
		
		while(!fin.eof() && spaceFinder!='\n'){
			fin>>user_word;
			cout<<"correct word is:"<<correct_word<<"\t"<<"user word is:"<<user_word<<endl;
			findErrors(correct_word, user_word, errorType);
			
			displayErrors(errorType,insCounter,delCounter,subsCounter,transCounter,errorCounter,correctCounter);
			if(!fin.eof())
				fin.get(spaceFinder);
		}
		cout<<endl;		
	}
	cout<<"\nNumber of Deletions:"<<delCounter<<endl;
	cout<<"\nNumber of Insertions:"<<insCounter<<endl;
	cout<<"\nNumber of Substitutions:"<<subsCounter<<endl;
	cout<<"\nNumber of Transpositions:"<<transCounter<<endl;
	cout<<"\nNumber of Correct words:"<<correctCounter<<endl;
	cout<<"\nNumber of Misspelied:"<<errorCounter<<endl<<endl;
	//system("pause");
	return 0;
}

void findErrors(string correct_word,string user_word,typeOfError &errorType){
	if(correct_word==user_word){
		errorType=CORRECT;
	}
	else if(correct_word.size()==user_word.size()){
		isSubstitution(correct_word,user_word,errorType);
	}
	else if(correct_word.size()==user_word.size()+1){
		isDeletion(correct_word,user_word,errorType);
	}
	else if(correct_word.size()==user_word.size()-1){
		isInsertion(correct_word,user_word,errorType);
	}
}

void isSubstitution(string correct_word,string user_word,typeOfError &errorType){
	string::size_type i;
	
	for(i=0;i<correct_word.size();++i){
		if(correct_word[i]!=user_word[i])
			break;
	}
	
	//Hello
	//Hillo
	if(correct_word.substr(i+1)==user_word.substr(i+1)){
		errorType=SUBSTITUTION;
	}
	//Hello
	//Helli
	else if(i==correct_word.size()-1){
		errorType=SUBSTITUTION;
	}
	else{
			isTransposition(correct_word,user_word,errorType);
	}
}

void isTransposition(string correct_word,string user_word,typeOfError &errorType){
	string::size_type i;
	
	for(i=0;i<correct_word.size();++i){
		if(correct_word[i]!=user_word[i])
			break;
	}
	//Hello
	//Helol
	if(i==correct_word.size()-2){
		//as transposition can occur with next char only and correct_word[correct_word.size()-1] th element dont have next char
		if((correct_word[i]==user_word[i+1]) && (
		correct_word[i+1]==user_word[i]))
			errorType=TRANSPOSITION;
	}
	//Hello
	//Hlelo
	else if((correct_word[i]==user_word[i+1]) && (
	correct_word[i+1]==user_word[i])){
		if(correct_word.substr(i+2)==user_word.substr(i+2))//check one letter after the mismatch, whether they r same or not
			errorType=TRANSPOSITION;
	}
	else{
		errorType=ERROR;
	}
}

void isDeletion(string correct_word,string user_word,typeOfError &errorType){
	string::size_type i;
	
	for(i=0;i<user_word.size();++i){
		if(correct_word[i]!=user_word[i])
			break;
	}
	//Hello
	//Hell
	if(i==user_word.size()){
		errorType=DELETION;
	}
	//Hello
	//Hllo
	else if(correct_word.substr(i+1)==user_word.substr(i)){
		errorType=DELETION;
	}
	else{
		errorType=DELETION;
	}
}
void isInsertion(string correct_word,string user_word,typeOfError &errorType){
	string::size_type i;
	
	for(i=0;i<correct_word.size();++i){
		if(correct_word[i]!=user_word[i])
			break;
	}
	//Hello
	//Helloo
	if(i==correct_word.size()){
		errorType=INSERTION;
	}
	//Hello
	//Heillo
	else if(correct_word.substr(i)==user_word.substr(i+1)){
		errorType=INSERTION;
	}
	else{
		errorType=ERROR;
	}
}

void displayErrors(typeOfError errorType,int &insCounter,int &delCounter,int &subsCounter,int &transCounter,int &errorCounter,int &correctCounter){
	switch(errorType){
		case INSERTION:cout<<"Insertion Error"<<endl<<endl;
		insCounter++;
		break;
		case DELETION:cout<<"Deletion Error"<<endl<<endl;
		delCounter++;
		break;
		case SUBSTITUTION:cout<<"Substitution Error"<<endl<<endl;
		subsCounter++;
		break;
		case TRANSPOSITION:cout<<"Transposition Error"<<endl<<endl;
		transCounter++;
		break;
		case CORRECT:cout<<"Correct Error"<<endl<<endl;
		correctCounter++;
		break;
		default:cout<<"Badly misspelled"<<endl<<endl;
		errorCounter++;
		break;
	}
}


