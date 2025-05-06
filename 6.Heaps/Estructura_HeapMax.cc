#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

template<typename Type>
class HeapMax{
    private:
        vector<Type> storage_;

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
            int i = storage_.size() - 1;

            while(i > 0 && storage_[parent(i)] < storage_[i]){
                swap(storage_[parent(i)], storage_[i]);
                i = parent(i);
            }
        }

        void heapifyDown(){
            int i = 0, size = storage_.size(), left = leftChild(i), right = rightChild(i);

            while((left < size && storage_[i] < storage_[left]) || (right < size && storage_[i] < storage_[right])){
                int largest = i;

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
        HeapMax(): storage_(vector<Type> ()) {}

        void insert(const Type& elem){
            storage_.push_back(elem);
            heapifyUp();
        }

        Type pop(){
            assert(!empty());

            Type maxElem = storage_.front();
            storage_.front() = storage_.back();
            storage_.pop_back();

            heapifyDown();

            return maxElem;
        }

        Type top() const {
            return storage_.front();
        }

        int size() const {
            return storage_.size();
        }

        bool empty(){
            return storage_.empty();
        }

};

int main(){
    cout << "HeapMax" << endl;

    return 0;
}