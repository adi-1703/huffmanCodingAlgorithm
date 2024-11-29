#include<bits/stdc++.h>
using namespace std;

long long totalTableSize = 0;
long long messageSize = 0;

map<char,string> huffmanTable;


/*  Instead of a class in the priority queue we could have used
    pair<int,char> but this would be wrong cuz we need to make
    a binary tree and its best to use a class or struct to 
    represent the node of a binary tree.
    Huffman tree is a full binary tree.
*/
class Node{
    public:
    char data;
    long long frequency;
    Node *left,*right; // For left and right child

    // Constructor
    Node(int data,long long frequency){
        this->data=data;
        this->frequency=frequency;
        left=nullptr;
        right=nullptr;
    }
};

class cmp{
    public:
    bool operator()(Node *a,Node *b){
        return a->frequency>b->frequency;
    }   
};

// Print Huffman code
void printHuffmanCodes(Node *root,string str,vector<char> &arr,vector<int> &freq){
    // Traverse the tree until leaf node is found
    if(root==nullptr)return;
    if(root->data != '$'){
        // cout<<root->data<<" : "<<str<<endl;
        huffmanTable[root->data]=str;
        totalTableSize += str.size();
        messageSize += (str.size() * 1LL * freq[(int)(root->data - 'a')]);
        return;
    }
    printHuffmanCodes(root->left,str+"0",arr,freq);
    printHuffmanCodes(root->right,str+"1",arr,freq);
}


// Make Huffman Tree
void huffmanCodes(vector<char> &arr,vector<int> &freq,int n){
    // Using this priority Queue we will be able to get smallest node in O(log(n)) time
    priority_queue< Node* , vector<Node*>,cmp> minHeap;
    for(int i=0;i<n;i++){
        // Making Leaf Nodes
        Node *node= new Node(arr[i],freq[i]);
        minHeap.push(node);
    }
    
    while(minHeap.size()>1){
        Node *lChild=minHeap.top();minHeap.pop();
        Node *rChild=minHeap.top();minHeap.pop();
        Node *temp= new Node('$',lChild->frequency+rChild->frequency);
        // Merging the two smallest leaf nodes
        temp->left=lChild;
        temp->right=rChild;
        minHeap.push(temp);
    }

    string str="";
    Node* root=minHeap.top();
    printHuffmanCodes(root,str,arr,freq);

}

int main(){
    // Sample array used - I used all 26 char
    int n=26; // Using all lower case characters
    totalTableSize = (26*8); // Store ASCII codes for each character for ex: A = 65 = 01000001
    vector<char> arr(26);
    for(int i=0;i<26;i++){
        arr[i]=(char)('a'+ i );
    }
    int mn=50,mx=100;
    long long initialSize = 0;
    vector<int> freq(26);
    for(int i=0;i<26;i++){
        int x=(rand()) % (mx-mn) + (mn);  // Make frequency of each character come within [100,1e5)
        freq[i]=x;
        initialSize += (8*x);
    }
    // for(auto &val:arr)cout<<val<<" ";cout<<endl;
    // for(auto &val:freq)cout<<val<<" ";cout<<endl;


    // This was the input generated during the test
    // a b c d e f g h i j k l m n o p q r s t u v w x y z 
    // 91 67 84 50 69 74 78 58 62 64 55 95 81 77 61 91 95 92 77 86 91 54 52 53 92 82 


    huffmanCodes(arr,freq,n);
    long long finalTotalSize=totalTableSize + messageSize;
    long long diffInSize=initialSize- finalTotalSize;
    double compressionPercentage = ((double)1 * diffInSize ) / initialSize;
    cout<< compressionPercentage* 100<<endl;
    for(auto &val:huffmanTable){
        cout<<val.first<<" : "<<val.second<<endl;
    }
    // CompressionRatio came out to be 38.95 %  and Huffman Table looked like 
    // a : 11111
    // b : 10101
    // c : 11101
    // d : 01100
    // e : 10110
    // f : 10111
    // g : 11010
    // h : 10001
    // i : 10011
    // j : 10100
    // k : 10000
    // l : 0100
    // m : 11011
    // n : 11000
    // o : 10010
    // p : 0000
    // q : 0101
    // r : 0011
    // s : 11001
    // t : 11110
    // u : 0001
    // v : 01111
    // w : 01101
    // x : 01110
    // y : 0010
    // z : 11100
}