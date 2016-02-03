//
// Created by Julian  on 30/01/16.
//

#ifndef DATA_BLOCK_TREE_H
#define DATA_BLOCK_TREE_H

#include <queue>
#include <cstdint>

using namespace std; 

//
struct DataBlock
{
	uint8_t data[512];
};

//
struct DataBlockIndex
{
	uint16_t blockIndex;
	uint8_t* ptr;
	uint16_t len;

	void Shrink(uint16_t n)
	{
		this->ptr += n;
		this->len -= n; 
	}

};

//
class FreeDataBlockNode
{
	queue<DataBlockIndex*>* values;

	FreeDataBlockNode* left;
	FreeDataBlockNode* right;

public:

	//--------------------------------------------------------------
	// Name: FreeDataBlockNode
	// Desc: ctor
	//--------------------------------------------------------------
	FreeDataBlockNode(DataBlockIndex* val)
	{
		this->values = new queue<DataBlockIndex*>(); 

		this->left = nullptr; 
		this->right = nullptr; 

		values->push(val); 
	}
	//--------------------------------------------------------------
	// Name: ~FreeDataBlockNode
	// Desc: dtor
	//--------------------------------------------------------------
	~FreeDataBlockNode()
	{
		if (this->left) {
			delete this->left; 
		}
		if (this->right) {
			delete this->right;
		}
	}
	//--------------------------------------------------------------
	// Name: CountNodes
	// Desc: count the number of nodes in the tree
	//--------------------------------------------------------------
	uint32_t CountNodes() const
	{
		uint32_t count = 1; 

		if (this->left != nullptr) {
			count += this->left->CountNodes(); 
		} 

		if (this->right != nullptr) {
			count += this->right->CountNodes(); 
		}

		return count; 
	}
	//---------------------------------------------------------------
	// Name: Depth
	// Desc: depth of the longest branch
	//---------------------------------------------------------------
	uint32_t Depth() const
	{ 
		uint8_t depth = 1; 
		uint8_t lDepth = 0; 
		uint8_t rDepth = 0; 

		if (this->left != nullptr) {
			lDepth = this->left->Depth(); 
		}

		if (this->right != nullptr) {
			rDepth = this->right->Depth(); 
		}

		return 1 + max(lDepth, rDepth); 
	}
	//---------------------------------------------------------------
	// Name: Value
	// Desc: 
	//---------------------------------------------------------------
	uint32_t Value() const
	{
		return this->values->front()->len; 
	}
	//---------------------------------------------------------------
	// Name: Insert
	// Desc: insert at this node or pass down to lower nodes
	//---------------------------------------------------------------
	void Insert(DataBlockIndex* val)
	{
		if (val->len <= 0 || val == nullptr) {
			return; 
		}

		if (val->len < this->values->front()->len) {
			if (this->left) {
				this->left->Insert(val);
			} else {
				this->left = new FreeDataBlockNode(val);
			}

			return;
		}

		if (val->len > this->values->front()->len) {

			if (this->right) {
				this->right->Insert(val);
			} else {
				this->right = new FreeDataBlockNode(val);
			}
			return;
		}


		// we're supposed to be here
		this->values->push(val); 
	}
	//---------------------------------------------------------------
	// Name: Allocate
	// Desc: if I'm big enough to allocate size-bytes AND my children aren't then 
	//       allocate here, otherwise pass it down to appropriate child
	//---------------------------------------------------------------
	void* Allocate(uint16_t size)
	{
		// too big to allocate here?
		if (size > this->values->front()->len) {
			return nullptr; 
		}

		// try to alloc on the smaller left side
		auto alloc = this->left->Allocate(size); 

		if (alloc != nullptr) {
			return alloc; 
		}

		// try to alloc on the smaller right side
		alloc = this->right->Allocate(size); 

		if (alloc != nullptr) {
			return alloc; 
		}

		// we gotta alloc here 
		auto dataBlockIndex = this->values->front(); 

		alloc = dataBlockIndex->ptr; 
		dataBlockIndex->Shrink(size); 
		
		// if we allocated ourselves smaller than one of our children then we need to swap
		if (this->values->size() == 1) {
			BalanceTree(); 
		} else {

			this->Insert(dataBlockIndex);
			this->values->pop();
		}

		return alloc; 
	}
	//---------------------------------------------------------------
	// Name: BalanceTree
	// Desc: 
	//---------------------------------------------------------------
	void BalanceTree()
	{		
		if (this->values->size() > 1) {
			return; 
		}

		auto dataBlockIndex = this->values->front();

		if (dataBlockIndex->len < this->left->Value()) {
			// we have to swap with left 
			this->Swap(this, this->left); 
		} 

		if (dataBlockIndex->len < this->right->Value()) {
			// we have to swap with right
			this->Swap(this, this->right); 
		}
	}
	//---------------------------------------------------------------
	// Name: Swap
	// Desc: 
	//---------------------------------------------------------------
	static void Swap(FreeDataBlockNode* a, FreeDataBlockNode* b)
	{
		auto tempValuesA = a->values; 
		auto tempLeftA = a->left; 
		auto tempRightA = a->right; 

		a->values = b->values; 
		a->left = b->left; 
		a->right = b->right; 

		b->values = tempValuesA; 
		b->left = tempLeftA; 
		b->right = tempRightA; 
	}
};

#endif // DATA_BLOCK_TREE_H