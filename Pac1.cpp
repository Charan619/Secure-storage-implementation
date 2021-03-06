#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include<bits/stdc++.h>
using namespace std;

#define MAX 50

struct Node {
    char data;
    struct Node *left, *right;
};

struct Node* newNode(char key)
{
    struct Node* temp = new Node;
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
};

void insert(struct Node* temp, char key)
{
    queue<struct Node*> q;
    q.push(temp);

    // Do level order traversal until we find
    // an empty place.
    while (!q.empty()) {
        struct Node* temp = q.front();
        q.pop();

        if (!temp->left) {
            temp->left = newNode(key);
            break;
        } else
            q.push(temp->left);

        if (!temp->right) {
            temp->right = newNode(key);
            break;
        } else
            q.push(temp->right);
    }
}

// function to print the zigzag traversal
void zizagtraversal(struct Node* root,char str[100])
{
    int i=0;
    // if null then return
    if (!root)
        return;

    // declare two stacks
    stack<struct Node*> currentlevel;
    stack<struct Node*> nextlevel;

    // push the root
    currentlevel.push(root);

    // check if stack is empty
    bool lefttoright = true;
    while (!currentlevel.empty())
    {

        // pop out of stack
        struct Node* temp = currentlevel.top();
        currentlevel.pop();

        // if not null
        if (temp)
        {

            // print the data in it
            str[i]=temp->data;
            i++;
            cout << temp->data << " ";

            // store data according to current
            // order.
            if (lefttoright) {
                if (temp->left)
                    nextlevel.push(temp->left);
                if (temp->right)
                    nextlevel.push(temp->right);
            }
            else {
                if (temp->right)
                    nextlevel.push(temp->right);
                if (temp->left)
                    nextlevel.push(temp->left);
            }
        }

        if (currentlevel.empty()) {
            lefttoright = !lefttoright;
            swap(currentlevel, nextlevel);
        }
    }
    str[i]='\0';

}

void rotatediag(int ar[][4])
{
	int t1, t2, t3, t4;
	t1 = ar[0][0];
	t2 = ar[0][3];
	t3 = ar[3][3];
	t4 = ar[3][0];
	ar[0][3] = t1;
	ar[3][3] = t2;
	ar[3][0] = t3;
	ar[0][0] = t4;
}

void addroundkey(int ar[][4])
{
	if(ar[0][1]==1)
	{
		ar[0][1]=0;
	}
	else
	{
		ar[0][1]=1;
	}
	if(ar[1][0]==1)
	{
		ar[1][0]=0;
	}
	else
	{
		ar[1][0]=1;
	}
	if(ar[1][2]==1)
	{
		ar[1][2]=0;
	}
	else
	{
		ar[1][2]=1;
	}
	if(ar[1][1]==1)
	{
		ar[1][1]=0;
	}
	else
	{
		ar[1][1]=1;
	}
	if(ar[2][1]==1)
	{
		ar[2][1]=0;
	}
	else
	{
		ar[2][1]=1;
	}
	if(ar[0][3]==1)
	{
		ar[0][3]=0;
	}
	else
	{
		ar[0][3]=1;
	}
	if(ar[3][3]==1)
	{
		ar[3][3]=0;
	}
	else
	{
		ar[3][3]=1;
	}
}

void shiftrows(int ar[][4])
{
	int j=0, i=0;
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			int temp;
			temp = ar[i][j];
			ar[i][j] = ar[i+1][j];
			ar[i+1][j] = temp;
		}
	}
}


int numberOfPointers;

struct Block
{
    //number of nodes
    int tNodes;
    //for parent Block and index
    Block *parentBlock;
    //values
    int value[MAX];
    char *str[MAX];
    //child Blocks
    Block *childBlock[MAX];
    Block()
    { //constructor to initialize a block
        tNodes = 0;
        parentBlock = NULL;
        for(int i=0; i<MAX; i++)
        {

            str[i]=NULL;
            value[i] = INT_MAX;
            childBlock[i] = NULL;
        }
    }
};
//declare root Block
Block *rootBlock = new Block();

