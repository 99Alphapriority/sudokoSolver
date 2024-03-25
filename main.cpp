#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<random>
#include<chrono>
#include<time.h>
#include<thread>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>

void printPuzzle(char board[9][9], bool clear = true);

void sleep(int milliseconds)
{
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

bool isValid(char num, int i, int j, char board[9][9])
{
	for(int k = 0; k < 9; k++)
    {
    	if(num == board[i][k])
        	return false;

        if(num == board[k][j])
        	return false;

        if (num == board[3 * (i / 3) + k / 3][3 * (j / 3) + k % 3])
        	return false;
    }
    
	return true;
}

bool solve(char board[9][9], bool visualize = false)
{
	int row, col;

        for(int row = 0; row < 9; row++)
        {
            for(int col = 0; col < 9; col++)
            {
                if(board[row][col] == '.')
                {
                    for(char num = '1'; num <= '9'; num++)
                    {
                        if(isValid(num, row, col, board))
                        {
                            board[row][col] = num;
			    		
							if(visualize)
			    			{
			    				sleep(50);
								printPuzzle(board);
			    			}

                           	if(solve(board, visualize))
                                return true;
                            
							board[row][col] = '.';
			    
							if(visualize)
			    			{
			    				sleep(50);
								printPuzzle(board);
			    			}
                        }
                    }

                    return false;
                }
            }
        }
        return true;
}

void solveSudoku(char board[9][9], bool visualize)
{
	solve(board, visualize);
}

void setCursorPosition(int x, int y)
{
	printf("\033[%d;%dH", y+1, x+1);
	std::cout.flush();
}

void printPuzzle(char board[9][9], bool clear)
{
	if(clear)
	{
		setCursorPosition(0,0);
	}

	std::string text, separator, padding;

	for(int i = 0; i < 9; i++)
	{
		text = "|";
		separator = " -";
		padding = "|";

		for(int j = 0; j < 9; j++)
		{
			char value = (board[i][j] == '.' ? ' ' : board[i][j]);
			text += "  " ;
			text += value; 
			text += "  |";
			separator += "------";
	        	padding += "     |";

			if(j % 3 == 2 && j != 8)
			{
				text += "|";
				padding += "|";
			}
		}

		if(i != 0 && i%3 == 0)
		{
			std::replace(separator.begin(), separator.end(), '-', '=');
		}

		std::cout << separator << std::endl;
		std::cout << padding << std::endl;
		std::cout << text << std::endl;
		std::cout << padding << std::endl;
	}
	std::cout << separator << std::endl;
}

int main()
{

#if 0
	char board[9][9] =
	{
		{'5','3','.','.','7','.','.','.','.'},
		{'6','.','.','1','9','5','.','.','.'},
		{'.','9','8','.','.','.','.','6','.'},
		{'8','.','.','.','6','.','.','.','3'},
		{'4','.','.','8','.','3','.','.','1'},
		{'7','.','.','.','2','.','.','.','6'},
		{'.','6','.','.','.','.','2','8','.'},
		{'.','.','.','4','1','9','.','.','5'},
		{'.','.','.','.','8','.','.','7','9'}
	};
#endif

	char board[9][9] =
    {
        {'.','.','8','6','.','.','.','.','.'},
        {'.','.','.','.','2','.','.','.','4'},
        {'3','6','.','.','.','1','.','9','.'},
        {'5','9','.','.','.','6','.','3','.'},
        {'.','7','.','.','.','.','.','.','.'},
        {'.','.','.','1','.','.','6','.','.'},
        {'8','5','.','4','.','.','.','.','9'},
        {'.','.','1','.','.','.','.','8','.'},
        {'.','.','7','.','.','5','.','.','.'}
    };

	system("clear");

	printPuzzle(board);

	std::string run;
	std::cout << "solve puzzle? (Y/N) ";
	std::cin >> run;

	std::string vis;
	bool visualize;
	std::cout << "Do you want visualization? (Y/N) ";
	std::cin >> vis;

	if("n" == run || "N" == run)
	{
		std::cout.flush();
		return 0;
	}

	if("n" == vis || "N" == vis)
		visualize = false;
	else
		visualize = true;

	solveSudoku(board, visualize);
	
	printPuzzle(board, false);

	std::cout.flush();
	
	return 0;

}
