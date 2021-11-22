/* author: Mohammad Sheraj */
/* email: mdsheraj123@gmail.com */
// freopen("input.txt", "r", stdin);
// freopen("output.txt", "w", stdout);
// Use long long instead of long for answer too
// cout << "Line 1..." << flush;
// cout<<__cplusplus<<endl; // for c++ version
//////////////
// printf("%.2lf",double_value);
// cout<<"Case #"<<test_case<<": "<<answer<<endl;
///////////////////////////////////////////////////////////////
// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <stack>
#include <queue> //(priority_queue default is max heap) priority_queue <int, vector<int>, greater<int>> pq;
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <set>       //sorts by value
#include <map>       //sorts by key
#include <bitset>    //(c & a).any() //access like array
#include <algorithm> //max/min //lower_bound/upper_bound //binary_search //reverse //next_permutation
#include <climits>   //INT_MIN //LLONG_MAX
#include <math.h>    //ceil/floor
// #include <time.h> //clock_t clock() //CLOCKS_PER_SEC
// #include <chrono>  //system time
// #include <cstring>  //provides functions for dealing with C-style strings — null-terminated arrays of characters.
// #include <numeric> //gcd //there will be sqiggly red line but no compilation error
#include <fstream> //fstream fio("sample.txt",ios::trunc|ios::out|ios::in);fio<<line;getline(fio,line);fio.close();
// #include <thread>  //thread my_thread(runner, 10, " ready");my_thread.join();
// #include <mutex>   //mutex n;n.lock();n.unlock();
// #include <semaphore.h> //sem_t m;sem_init(&m, 0, 1);sem_destroy(&m);sem_wait(&m);sem_post(&m);
// #include <iomanip>  //cout<<setprecision(5); contain functions to manipulate i/o format.
// #include <memory>   //unique_ptr/shared_ptr/weak_ptr
// #include <unistd.h> //sleep(10) in seconds
// #include <cxxabi.h> //Demangling type name so that it is human-readable

#define endl "\n"
using namespace std;

// struct cmp {
//     bool operator() (int a, int b) const {
//         return a<b;
//     }
// };

void setup() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef SHERAJ
    freopen("input.txt", "r", stdin);
#endif
}
/////////////////////////////////////////////////////////////////////////

struct node {
    bool ending;
    struct node* children[26];
};


bool compare(tuple<string,int,int,int,int>& a, tuple<string,int,int,int,int>& b) {
    return get<0>(a).size()>get<0>(b).size();
}

std::istream& safeGetline(std::istream& is, std::string& t) { // To be line ending independent
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case std::streambuf::traits_type::eof():
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}

int main()
{
    setup();

    struct node* head = new struct node;
    head->ending = false;
    for(int i=0;i<26;i++) {
        head->children[i] = nullptr;
    }

    // Read from the text file
    ifstream MyReadFile("words_alpha.txt");
    // Create a text string, which is used to output the text file
    string myText;
    // Use a while loop together with the getline() function to read the file line by line
    while (!safeGetline(MyReadFile, myText).eof()) {
        if(myText.size()>=4) {
            struct node* current = head;
            for(int i=0;i<myText.size();i++) {
                if(current->children[myText[i]-'a']==nullptr) {
                    current->children[myText[i]-'a'] = new struct node;
                    current->children[myText[i]-'a']->ending = false;
                    for(int j=0;j<26;j++) {
                        current->children[myText[i]-'a']->children[j] = nullptr;
                    }
                }
                if(i==myText.size()-1) {
                    current->children[myText[i]-'a']->ending = true;
                }
                current = current->children[myText[i]-'a'];
            }
        }
    }

    char grid[10][10] = {
    {'l','w','y','r','g','v','w','s','r','z'},
    {'b','n','i','e','p','a','c','l','c','e'},
    {'s','l','a','g','u','r','f','i','h','e'},
    {'t','n','e','d','u','r','p','p','s','w'},
    {'i','d','r','n','g','i','e','f','i','p'},
    {'f','o','p','k','r','e','j','s','r','m'},
    {'l','g','e','m','i','c','e','o','e','i'},
    {'e','c','i','t','a','n','u','l','h','l'},
    {'g','r','b','l','e','a','k','p','c','i'},
    {'n','i','r','g','s','o','a','h','c','x'}
    };

    vector<tuple<string,int,int,int,int>> answer; //start x,y end x,y
    answer.clear();

    for(int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
            for(int direction=0;direction<8;direction++) {
                int x = i;
                int y = j;
                string temp;
                temp.clear();
                struct node* currentNode = head;
                while(x>=0&&y>=0&&x<10&&y<10) {
                    if(currentNode->children[grid[x][y]-'a']!=nullptr) {
                        temp+=grid[x][y];
                        if(temp.size()>=4 && currentNode->children[grid[x][y]-'a']->ending) {
                            answer.push_back(make_tuple(temp,i,j,x,y));
                        }
                        currentNode = currentNode->children[grid[x][y]-'a'];
                        switch(direction) {
                            case 0: // search forward
                                y++;
                                break;
                            case 1: // search backward
                                y--;
                                break;
                            case 2: // search up
                                x--;
                                break;
                            case 3: // search down
                                x++;
                                break;
                            case 4: // search forward up
                                x--;
                                y++;
                                break;
                            case 5: // search forward down
                                x++;
                                y++;
                                break;
                            case 6: // search backward up
                                x--;
                                y--;
                                break;
                            case 7: // search backward down
                                x++;
                                y--;
                                break;
                            default:
                                cout<<"ERROR"<<endl;
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }

    sort(answer.begin(),answer.end(),compare);
    cout<<answer.size()<<endl;

    for(auto tempo: answer) {
        cout<<get<0>(tempo)<<" ";
        cout<<"start x="<<get<1>(tempo)<<" y="<<get<2>(tempo)<<" end x="<<get<3>(tempo)<<" y="<<get<4>(tempo)<<endl;
    }

    cout<<endl<<"DONE!"<<endl;

    // Close the file
    MyReadFile.close();
	return 0;
}