//function to split the leaf nodes
void splitLeaf(Block *curBlock){
    int x, i, j;

    //split the greater half to the left when numberOfPointer is odd
    //else split equal equal when numberOfPointer is even
    if(numberOfPointers%2)
        x = (numberOfPointers+1)/2;
    else x = numberOfPointers/2;

    //we don't declare another block for leftBlock, rather re-use curBlock as leftBlock and
    //take away the right half values to the rightBlock
    Block *rightBlock = new Block();

    //so leftBlock has x number of nodes
    curBlock->tNodes = x;
    //and rightBlock has numberOfPointers-x
    rightBlock->tNodes = numberOfPointers-x;
    //so both of them have their common parent [even parent may be null, so both of them will have null parent]
    rightBlock->parentBlock = curBlock->parentBlock;

    for(i=x, j=0; i<numberOfPointers; i++, j++){
        //take the right-half values from curBlocks and put in the rightBlock
        rightBlock->value[j] = curBlock->value[i];
        rightBlock->str[j] = curBlock->str[i];
        //and erase right-half values from curBlock to make it real leftBlock
        //so that it does not contain all values only contains left-half values
        curBlock->value[i] = INT_MAX;
        curBlock->str[i] = NULL;
    }
    //for splitting the leaf blocks we copy the first item from the rightBlock to their parentBlock
    //and val contains that value
    int val = rightBlock->value[0];
    char *sptr=rightBlock->str[0];
    //if the leaf itself is a parent then
    if(curBlock->parentBlock==NULL){
        //it has null parent, so create a new parent
        Block *parentBlock = new Block();
        //and new parent should have a null parent
        parentBlock->parentBlock = NULL;
        //new parent will have only one member
        parentBlock->tNodes=1;
        //and that member is val
        parentBlock->value[0] = val;
        parentBlock->str[0] = sptr;
        //so the parent has two child, so assign them (don't forget curBlock is actually the leftBlock)
        parentBlock->childBlock[0] = curBlock;
        parentBlock->childBlock[1] = rightBlock;
        //their parent of the left and right blocks is no longer null, so assign their parent
        curBlock->parentBlock = rightBlock->parentBlock = parentBlock;
        //from now on this parentBlock is the rootBlock
        rootBlock = parentBlock;
        return;
    }
    else{   //if the splitted leaf block is not rootBlock then

        // we have to put the val and assign the rightBlock to the right place in the parentBlock
        // so we go to the parentBlock and from now we consider the curBlock as the parentBlock of the splitted Block

        curBlock = curBlock->parentBlock;

        //for the sake of insertNodeion sort to put the rightBlock and val in the exact position
        //of th parentBlock [here curBlock] take a new child block and assign rightBlock to it
        Block *newChildBlock = new Block();
        newChildBlock = rightBlock;

        //simple insertion sort to put val at the exact position of values[] in the parentBlock [here curBlock]

        for(i=0; i<=curBlock->tNodes; i++){
            if(val < curBlock->value[i]){
                swap(curBlock->str[i],sptr);
                swap(curBlock->value[i], val);
            }
        }

        //after putting val number of nodes gets increase by one
        curBlock->tNodes++;

         //simple insertNodeion sort to put rightBlock at the exact position
         //of childBlock[] in the parentBlock [here curBlock]

        for(i=0; i<curBlock->tNodes; i++){
            if(newChildBlock->value[0] < curBlock->childBlock[i]->value[0]){
                swap(curBlock->childBlock[i], newChildBlock);
            }
        }
        curBlock->childBlock[i] = newChildBlock;

        //we reordered some blocks and pointers, so for the sake of safety
        //all childBlocks' should have their parent updated
        for(i=0;curBlock->childBlock[i]!=NULL;i++){
            curBlock->childBlock[i]->parentBlock = curBlock;
        }
    }

}

