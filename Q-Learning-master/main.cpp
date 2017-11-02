// -*- C++ -*-
//===--------------------------- Q-Learning ---------------------------------===//
//
//                     C++ Version of Q-Learning
//
// This file implements an simple C++ Q-Learning algorithm
// Author is Jin Fagang.
//
//===----------------------------------------------------------------------===//
#include <iostream>
#include <string>
#include <string.h>
#include "utils/utils.h"
#include <cstdlib>

using namespace std;

// I think Q matrix and R matrix must be same
// and it must be same both row and column
#define MATRIX_ROW 100
#define MATRIX_COLUMN 100
// state num must be equal to action num
#define STATE_NUM 100
#define ACTION_NUM 100
#define DES_STATE 100
#define MAX_EPISODE 100
// this value using for Q(s,a)=R(s,a)+alpha * max{Q(s', a')}
// Q(s', a') is the all next step Q value
#define alpha 0.8

// define the most important Q-matrix and R-matrix
// R-matrix is given
double R[100][100] = {{0, 0, 0, 0, 0, 0},	//1
                     {0, 0, 0, 0, 0, 0},	//2
                     {0, 0, 0, 0, 0, 0},	//3
                     {0, 0, 0, 0, 0, 0},	//4
                     {0, 0, 0, 0, 0, 0},	//5
		     {0, 0, 0, 0, 0, 0},	//6
                     {0, 0, 0, 0, 0, 0},	//7
                     {0, 0, 0, 0, 0, 0},	//8
                     {0, 0, 0, 0, 0, 0},	//9
                     {0, 0, 0, 0, 0, -1},	//10
		     {0, 0, 0, 0, -1, 0},	//11
                     {0, 0, 0, -1, 0, 0},	//12
                     {0, 0, -1, 0, 0, 0},	//13
                     {0, -1, 0, 0, 0, 0},	//14
		     {-1, 0, 0, 0, 0, 0},	//15
                     {0, 0, 0, 0, 0, 0},	//16
                     {0, 0, 0, 0, 0, 0},	//17
                     {0, 0, 0, 0, 0, 0},	//18
                     {0, 0, 0, 0, 0, 0},	//19
		     {0, 0, 0, 0, 0, 0},	//20
		     {0, 0, 0, 0, 0, 0},	//21
                     {0, 0, 0, 0, 0, 0},	//22
                     {0, 0, 0, 0, 0, 0},	//23
                     {0, 0, 0, 0, 0, 0},	//24
                     {0, 0, 0, 0, 0, 0},	//25
		     {0, 0, 0, 0, 0, 0},	//26
                     {0, 0, 0, 0, 0, 0},	//27
                     {0, 0, 0, 0, 0, 0},	//28
                     {0, 0, 0, 0, 0, 0},	//29
                     {0, 0, 0, 0, 0, 0},	//30
		     {0, 0, 0, 0, 0, 0},	//31
                     {0, 0, 0, 0, 0, 0},	//32
                     {0, 0, 0, 0, 0, 0},	//33
                     {0, 0, 0, 0, 0, 0},		//34
		     {0, 0, 0, 0, 0, 0},	//35
                     {0, 0, 0, 0, 0, 0},	//36
                     {0, 0, 0, 0, 0, 0},	//37
                     {0, 0, 0, 0, 0, 0},	//38
                     {0, 0, 0, 0, 0, 0},		//39
		     {0, 0, 0, 0, 0, 0},		//40
		     {0, 0, 0, 0, 0, -1},	//41
                     {0, 0, 0, 0, -1, 0},	//42
                     {0, 0, 0, -1, 0, -1},	//43
                     {0, 0, -1, 0, -1, 0},	//44
                     {0, -1, 0, -1, 0, 0},	//45
		     {-1, 0, -1, 0, 0, 0},	//46
                     {0, 0, 0, 0, 0, 0},	//47
                     {-1, 0, 0, -1, 0, 0},	//48
                     {0, 0, 0, 0, 0, 0},	//49
                     {0, 0, 0, 0, 0, -1},	//50
		     {0, 0, 0, 0, -1, 0},	//51
                     {0, 0, 0, -1, 0, 0},	//52
                     {0, 0, -1, 0, 0, 0},	//53
                     {0, -1, 0, 0, 0, 0},	//54
		     {-1, 0, 0, 0, 0, 0},	//55
                     {0, 0, -1, 0, 0, 0},	//56
                     {0, 0, 0, 0, -1, 0},	//57
                     {0, 0, 0, -1, 0, -1},	//58
                     {0, 0, -1, 0, -1, 0},	//59
		     {0, -1, 0, -1, 0, 0},	//60
		     {-1, 0, -1, 0, 0, 0},	//61
                     {0, -1, 0, 0, 0, 0},	//62
                     {-1, 0, 0, 0, 0, 0},	//63
                     {0, 0, 0, 0, 0, 0},	//64
                     {0, 0, 0, 0, 0, 0},	//65
		     {0, 0, 0, 0, 0, 0},	//66
                     {0, 0, 0, 0, 0, 0},	//67
                     {0, 0, 0, 0, 0, 0},	//68
                     {0, 0, 0, 0, 0, 0},	//69
                     {0, 0, 0, 0, 0, 0},	//70
		     {0, 0, 0, 0, 0, 0},	//71
                     {0, 0, 0, 0, 0, 0},	//72
                     {0, 0, 0, 0, 0, 0},	//73
                     {0, 0, 0, 0, 0, 100},	//74
		     {0, 0, 0, 0, 100, 0},	//75
                     {0, 0, 0, 100, 0, 0},	//76
                     {0, 0, 100, 0, 0, 0},	//77
                     {0, 100, 0, 0, 0, 0},	//78
                     {100, 0, 0, 0, 0, 0},	//79
		     {0, 0, 0, 0, 0, 0},	//80
		     {0, 0, 0, 0, 0, -1},	//81
                     {0, 0, 0, 0, -1, 0},	//82
                     {0, 0, 0, -1, 0, 0},	//83
                     {0, 0, -1, 0, 0, 0},	//84
                     {0, -1, 0, 0, 0, 0},	//85
		     {-1, 0, 0, 0, 0, 0},	//86
                     {0, 0, 0, 0, 0, 0},	//87
                     {0, 0, 0, 0, -1, 0},	//88
                     {0, 0, 0, -1, 0, -1},	//89
                     {0, 0, -1, 0, -1, 0},	//90
		     {0, -1, 0, -1, 0, 0},	//91
                     {-1, 0, -1, 0, 0, -1},	//92
                     {0, 0, 0, 0, 0, 0},	//93
                     {-1, 0, 0, -1, 0, 0},	//94
		     {0, 0, 0, 0, 100, 0},	//95
                     {0, -1, 0, 100, 100, 100},	//96
                     {-1, 0, 100, 100, 100, 100},	//97
                     {0, 100, 0, 0, 0, 0},	//98
                     {100, 100, 100, 100, 100, 100},	//99
		     {0, 0, 0, 0, 0, 0}};	//100


