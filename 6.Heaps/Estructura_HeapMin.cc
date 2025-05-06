#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

template<typename Type>
class HeapMin{
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
            unsigned int i = storage_.size() - 1;

            while(i > 0 && storage_[parent(i)] > storage_[i]){
                swap(storage_[parent(i)], storage_[i]);
                i = parent(i);
            }
        }

        void heapifyDown(){
            unsigned int i = 0, size = storage_.size(), left = leftChild(i), right = rightChild(i);

            while((left < size && storage_[i] > storage_[left]) || (right < size && storage_[i] > storage_[right])){
                unsigned int smallest = i;

                if(left < size && storage_[i] > storage_[left]){
                    smallest = left;
                }

                if(right < size && storage_[i] > storage_[right]){
                    smallest = right;
                }

                swap(storage_[i],  storage_[smallest]);
                
                i = smallest;
                left = leftChild(i);
                right = rightChild(i);
            }

        }

    public:
        HeapMin(): storage_(vector<Type> ()) {}

        void insert(const Type& elem){
            storage_.push_back(elem);
            heapifyUp();
        }

        Type pop(){
            assert(!empty());

            Type minElem = storage_.front();
            storage_.front() = storage_.back();
            storage_.pop_back();

            heapifyDown();

            return minElem;
        }

        Type top() const {
            return storage_.front();
        }

        int size() const {
            return storage_.size();
        }

        bool empty() const {
            return storage_.empty();
        }

};

int main(){
    cout << "HeapMin" << endl;

    return 0;
}