//function to split the non leaf nodes
void splitNonLeaf(Block *curBlock){
    int x, i, j;

    //split the less half to the left when numberOfPointer is odd
    //else split equal equal when numberOfPointer is even.  n/2 does it nicely for us

    x = numberOfPointers/2;

    //declare rightBlock and we will use curBlock as the leftBlock
    Block *rightBlock = new Block();

    //so leftBlock has x number of nodes
    curBlock->tNodes = x;
    //rightBlock has numberOfPointers-x-1 children, because we won't copy and paste
    //rather delete and paste the first item of the rightBlock
    rightBlock->tNodes = numberOfPointers-x-1;
    //both children have their common parent
    rightBlock->parentBlock = curBlock->parentBlock;


    for(i=x, j=0; i<=numberOfPointers; i++, j++){
        //copy the right-half members to the rightBlock
        rightBlock->value[j] = curBlock->value[i];
        rightBlock->str[j] = curBlock->str[i];
        //and also copy their children
        rightBlock->childBlock[j] = curBlock->childBlock[i];
        //erase the right-half values from curBlock to make it perfect leftBlock
        //which won't contain only left-half values and their children
        curBlock->value[i] = INT_MAX;
        curBlock->str[j]= NULL;
        //erase all the right-half childBlocks from curBlock except the x one
        //because if left child has 3 nodes then it should have 4 childBlocks, so don't delete that child
        if(i!=x)curBlock->childBlock[i] = NULL;
    }

    //we will take a copy of the first item of the rightBlock
    //as we will delete that item later from the list
    int val = rightBlock->value[0];
    char* sptr=rightBlock->str[0];
    //just right-shift value[] and childBlock[] by one from rightBlock
    //to have no repeat of the first item for non-leaf Block
    memcpy(&rightBlock->str,&rightBlock->str[1], sizeof(char*)*(rightBlock->tNodes+1));
    memcpy(&rightBlock->value, &rightBlock->value[1], sizeof(int)*(rightBlock->tNodes+1));
    memcpy(&rightBlock->childBlock, &rightBlock->childBlock[1], sizeof(rootBlock)*(rightBlock->tNodes+1));

    //we reordered some values and positions so don't forget
    //to assign the children's exact parent

    for(i=0;curBlock->childBlock[i]!=NULL;i++){
        curBlock->childBlock[i]->parentBlock = curBlock;
    }
    for(i=0;rightBlock->childBlock[i]!=NULL;i++){
        rightBlock->childBlock[i]->parentBlock = rightBlock;
    }

    //if the splitted block itself a parent
    if(curBlock->parentBlock==NULL){
        //create a new parent
        Block *parentBlock = new Block();
        //parent should have a null parent
        parentBlock->parentBlock = NULL;
        //parent will have only one node
        parentBlock->tNodes=1;
        //the only value is the val
        parentBlock->value[0] = val;
        //it has two children, leftBlock and rightBlock
        parentBlock->childBlock[0] = curBlock;
        parentBlock->childBlock[1] = rightBlock;

        //and both rightBlock and leftBlock has no longer null parent, they have their new parent
        curBlock->parentBlock = rightBlock->parentBlock = parentBlock;

        //from now on this new parent is the root parent
        rootBlock = parentBlock;
        return;
    }
    else{   //if the splitted leaf block is not rootBlock then

        // we have to put the val and assign the rightBlock to the right place in the parentBlock
        // so we go to the parentBlock and from now we consider the curBlock as the parentBlock of the splitted Block
        curBlock = curBlock->parentBlock;

        //for the sake of insertNodeion sort to put the rightBlock and val in the exact position
        //of th parentBlock [here curBlock] take a new child block and assign rightBlock to it

        Block *newChildBlock = new Block();
        newChildBlock = rightBlock;

        //simple insertion sort to put val at the exact position of values[] in the parentBlock [here curBlock]


        for(i=0; i<=curBlock->tNodes; i++){
            if(val < curBlock->value[i]){
                swap(curBlock->str[i], sptr);
                swap(curBlock->value[i], val);
            }
        }

        //after putting val number of nodes gets increase by one
        curBlock->tNodes++;

        //simple insertNodeion sort to put rightBlock at the exact position
         //of childBlock[] in the parentBlock [here curBlock]

        for(i=0; i<curBlock->tNodes; i++){
            if(newChildBlock->value[0] < curBlock->childBlock[i]->value[0]){
                swap(curBlock->childBlock[i], newChildBlock);
            }
        }
        curBlock->childBlock[i] = newChildBlock;

        //we reordered some blocks and pointers, so for the sake of safety
        //all childBlocks' should have their parent updated
         for(i=0;curBlock->childBlock[i]!=NULL;i++){
            curBlock->childBlock[i]->parentBlock = curBlock;
        }
    }

}

void insertNode(Block *curBlock, int val,char* sptr){

    char* tmp;
    for(int i=0; i<=curBlock->tNodes; i++)
    {
        if(val < curBlock->value[i] && curBlock->childBlock[i]!=NULL)
        {
                cout<<"nonleaf ";
                insertNode(curBlock->childBlock[i], val,sptr);
                if(curBlock->tNodes==numberOfPointers)
                    splitNonLeaf(curBlock);
                return;
        }
        else if(val < curBlock->value[i] && curBlock->childBlock[i]==NULL)
        {
            tmp=*&curBlock->str[i];
            curBlock->str[i]=*&sptr;
            sptr=*&tmp;

            //swap(curBlock->str[i],*& sptr);
            //cout<<sptr<<" "<<" - ";


            cout<<" yo ";
            //cout<<curBlock->str[i];
            swap(curBlock->value[i], val);
            cout<<curBlock->tNodes;

            //swap(curBlock->childBlock[i], newChildBlock);
            if(i==curBlock->tNodes)
            {
                    curBlock->tNodes++;
                    break;
            }
        }
    }

    if(curBlock->tNodes==numberOfPointers){

            splitLeaf(curBlock);
    }
}


