#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

int optimal(const vector<int>& pages, int frames) {
  int misses = 0;
  unordered_map<int,int> hist;
  unordered_map<int,int> last_time_used;
  for (auto p : pages) {
    ++hist[p];
  }
  auto myGreater = [&](const int a, const int b){
    return hist[a] > hist[b] ||
      hist[a] == hist[b] && last_time_used[a] > last_time_used[b];
  };
  priority_queue<int, vector<int>, decltype(myGreater)> pq(myGreater);
  unordered_set<int> s;
  int i = 0;
  for (auto p : pages) {
    last_time_used[p] = i;
    if (s.find(p) != s.end()) {
      --hist[p];
    } else {
      ++misses;
      if (pq.size() == frames) {
        s.erase(pq.top());
        pq.pop();
      }
      pq.push(p);
      s.insert(p);
    }
    ++i;
  }
  return misses;
}

int LRU(const vector<int>& pages, int frames) {
  int misses = 0;
  unordered_map<int,int> last_time_used;
  auto myLess = [&](const int a, const int b) {
    return last_time_used[a] > last_time_used[b];
  };
  priority_queue<int, vector<int>, decltype(myLess)> pq(myLess);
  unordered_set<int> s;
  int i = 0;
  for (auto p : pages) {
    last_time_used[p] = i;
    if (s.find(p) != s.end()) {
      ;
    } else {
      ++misses;
      if (pq.size() == frames) {
        s.erase(pq.top());
        pq.pop();
      }
      pq.push(p);
      s.insert(p);
    }
    ++i;
  }
  return misses;
}

int FIFO(const vector<int>& pages, int frames) {
  int misses = 0;
  queue<int> q;
  unordered_set<int> s;
  int i = 0;
  for (auto p : pages) {
    if (s.find(p) != s.end()) {
      ;
    } else {
      ++misses;
      if (q.size() == frames) {
        s.erase(q.front());
        q.pop();
      }
      q.push(p);
      s.insert(p);
    }
    ++i;
  }
  return misses;
}

int main() {
  int p;
  vector<int> pages;
  string input;
  getline(cin, input);
  istringstream ss(input);
  while (ss >> p) {
    pages.push_back(p);
  }
  int frames = 4;
  cout << "Optimal misses: " << optimal(pages, frames) << '\n';
  cout << "LRU misses: " << LRU(pages, frames) << '\n';
  cout << "FIFO misses: " << FIFO(pages, frames) << '\n';
}