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
  unordered_map<int,queue<int>> next_use;
  int i = 0;
  for (auto p : pages) {
    ++hist[p];
    next_use[p].push(i);
    ++i;
  }
  unordered_set<int> s;
  for (auto p : pages) {
    next_use[p].pop();
    --hist[p];
    if (s.find(p) == s.end()) {
      ++misses;
      if (s.size() == frames) {
        auto to_remove = min_element(s.begin(), s.end(), [&](int a, int b){
          return hist[a] < hist[b] || 
            hist[a] == hist[b] && next_use[a] > next_use[b];
        });
        s.erase(to_remove);
      }
      s.insert(p);
    }
  }
  return misses;
}

int LRU(const vector<int>& pages, int frames) {
  int misses = 0;
  unordered_map<int,int> hist;
  unordered_map<int,int> last_time_used;
  for (auto p : pages) {
    ++hist[p];
  }
  unordered_set<int> s;
  int i = 0;
  for (auto p : pages) {
    last_time_used[p] = i;
    --hist[p];
    if (s.find(p) == s.end()) {
      ++misses;
      if (s.size() == frames) {
        auto to_remove = min_element(s.begin(), s.end(), [&](int a, int b){
          return last_time_used[a] < last_time_used[b];
        });
        s.erase(to_remove);
      }
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
    if (s.find(p) == s.end()) {
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