void redistributeBlock(Block *leftBlock, Block *rightBlock, bool isLeaf, int posOfLeftBlock, int whichOneisCurBlock){

    //re-distribution will affect the first value of the rightBlock, so remember it
    //for later replacement of the copy of this value somewhere in ancestor Block
    int PrevRightFirstVal = rightBlock->value[0];
    char* PrevRightFirstStr = rightBlock->str[0];

    if(whichOneisCurBlock==0){ //leftBlock is curBlock

        //if the blocks are not leaf node
        if(!isLeaf){
            //bring down the value from which it is left child in parentBlock
            leftBlock->value[leftBlock->tNodes] = leftBlock->parentBlock->value[posOfLeftBlock];
            //the right child of newly added value should be the left child of first value of rightBlock
            leftBlock->childBlock[leftBlock->tNodes+1] = rightBlock->childBlock[0];
            //increase leftBlock's number of nodes by one
            leftBlock->tNodes++;
            //send up a the first value of the rightBlock to the parentBlock
            leftBlock->parentBlock->str[posOfLeftBlock] = rightBlock->str[0];
            leftBlock->parentBlock->value[posOfLeftBlock] = rightBlock->value[0];
            //shift left by one in rightBlock
            memcpy(&rightBlock->str[0],&rightBlock->str[1], sizeof(char*)*(rightBlock->tNodes+1));
            memcpy(&rightBlock->value[0], &rightBlock->value[1], sizeof(int)*(rightBlock->tNodes+1));
            memcpy(&rightBlock->childBlock[0], &rightBlock->childBlock[1], sizeof(rootBlock)*(rightBlock->tNodes+1));
            rightBlock->tNodes--;

        }
        else
        {
            //borrow the first value of rightBlock to the last position of leftBlock
            leftBlock->str[leftBlock->tNodes] = rightBlock->str[0];
            leftBlock->value[leftBlock->tNodes] = rightBlock->value[0];
            leftBlock->tNodes++;
            //shift by one node to left of the rightBlock

            memcpy(&rightBlock->str[0],&rightBlock->str[1], sizeof(char*)*(rightBlock->tNodes+1));
            memcpy(&rightBlock->value[0], &rightBlock->value[1], sizeof(int)*(rightBlock->tNodes+1));
            //decrease number of nodes by one
            rightBlock->tNodes--;

            leftBlock->parentBlock->value[posOfLeftBlock] = rightBlock->value[0];
        }



    }else{ //rightBlock is curBlock

        if(!isLeaf){

            //shift right by one in rightBlock so that first position becomes free
            memcpy(&rightBlock->str[1],&rightBlock->str[0], sizeof(char*)*(rightBlock->tNodes+1));
            memcpy(&rightBlock->value[1], &rightBlock->value[0], sizeof(int)*(rightBlock->tNodes+1));
            memcpy(&rightBlock->childBlock[1], &rightBlock->childBlock[0], sizeof(rootBlock)*(rightBlock->tNodes+1));
            //bring down the value from which it is left child in parentBlock to first pos of rightBlock
            rightBlock->value[0] = leftBlock->parentBlock->value[posOfLeftBlock];
            //and the left child of the newly first value of right child will be the last child of leftBlock
            rightBlock->childBlock[0] = leftBlock->childBlock[leftBlock->tNodes];

            rightBlock->tNodes++;

            //send up a the last value of the leftBlock to the parentBlock
            leftBlock->parentBlock->value[posOfLeftBlock] = leftBlock->value[leftBlock->tNodes-1];
            //erase the last element and pointer of leftBlock
            leftBlock->value[leftBlock->tNodes-1] = INT_MAX;
            leftBlock->childBlock[leftBlock->tNodes] = NULL;
            leftBlock->tNodes--;

        }else{

            //shift by one node to right of the rightBlock so that we can free the first position
            memcpy(&rightBlock->str[1],&rightBlock->str[0], sizeof(char*)*(rightBlock->tNodes+1));
            memcpy(&rightBlock->value[1], &rightBlock->value[0], sizeof(int)*(rightBlock->tNodes+1));
            //borrow the last value of leftBlock to the first position of rightBlock
            rightBlock->str[0] = leftBlock->str[leftBlock->tNodes-1];
            rightBlock->value[0] = leftBlock->value[leftBlock->tNodes-1];
            //increase number of nodes by one
            rightBlock->tNodes++;

            leftBlock->str[leftBlock->tNodes-1] = NULL;
            leftBlock->value[leftBlock->tNodes-1] = INT_MAX;
            leftBlock->tNodes--;

            leftBlock->parentBlock->str[posOfLeftBlock] = rightBlock->str[0];
            leftBlock->parentBlock->value[posOfLeftBlock] = rightBlock->value[0];
        }
    }
}

