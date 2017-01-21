#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector<float> merge(vector<float> firstHalf, vector<float> secondHalf){
	vector<float> combined;
	for(int i = firstHalf.size() + secondHalf.size(); i > 0;  i--){//merge two vectors
		if(firstHalf.back() > secondHalf.back() && !firstHalf.empty()){
			combined.push_back(firstHalf.back());
			firstHalf.pop_back();
		}else if(!secondHalf.empty()){
			combined.push_back(secondHalf.back());
			secondHalf.pop_back();
		}
	}
	vector<float> revCombined;//reverse merged vectors. Vectors don't have pop_front and I didn't want to use lists.
	
	for(int i = 0; i < combined.size(); i++){
		revCombined.push_back(combined[combined.size()-i-1]);
	}
	return revCombined;
}

vector<float> mergeSort(vector<float> &inputArray){//for example [9, 8, 1] as input
	if(inputArray.size() > 1){
		vector<float> firstHalf;
		vector<float> secondHalf;
		
		for(int i = 0; i < inputArray.size()/2; i++){//auto round the input array because size() returns int
			firstHalf.push_back(inputArray[i]);
		}//first half = [9, 8]
		
		for(int i = inputArray.size()/2; i < inputArray.size(); i++){
			secondHalf.push_back(inputArray[i]);
		}//second half = [1]
		
		return merge(mergeSort(firstHalf), mergeSort(secondHalf));
	}
	else{
		return inputArray;
	}
}





vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while(getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}
				  
	return internal;
}
vector<float> floatVectorInput(){
	string inputString;
	getline(cin, inputString);

	vector<string> stringArray = split(inputString, ' ');

	vector<float> array; 
	for(int i = 0; i < stringArray.size(); i++){
		array.push_back(stof(stringArray[i]));
	}
	return array;	
}


int main(){
	cout << "Array to sort (separate by spaces): " << endl;
	vector<float> inputArray = floatVectorInput();

	vector<float> sorted = mergeSort(inputArray);
	
	cout << endl << "Sorted Array:" << endl;	
	for(int i = 0; i < sorted.size(); i++){
		cout << sorted[i];
		if(i == sorted.size()-1){
			cout << endl << endl;
		}else{
			cout << ", ";
		}
	}
	return 0;
}
