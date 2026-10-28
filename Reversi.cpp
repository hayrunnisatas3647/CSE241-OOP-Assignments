#include <iostream>
#include <string>
#define size 12
int k;

using namespace std;

void creatBoard(char board[size][size]);
void printBoard(char board[size][size]);
bool isvalid(int a,int b,char board[size][size],char player,int& count);
void computerMove(char board[size][size]);
void playGame(char board[size][size],char player);
bool makeMove(int a,int b,char board[size][size],char player);
bool validMove(char board[size][size],char player);
void result(char board[size][size]);

int main()
{   
    char board[size][size];

    string input;

    cout<<"Enter board size (8, 10, 12): ";
    cin>>input;

    while(input!="8" && input!="10" && input!="12")
    {
        cout<<"Invalid size! Try again: ";
        cin>>input;
    }

    if(input=="8")
        k=8;
    else if(input=="10")
        k=10;
    else
        k=12;

    creatBoard(board);
    printBoard(board);
    playGame(board,'o');
   
    return 0;
}

// Create the board and place the initial pieces.
void creatBoard(char board[size][size]){
    int i,j,middle;
    for(i=0;i<k;i++){ 
        for(j=0;j<k;j++){
            board[i][j]='.';      
        }
    }
    middle=k/2;
board[middle-1][middle-1]='x';
board[middle-1][middle]='o';
board[middle][middle-1]='o';
board[middle][middle]='x';
}