void mergeBlock(Block *leftBlock, Block *rightBlock, bool isLeaf, int posOfRightBlock){

    //cout << "leftBlock " << leftBlock->value[0] << " rightBlock " << rightBlock->value[0] << endl;
    //cout << "size " << leftBlock->tNodes << " size " << rightBlock->tNodes << endl;
    if(!isLeaf)
    {
        leftBlock->str[leftBlock->tNodes] = leftBlock->parentBlock->str[posOfRightBlock-1];
        leftBlock->value[leftBlock->tNodes] = leftBlock->parentBlock->value[posOfRightBlock-1];
        leftBlock->tNodes++;
    }

    memcpy(&leftBlock->str[leftBlock->tNodes], &rightBlock->str[0], sizeof(char*)*(rightBlock->tNodes+1));
    memcpy(&leftBlock->value[leftBlock->tNodes], &rightBlock->value[0], sizeof(int)*(rightBlock->tNodes+1));
    memcpy(&leftBlock->childBlock[leftBlock->tNodes], &rightBlock->childBlock[0], sizeof(rootBlock)*(rightBlock->tNodes+1));


    leftBlock->tNodes += rightBlock->tNodes;


    //cout << "before: " << leftBlock->parentBlock->value[1] << endl;
    memcpy(&leftBlock->parentBlock->str[posOfRightBlock-1], &leftBlock->parentBlock->str[posOfRightBlock], sizeof(char*)*(leftBlock->parentBlock->tNodes+1));
    memcpy(&leftBlock->parentBlock->value[posOfRightBlock-1], &leftBlock->parentBlock->value[posOfRightBlock], sizeof(int)*(leftBlock->parentBlock->tNodes+1));
    memcpy(&leftBlock->parentBlock->childBlock[posOfRightBlock], &leftBlock->parentBlock->childBlock[posOfRightBlock+1], sizeof(rootBlock)*(leftBlock->parentBlock->tNodes+1));
    //cout << "after merging " << leftBlock->parentBlock->childBlock[posOfRightBlock-2]->value[0] << " and ";// << leftBlock->parentBlock->childBlock[posOfRightBlock]->value[0] << endl;
    leftBlock->parentBlock->tNodes--;

    //we reordered some blocks and pointers, so for the sake of safety
    //all childBlocks' should have their parent updated
     for(int i=0;leftBlock->childBlock[i]!=NULL;i++){
        leftBlock->childBlock[i]->parentBlock = leftBlock;
    }



}
bool dataFound;
void deleteNode(Block *curBlock, int val, int curBlockPosition){

     //to check if the current block is a leaf or not
     bool isLeaf;
     if(curBlock->childBlock[0]==NULL)
        isLeaf = true;
     else isLeaf = false;

    //left most value could be changed due to merge or re-distribution later,
    //so keep it to replace it's copy from it's ancestor
    int prevLeftMostVal = curBlock->value[0];



     for(int i=0;dataFound==false &&  i<=curBlock->tNodes; i++){
        if(val < curBlock->value[i] && curBlock->childBlock[i] != NULL){
            deleteNode(curBlock->childBlock[i], val, i);

        }
        //if we could find the target value at any leafBlock then
        else if(val == curBlock->value[i] && curBlock->childBlock[i] == NULL){

            //delete the node by shifting all values and pointers  by one to the left
            memcpy(&curBlock->str[i], &curBlock->str[i+1], sizeof(char*)*(curBlock->tNodes+1));
            memcpy(&curBlock->value[i], &curBlock->value[i+1], sizeof(int)*(curBlock->tNodes+1));
            //decrease number of nodes by one
            curBlock->tNodes--;
            dataFound = true;
            break;
        }
     }

    //if the root is the only leaf
     if(curBlock->parentBlock == NULL && curBlock->childBlock[0] == NULL){
        return;
     }


  //if the curBlock is rootBlock and it has one pointers only
    if(curBlock->parentBlock==NULL && curBlock->childBlock[0] != NULL && curBlock->tNodes == 0){
        rootBlock = curBlock->childBlock[0];
        rootBlock->parentBlock = NULL;
        return;
    }


    //now check if the curBlock has less than half of the number of maximum node
    //cout << curBlockPosition << endl;
    //if less than half we will try to re-distribute first

    //cout << curBlock->childBlock[0]->value[0] << " "<< curBlockPosition << endl;
    if(isLeaf && curBlock->parentBlock!=NULL){

        if(curBlockPosition==0){
            Block *rightBlock = new Block();
            rightBlock = curBlock->parentBlock->childBlock[1];

            //if we the right one has more than half nodes of maximum capacity than re-distribute
            if(rightBlock!=NULL && rightBlock->tNodes > (numberOfPointers+1)/2){

                    redistributeBlock(curBlock, rightBlock, isLeaf, 0, 0);
            }
            //else there is nothing to re-distribute, so we can merge them
            else if (rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers){

                    mergeBlock(curBlock, rightBlock, isLeaf, 1);
            }
        }

        else{


            Block *leftBlock = new Block();
            Block *rightBlock = new Block();


            leftBlock = curBlock->parentBlock->childBlock[curBlockPosition-1];

            rightBlock = curBlock->parentBlock->childBlock[curBlockPosition+1];


            //if we see that left one has more than half nodes of maximum capacity then try to re-distribute
            if(leftBlock!=NULL && leftBlock->tNodes > (numberOfPointers+1)/2){
                 redistributeBlock(leftBlock, curBlock, isLeaf, curBlockPosition-1, 1);
            }
            else if(rightBlock!=NULL && rightBlock->tNodes > (numberOfPointers+1)/2){
                redistributeBlock(curBlock, rightBlock, isLeaf, curBlockPosition, 0);
            }
            else if (leftBlock!=NULL && curBlock->tNodes+leftBlock->tNodes < numberOfPointers){
                mergeBlock(leftBlock, curBlock, isLeaf, curBlockPosition);
            }
            else if (rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers){
               mergeBlock(curBlock, rightBlock, isLeaf, curBlockPosition+1);
            }
        }
    }
    else if(!isLeaf && curBlock->parentBlock!=NULL){

        if(curBlockPosition==0){
            Block *rightBlock = new Block();
            rightBlock = curBlock->parentBlock->childBlock[1];

            //if we see the right one has more than half nodes of maximum capacity than re-distribute
            if( rightBlock!=NULL && rightBlock->tNodes-1 >= ceil((numberOfPointers-1)/2) ){
                redistributeBlock(curBlock, rightBlock, isLeaf, 0, 0);
            }
            //else there is nothing to re-distribute, so we can merge them
            else if (rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers - 1){
                mergeBlock(curBlock, rightBlock, isLeaf, 1);
            }
        }
        //for any other case we can safely take the left one to try for re-distribution
        else{


            Block *leftBlock = new Block();
            Block *rightBlock = new Block();


            leftBlock = curBlock->parentBlock->childBlock[curBlockPosition-1];

            rightBlock = curBlock->parentBlock->childBlock[curBlockPosition+1];


            //if we see that left one has more than half nodes of maximum capacity then try to re-distribute
            if( leftBlock!=NULL && leftBlock->tNodes-1 >= ceil((numberOfPointers-1)/2)){
                 redistributeBlock(leftBlock, curBlock, isLeaf, curBlockPosition-1, 1);
            }
            else if(rightBlock!=NULL && rightBlock->tNodes-1 >=  ceil((numberOfPointers-1)/2)){
                redistributeBlock(curBlock, rightBlock, isLeaf, curBlockPosition, 0);
            }
            //else there is nothing to re-distribute, so we merge them

            else if ( leftBlock!=NULL && curBlock->tNodes+leftBlock->tNodes < numberOfPointers-1) {
                mergeBlock(leftBlock, curBlock, isLeaf, curBlockPosition);
            }
            else if ( rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers-1){
               mergeBlock(curBlock, rightBlock, isLeaf, curBlockPosition+1);
            }
        }

    }



    //delete the duplicate if any in the ancestor Block
    Block *tempBlock = new Block();
    tempBlock = curBlock->parentBlock;
    while(tempBlock!=NULL){
            for(int i=0; i<tempBlock->tNodes;i++){
                if(tempBlock->value[i]==prevLeftMostVal)
                {
                    tempBlock->value[i] = curBlock->value[0];
                    break;
                }
        }
        tempBlock = tempBlock->parentBlock;
    }

}

