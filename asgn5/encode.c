#include "node.h"
#include "pq.h"
#include "io.h"
#include "code.h"
#include "stack.h"
#include "defines.h"
#include "huffman.h"
#include "header.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define OPTIONS "hvi:o:"
int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It sets the verbose and undirected booleans to true if given.
    // It also sets the input and output files if they are given, and errors if the infile is invalid.
    int opt = 0;
    bool stats = false;
    int input = 0;
    int output = 1;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("HELP\n");
            printf("HELPMSG\n\n");
            return 0;
            break;
        case 'v': stats = true; break;
        case 'i': input = open(optarg, O_RDONLY); break;
        case 'o': output = open(optarg, O_WRONLY | O_CREAT, 00400 | 00200); break;
        }
    }

    /* Code C = code_init();
    code_push_bit(&C, 1);
    code_push_bit(&C, 0);
    code_push_bit(&C, 1);

    code_push_bit(&C, 0);

    code_push_bit(&C, 0);

    code_push_bit(&C, 1);

    code_push_bit(&C, 1);

    code_print(&C);
    uint8_t as = 19;
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_print(&C);

    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_print(&C);
    Node *nodeone = node_create('s', 4);
    Node *nocdetwo = node_create('a', 8);
    Stack *s = stack_create(12);
    stack_push(s, nodeone);
    stack_push(s, nocdetwo);
    stack_print(s);
    Node *nd;
    stack_pop(s, &nd);
    node_print(nd);
    node_delete(&nodeone);
    node_delete(&nocdetwo);

    stack_delete(&s);
    uint8_t arr[1000];
    int cnt = read_bytes(input, arr, 10);
    uint8_t scarr[10000];
    int cnt2 = read_bytes(input, scarr, 1000);
    printf("%d, count 2 \n", cnt2);
    printf("\n");
    printf("%ld\n", bytes_read);
    write_bytes(output, arr, cnt - 1);
    write_bytes(output, scarr, cnt2 - 1);*/
    uint64_t hist[ALPHABET] = { 0 };
    uint8_t arr[10];
    int bytes_read = 11;
    while (bytes_read >= 10) {
        bytes_read = read_bytes(input, arr, 10);
        for (int i = 0; i < bytes_read; i++) {
            hist[arr[i]]++;
        }
    }
    hist[0]++;
    hist[255]++;
    Node *root = build_tree(hist);
    node_print(root);
    Code ctable[ALPHABET] = { 0 };
    build_codes(root, ctable);
    /* for (int i = 0; i < 256; i++) {
        if (ctable[i].top != 0) {
            code_print(&ctable[i]);
        }
    }*/
    // Header head;
    //  head.magic = MAGIC;
    //  uint8_t magicbuff[4] = head.magic[1];
    // write_bytes(output, magicbuff, 4);
    dump_tree(output, root);
    lseek(input, 0, SEEK_SET);
    uint8_t arr2[1000] = { 0 };
    printf("num bytes we readin %d\n", bytes_read);
    int cntr2 = read_bytes(input, arr2, 1000);

    for (int i = 0; i < cntr2; i++) {
        printf("charr is %c\n", arr2[i]);
        code_print(&ctable[arr2[i]]);
        write_code(output, &ctable[arr2[i]]);
    }
    flush_codes(output);
    // write_bytes(output, arr2, cntr2);
}
