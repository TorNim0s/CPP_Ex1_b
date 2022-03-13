#include <iostream>
#include "mat.hpp"
#include <stdexcept>
#include <vector>

using namespace std;

namespace ariel{

    bool checkOdd(int a){
        return a%2 == 0;
    }

    string mat(int col, int row, char first_sign, char second_sign){
        const int LowerLine = 33; // ascii lowest point
        const int MaxLine = 126; // ascii highest point

        string ans;
        vector<vector<int>> matrix_tmp_1(row, vector<int>(col)); // getting the lower of between i and j
        vector<vector<int>> matrix_tmp_2(row, vector<int>(col)); // getting the lower from the other side of i and j.
        
        if(checkOdd(col) || checkOdd(row)){
            throw invalid_argument("Row and column must be odd");
        }
        if(col <= 0 || row <= 0){
            throw invalid_argument("Row and column must be greater than 0");
        }
        if (first_sign < LowerLine || first_sign > MaxLine || second_sign < LowerLine || second_sign > MaxLine ){
            throw invalid_argument("Symbols must be valid - in ascii between 33 and 126 only");
        }

        // creating the way of the matrix to look like we want in mats way for the manufacturing. but with numbers 0 and 1;

        for(int i = 0; i< row; i++){
            for(int j = 0; j<col; j++){
                matrix_tmp_1[i][j] = min(i,j); // getting the minimum of i and j normal position
                matrix_tmp_2[i][j] = min(row-1-i, col-1-j); // getting the minimum of i and j from the other side
                matrix_tmp_2[i][j] = min(matrix_tmp_1[i][j], matrix_tmp_2[i][j]) % 2; // combine them to get the mats we are looking for and make them only 0 or 1.
            }
        }

        // change number 0 to first_sign and 1 to second_sign and add it to ans

        for(int i = 0; i< row; i++){
            for(int j = 0; j<col; j++){
                ans += (matrix_tmp_2[i][j] == 0) ? first_sign : second_sign;
                ans += " ";
            }
            if(i < row-1){
                ans += "\n";
            }
        }

        return ans;
    }
}