char* searchNode(Block *curBlock, int val, int curBlockPosition)
{
    bool dataFound=false;
     //to check if the current block is a leaf or not
     bool isLeaf;
     if(curBlock->childBlock[0]==NULL)
        isLeaf = true;
     else isLeaf = false;

    //left most value could be changed due to merge or re-distribution later,
    //so keep it to replace it's copy from it's ancestor
    //int prevLeftMostVal = curBlock->value[0];



     for(int i=0;dataFound==false &&  i<=curBlock->tNodes; i++){
        if(val < curBlock->value[i] && curBlock->childBlock[i] != NULL)
        {
            searchNode(curBlock->childBlock[i], val, 0);

        }
        //if we could find the target value at any leafBlock then
        else if(val == curBlock->value[i] && curBlock->childBlock[i] == NULL)
        {

            //delete the node by shifting all values and pointers  by one to the left
           // memcpy(&curBlock->value[i], &curBlock->value[i+1], sizeof(int)*(curBlock->tNodes+1));
            //decrease number of nodes by one
            //curBlock->tNodes--;
            dataFound = true;
            return curBlock->str[i];

            break;
        }
     }
}

int searchintNode(Block *curBlock, int val, int curBlockPosition)
{
    bool dataFound=false;
     //to check if the current block is a leaf or not
     bool isLeaf;
     if(curBlock->childBlock[0]==NULL)
        isLeaf = true;
     else isLeaf = false;

    //left most value could be changed due to merge or re-distribution later,
    //so keep it to replace it's copy from it's ancestor
    //int prevLeftMostVal = curBlock->value[0];



     for(int i=0;dataFound==false &&  i<=curBlock->tNodes; i++)
     {
        if(val < curBlock->value[i] && curBlock->childBlock[i] != NULL)
        {
            searchNode(curBlock->childBlock[i], val, 0);

        }
        //if we could find the target value at any leafBlock then
        else if(val == curBlock->value[i] && curBlock->childBlock[i] == NULL)
        {

            //delete the node by shifting all values and pointers  by one to the left
           // memcpy(&curBlock->value[i], &curBlock->value[i+1], sizeof(int)*(curBlock->tNodes+1));
            //decrease number of nodes by one
            //curBlock->tNodes--;
            dataFound = true;
            //cout<<curBlock->str[i];
            break;
        }
     }
    if(dataFound)
        return 1;
    else
        return 0;
}

