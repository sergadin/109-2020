#include <iostream>
#include "exam-test.h"


int main()
{
    FILE *output;
    Node *root;
    int maxId; 
    char fname[64];

    if ((output = fopen("output.txt", "a")) == NULL) {
	return -1;
    }

    printf("data file name: ");
    char * s = fgets(fname, 64, stdin); 
    root = ReadGraph(fname, maxId);
    if (!root || !s) {
       printf("cannot process file %s\n", fname);
       return -1;
    }

    // test print of the graph
    PrintGraph(stdout, root);

    int *nodes_parents, *ranks;
    nodes_parents = new int[maxId];
    ranks = new int[maxId];

    // Если потомок одновременно и левый, и правый, считается, что он левый (и единственный)

    for (int i = 0; i < maxId; i++) {
	ranks[i] = CountParents(root, i, nodes_parents);
	for (int k = 0; k < ranks[i]; k++) {
		for (int l = k + 1; l < ranks[i]; l++) {
			if (nodes_parents[l] == nodes_parents[k]) {
				for (int p = l; p < ranks[i] - 1; p++) {
					nodes_parents[p] = nodes_parents[p + 1];
				}
				ranks[i] = ranks[i] - 1;
				l--;
			}
		}
	}
	if (ranks[i] > 1) {
		fprintf(output, "%d - %d parents:\n", i, ranks[i]);
		for (int j = 0; j < ranks[i]; j++) {
			fprintf(output, "%d\t", nodes_parents[j]);
		}
		fprintf(output, "\n");
	}
    }
    
    fprintf(output, "\n");
    fclose(output);
    DeleteGraph(root, maxId);
    delete[] nodes_parents;
    delete[] ranks;
    return 0;
}










