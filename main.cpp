#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::vector<float> merge(std::vector<float> firstHalf, std::vector<float> secondHalf){
	std::vector<float> combined;
	
	for(int i = firstHalf.size() + secondHalf.size(); i > 0;  i--){//merge two vectors
		if(!firstHalf.empty() && !secondHalf.empty() && firstHalf.back() > secondHalf.back() ){
			combined.push_back(firstHalf.back());
			firstHalf.pop_back();
		}
		else if(!firstHalf.empty() && !secondHalf.empty() && firstHalf.back() <= secondHalf.back() ){
			combined.push_back(secondHalf.back());
			secondHalf.pop_back();
		}
		else if(!firstHalf.empty() && secondHalf.empty()){
			combined.push_back(firstHalf.back());
			firstHalf.pop_back();
		}
		else if(firstHalf.empty() && !secondHalf.empty()){
			combined.push_back(secondHalf.back());
			secondHalf.pop_back();
		}
	}
	
	std::vector<float> revCombined;//reverse merged vectors. Vectors don't have pop_front and I didn't want to use lists.
	
	for(int i = 0; i < combined.size(); i++){
		revCombined.push_back(combined[combined.size()-i-1]);
	}
	return revCombined;
}

std::vector<float> mergeSort(std::vector<float> inputArray){//for example [9, 8, 1] as input
	if(inputArray.size() > 1){
		std::vector<float> firstHalf;
		std::vector<float> secondHalf;
		
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


std::vector<float> floatVectorInput(){
	std::string inputString;
    getline(std::cin, inputString);
    std::vector<float> array;
    std::istringstream iss(inputString);
    float val;
    while(iss >> val){
        array.push_back(val);
    }
    return array;  	
}


int main(){
	std::cout << "Array to sort (separate by spaces): " << std::endl;
	std::vector<float> arrayToSort = mergeSort(floatVectorInput());
	
	std::cout << std::endl << "Sorted Array:" << std::endl;	
	for(int i = 0; i < arrayToSort.size(); i++){
		std::cout << arrayToSort[i];
		if(i == arrayToSort.size()-1){
			std::cout << std::endl << std::endl;
		}else{
			std::cout << ", ";
		}
	}
	return 0;
}
