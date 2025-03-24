#include "tweetFunctions.h"

int main(int argc, char* argv[]){

FILE *tweetFile, *sentimentFile;
char tweets[MAX_TWEETS][MAX_TWEET_SIZE];
int num_tweets = 0;

  // check number of command-line arguments
  if ( argc < 4 ) {
	/* argc should be 4 for correct execution */ 
	/* We print argv[0] assuming it is the program name */
        printf( "usage: %s Candidate_name tweet_file sentiment_file ", argv[0] );
        return 1;
  } // end if
  else{
  	// open the file of tweets
	if ((tweetFile = fopen (argv[2], "r"))  ==  NULL ) {
        printf("Can't open tweet file %s.\n", argv[2]);
        return 2;
	}


  	// open the file of sentiment analysis results
i	if ((sentimentFile = fopen (argv[3], "r"))  ==  NULL ) {
        printf("Can't open sentiment file %s.\n", argv[3]);
        return 3;
	}
  } // end else

  printf("                 Analysis of tweets from %s \n", argv[1]);
  printf("============================================================== \n");


  // Read the tweets from the file into the tweets array, using fgets
  // Assume that <= MAX_TWEETS tweets are in the file
  // Use num_tweets to keep track of how many you read

  while((num_tweets < MAX_TWEETS) &&
	 fgets(tweets[num_tweets], MAX_TWEET_SIZE, tweetFile)){
	num_tweets++;
	}


  fclose(tweetFile);

  // Print out the number of tweets read.

  printf("Located %d tweets in %s.\n\n", num_tweets, tweetFile);

  // Print out the index (array subscript) of the longest tweet, the
  // number of characters in that tweet and the text of the tweet.
  /*
   * You need to create the max_chars and max_index functions 
   * in the tweetFunctions.c file. Place their function prototypes
   * in the tweetFunctions.h file.
   */

  printf("The longest tweet is #%d. It contains %d characters: \n %s\n\n", 
          max_index(tweets,num_tweets), max_chars(tweets,num_tweets), 
	  tweets[max_index(tweets,num_tweets)]);

  // Print out the index (array subscript) of the shortest tweet, the
  // number of characters in that tweet and the text of the <F12>tweet.
  /*
   * You need to create the min_chars and min_index functions 
   * in the tweetFunctions.c file. Place their function prototypes
   * in the tweetFunctions.h file.
   */

  printf("The shortest tweet is #%d. It contains %d characters: \n %s\n\n", 
          min_index(tweets,num_tweets), min_chars(tweets,num_tweets), 
	  tweets[min_index(tweets,num_tweets)]);
  
   // Print out a separator line

  printf("            ------------------------------------------------------       \n");
  printf("\n");

  // Print out a table of the alphabetic character frequenices in the tweets
  // Ignore case (i.e., just report frequencies of a ... z 
  /*
   * You need to create a character_frequency function in the 
   * tweetFunctions.c file. Place the function prototypes
   * in the tweetFunctions.h file. Note that characterFrequency
   * does not return a value.  Instead, it prints out the results
   * for this analysis.
   */

  printf("Character frequencies in %s are: \n\n", argv[2]);
  character_frequency(tweets, num_tweets);
  printf("\n");

  // Print out a separator line

  printf("            ------------------------------------------------------       \n");
  printf("\n");

 // Report the number and percentages of negative(0), neutral(2) and 
 // positive(4) tweets based on the integers prepended to each tweet, as 
 // seen in the "sentiments" file.

 /* 
  * You need to add a printf statement here to print out the line
  * that begins with "An analysis of the tweets in... "
  * You need to create a sentiment function in the 
  * tweetFunctions.c file. Place the function prototypes
  * in the tweetFunctions.h file. Note that sentiment 
  * does not return a value.  Instead, it prints out the results
  * for this analysis.
  */

  sentiment(sentimentFile, num_tweets);
  printf("\n");
  
  // Print out a separator line
  printf("            ------------------------------------------------------       \n");
  printf("\n");

  // List all the tweets 
 /* 
  * You need to add code here to print out all of the tweets
  * that you read in.
  * You need to create a show_all function in the 
  * tweetFunctions.c file. Place the function prototype
  * in the tweetFunctions.h file. 
  */
  printf("The full listing of the tweets in %s: \n", argv[2]);
  show_all(tweets,num_tweets);

return 0;

}
