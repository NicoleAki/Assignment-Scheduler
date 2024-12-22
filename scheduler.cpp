#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Assignment {
public:    
    string id;
    int weightage;
    int deadline;
    int execution_time;

    Assignment()
        : id(""), weightage(0), deadline(0), execution_time(0) {}

    Assignment(string id, int weightage, int deadline, int execution_time)
    :id(id),weightage(weightage),deadline(deadline),execution_time(execution_time){}
    
    
    int getPriority() const {
        // Priority based on weightage and then deadline (if weightage is the same)
        return weightage * 1000 + (1000 - deadline); 
    }
};

// Heap to store integers

class Heap {

private:
    vector<int> heap;


    void Heapify_Down(int index){//For when used in building a Max Heap or deleting the root.
        int l=2*index+1; //with index starting from 0 not 1
        int r=l+1;
        int largest; 

        if (l < heap.size() && heap[l]>heap[index]){
            largest=l;   
            
        }
        else{
            largest=index;
        }
        if (r < heap.size() && heap[r]>heap[largest]){
            largest=r;
        }
        if(largest != index){
            swap(heap[index], heap[largest]);
            Heapify_Down(largest);
        }
    }

    void Heapify_Up(int index){//For example when you add an element as a leaf or delete a leaf or internal node
        int parent = (index-1)/2;
        if (index>0 && heap[index]>heap[parent]){
            int temp = heap[parent];
            heap[parent]=heap[index];
            heap[index]=temp;
            Heapify_Up(parent);
        }
    }

public:

    bool isEmpty(){
        return heap.empty();
    }

    /*void Heap_Increase_Key(int heap_size,int val){
        if (val<heap[heap_size]){
            return; //Underflow
        }
        heap[heap_size]=val;
        int parent=(heap_size-1)/2;
        while(heap_size>0 && heap[parent]<heap[heap_size]){
            int temp = heap[parent];// exchange heap[i] with heap[parent]
            heap[parent]=heap[heap_size];
            heap[heap_size]=temp;
            heap_size=(heap_size-1)/2; //assign it the parent index
        }
    }*/

    void insert(int val){
        heap.push_back(val); //instead of heap.size()=heap.size()+1;
        //heap[heap.size()]=-10000;
        Heapify_Up(heap.size() - 1);
    }

    /*void Delete_Max(){
        heap[0]=heap[heap.size()];
        Heapify_Down(0);
    }*/

    int extractMax(){
        if (heap.empty()){
            return -1; //underflow
        }
        int max = heap[0];
        heap[0]=heap.back();
        heap.pop_back(); // instead of heap.size()=heap.size()-1;
        Heapify_Down(0);
        return max;
    }

    int peekMax(){
        if(heap.empty()){
            return -1;
        }
        return heap[0];
    }

    void print() {
        for (int i = 0; i < heap.size(); ++i) {
            std::cout << heap[i] << " ";
        }
        std::cout << std::endl;
    }
};


class AssignmentScheduler {

private: 
    vector<string> executedTasks;
    vector<string> discardedTasks;
    
public:
    void scheduleAssignments(std::vector<Assignment> &assignments) {
        int currentTime = 0; 
        Heap heap;

        unordered_map<int, vector<Assignment>> weightageToAssignments;

        for (const auto& assignment : assignments){
            int priority = assignment.getPriority();
            heap.insert(priority);
            }


        // Process assignments from the heap
        while (!heap.isEmpty()) {
            int priority = heap.extractMax();

            //Find ass corresponding to priority
            auto it = find_if(assignments.begin(), assignments.end(), [priority](const Assignment& a) {
                return a.getPriority() == priority;
            });

            if (it != assignments.end()) {
                Assignment current = *it;

                if (currentTime + current.execution_time <= current.deadline) {
                    executedTasks.push_back("\"" + current.id + "\"");
                    currentTime += current.execution_time;
                } else {
                    discardedTasks.push_back("{\"id\": \"" + current.id + "\", \"reason\": \"Deadline passed\"}");
            }
        }
        }
    }


    void printResults(){
        cout <<"Executed Tasks: [" ;

        for (size_t i = 0; i < executedTasks.size(); ++i){
            cout << executedTasks[i];
            if (i < executedTasks.size() - 1)
                cout << ", ";
        }
        cout << "]\n";
        cout <<"Discarded Tasks: [" ;

        for (size_t i = 0; i < discardedTasks.size(); ++i){
            cout << discardedTasks[i];
            if (i < discardedTasks.size() - 1)
                cout << ", ";
        }
        cout << "]\n";
        
    }
};