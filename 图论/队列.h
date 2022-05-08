#pragma once
#include<iostream>
#define MAX 10
using namespace std;
struct Stack {
	int rear;
	int top;
	int data[MAX];
};
void init(Stack* stack);
bool stack_empty(Stack* stack);
int push(Stack* stack);
void pop(Stack* stack, int data);