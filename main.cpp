#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

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
	
	for(int i = 0; i < int(combined.size()); i++){
		revCombined.push_back(combined[combined.size()-i-1]);
	}
	return revCombined;
}

std::vector<float> mergeSort(std::vector<float> inputArray){//for example [9, 8, 1] as input
	if(inputArray.size() > 1){
		std::vector<float> firstHalf;
		std::vector<float> secondHalf;
		
		for(int i = 0; i < int(inputArray.size())/2; i++){
			firstHalf.push_back(inputArray[i]);
		}//first half = [9, 8]
		
		for(int i = int(inputArray.size())/2; i < int(inputArray.size()); i++){
			secondHalf.push_back(inputArray[i]);
		}//second half = [1]
		
		return merge(mergeSort(firstHalf), mergeSort(secondHalf));
	}
	else{
		return inputArray;
	}
}

std::vector<float> bubbleSort(std::vector<float>& array){
	float tmp;
	int passCounter = 0;//counts how many times no swap is made
	while(passCounter < int(array.size())-1){//when no swaps are made over entire list, list is sorted
		for(int i = 0; i < int(array.size())-1; ++i){
			if(array[i]>array[i+1]){
				tmp = array[i+1];
				array[i+1] = array[i];
				array[i] = tmp;
				passCounter = 0;
			}
			else{
				passCounter++;
			}
		}
	}

	return array;
}

std::vector<float> genFloatVector(int size){
	std::vector<float> output;
	for(int i = 0; i < size; i++){
		output.push_back((float(rand()%1000000)/10)-50000);
	}
	
	return output;
}


int main(){
	int start, end, interval;
	std::cout << "Enter start point: "; std::cin >> start;
	std::cout << "Enter end point: "; std::cin >> end;
	std::cout << "Enter interval: "; std::cin >> interval;
	
	
	for(int size = start; size <= end; size += interval){
		int mergeTimeSum = 0;
		int bubbleTimeSum = 0;
		int iterations = 10;
		for(int i = 0; i < iterations; i++){
			int startTime = 0;
			int endTime = 0;
			std::vector<float> arrayToSort = genFloatVector(size);
			
			startTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
				std::vector<float> bubbleSorted = bubbleSort(arrayToSort);
			endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			bubbleTimeSum += endTime-startTime;
			
			startTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
				std::vector<float> mergeSorted = mergeSort(arrayToSort);
			endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			mergeTimeSum += endTime-startTime;
			
			if(mergeSorted != bubbleSorted){
				std::cout << "Error: Sort error. \n\n";
				return -1;
			}
		}
		
		std::cout << "Sorting " << size << " items:" << std::endl;
		std::cout << "	Bubble Sort Time:   " << bubbleTimeSum/iterations << " μs" << std::endl;
		std::cout << "	Merge  Sort Time:   " << mergeTimeSum/iterations << " μs" << std::endl;
	}
	return 0;
}
