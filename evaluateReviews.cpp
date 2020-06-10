// Add any #includes for C++ libraries here.
// We have already included iostream as an example.
#include <iostream>

// The #include adds all the function declarations (a.k.a. prototypes) from the
// reviews.h file, which means the compiler knows about them when it is compiling
// the main function below (e.g. it can verify the parameter types and return types
// of the function declarations match the way those functions are used in main() ).
// However, the #include does not add the actual code for the functions, which is
// in reviews.cpp. This means you need to compile with a g++ command including both
// .cpp source files. For this project, we will being using some features from C++11,
// which requires an additional flag. Compile with this command:
//     g++ --std=c++11 evaluateReviews.cpp reviews.cpp -o evaluateReviews
#include "reviews.h"
#include <fstream>
#include <string>
using namespace std;

const double SCORE_LIMIT_TRUTHFUL = 3;
const double SCORE_LIMIT_DECEPTIVE = -3;


int main(){
    //opening the keywords and weights
    ifstream keyIn("keywordWeights.txt");
    //creating the report text file
    ofstream reportOut("report.txt");
    vector<string> keywords;
    vector<double> weights;
    if(!keyIn.is_open()){
        cout<< "Error: keywordWeights.txt could not be opened.";
        return 1;
        //an error if terminal can't find the file
    }
    readKeywordWeights(keyIn, keywords, weights);
    //stores the keywords and weights into vectors
    reportOut <<"review score category"<< endl;
    int review = 0;
    ifstream reviewIn("review00.txt");
    //starts reading from the first review
    int truthful = 0;
    int deceptive = 0;
    int uncategorized = 0;
    double highest=0;
    double lowest=0;
    int reviewh = 0;
    int reviewl = 0;
    while(reviewIn.is_open()){
        //as long as there is a review this loop runs
        vector<string> reviewWords;
        readReview(reviewIn,reviewWords);
        //read in review and saves into the vector reviewWords
        reportOut << review << " ";
        double score = reviewScore(reviewWords,keywords,weights);
        //finds and stores the score of the review
        reportOut << score << " ";
        //determining if the score is truthful or deceptive or uncategorized
        if (score > 3){
            reportOut << "truthful"<< endl;
            ++truthful; 
        }
        else if(score < -3){
            reportOut << "deceptive"<< endl;
            ++deceptive;
        }
        else{
            reportOut << "uncategorized"<<endl;
            ++uncategorized;
        }
        //compares to highest and lowest and keeps the review number stored
        if(score > highest){
            highest = score;
            reviewh = review;
        }
        if (score < lowest){
            lowest = score;
            reviewl = review;
        }
        ++review; 
        //goes to next review
        reviewIn.close();
        //close the input and clear it to read the next one
        reviewIn.clear();
        if(review < 10){
            //adds a 0 in front of reviews less than 10 and opens the next review
            string newReview = "review0" + to_string(review) + ".txt";
            reviewIn.open(newReview);
        }
        else{
            string newReview = "review" + to_string(review) + ".txt";
            reviewIn.open(newReview);
        }
    }
    reportOut << endl<< "Number of reviews: " << review<< endl;
    reportOut<< "Number of truthful reviews: "<< truthful<<endl;
    reportOut<< "Number of deceptive reviews: "<< deceptive<<endl;
    reportOut<< "Number of uncategorized reviews: "<< uncategorized<< endl;
    reportOut << endl<< "Review with highest score : "<< reviewh<< endl;
    reportOut << "Review with lowest score : "<< reviewl<< endl;
    reportOut.close();
}




