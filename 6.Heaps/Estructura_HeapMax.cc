#include <iostream>
#include <cassert>
#include <vector>
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dist(1, 100);

template<typename Type>
class HeapMax{
    private:
        vector<pair<unsigned int, Type>> storage_;

        unsigned int parent(const unsigned int i) const {
            return (i - 1) / 2;
        }

        unsigned int leftChild(const unsigned int i) const {
            return (i * 2) + 1;
        }

        unsigned int rightChild(const unsigned int i) const {
            return (i * 2) + 2;
        }

        void heapifyUp(){
            unsigned int i = storage_.size() - 1;

            while(i > 0 && storage_[parent(i)] < storage_[i]){
                swap(storage_[parent(i)], storage_[i]);
                i = parent(i);
            }
        }

        void heapifyDown(){
            unsigned int i = 0, size = storage_.size(), left = leftChild(i), right = rightChild(i);

            while((left < size && storage_[i] < storage_[left]) || (right < size && storage_[i] < storage_[right])){
                unsigned int largest = i;

                if(left < size && storage_[i] < storage_[left]){
                    largest = left;
                }

                if(right < size && storage_[i] < storage_[right]){
                    largest = right;
                }

                swap(storage_[i],  storage_[largest]);
                
                i = largest;
                left = leftChild(i);
                right = rightChild(i);
            }

        }

    public:
        HeapMax(): storage_(vector<pair<unsigned int, Type>> ()) {}

        void insert(const Type& elem){
            pair<unsigned int, Type> newNode = make_pair(dist(gen) ,elem);
            storage_.push_back(newNode);
            heapifyUp();
        }

        Type pop(){
            assert(!empty());

            pair<unsigned int, Type> maxElem = storage_.front();
            storage_.front() = storage_.back();
            storage_.pop_back();

            heapifyDown();

            return maxElem.second;
        }

        Type top() const {
            return storage_.front().second;
        }

        int size() const {
            return storage_.size();
        }

        bool empty() const {
            return storage_.empty();
        }

};

int main(){
    cout << "HeapMax" << endl;
    vector<int> a = {15, 10, 20, 17, 8, 25, 30};
    HeapMax<int> H;

    for(int i : a){
        //cout << i << endl;
        H.insert(i);
    }

    int size = H.size() - 1;
    for(int i = 0; i < size; i++){
        cout << H.pop() << endl;
    }


    return 0;
}