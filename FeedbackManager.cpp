#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

class FeedbackManager {
private:
    struct FeedbackNode {
        string feedback;
        FeedbackNode* next;
        FeedbackNode(const string& fb) : feedback(fb), next(nullptr) {}
    };
    FeedbackNode* front;
    FeedbackNode* rear;
public:
    FeedbackManager() : front(nullptr), rear(nullptr) {}
    ~FeedbackManager() {
        while (front) {
            FeedbackNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
    void enqueueFeedback(const string& feedback, bool writeToFile = true) {
        FeedbackNode* newNode = new FeedbackNode(feedback);
        if (!front) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        if (writeToFile) {
            cout << "Thank you for your valuable feedback\n";
            ofstream feed("Feedbacks.txt", ios::app);
            feed << feedback << endl;
            feed.close();
            cout << "We appreciate it." << endl;
        }
    }
    void dequeueFeedback() {
        if (front) {
            string fb = front->feedback;
            FeedbackNode* temp = front;
            front = front->next;
            if (!front)
                rear = nullptr;
            delete temp;
            cout << "feedback dequeued.." << endl;
            cout << "dequeued: " << fb << endl;
        }
        else {
            cout << "no feedback to dequeue..." << endl;
        }
        // Update file: remove the first line.
        ifstream fin("Feedbacks.txt");
        ofstream fout("feed_temp.txt");
        string line;
        bool firstLine = true;
        while (getline(fin, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            fout << line << endl;
        }
        fin.close();
        fout.close();
        remove("Feedbacks.txt");
        rename("feed_temp.txt", "Feedbacks.txt");
    }
    void displayFeedbacks() {
        int count = 0;
        FeedbackNode* temp = front;
        while (temp) {
            count++;
            cout << count << ". " << temp->feedback << endl;
            temp = temp->next;
        }
    }
    void loadFeedbacksFromFile() {
        ifstream feed("Feedbacks.txt");
        string line;
        while (getline(feed, line)) {
            enqueueFeedback(line, false);
        }
        feed.close();
    }
};