// Display the current board.
void printBoard(char board[size][size]){
    int i,j;
    char c;
    cout<<"   ";
    for(c='a';c<'a'+k;c++){
        cout<<c<<" ";
    }
    cout<<endl;
    for(i=0;i<k;i++){ 
        if(i+1 < 10)
            cout << i+1 << "  ";
        else
            cout << i+1 << " ";
        for(j=0;j<k;j++){
        cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    
}

// Check if a move is valid and count the pieces that can be flipped.
bool isvalid(int a,int b,char board[size][size],char player,int& count){


    int i;
    bool control;
    control=false;
    count=0;
    if(a < 0 || a >= k|| b < 0 || b >= k)
    return false;

    if(board[a][b] != '.')
    return false;
    
    // Check downward direction.
    for(i=a+1;i<k;i++){
        if(board[i][b]=='.')
            break;

        if(board[i][b]==player){
            if(i==a+1)
                break;
            else{
                control=true;
                count+=i-a-1;
                break;
            }
        } 
    }
    
    // Check upward direction.
      for(i=a-1;i>=0;i--){
        if(board[i][b]=='.')
            break;

        if(board[i][b]==player){
            if(i==a-1)
                break;
            else{
                control=true;
                count+=a-i-1;
                break;
            }
        } 
    }
    
   
    // Check left direction.
      for(i=b-1;i>=0;i--){
        if(board[a][i]=='.')
            break;

        if(board[a][i]==player){
            if(i==b-1)
                break;
            else{
                control=true;
                count+=b-i-1;
                break;
            }
        } 
    }
    
    
    // Check right direction.
      for(i=b+1;i<k;i++){
        if(board[a][i]=='.')
            break;

        if(board[a][i]==player){
            if(i==b+1)
                break;
            else{
                control=true;
                count+=i-b-1;
                break;
            }
        } 
    }
    
    // Check upper-right diagonal direction.
       for(i=b+1; i<k && a-(i-b)>=0; i++){
        if(board[a-(i-b)][i]=='.')
            break;

        if(board[a-(i-b)][i]==player){
            if(i==b+1)
                break;
            else{
                control=true;
                count+=i-b-1;
                break;
            }
        } 
    }
    
    
    // Check lower-right diagonal direction.
    for(i=b+1; i<k && a+(i-b)<k; i++){
        if(board[a+(i-b)][i]=='.')
            break;

        if(board[a+(i-b)][i]==player){
            if(i==b+1)
                break;
            else{
                control=true;
                count+=i-b-1;
                break;
            }
        } 
    }
    
    // Check lower-left diagonal direction.
    for(i=a+1; i<k && b-(i-a)>=0; i++){
        if(board[i][b-(i-a)]=='.')
            break;

        if(board[i][b-(i-a)]==player){
            if(i==a+1)
                break;
            else{
                control=true;
                count+=i-a-1;
                break;
            }
        } 
    }
    
  
    // Check upper-left diagonal direction.
    for(i=a-1; i>=0 && b-(a-i)>=0; i--){
        if(board[i][b-(a-i)]=='.')
            break;

        if(board[i][b-(a-i)]==player){
            if(i==a-1)
                break;
            else{
                control=true;
                count+=a-i-1;
                break;
            }
        } 
    }

    return control;
    
}

// Flip the opponent's pieces and place the player's piece.
bool makeMove(int a,int b,char board[size][size],char player){
    int i;
    bool control;
    control=false;

    if(a < 0 || a >= k || b < 0 || b >= k)
    return false;

    if(board[a][b] != '.')
    return false;

    //Check downward direction.
    for(i=a+1;i<k;i++){
        if(board[i][b]=='.')
            break;

        if(board[i][b]==player){
            if(i==a+1)
                break;
            else{
                control=true;

                for(int j=a+1; j<i;j++)
                    board[j][b]=player;

                break;
            }
        } 
    }

    // Check upward direction.
      for(i=a-1;i>=0;i--){
        if(board[i][b]=='.')
            break;

        if(board[i][b]==player){
            if(i==a-1)
                break;
            else{
                control=true;

                
                for(int j=a-1; j>i;j--)
                    board[j][b]=player;
                break;
            }
        } 
    }

    // Check left direction.
      for(i=b-1;i>=0;i--){
        if(board[a][i]=='.')
            break;

        if(board[a][i]==player){
            if(i==b-1)
                break;
            else{
                control=true;

                for(int j=b-1; j>i;j--)
                    board[a][j]=player;

                break;
            }
        } 
    }

    // Check right direction.
      for(i=b+1;i<k;i++){
        if(board[a][i]=='.')
            break;

        if(board[a][i]==player){
            if(i==b+1)
                break;
            else{
                control=true;

                for(int j=b+1; j<i;j++)
                    board[a][j]=player;
                break;
            }
        } 
    }

    // Check upper-right diagonal direction.
       for(i=b+1; i<k && a-(i-b)>=0; i++){
        if(board[a-(i-b)][i]=='.')
            break;

        if(board[a-(i-b)][i]==player){
            if(i==b+1)
                break;
            else{
                control=true;
                
                for(int j=b+1; j<i;j++)
                    board[a-(j-b)][j]=player;
                break;
            }
        } 
    }

    // Check lower-right diagonal direction.
    for(i=b+1; i<k && a+(i-b)<k; i++){
        if(board[a+(i-b)][i]=='.')
            break;

        if(board[a+(i-b)][i]==player){
            if(i==b+1)
                break;
            else{
                control=true;

                for(int j=b+1; j<i;j++)
                    board[a+(j-b)][j]=player;

                break;
            }
        } 
    }
    
    // Check lower-left diagonal direction.
    for(i=a+1; i<k && b-(i-a)>=0; i++){
        if(board[i][b-(i-a)]=='.')
            break;

        if(board[i][b-(i-a)]==player){
            if(i==a+1)
                break;
            else{
                control=true;

                for(int j=a+1; j<i;j++)
                    board[j][ b-(j-a)]=player;
                break;
            }
        } 
    }

    // Check upper-left diagonal direction.
    for(i=a-1; i>=0 && b-(a-i)>=0; i--){
        if(board[i][b-(a-i)]=='.')
            break;

        if(board[i][b-(a-i)]==player){
            if(i==a-1)
                break;
            else{
                control=true;

                for(int j=a-1; j>i;j--)
                    board[j][b-(a-j)]=player;
                break;
            }
        } 
    }

    if(control)
    board[a][b] = player;

    return control;

}

// Find and play the computer's best move
void computerMove(char board[size][size]){
    
    int maxsize=0;
    int bestrow=-1;
    int bestcol=-1;
    int count=0;
    bool control;
    char c;
    for(int i=0;i<k;i++){
            for(int j=0; j<k; j++){
                control= isvalid(i,j,board,'x',count);
                if(control){
                   if(count>maxsize){
                    maxsize=count;
                    bestrow=i;
                    bestcol=j;
                   }

                }
            }
    }
    if(bestrow != -1 && bestcol != -1){
        makeMove(bestrow,bestcol,board,'x');
        
        c='a'+bestcol;
        cout<<"computer move "<<bestrow+1<<c<<endl;
    }
    
}

// Manage player turns and continue the game until it ends.
void playGame(char board[size][size],char player){
    int row,a,b;
    char col;
    string move;
    bool control;
    
    player='o';

    do{

        if(!validMove(board,'o') && !validMove(board,'x')){
            break;
        }

        if(player=='o' && !validMove(board,'o')){
            cout<<"No valid move! Turn skipped."<<endl;
            player='x';
        }

        if(player=='o'){

            cout<<"Enter your move: ";
            cin>>move;

            // Check the input length to reject invalid move formats.
            if(move.length()!=2 && move.length()!=3)
            {
                cout<<"Invalid input! Try again."<<endl;
                continue;
            }

            if(move.length()==2)
            {
                if(move[0]<'1' || move[0]>'9')
                {
                    cout<<"Invalid input! Try again."<<endl;
                    continue;
                }

                    row=move[0]-'0';
                    col=move[1];
            }
            else
            {
                if(move[0]!='1' || (move[1]!='0' && move[1]!='1' && move[1]!='2'))
                {
                    cout<<"Invalid input! Try again."<<endl;
                    continue;
                }

                row=10+(move[1]-'0');
                col=move[2];
            }

            if(row<1 || row>k || col<'a' || col>='a'+k)
            {
                cout << "Invalid input! Try again." << endl;
                continue;
            }

            a = row - 1;
            b = col - 'a';
                
            int count=0;

            control=isvalid(a,b,board,player,count);
            if(!control){
                cout<<"invalid move! Try again."<<endl;
                continue;
            }else{
                makeMove(a,b,board,'o');
                printBoard(board);
                player='x';
            }
        }

        if(player=='x' && !validMove(board,'x')){
            cout << "Computer has no valid move! Turn skipped." << endl;
            player='o';
        }

        if(player=='x'){
            computerMove(board);
            printBoard(board);
            player='o';
            }

    }while(validMove(board,'o') || validMove(board,'x'));

    result(board);
}

// Check if the player has any valid moves.
bool validMove(char board[size][size],char player){
    int count=0;
    bool control=false;
    int i,j;

    for(i=0;i<k;i++){
        for(j=0;j<k;j++){
            control=isvalid(i,j,board,player,count);
            if(control){
                return true;
            }

        }
    }
    return false;
}

// Count the pieces and display the winner.
void result(char board[size][size]){
    int i,j;
    int ocount=0;
    int xcount=0;
    for(i=0;i<k;i++){
        for(j=0;j<k;j++){
            if(board[i][j]=='o')
                ocount++;
            
            if(board[i][j]=='x')
                xcount++;
        }
    }
    if(ocount<xcount){
        cout<<"computer wins"<<endl;
    }else if(ocount>xcount){
        cout<<"you WİN"<<endl;
    }else{
        cout << "It's a draw!" << endl;
    }

    cout << "Your score: " << ocount << endl;
    cout << "Computer score: " << xcount << endl;
 }
