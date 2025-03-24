
tweetStats:	tweetStats.c tweetFunctions.c tweetFunctions.h
	gcc -Wall -o tweetStats tweetStats.c tweetFunctions.c

donald:	tweetStats
	./tweetStats Donald_Trump donald.txt donald_sentiments.txt > donald_report.txt

hillary: tweetStats
	./tweetStats Hillary_Clinton hillary.txt hillary_sentiments.txt > hillary_report.txt

tweetClean:	tweetClean.c
	gcc -o tweetClean tweetClean.c

clean:	
	rm tweetStats
	rm donald_report.txt
	rm hillary_report.txt
