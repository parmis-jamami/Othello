#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>
#include<windows.h>
using namespace std;
struct Player
{
  string name;
  char color;
  int score;
};
void clear_screen() 
{
    cout << "\033[2J\033[1;1H";
}

void show_menu()
{
    cout <<"\033[35m"<<"*** othello menu ***\n"<<"\033[0m";
    cout <<"\033[35m"<< "1. New Game\n"<<"\033[0m"; 
    cout <<"\033[35m"<< "2. Load Game\n"<<"\033[0m"; 
    cout <<"\033[35m"<< "3. Help\n"<<"\033[0m"; 
    cout <<"\033[35m"<< "4. Game History\n"<<"\033[0m"; 
    cout <<"\033[35m"<< "5. Exit\n"<<"\033[0m";
    cout <<"*** Enter your choice: ***";
}
void move_cursor(int &row, int &col, char key)
{
  if (key == 'w' && row > 0) row--;      // حرکت به بالا
  else if (key == 's' && row < 7) row++; // حرکت به پایین
  else if (key == 'a' && col > 0) col--; // حرکت به چپ
  else if (key == 'd' && col < 7) col++; // حرکت به راست
}
bool is_on_board(int r,int c)
{
  if(r>=0 && r<8 && c>=0 && c<8) return true;
  else return false;
}
char switch_player(char p)
{
  return (p == 'B') ? 'W' : 'B';
}
bool is_valid_move(char board[8][8],int r,int c,char player)
{
  if(is_on_board(r,c)==false || board[r][c] != '-') return false; //اگر خانه خارج صفحه یا پر باشد حرکت نامعتبر است
  char opp=switch_player(player);
  for(int dr=-1;dr<=1;dr++)  //بررسی همه جهت ها
  {
    for(int dc=-1;dc<=1;dc++)
    {
      if(dr==0 && dc==0) continue;
      int i=r+dr;
      int j=c+dc;
      if(is_on_board(i,j) && board[i][j]==opp)
      {
        while(is_on_board(i,j))
        {
          i+=dr;
          j+=dc;
          if(is_on_board(i,j)==false) break;
          if(board[i][j]=='-') break;
          if(board[i][j]==player) return true;
        }
      }
    }
  }
  return false;    //حرکت معتبری وجود ندارد
}
void print_board (char board[8][8],int cursor_row,int cursor_column,char player)
{ 
  cout<<"\nBoard:\n";
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<8;j++)
    { 
      char cell=board[i][j];
      if(cell=='-' && is_valid_move(board,i,j,player))
      {
        cell='*';
      }
      // انتخاب رنگ
      string color;
      if(cell == '-') color="\033[32m";  // رنگ سبز برای خانه خالی
      else if(cell == 'B') color ="\033[34m"; //آبی برای مهره سیاه
      else if(cell == 'W') color ="\033[37m"; // سفید برای مهره سفید
      else if(cell == '*') color="\033[33m";  //زرد برای خانه های معتبر
      if(i==cursor_row &&  j==cursor_column)
      {
        cout<<"["<<color<<cell<<"\033[0m"<<"] ";
      }
      else
      {
        cout<<" "<<color<<cell<<"\033[0m"<<"  ";
      }
    }
    cout<<endl;
  }
}
void apply_move(char board[8][8],int r,int c,char player)
{
  char opp=switch_player(player);
  board[r][c]=player;
  for(int dr=-1;dr<=1;dr++)  //بررسی همه جهت ها
  {
    for(int dc=-1;dc<=1;dc++)
    {
      if(dr==0 && dc==0) continue;
      int i=r+dr;
      int j=c+dc;
      if(is_on_board(i,j) && board[i][j]==opp)
      {
        while(is_on_board(i,j) && board[i][j]==opp)  //جلو بره تا برسه به مهره خودش یا خونه خالی یا بیرون صفحه
        {
          i+=dr;
          j+=dc;
        }
        if(is_on_board(i,j) && board[i][j]==player)
        {
          int x=r+dr;
          int y=c+dc;
          while(x!=i || y!=j)
          {
            board[x][y]=player;  //برگرداندن مهره ها
            x+=dr;
            y+=dc;
          }
        }
      }
    }
  }
}
bool has_valid_move(char board[8][8],char player)
{
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<8;j++)
    {
      if(is_valid_move(board,i,j,player)) return true;
    }
  }
  return false;
}
void computer_move(char board[8][8], char player, int difficulty) 
{
    int move_row[64];
    int move_column[64]; 
    int move_count = 0;

    // پیدا کردن همه حرکت‌های معتبر
    for(int i=0; i<8; i++) 
    {
        for(int j=0; j<8; j++) 
        {
            if(is_valid_move(board, i, j, player)) 
            {
                move_row[move_count] = i;
                move_column[move_count] = j;
                move_count++;
            }
        }
    }

    if(move_count == 0) 
    {
        cout << "Computer has no valid moves, Pass" << endl;
        return;
    }

    int r, c;

    if(difficulty == 1) 
    { // آسان: بدترین حرکت
        int worst_score = 64, worst_index = 0;
        for(int i=0; i<move_count; i++) 
        {
            char temp_board[8][8];
            for(int x=0; x<8; x++)
            {
                for(int y=0; y<8; y++)
                {
                    temp_board[x][y] = board[x][y];
                }
            }
            apply_move(temp_board, move_row[i], move_column[i], player);

            int score = 0;
            for(int x=0; x<8; x++)
            {
                for(int y=0; y<8; y++)
                {
                    if(temp_board[x][y] == player) score++;
                }
            }  

            if(score < worst_score) 
            {
                worst_score = score;
                worst_index = i;
            }
        }
        r = move_row[worst_index];
        c = move_column[worst_index];
    }
    else if(difficulty == 2) 
    { // متوسط: حرکت تصادفی
        int random_choice = rand() % move_count;
        r = move_row[random_choice];
        c = move_column[random_choice];
    }
    else 
    { // سخت: بهترین حرکت
        int best_score = 0; 
        int best_index = 0;
        for(int i=0; i<move_count; i++) 
        {
            char temp_board[8][8];
            for(int x=0; x<8; x++)
            {
                for(int y=0; y<8; y++)
                {
                    temp_board[x][y] = board[x][y];
                }
            }
            apply_move(temp_board, move_row[i], move_column[i], player);

            int score = 0;
            for(int x=0; x<8; x++)
            {
                for(int y=0; y<8; y++)
                {
                    if(temp_board[x][y] == player) score++;
                }
            }
              
            if(score > best_score) 
            {
                best_score = score;
                best_index = i;
            }
        }
        r = move_row[best_index];
        c = move_column[best_index];
    }
    // اعمال حرکت انتخاب‌شده
    apply_move(board, r, c, player);
}
void start_new_game()
{ 
  time_t start_t = time(0);       // زمان شروع بازی
  tm start_now = *localtime(&start_t);
  cout << "the date of the start of the game: "<< start_now.tm_year + 1900 << "/"<< start_now.tm_mon + 1 << "/"<< start_now.tm_mday << endl;
  cout << "time of start: "<< start_now.tm_hour << ":"<< start_now.tm_min << ":"<< start_now.tm_sec << endl;
  srand(static_cast<unsigned int>(time(nullptr)));
  char board[8][8];
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<8;j++)
    {
      board[i][j] ='-';
    }
  }
  board[3][3] = 'W'; 
  board[4][4] = 'W'; 
  board[3][4] = 'B'; 
  board[4][3] = 'B';
  int cursor_row=0;
  int cursor_column=0;
  char player='B';
  bool running=true;
  cout<<"\033[31m"<<"choose game mode..."<<"\033[0m"<<endl;
  cout<<"\033[31m"<<"1. two players"<<"\033[0m"<<endl;
  cout<<"\033[31m"<<"2. one player(play with computer)"<<"\033[0m"<<endl;
  int mode;
  cin>>mode;
  Player black;
  Player white;
  int difficulty;
  if(mode==1)
  {
    cout<<"\033[33m"<<"Enter black player name"<<"\033[0m"<<endl;
    cin>>black.name;
    cout<<"\033[33m"<<"Enter white player name"<<"\033[0m"<<endl;
    cin>>white.name;
  }
  else
  {
    cout<<"\033[33m"<<"Enter your name (you're black player)"<<"\033[0m"<<endl;
    cin>>black.name;
    white.name="computer";
    cout<<"\033[32m"<<"Choose the robot difficulty 1.easy 2.medium 3.hard"<<"\033[0m"<<endl; 
    cin>>difficulty;
  }
  while (running)
  {
    clear_screen();   //پاک کردن خروجی قبلی
    cout<<"currnt player: "<<(player=='B'?black.name:white.name)<<(player=='B'?" (Black)":" (White)")<<endl;
    print_board(board,cursor_row,cursor_column,player);
    if(mode==2 && player=='W')   //نوبت ربات
    {
      if(has_valid_move(board,player))
        { 
          cout << "\033[36m" << "Computer is thinking..." << "\033[0m" << endl;
          Sleep(1000);
          computer_move(board,player,difficulty);
          player=switch_player(player);
        }
      if(has_valid_move(board,player)==false)
        {
          cout<<"Player "<<(player=='B'?black.name:white.name)<<" has no valid move"<<endl;
          player=switch_player(player);
          if(has_valid_move(board,player)==false)
          {
            cout<<"game over"<<endl;
            running=false;
          }
        }

    }
    else
    {

      cout<<"use w(up)  s(down)  a(left)  d(right)  to move and Enter to select"<<endl;
      char key=getch();
      if(key==13)
      {
        if(is_valid_move(board,cursor_row,cursor_column,player))
        {
          apply_move(board,cursor_row,cursor_column,player);
          player=switch_player(player);
          if(has_valid_move(board,player)==false)
          {
            cout<<"Player "<<(player=='B'?black.name:white.name)<<"has no valid move"<<endl;
            player=switch_player(player);
            if(has_valid_move(board,player)==false)
            {
              cout<<"game over"<<endl;
              running=false;
            }
          }
        }
        else
        {
          cout<<"invalid move, try again...";
          getch();   //بعد از دیده شدن پیام توسط کاربر یک کلید زده شه و بعد ادامه برنامه اجرا شه
        }
      }
      else
      {
        move_cursor(cursor_row, cursor_column, key);
      }
    }
  }
  int countB=0;
  int countW=0;
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<8;j++)
    {
      if(board[i][j]=='B') countB++;
      else if(board[i][j]=='W') countW++;
    }
  }
  time_t end_t = time(0);         // زمان پایان بازی
  tm end_now = *localtime(&end_t);
  cout << "the date of the end of the game: "<< end_now.tm_year + 1900 << "/"<< end_now.tm_mon + 1 << "/"<< end_now.tm_mday << endl;
  cout << "the time of the end of the game: "<< end_now.tm_hour << ":"<< end_now.tm_min << ":"<< end_now.tm_sec << endl;

  double duration = difftime(end_t, start_t); // مدت زمان بازی به ثانیه
  int total_seconds=int(duration);
  int hours = total_seconds / 3600;
  int minutes = (total_seconds % 3600) / 60;
  int seconds = total_seconds % 60;
  cout << "the total time of the game: "<< hours << "hours "<< minutes << "minutes "<< seconds << "seconds " << endl;
  cout<<"The final score of "<<black.name<<"is "<<countB<<endl<<"The final score of "<<white.name<<"is "<<countW<<endl;
  if(countB>countW) cout<<"\033[32m"<<black.name<<" Wins!"<<"\033[0m"<<endl;
  else if(countW>countB) cout<<"\033[32m"<<white.name<<" Wins!"<<"\033[0m"<<endl;
  else cout<<"It's a draw"<<endl;
  // پابان بازی و ذخیره نتیجه بازی در فایل
  ofstream file("history_file.txt",ios::app);
  file<<"start: "<<start_now.tm_year + 1900 << "/"<< start_now.tm_mon + 1 << "/"<< start_now.tm_mday << endl<<start_now.tm_hour << ":"<< start_now.tm_min << ":"<< start_now.tm_sec << endl;
  file<<"end: "<<end_now.tm_year + 1900 << "/"<< end_now.tm_mon + 1 << "/"<< end_now.tm_mday << endl<<end_now.tm_hour << ":"<< end_now.tm_min << ":"<< end_now.tm_sec << endl;
  file<<black.name<<" (Black)"<<countB<<" | "<<white.name<<" (White)"<<countW<<endl;
  if(countB>countW) file<<"Winner: "<<black.name<<endl;
  else if(countW>countB) file<<"Winner: "<<white.name<<endl;
  else file<<"draw "<<endl;
  file.close();
}
int main()
{
    int choice;
    bool running=true;
    while (running)
    {
        show_menu();
        cin>>choice;
        switch (choice)
        {
            case 1:
              cout<<"Starting a new game...\n"<<endl;
              start_new_game();
              break;
            case 2:
              cout<<"Loading last saved game...\n";
              break;
            case 3:
              cout <<"Help: Rules of othello..."<<endl;
              cout <<"\033[34m"<< "1. The game is played on an 8x8 board."<<"\033[0m"<<endl;
              cout <<"\033[34m"<< "2. Black always moves first."<<"\033[0m"<<endl;
              cout <<"\033[34m"<< "3. A move is valid if it captures opponent's pieces between your new piece and another of your pieces."<<"\033[0m"<<endl;
              cout <<"\033[34m"<< "4. Captured pieces are flipped to your color."<<"\033[0m"<<endl;
              cout <<"\033[34m"<< "5. If a player has no valid moves, they must pass."<<"\033[0m"<<endl;
              cout <<"\033[34m"<< "6. The game ends when neither player can move."<<"\033[0m"<<endl;
              cout <<"\033[34m"<< "7. The winner is the player with the most pieces."<<"\033[0m"<<endl;
              cout <<"\033[34m"<<"8. You can use w s a d to move on the board. "<<"\033[0m"<<endl;
              break;
            case 4:
              cout<<"Showing the game history...\n";
              {
                ifstream input_file("history_file.txt");
                if(input_file.is_open())
                {
                  int max_lines=100;
                  string lines[max_lines];
                  int count=0;
                  while(count<max_lines && getline(input_file,lines[count]))
                  {
                    count++;
                  }
                  input_file.close();
                  // چاپ از اخر به اول
                  for(int i=count-1;i>=0;i--)
                  {
                    cout<<lines[i]<<endl;;
                  }
                }
                else
                {
                  cout<<"Error"<<endl;
                }
              }
              break;
            case 5:
              cout<<"Exiting the game Goodbye";
              running=false;
              break;
            default:
              cout<<"invalid choice,please try again";

              
        }
    }
    return 0;
}