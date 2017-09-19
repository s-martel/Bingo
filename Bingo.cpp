/*
 * Steve Martel (A02588438)
 * 12/10/2014
 * CS 2308.001
 * Bonus Assignment
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

void seedRand();
int bingoNumber(int column, int size);
bool searchList(const int list[], int numElems, int value);

int main()
{
   int card_quantity, size, number, called_number, called_total = 0;
   int *called_numsArr = 0;
   int h, i, j;
   char menuChoice = 'y';
   bool game_over = false;
   int marks;

   struct BingoCard
   {
      int **arrPtr;
      int *used_nums;
      int used_counter;
   };

   BingoCard *cardArr = 0;

   while (menuChoice != 'n')
   {
      seedRand();

      while ((std::cout << "Please Select Number of Cards or Players (1 to 100): ")
             && (!(std::cin >> card_quantity) || card_quantity < 1 || card_quantity > 100))
      {
         std::cout << "Invalid entry" << endl;
	 std::cin.clear();
	 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }

      while ((std::cout << "Please Select Maximum Row & Columns Size (1 to 100): ")
	     && (!(std::cin >> size) || size < 1 || size > 100))
      {
         std::cout << "Invalid entry" << endl;
	 std::cin.clear();
	 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }

      // allocate dynamic memory
      cardArr = new BingoCard [card_quantity];
      called_numsArr = new int [size * 3 * size];
      for (h = 0; h < card_quantity; ++h)
      {
         cardArr[h].arrPtr = new int* [size];
	 for (i = 0; i < size; ++i)
	    cardArr[h].arrPtr[i] = new int [size];
	 cardArr[h].used_nums = new int [size * size];
      }

      // fill array with numbers
      for (h = 0; h < card_quantity; ++h)
      {
         for (i = 0; i < size; ++i)
            for (j = 0; j < size; ++j)
            {
               cardArr[h].used_counter = 0;
	       do
                  number = bingoNumber((i + 1), size);
               while (searchList(cardArr[h].used_nums, cardArr[h].used_counter, number));
                  cardArr[h].arrPtr[j][i] = number;

               cardArr[h].used_nums[cardArr[h].used_counter] = number;
               ++ cardArr[h].used_counter;
            }
      }

      while (game_over == false)
      {
      // print numbers in array
         for (h = 0; h < card_quantity; ++h)
         {
            for (i = 0; i < size; ++i)
            {
               for (j = 0; j < size; ++j)
                  cout << setw(3) << cardArr[h].arrPtr[i][j];
               cout << endl;
            }
            cout << endl;
         }

         // generate called number
         called_number = (rand() % (size * 3 * size)) + 1;
         while (searchList(called_numsArr, called_total, called_number))
            called_number = (rand() % (size * 3 * size)) + 1;
         called_numsArr[called_total] = called_number;
         ++called_total;
         cout << endl << "*** Called number is: " << called_number << " ***" << endl;

         cout << "Press Enter or Return when ready...";
         cin.ignore(999, '\n');
         cin.get();

         // mark matching numbers
         for (h = 0; h < card_quantity; ++h)
            for (i = 0; i < size; ++i)
               for (j = 0; j < size; ++j)
                  if (cardArr[h].arrPtr[j][i] == called_number)
                     cardArr[h].arrPtr[j][i] = 0;

         // check for win
         for (h = 0; h < card_quantity; ++h)
         {
            for(i = 0; i < size; ++i)
            {
               marks = 0;
               for(j = 0; j < size; ++j)
               {
                  if(cardArr[h].arrPtr[j][i] == 0)
                     ++ marks;
                  if (marks == size)
                  game_over = true;
               }
            }

            for(j = 0; j < size; ++j)
            {
               marks = 0;
               for(i = 0; i < size; ++i)
               {
                  if(cardArr[h].arrPtr[j][i] == 0)
                     ++ marks;
                  if (marks == size)
                     game_over = true;
               }
            }
         }
      }

      cout << "BBBBB   IIIIII  N    N   GGGGG   OOOO " << endl
           << "B   BB    II    NN   N  G       O    O" << endl
           << "BBBB      II    N N  N  G   GG  O    O" << endl
           << "B   BB    II    N  N N  G    G  O    O" << endl
           << "BBBBB   IIIIII  N   NN   GGGG    OOOO " << endl << endl;

      cout << "Play Again? ('y' for yes, 'n' for no):";
      cin >> menuChoice;

      while (menuChoice != 'y' && menuChoice != 'n')
      {
         cout << "Play Again? ('y' for yes, 'n' for no):";
         cin >> menuChoice;
      }

      called_total = 0;
      game_over = 0;

      // deallocate dynamic memory
      for (h = 0; h < card_quantity; ++h)
      {
         for (i = 0; i < size; ++i)
            delete [] cardArr[h].arrPtr[i];
         delete [] cardArr[h].arrPtr;
         delete [] cardArr[h].used_nums;
         cardArr[h].arrPtr = 0;
         cardArr[h].used_nums = 0;
      }
         delete [] called_numsArr;
         delete [] cardArr;
   }

   cout << endl << "Thank you for playing!  :)" << endl << endl
        << "Press Enter or Return when ready...";
   cin.ignore(999, '\n');
   cin.get();
   return EXIT_SUCCESS;
}

// Functions //

void seedRand()
{
   srand( (unsigned) time(NULL) );
}

int bingoNumber(int column, int size)
{
   int upperBound = column * 3 * size;
   int lowerBound = (column - 1) * 3 * size + 1;
   return ( rand() % (upperBound - lowerBound + 1) ) + lowerBound;
}

bool searchList(const int list[], int numElems, int value)
{
   int index = 0;

   while (index < numElems)
   {
      if (list[index] == value)
         return true;
      ++index;
   }
   return false;
}