void print(vector < Block* > Blocks){
    vector < Block* > newBlocks;
    for(int i=0; i<Blocks.size(); i++){ //for every block
        Block *curBlock = Blocks[i];

        cout <<"[|";
        int j;
        for(j=0; j<curBlock->tNodes; j++){  //traverse the childBlocks, print values and save all the childBlocks
            cout << curBlock->value[j]<<curBlock->str[j] << "|";
            if(curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);
        }
        if(curBlock->value[j]==INT_MAX && curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);

        cout << "]  ";
    }

    if(newBlocks.size()==0){ //if there is no childBlock block left to send out then just the end of the recursion

        puts("");
        puts("");
        Blocks.clear();
        //exit(0);
    }
    else {                    //else send the childBlocks to the recursion to continue to the more depth
        puts("");
        puts("");
        Blocks.clear();
        print(newBlocks);
    }
}



int main()
{
    char str[20][100];
    int row=0;
    vector < Block* > Blocks;
    cout<<"Enter the order of the B+ tree as required"<<endl;
    cin>>numberOfPointers;
    while(1)
    {
        cout<<"\t\t\t Encrypted Message Vault"<<endl;
        cout<<endl;
        cout<<"1. Add a new message"<<endl;
        cout<<"2. Retrieve a message"<<endl;
        cout<<"3. Delete a message"<<endl;
        cout<<"4. Exit the program"<<endl;
        int cc;
        cin>>cc;
        if(cc==1)
        {
            cout<<"Enter the required index value as a 3-digit number"<<endl;
            int indx, mat[4][4]={0}, i, z, j;
            cin>>indx;
            for(i=0; i<4; i++)
            {
                for(j=0; j<4; j++)
                {
                    if(indx/2!=0)
                    {
                        int temp = indx%2;
                        indx = indx/2;
                        mat[i][j] = temp;
                    }
                }
            }
            cout<<"Enter the number of rounds of encryption necessary"<<endl;
            int ro;
            cin>>ro;
            int k=0;
            for(k=0; k<ro; k++)
            {
                addroundkey(mat);
                rotatediag(mat);
                shiftrows(mat);
            }
            cout<<"Please remember to recall the number of rounds of encryption for any future purposes"<<endl;
            int newval = 0, power=0, sum=1;
            for(i=0; i<4; i++)
            {
                for(j=0; j<4; j++)
                {
                    if(mat[i][j]==1)
                    {
                        for(k=0; k<power; k++)
                        {
                            sum = sum*2;
                        }
                        newval+=sum;
                        sum = 1;
                    }
                    else
                    {
                        continue;
                    }
                    power+=1;
                }
            }
            if(searchintNode(rootBlock,newval,0))
            {
                cout<<"Key already present, Enter new key"<<endl;
                continue;
            }
            cout<<"Enter the string that needs to be encrypted and stored."<<endl;
            string s;
            cin>>s;
            int len = s.length();
            char ch;
            ch = s[0];
            struct Node* root = newNode(ch);
            for(i=1; i<len; i++)
            {
                ch = s[i];
                insert(root, ch);
            }
            zizagtraversal(root,str[row]);
            insertNode(rootBlock, newval,str[row]);
            row++;

            Blocks.clear();
            Blocks.push_back(rootBlock);
            print(Blocks);
            puts("");
        }
        else if(cc==2)
        {
            cout<<"Enter the required index value as a 3-digit number"<<endl;
            int indx, mat[4][4]={0}, i, z, j;
            cin>>indx;
            for(i=0; i<4; i++)
            {
                for(j=0; j<4; j++)
                {
                    if(indx/2!=0)
                    {
                        int temp = indx%2;
                        indx = indx/2;
                        mat[i][j] = temp;
                    }
                }
            }
            cout<<"Enter the number of rounds of encryption necessary"<<endl;
            int ro;
            cin>>ro;
            int k=0;
            for(k=0; k<ro; k++)
            {
                addroundkey(mat);
                rotatediag(mat);
                shiftrows(mat);
            }
            int newval = 0, power=0, sum=1;
            for(i=0; i<4; i++)
            {
                for(j=0; j<4; j++)
                {
                    if(mat[i][j]==1)
                    {
                        for(k=0; k<power; k++)
                        {
                            sum = sum*2;
                        }
                        newval+=sum;
                        sum = 1;
                    }
                    else
                    {
                        continue;
                    }
                    power+=1;
                }
            }
            char *ar = searchNode(rootBlock, newval, 0);
            if(ar==NULL)
            {
                cout<<"Value doesn't exist in the tree"<<endl;
            }
            int l = strlen(ar);
            char ch;
            ch = ar[0];
            struct Node* root = newNode(ch);
            for(i=1; i<l; i++)
            {
                ch = ar[i];
                insert(root, ch);
            }
            char retstr[100];
            zizagtraversal(root,retstr);
            cout<<endl;
        }
        else if(cc==3)
        {
            cout<<"Enter the required index value as a 3-digit number"<<endl;
            int indx, mat[4][4]={0}, i, z, j;
            cin>>indx;
            for(i=0; i<4; i++)
            {
                for(j=0; j<4; j++)
                {
                    if(indx/2!=0)
                    {
                        int temp = indx%2;
                        indx = indx/2;
                        mat[i][j] = temp;
                    }
                }
            }
            cout<<"Enter the number of rounds of encryption necessary"<<endl;
            int ro;
            cin>>ro;
            int k=0;
            for(k=0; k<ro; k++)
            {
                addroundkey(mat);
                rotatediag(mat);
                shiftrows(mat);
            }
            int newval = 0, power=0, sum=1;
            for(i=0; i<4; i++)
            {
                for(j=0; j<4; j++)
                {
                    if(mat[i][j]==1)
                    {
                        for(k=0; k<power; k++)
                        {
                            sum = sum*2;
                        }
                        newval+=sum;
                        sum = 1;
                    }
                    else
                    {
                        continue;
                    }
                    power+=1;
                }
            }
            cout<<newval;
            if(searchintNode(rootBlock,newval,0))
            {
                deleteNode(rootBlock, newval, 0);
                //cout<<"Key not present, hence no deletion possible"<<endl;
                //continue;
            }
            else
            {
                //deleteNode(rootBlock, newval, 0);
                cout<<"Key not present, hence no deletion possible"<<endl;
                continue;
            }

        }
        else if(cc==4)
        {
            cout<<"The program will terminate now."<<endl;
            break;
        }
    }

	return 0;
}