double Q[100][100];
int possible_action[10];
int possible_action_num;


// get in state s, possible actions
void get_possible_action(double R[100][100], int state, int possible_action[10]){
    // find R[i][j] value > 0 is action we can do later
    possible_action_num = 0;
    for(int i = 0; i < ACTION_NUM; i++){
        if (R[state][i] >= 0){
            possible_action[possible_action_num] = i;
            possible_action_num++;

	//     possible_action_num = 0;
	//     for(int i = 0; i < ACTION_NUM; i++){
	//         if (R[state][i] >= 0){
	//             possible_action[possible_action_num] = i;
	//             possible_action_num++;
        }
    }
}
double get_max_q(double Q[100][100], int state){
    double temp_max = 0;
    for (int i = 0; i < ACTION_NUM; ++i) {
        if ((R[state][i] >= 0) && (Q[state][i] > temp_max)){
            temp_max = Q[state][i];
        }
    }
    return temp_max;
}
int episode_iterator(int init_state, double Q[100][100], double R[100][100]){

    double Q_before, Q_after;
    // next action
    int next_action;
    double max_q;

    // start series event loop
    int step=0;
    while (1){
        cout << "-- step " << step << ": initial state: " << init_state << endl;
        // memset possible_action array
        memset(possible_action, 0, 10*sizeof(int));
        get_possible_action(R, init_state, possible_action);

        // get next action
        next_action = possible_action[rand()%possible_action_num];
        cout << "-- step " << step << ": next action: " << next_action << endl;
        // treat next action as state, and we can get max{Q(s', a')}
        max_q = get_max_q(Q, next_action);

        Q_before = Q[init_state][next_action];
        // update formula Q(s,a)=R(s,a)+alpha * max{Q(s', a')}
        Q[init_state][next_action] = R[init_state][next_action] + alpha * max_q;
        Q_after = Q[init_state][next_action];

        // next episode rules
        // if next_action is destination state, then go next episode
        // if not, then go back to this loop
        if (next_action == DES_STATE){
            init_state = rand()%STATE_NUM;
            break;
        }else{
            // if not destination state, then next action becomes initial state
            init_state = next_action;
        }
        step++;
    }
    return init_state;
}

int inference_best_action(int now_state, double Q[100][100]){
    // get the max value of Q corresponding action when state is nw_state
    double temp_max_q=0;
    int best_action=0;
    for (int i = 0; i < ACTION_NUM; ++i) {
        if (Q[now_state][i] > temp_max_q){
            temp_max_q = Q[now_state][i];
            best_action = i;
        }
    }
    return best_action;
}
void run_training(int init_state){
    int initial_state = init_state;

    // start random
    srand((unsigned)time(NULL));
    cout << "[INFO] start training..." << endl;
    for (int i = 0; i < MAX_EPISODE; ++i) {
        cout << "[INFO] Episode: " << i << endl;
        initial_state = episode_iterator(initial_state, Q, R);
        cout << "-- updated Q matrix: " << endl;
        print_matrix(Q, 6, 6);
    }
}

int main() {

    cout << "Q matrix:" << endl;
    print_matrix(Q, 6, 6);
    cout << "R matrix:" << endl;
    print_matrix(R, 6, 6);

    run_training(1);
    cout << "Q convergence matrix:" << endl;
    print_matrix(Q, 6, 6);

    int position;
    while (1){
        cout << "please input robot locate room: " << endl;
        cin >> position;
        cout << position << "->";
        while (1){
            int best_action = inference_best_action(position, Q);
            cout << best_action << "->";
            if (best_action == DES_STATE){
                cout << "out" << endl;
                break;
            }else{
                position = best_action;
            }
        }
    }

    return 0;
}
