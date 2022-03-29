#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

//Struktur pada Program
struct Node{
    int id;
    char name[255];
    int age;
	int bonus;
    struct Node *left;
    struct Node *right;
    int height;
};

int maximum;
char nameBonus[255];
int idBonus;
int ageBonus;

//Main menu in Program
void mainMenu(){
    puts("LEO and Friend\'s Company");
    puts("___________________________\n");
    puts("1. Add a new data");
    puts("2. Update a certain data");
    puts("3. Searching certain data");
    puts("4. Delete a certain data");
    puts("5. Show Bonus Employee");
    puts("6. Show All Data");
    puts("7. Exit");
}

// Calculate height
int height(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

//add node
struct Node *newNode(char name[], int key, int bonus, int age){
    struct Node *temp = malloc(sizeof(struct Node));
    strcpy(temp->name, name);
    temp->id = key;
    temp->age = age;
    temp->bonus = bonus;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

//Right Rotate
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
struct Node *leftRotate(struct Node *x) {
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(struct Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insert node
struct Node *insertNode(struct Node *node, char name[], int key, int bonus, int age) {
  // Find the correct position to insertNode the node
  if (node == NULL)
    return (newNode(name, key, bonus, age));

  if (key < node->id){
    node->left = insertNode(node->left, name, key, bonus, age);
  }else if (key > node->id)
    node->right = insertNode(node->right, name, key, bonus, age);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left), height(node->right));
               
  int balance = getBalance(node);
  if (balance > 1 && key < node->left->id)
    return rightRotate(node);

  if (balance < -1 && key > node->right->id)
    return leftRotate(node);

  if (balance > 1 && key > node->left->id) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->id) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

int searchID(struct Node *root, int tempID){
	if(root == NULL){
		return 0;
	}else{
		struct Node *temp = malloc(sizeof(struct Node));
		temp = root;
		while(temp != NULL){
			if(temp->id == tempID){
				return 1;
			}else if(temp->id > tempID){
				temp = temp->left;
			}else if(temp->id < tempID){
				temp = temp->right;
			}
		}
		return 0;
	}
}

void add(struct Node **root){
	system("cls");
	char tempName[255];
	int tempID;
	int tempAge;
	int tempBonus;
	int exist = 1;
	while(exist != 0){
		fflush(stdin);
		printf("Input employee\'s name [3..20]: ");
		scanf(" %[^\n]", &tempName);
		fflush(stdin);
		printf("Input employee\'s ID [B...]: B");
		scanf("%d", &tempID);
		printf("Input employee\'s age [21-40]: ");
		scanf("%d", &tempAge);
		exist = searchID(*root, tempID);
		if(exist == 1){
			printf("\n--- There is another employee with same ID ---");
			printf("\nPress Enter to Continue");
			getch();
			system("cls");
		}
	}
	srand(time(NULL));
	tempBonus = rand() % 100 + 1;
	*root = insertNode(*root, tempName, tempID, tempBonus, tempAge);
	printf("\n\n--- Add new data success ---");
	printf("\nPress Enter to Continue\n");
	getch();
	system("cls");
}

//Search data
struct Node *searchNode(struct Node *root, int tempID)
{
    if(root)
    {
        if(root->id == tempID)
        {
            return root;
        }
        else
        {
            struct Node *temp;
            temp = searchNode(root->left, tempID);
            if(temp == NULL){
                temp = searchNode(root->right, tempID);
            }
            return temp;
        }
    }
	else{
    	return 0;
    }
}

//Update data
struct Node *updateNode(struct Node *root)
{
  if(root)
  {
    int tempID;
    printf("Input Karyawan's ID that want to be changed: B");
    scanf("%d", &tempID);
    struct Node *temp = searchNode(root, tempID);
    if(temp != NULL)
    {
      printf("Input new name: ");
      scanf(" %[^\n]",&temp->name);
      printf("Input new age: ");
      scanf("%d",&temp->age);
      printf("\n\n--- Update new data success ---");
      printf("\nPress Enter to Continue\n");
      getch();
      system("cls");
    }
    else if(temp == NULL){
      printf("\n--- Cannot find specific Karyawan's ID---\n");
      printf("Press Enter to Continue\n");
      getch();
      system("cls");
    }
  }
  else{
    printf("\n\n   --- There is No Employee in The Storage ---\n");
      printf("Press Enter to Continue\n");
      getch();
      system("cls");
  }
}

struct Node * minValueNode(struct Node* node)
{
	struct Node* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}


struct Node* deleteNode(struct Node* root, int key)
{
	// STEP 1: PERFORM STANDARD BST DELETE

	if (root == NULL)
		return root;

	if ( key < root->id )
		root->left = deleteNode(root->left, key);

	else if( key > root->id )
		root->right = deleteNode(root->right, key);

	else
	{
		// node with only one child or no child
		if( (root->left == NULL) || (root->right == NULL) )
		{
			struct Node *temp = root->left ? root->left : root->right;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case
				*root = *temp;
				free(temp);
		}
		else
		{
			// node with two children: Get the successor (smallest in the right subtree)
			struct Node* temp = minValueNode(root->right);

			// Copy the inorder successor's data to this node
			root->id = temp->id;
			root->age = temp->age;
			root->bonus = temp->bonus;
			root->height = temp->height;
			strcpy(root->name, temp->name);

			// Delete the inorder successor
			root->right = deleteNode(root->right, temp->id);
		}
	}

	// If the tree had only one node then return
	if (root == NULL)
	return root;

	root->height = 1 + max(height(root->left),
						height(root->right));

	int balance = getBalance(root);

	// Left Left Case
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

void del(struct Node **root){
  if(*root == NULL){
	printf("\n\n   --- There is No Employee in The Storage ---\n");
    printf("Press Enter to Continue\n");
    getch();
    system("cls");
  }else{
	int key;
    struct Node *temp = malloc(sizeof(struct Node));
    temp = *root;
    printf("\nInput Karyawan's ID that want to be deleted: B");
    scanf("%d", &key);

    if(searchNode(*root, key) == NULL)
    {
      printf("\n--- Cannot find specific Karyawan's ID ---\n");
      printf("Press Enter to Continue\n");
      getch();
      system("cls");
    }
    else if(searchNode(*root, key) != NULL)
    {
      *root = deleteNode(*root, key);
      printf("\n--- Delete Success ---\n");
      printf("Press Enter to Continue\n");
      getch();
      system("cls");
    }	
  }
}

void preOrder(struct Node *root){
	if(root != NULL){
		printf("B%d -> %s, %d years old [%d]\n", root->id, root->name, root->age, root->bonus);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(struct Node *root){
	if(root != NULL){
		inOrder(root->left);
		printf("B%d -> %s, %d years old [%d]\n", root->id, root->name, root->age, root->bonus);
		inOrder(root->right);
	}
}

void postOrder(struct Node *root){
	if(root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		printf("B%d -> %s, %d years old [%d]\n", root->id, root->name, root->age, root->bonus);
	}
}

void show(struct Node *root){
	if(!root){
		printf("\n\n   --- There is No Employee in The Storage ---\n");
    	printf("Press Enter to Continue\n");
    	getch();
    	system("cls");
	}else{
		printf("\nPreorder :\n");
		preOrder(root);
		printf("\nInorder :\n");
		inOrder(root);
		printf("\nPostorder :\n");
		postOrder(root);
		printf("Press Enter to Continue\n");
    	getch();
    	system("cls");
	}
}

void searchBonus(struct Node *root){
	if(root != NULL){
		if(root->bonus > maximum){
			maximum = root->bonus;
			strcpy(nameBonus, root->name);
			idBonus = root->id;
			ageBonus = root->age;
		}
		searchBonus(root->left);
		searchBonus(root->right);	
	}
}

void bonus(struct Node *root){
	if(root == NULL){
		printf("\n\n   --- There is No Employee in The Storage ---\n");
    	printf("Press Enter to Continue\n");
    	getch();
    	system("cls");
	}else{
		struct Node *temp = malloc(sizeof(struct Node));
		temp = root;
		maximum = -1;
		searchBonus(temp);
		printf("\n\nCongratulations to:\n\n");
		printf("   Name : %s\n", nameBonus);
		printf("   ID : B%d\n", idBonus);
		printf("   Age : %d\n\n", ageBonus);
		printf("You will get a bonus because you has the highest performace\'s point this month!\n\n");
		printf("Press Enter to Continue\n");
		getch();
		system("cls");
	}
}

void searchEmployee(struct Node *root){
	if(root == NULL){
		printf("\n\n   --- There is No Employee in The Storage ---\n");
    	printf("Press Enter to Continue\n");
    	getch();
    	system("cls");
	}else{
		struct Node *temp = malloc(sizeof(struct Node));
		temp = root;
		int tempID;
		int flag = 0;
		printf("\nInput Employee\'s ID: B");
		scanf("%d", &tempID);
		while(temp != NULL){
			if(temp->id == tempID){
				flag = 1;
				break;
			}else if(temp->id > tempID){
				temp = temp->left;
			}else{
				temp = temp->right;
			}
		}
		if(flag == 1){
			printf("\nName : %s\n", temp->name);
			printf("ID : B%d\n", temp->id);
			printf("Age : %d\n", temp->age);
			printf("\nPress Enter to Continue\n");
			getch();
			system("cls");
		}else{
			printf("\nId Not Found, Please Check Again");
			printf("\nPress Enter to Continue\n");
			getch();
			system("cls");
		}
	}
}

//Bagian utama Pada program
int main(){
    struct Node *root = malloc(sizeof(struct Node));
    root = NULL;
    int input;

    do{
        mainMenu();
        printf("\nInput choice : ");
        scanf("%d", &input);
        switch(input){
            case 1:
                add(&root);
                break;
            case 2:
                updateNode(root);
                break;
            case 3:
                searchEmployee(root);
                break;
            case 4:
                del(&root);
                break;
            case 5:
                bonus(root);
                break;
            case 6:
                show(root);
                break;
            case 7:
                free(root);
                break;
            //default:

        }
    }while(input != 7);

    return 0;
}
