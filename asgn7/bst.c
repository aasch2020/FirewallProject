#include "bst.h"
#include <string.h>
#include "node.h"
Node *bst_create(void){
	return NULL;
}

uint32_t bst_height(Node *root){
	if(root){
		int l = bst_height(root->left);
		int r = bst_height(root->right);
		if(l > r){
			return 1 + l;

		}else{
			return 1 + r;
		}



	}
	return 0;


}

uint32_t bst_size(Node *root){
	if(root){
		return 1 + bst_size(root->left) + bst_size(root->right);

	}

	return 0;
}

Node *bst_find(Node *root, char *oldspeak){
	if(root){
		if(strcmp(root->oldspeak, oldspeak) > 0){
			bst_find(root->left, oldspeak);


		}
		if(strcmp(root->oldspeak, oldspeak) < 0){
			bst_find(root->right, oldspeak);
			
		}




	}
	return root;


}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak){
	if(root){
		 if(strcmp(root->oldspeak, oldspeak) > 0){
                        root->left = bst_insert(root->left, oldspeak, newspeak);


                }
                if(strcmp(root->oldspeak, oldspeak) < 0){
                        root->right = bst_insert(root->right, oldspeak, newspeak);

                }
		if(strcmp(root->oldspeak, oldspeak) == 0){
			return root;

		}
	

	}

	return node_create(oldspeak, newspeak);

	



}

void bst_print(Node *root){
	if(root){
		bst_print(root->left);
		node_print(root);
		bst_print(root->right);
	}

}
